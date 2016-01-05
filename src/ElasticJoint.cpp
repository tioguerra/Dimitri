#include "ElasticJoint.h"
#include "dynamixel.h"
#include <cstdio>

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

void ElasticJoint::update()
{
  // Read the current angle of the motor
  int value1 = (dxl_read_word(this->jointId, 36)-this->jointCenterValue);
  float motorAngle = VALUE2ANGLE(value1);
  int result1 = dxl_get_result();
  // Read the current angle of the spring
  int value2 = (dxl_read_word(this->springId, 36)-this->springCenterValue);
  float springAngle = SPRINGVALUE2ANGLE(value2);
  int result2 = dxl_get_result();
  if (result1 == 1 && result2 == 1)
  {
    // Stores the resulting torque
    this->torque = SPRINGANGLE2TORQUE(springAngle);
    // Stores resulting angle 
    this->angle = motorAngle + springAngle;
    // Write the goal angle to the motor
    dxl_write_word(this->jointId, 30,
          this->jointCenterValue + ANGLE2VALUE(this->goalAngle - springAngle));
  }
}

