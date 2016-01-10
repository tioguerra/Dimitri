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

  // Saves the new control mode
  this->controlMode = mode;
}

float Joint::getAngle()
{
  // Return the joint angle last read from the motor
  return angle;
}

void Joint::setMaxAngle(float angle)
{
  // Sets the maximum angle limit for this joint
  this->maxAngle = angle;
}

float Joint::getMaxAngle()
{
  // Returns the maximum angle limit for this joint
  return this->maxAngle;
}

void Joint::setMinAngle(float angle)
{
  // Sets the minimum angle limit for this joint
  this->minAngle = angle;
}

float Joint::getMinAngle()
{
  // Returns the minimum angle limit for this joint
  return this->minAngle;
}

void Joint::setAngleLimits(float minAngle, float maxAngle)
{
  // Adjust minimum and maximum joint limits
  setMinAngle(minAngle);
  setMaxAngle(maxAngle);
}

void Joint::setMaxTorque(int torque)
{
  // Set the maximum torque to the motors
  dxl_write_word(this->jointId, 34, torque);
}

int Joint::getMaxTorque()
{
  // Returns the current maximum torque set
  // in the motors
  return dxl_read_word(this->jointId, 34);
}


void Joint::setGoalAngle(float angle)
{
  // Sets new goal angle only if within the joint limits
  if (angle >= this->minAngle && angle <= this->maxAngle)
      this->goalAngle = angle;
}

float Joint::getGoalAngle()
{
  // Returns the current goal angle
  return goalAngle;
}

void Joint::readAngle()
{
  // In the case of the simple joint the
  // angle is the motor angle.
  this->readMotorAngle();
  this->angle = this->motorAngle;
}

void Joint::readMotorAngle()
{
  // Read the motor angle from the motor
  int value = dxl_read_word(this->jointId, 36);
  if (dxl_get_result() == 1)
  {
    this->motorAngle = VALUE2ANGLE(value - this->jointCenterValue);
  }
}

void Joint::writeGoalAngle(float angle)
{
  // Write the goal angle to the motor
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

