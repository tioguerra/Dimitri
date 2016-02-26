#include "Object.h"

Object::Object()
{
	//set values for default constructor
	setType("Object");
	setColor(Scalar(0,0,0));
        setArea(0);
}

Object::Object(string name){

	setType(name);
	
	if(name=="pink"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(155,128,114));
		setHSVmax(Scalar(174,204,256));

		//BGR value for Green:
		setColor(Scalar(255,0,0));

	}
	if(name=="blue"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(92,0,0));
		setHSVmax(Scalar(124,256,256));

		//BGR value for Green:
		setColor(Scalar(255,0,0));

	}
	if(name=="green"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(61,88,89));
		setHSVmax(Scalar(99,173,231));

		//BGR value for Yellow:
		setColor(Scalar(0,255,0));

	}
	if(name=="yellow"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(20,124,123));
		setHSVmax(Scalar(30,256,256));

		//BGR value for Red:
		setColor(Scalar(0,255,255));

	}
	if(name=="red"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(4,212,92));
		setHSVmax(Scalar(11,255,255));

		//BGR value for Red:
		setColor(Scalar(0,0,255));

	}
	if(name=="orange"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(0,159,0));
		setHSVmax(Scalar(45,255,255));

		//BGR value for Red:
		setColor(Scalar(0,0,255));

	}
}

Object::~Object(void)
{
}

int Object::getXPos(){

	return Object::xPos;

}

void Object::setXPos(int x){

	Object::xPos = x;

}

int Object::getYPos(){

	return Object::yPos;

}

void Object::setYPos(int y){

	Object::yPos = y;

}

Scalar Object::getHSVmin(){

	return Object::HSVmin;

}
Scalar Object::getHSVmax(){

	return Object::HSVmax;
}

void Object::setHSVmin(Scalar min){

	Object::HSVmin = min;
}


void Object::setHSVmax(Scalar max){

	Object::HSVmax = max;
}
