#include "FireFlyCam.h"
#include <sstream>

using namespace cv;

#define CAMERA_WIDTH 1280
#define CAMERA_HEIGHT 960
#define MAX_NUM_OBJECTS 50
#define MIN_OBJECT_AREA (20*20)
#define CAMERA_HORIZONTAL_FIELD (DEG2RAD(45.0))
#define CAMERA_VERTICAL_FIELD (DEG2RAD(30.0))

FireFlyCam::FireFlyCam(int device_num)
{
  this->busMgr.GetCameraFromIndex(0, &guid);
  this->cam.Connect(&guid);
  this->cam.StartCapture();
  this->focusObjIndex = 0;
  this->focusStepDiv = 5.0;
  this->head = NULL;
  this->firstCapture = true;
  waitKey(1000);
}

FireFlyCam::~FireFlyCam()
{
  this->cam.StopCapture();
  this->cam.Disconnect();
}

void FireFlyCam::morphOps(Mat &thresh)
{

	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle
	Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));

	erode(thresh,thresh,erodeElement);
	erode(thresh,thresh,erodeElement);

	dilate(thresh,thresh,dilateElement);
	dilate(thresh,thresh,dilateElement);
}

std::string FireFlyCam::intToString(int number)
{

	std::stringstream ss;
	ss << number;
	return ss.str();
}

void FireFlyCam::drawObject(vector<Object> theObjects,Mat &frame, Mat &temp,
                vector< vector<Point> > contours, vector<Vec4i> hierarchy)
{

	for(unsigned int i = 0 ; i < theObjects.size() ; i++)
        {

          cv::drawContours(frame, contours, i,
                      theObjects.at(i).getColor(), 3, 8, hierarchy);
          cv::circle(frame,
              cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()),
              5,theObjects.at(i).getColor());
          cv::putText(frame,intToString(theObjects.at(i).getXPos()) + " , "
              + intToString(theObjects.at(i).getYPos()),
              cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()+20),
              1,1,theObjects.at(i).getColor());
          cv::putText(frame,theObjects.at(i).getType(),
              cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()-20),
              1,2,theObjects.at(i).getColor());
	}
}

void FireFlyCam::trackFilteredObject(Object *theObject, Mat threshold, 
                                 Mat HSV, Mat &cameraFeed)
{

	vector <Object> objects;
	Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
	//use moments method to find our filtered object
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if(numObjects<MAX_NUM_OBJECTS){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

		//if the area is less than 20 px by 20px then it is probably just noise
		//if the area is the same as the 3/2 of the image size, probably just a bad filter
		//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.

				if (area > MIN_OBJECT_AREA)
                                {

					Object object;

					object.setXPos(moment.m10/area);
					object.setYPos(moment.m01/area);
                                        object.setArea(area);
					object.setType(theObject->getType());
					object.setColor(theObject->getColor());

					objects.push_back(object);

                                        if (!objectFound || object.getArea() > theObject->getArea())
                                        {
                                          theObject->setXPos(object.getXPos());
                                          theObject->setYPos(object.getYPos());
                                          theObject->setArea(object.getArea());
                                        }

					objectFound = true;

				}
			}

			//let user know you found an object
			if(objectFound == true)
                        {
				//draw object location on screen
				drawObject(objects,cameraFeed,temp,contours,hierarchy);
                        }

		} else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
	}
}

void FireFlyCam::addObjectToTrack(Object *obj)
{
  this->objectsToTrack.push_back(obj);
}

void FireFlyCam::processFrame()
{
  //this->capture.read(this->cameraImage);
  this->cam.RetrieveBuffer( &rawImage );
  this->rawImage.Convert(PIXEL_FORMAT_BGR, &convertedImage);
  if (this->firstCapture)
  {
    printf("Capturing %d x %d pixels\n",convertedImage.GetCols(),convertedImage.GetRows());
    this->cameraImage = Mat(convertedImage.GetRows(),convertedImage.GetCols(),CV_8UC3,Scalar(0,0,0));
    this->firstCapture = false;
  }
  //this->cameraImage.put(0, 0, convertedImage.GetData());
  memcpy(cameraImage.data,convertedImage.GetData(),convertedImage.GetCols()*convertedImage.GetRows()*3);
  for (unsigned int i = 0 ; i < this->objectsToTrack.size() ; i++)
  {
    cvtColor(this->cameraImage, this->HSVImage, COLOR_BGR2HSV);
    inRange(this->HSVImage, this->objectsToTrack[i]->getHSVmin(),
            this->objectsToTrack[i]->getHSVmax(), this->thresholdImage);
    this->morphOps(this->thresholdImage);
    this->trackFilteredObject(this->objectsToTrack[i], this->thresholdImage,
                        this->HSVImage, this->cameraImage);
    if (this->head != NULL && i == this->focusObjIndex)
    {
      Joint *pan = head->getJoint(HEADPAN);
      Joint *tilt = head->getJoint(HEADTILT);
      float x = this->objectsToTrack[i]->getXPos();
      float y = this->objectsToTrack[i]->getYPos();
      float half_width = float(CAMERA_WIDTH) / 2.0;
      float half_height = float(CAMERA_HEIGHT) / 2.0;
      float pan_angle = ((x - half_width) / half_width)*(CAMERA_HORIZONTAL_FIELD/2.0);
      float tilt_angle = ((y - half_height) / half_height)*(CAMERA_VERTICAL_FIELD/2.0);
      this->focusPan = pan->getAngle() - pan_angle;
      this->focusTilt = tilt->getAngle() - tilt_angle;
    }
  }
  imshow("Dimitri's Vision", cameraImage);
}

void FireFlyCam::moveHeadToFocus()
{
      Joint *pan = head->getJoint(HEADPAN);
      Joint *tilt = head->getJoint(HEADTILT);
      float deltaPan = this->focusPan - pan->getAngle();
      float deltaTilt = this->focusTilt - tilt->getAngle();
      deltaPan /= this->focusStepDiv*3.0/5.0;
      deltaTilt /= this->focusStepDiv;
      pan->setGoalAngle(pan->getAngle() + deltaPan);
      tilt->setGoalAngle(tilt->getAngle() + deltaTilt);
}

float FireFlyCam::getNormalizedFocusPan()
{
  return this->head->getJoint(HEADPAN)->normalizeAngle(this->focusPan);
}

float FireFlyCam::getNormalizedFocusTilt()
{
  return this->head->getJoint(HEADTILT)->normalizeAngle(this->focusTilt);
}

