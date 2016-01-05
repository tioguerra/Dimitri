#include "Dimitri.h"
#include "dynamixel.h"

Dimitri::Dimitri(int deviceIndex, int baudnum)
{
  // Initialize the communications channel
  dxl_initialize(deviceIndex, baudnum);

  // Builds right arm
  this->rightArm = new JointChain();
  this->rightArm->addJoint(new ElasticJoint(1, 101, 1860, 2646));
  this->rightArm->addJoint(new ElasticJoint(2, 102, 860, 2748));
  this->rightArm->addJoint(new ElasticJoint(3, 103, 1340, 4584));
  this->rightArm->addJoint(new ElasticJoint(4, 104, 2216, 4454));

  // Builds left arm
  this->leftArm = new JointChain();
  this->leftArm->addJoint(new Joint(8, 4096-1670));
  this->leftArm->addJoint(new ElasticJoint(7, 107, 4096-2667, 63172));
  this->leftArm->addJoint(new ElasticJoint(6, 106, 7428-4096, 58371));
  this->leftArm->addJoint(new ElasticJoint(5, 105, 5697-4096, 63327));

  // Builds head
  this->head = new JointChain();
  this->head->addJoint(new Joint(9, 2048));
  this->head->addJoint(new Joint(10, 2056));

  // Builds waist
  this->waist = new JointChain();
  this->waist->addJoint(new Joint(11, 2048));
  this->waist->addJoint(new Joint(12, 2048));
  this->waist->addJoint(new Joint(13, 2038));
}

Dimitri::~Dimitri()
{
  // Delete left arm
  dxl_terminate();
  for (int i = 0 ; i < leftArm->getTotalJoints() ; i++)
  {
    delete this->leftArm->getJoint(i);
  }
  delete this->leftArm;

  // Delete right arm
  for (int i = 0 ; i < rightArm->getTotalJoints() ; i++)
  {
    delete this->rightArm->getJoint(i);
  }
  delete this->rightArm;

  // Delete head
  for (int i = 0 ; i < head->getTotalJoints() ; i++)
  {
    delete this->head->getJoint(i);
  }
  delete this->head;

  // Delete waist
  for (int i = 0 ; i < waist->getTotalJoints() ; i++)
  {
    delete this->waist->getJoint(i);
  }
  delete this->waist;
}

void Dimitri::update()
{
  this->leftArm->update();
  this->rightArm->update();
  this->head->update();
  this->waist->update();
}

void Dimitri::setControlMode(int mode)
{
  this->leftArm->setControlMode(mode);
  this->rightArm->setControlMode(mode);
  this->head->setControlMode(mode);
  this->waist->setControlMode(mode);
}

void Dimitri::setMaxTorque(int torque)
{
  this->leftArm->setMaxTorque(torque);
  this->rightArm->setMaxTorque(torque);
  this->head->setMaxTorque(torque);
  this->waist->setMaxTorque(torque);
}

