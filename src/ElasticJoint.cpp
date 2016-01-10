#include "ElasticJoint.h"
#include "dynamixel.h"
#include <cstdio>

#define SPRINGVALUEMEMORY 0.7

ElasticJoint::ElasticJoint(int jointId, int springId, int jointCenterValue, int springCenterValue)
                                          : Joint(jointId, jointCenterValue)
{
  this->isElastic = true;
  this->springId = springId;
  this->pidController = new PidController(KP, KI, KD);
  this->springCenterValue = springCenterValue;
}

ElasticJoint::~ElasticJoint()
{
  delete this->pidController;
}

void ElasticJoint::readAngle()
{
  // Read current motor angle
  int value = dxl_read_word(this->jointId, 36);
  if (dxl_get_result() == 1)
  {
    this->motorAngle = VALUE2ANGLE(value - this->jointCenterValue);
  }

  // Read the current angle of the spring
  this->readSpringAngle();

  // Stores resulting angle 
  this->angle = this->motorAngle + this->springAngle;

}


void ElasticJoint::readSpringAngle()
{
  bool quit = false;
  int count = 1;
  int value;

  do
  {
    value = dxl_read_word(this->springId, 36);
    if (dxl_get_result() == 1)
    {
      this->springAngle = (SPRINGVALUEMEMORY)*this->springAngle
                        + (1-SPRINGVALUEMEMORY)*SPRINGVALUE2ANGLE(value - this->springCenterValue);
      // Stores the resulting torque
      this->torque = SPRINGANGLE2TORQUE(this->springAngle);
      quit = true;
    }
    if (count > 3) quit = true;
    count++;
  } while (!quit);

}

void ElasticJoint::update()
{

  // Read the current angle of the motor
  this->readAngle();

  // Behave accordingly to respective control mode
  switch (this->controlMode)
  {
    case ANGLE:
      {
        // Write the goal angle to the motor
        this->writeGoalAngle(this->goalAngle - this->springAngle);
      }
      break;
    case TEACH:
      {

        // Will only change the goal angle if enough torque is
        // applied to the motors
        if (fabs(this->torque) > TORQUE_TEACH_THRESHOLD)
        {
          this->goalAngle = this->angle;
        }

        // Write the goal angle to the motor
        this->writeGoalAngle(this->goalAngle);
      }
      break;
  }
}

