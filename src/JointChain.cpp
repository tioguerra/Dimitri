#include "JointChain.h"
#include "dynamixel.h"

JointChain::JointChain()
{
  totalJoints = 0;
}

JointChain::~JointChain()
{
}

void JointChain::setControlMode(int mode)
{
  for (int i = 0 ; i < this->totalJoints ; i++)
  {
    this->joints[i]->setControlMode(mode);
  }
}

void JointChain::setMaxTorque(int torque)
{
  for (int i = 0 ; i < this->totalJoints ; i++)
  {
    this->joints[i]->setMaxTorque(torque);
  }
}

void JointChain::addJoint(Joint *joint)
{
  if (totalJoints < MAX_JOINTS_IN_JOINTCHAIN)
  {
    joints[totalJoints] = joint;
    totalJoints++;
  }
}

void JointChain::update()
{
  for (int i = 0 ; i < totalJoints ; i++)
  {
    joints[i]->update();
  }
}

