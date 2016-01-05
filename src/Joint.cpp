#include "Joint.h"
#include "dynamixel.h"
#include <cstdio>

Joint::Joint(int jointId, int jointCenterValue)
{
  this->angle = 0.0;
  this->controlMode = OFF;
  this->jointId = jointId;
  this->isElastic = false;
  this->goalAngle = 0.0;
  this->maxAngle = 360.0;
  this->minAngle = 0.0;
  this->maxTorque = 1024;
  this->jointCenterValue = jointCenterValue;
}

Joint::~Joint()
{
}

void Joint::setControlMode(int mode)
{
  switch (mode)
  {
    case ANGLE:
    case TORQUE:
      // Enable torque to the motors
      dxl_write_byte(this->jointId, 0x18, 1);
      break;
    case OFF:
      // Disable torque to the motors
      dxl_write_byte(this->jointId, 0x18, 0);
      break;
  }
  this->controlMode = mode;
}

float Joint::getAngle()
{
  return angle;
}

void Joint::setMaxAngle(float angle)
{
  int value = ANGLE2VALUE(angle);
  dxl_write_word(this->jointId, 6, value);
}

float Joint::getMaxAngle()
{
  int value = dxl_read_word(this->jointId, 6);
  return VALUE2ANGLE(value);
}

void Joint::setMinAngle(float angle)
{
  int value = ANGLE2VALUE(angle);
  dxl_write_word(this->jointId, 8, value);
}

float Joint::getMinAngle()
{
  int value = dxl_read_word(this->jointId, 8);
  return VALUE2ANGLE(value);
}

void Joint::setMaxTorque(int torque)
{
  dxl_write_word(this->jointId, 34, torque);
}

int Joint::getMaxTorque()
{
  return dxl_read_word(this->jointId, 34);
}


void Joint::setGoalAngle(float angle)
{
  goalAngle = angle;
}

float Joint::getGoalAngle()
{
  return goalAngle;
}


void Joint::update()
{
  // Read the current angle of the motor
  int value = dxl_read_word(this->jointId, 36);
  if (dxl_get_result() == 1)
  {
    this->angle = VALUE2ANGLE(value - this->jointCenterValue);
  }

  switch (this->controlMode)
  {
    case ANGLE:
      // Write the goal angle to the motor
      dxl_write_word(this->jointId, 30, this->jointCenterValue + ANGLE2VALUE(this->goalAngle));
      break;
    default:
      break;
  }
}

