#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"
#include "JointChain.h"
#include <vector>
#include <string>

class Camera
{
  private:
    cv::Mat cameraImage;
    cv::Mat thresholdImage;
    cv::Mat HSVImage;
    VideoCapture capture;
    std::vector<Object *> objectsToTrack;
    std::string intToString(int number);
    unsigned int focusObjIndex;
    void morphOps(Mat &thresh);
    void drawObject(vector<Object> theObjects,Mat &frame, Mat &temp,
                vector< vector<Point> > contours, vector<Vec4i> hierarchy);
    void trackFilteredObject(Object *theObject,Mat threshold,Mat HSV, Mat &cameraFeed);
    JointChain *head;
    float focusPan;
    float focusTilt;
  public:
    Camera();
    ~Camera();
    void addObjectToTrack(Object *obj);
    void processFrame();
    void setFocusObjectIndex(int focusObjIndex) { this->focusObjIndex = focusObjIndex; }
    int getFocusObjectIndex() { return this->focusObjIndex; }
    void setHead(JointChain *head) { this->head = head; }
    float getFocusPan() { return focusPan; }
    float getFocusTilt() { return focusTilt; }
};

#endif

