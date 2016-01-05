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
      {

        // Read current position of the servo
        this->readMotorAngle();

        // Sets the current position as the goal
        this->goalAngle = this->motorAngle;

        // Writes that angle to the servo
        this->writeGoalAngle(this->goalAngle);

        // Enable torque to the motors
        dxl_write_byte(this->jointId, 0x18, 1);

      }
      break;

    case OFF:
      {

        // Disable torque to the motors
        dxl_write_byte(this->jointId, 0x18, 0);

      }
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

void Joint::readAngle()
{
  this->readMotorAngle();
  this->angle = this->motorAngle;
}

void Joint::readMotorAngle()
{
  int value = dxl_read_word(this->jointId, 36);
  if (dxl_get_result() == 1)
  {
    this->motorAngle = VALUE2ANGLE(value - this->jointCenterValue);
  }
}

void Joint::writeGoalAngle(float angle)
{
  dxl_write_word(this->jointId, 30, this->jointCenterValue + ANGLE2VALUE(angle));
}

void Joint::update()
{
  // Read the current angle of the motor
  this->readAngle();

  // Behave accordingly to respective control mode
  switch (this->controlMode)
  {
    case ANGLE:
      {

        // Write the goal angle to the motor
        this->writeGoalAngle(this->goalAngle);
        break;

      }
    case TEACH:
      {
        
        // Will only change the goal angle if the difference
        // between the current angle and the current goal
        // angle is large enough
        float difference = this->angle - this->goalAngle;
        if (fabs(difference) > ANGLE_TEACH_THRESHOLD)
        {
          this->goalAngle = this->angle;
          printf("Angle displacement detected!\n");
        }

        // Write the goal angle to the motor
        this->writeGoalAngle(this->goalAngle);

      }
    default:
      {
        break;
      }
  }
}

