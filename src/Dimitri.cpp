#include "Dimitri.h"
#include "dynamixel.h"

Dimitri::Dimitri(int deviceIndex, int baudnum)
{
  // Initialize the communications channel
  dxl_initialize(deviceIndex, baudnum);

  // Builds right arm
  this->rightArm = new JointChain();
  this->rightArm->addJoint(new ElasticJoint(1, 101, 1860, 2646));
  this->rightArm->addJoint(new ElasticJoint(2, 102, 5061-4096, 5770));
  this->rightArm->addJoint(new ElasticJoint(3, 103, 1340, 4584));
  this->rightArm->addJoint(new ElasticJoint(4, 104, 2216, 4454));

  // Builds left arm
  this->leftArm = new JointChain();
  this->leftArm->addJoint(new Joint(8, 4096-1670));
  this->leftArm->addJoint(new ElasticJoint(7, 107, 5518-4096, 63098));
  this->leftArm->addJoint(new ElasticJoint(6, 106, 7428-4096, 58345));
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

void Dimitri::setPose(float lroll, float lpitch, float lyaw, float lelbow,
         float rroll, float rpitch, float ryaw, float relbow,
         float wroll, float wpitch, float wyaw,
         float hpan, float htilt)
{
  this->leftArm->getJoint(ARMROLL)->setGoalAngle(lroll);
  this->leftArm->getJoint(ARMPITCH)->setGoalAngle(lpitch);
  this->leftArm->getJoint(ARMYAW)->setGoalAngle(lyaw);
  this->leftArm->getJoint(ELBOW)->setGoalAngle(lelbow);
  this->rightArm->getJoint(ARMROLL)->setGoalAngle(rroll);
  this->rightArm->getJoint(ARMPITCH)->setGoalAngle(rpitch);
  this->rightArm->getJoint(ARMYAW)->setGoalAngle(ryaw);
  this->rightArm->getJoint(ELBOW)->setGoalAngle(relbow);
  this->waist->getJoint(WAISTROLL)->setGoalAngle(wroll);
  this->waist->getJoint(WAISTPITCH)->setGoalAngle(wpitch);
  this->waist->getJoint(WAISTYAW)->setGoalAngle(wyaw);
  this->head->getJoint(PAN)->setGoalAngle(hpan);
  this->head->getJoint(TILT)->setGoalAngle(htilt);
}

void Dimitri::setPose(float pose[13])
{
  for (int i = 0 ; i < 21 ; i++)
  {
    switch (i)
    {
      case LROLL:
        this->leftArm->getJoint(ARMROLL)->setGoalAngle(pose[i]);
        break;
      case LPITCH:
        this->leftArm->getJoint(ARMPITCH)->setGoalAngle(pose[i]);
        break;
      case LYAW:
        this->leftArm->getJoint(ARMYAW)->setGoalAngle(pose[i]);
        break;
      case LELBOW:
        this->leftArm->getJoint(ELBOW)->setGoalAngle(pose[i]);
        break;
      case RROLL:
        this->rightArm->getJoint(ARMROLL)->setGoalAngle(pose[i]);
        break;
      case RPITCH:
        this->rightArm->getJoint(ARMPITCH)->setGoalAngle(pose[i]);
        break;
      case RYAW:
        this->rightArm->getJoint(ARMYAW)->setGoalAngle(pose[i]);
        break;
      case RELBOW:
        this->rightArm->getJoint(ELBOW)->setGoalAngle(pose[i]);
        break;
      case WROLL:
        this->waist->getJoint(WAISTROLL)->setGoalAngle(pose[i]);
        break;
      case WPITCH:
        this->waist->getJoint(WAISTPITCH)->setGoalAngle(pose[i]);
        break;
      case WYAW:
        this->waist->getJoint(WAISTYAW)->setGoalAngle(pose[i]);
        break;
      case HPAN:
        this->head->getJoint(PAN)->setGoalAngle(pose[i]);
        break;
      case HTILT:
        this->head->getJoint(TILT)->setGoalAngle(pose[i]);
        break;
    }
  }
}

void Dimitri::getPose(float (&pose)[13])
{
  for (int i = 0 ; i < 13 ; i++)
  {
    switch (i)
    {
      case LROLL:
        pose[i] = this->leftArm->getJoint(ARMROLL)->getAngle();
        break;
      case LPITCH:
        pose[i] = this->leftArm->getJoint(ARMPITCH)->getAngle();
        break;
      case LYAW:
        pose[i] = this->leftArm->getJoint(ARMYAW)->getAngle();
        break;
      case LELBOW:
        pose[i] = this->leftArm->getJoint(ELBOW)->getAngle();
        break;
      case RROLL:
        pose[i] = this->rightArm->getJoint(ARMROLL)->getAngle();
        break;
      case RPITCH:
        pose[i] = this->rightArm->getJoint(ARMPITCH)->getAngle();
        break;
      case RYAW:
        pose[i] = this->rightArm->getJoint(ARMYAW)->getAngle();
        break;
      case RELBOW:
        pose[i] = this->rightArm->getJoint(ELBOW)->getAngle();
        break;
      case WROLL:
        pose[i] = this->waist->getJoint(WAISTROLL)->getAngle();
        break;
      case WPITCH:
        pose[i] = this->waist->getJoint(WAISTPITCH)->getAngle();
        break;
      case WYAW:
        pose[i] = this->waist->getJoint(WAISTYAW)->getAngle();
        break;
      case HPAN:
        pose[i] = this->head->getJoint(PAN)->getAngle();
        break;
      case HTILT:
        pose[i] = this->head->getJoint(TILT)->getAngle();
        break;
    }
  }
}

void Dimitri::getPose(float &lroll, float &lpitch, float &lyaw, float &lelbow,
                 float &rroll, float &rpitch, float &ryaw, float &relbow,
                 float &wroll, float &wpitch, float &wyaw,
                 float &hpan, float &htilt)
{
  lroll = this->leftArm->getJoint(ARMROLL)->getGoalAngle();
  lpitch = this->leftArm->getJoint(ARMPITCH)->getGoalAngle();
  lyaw = this->leftArm->getJoint(ARMYAW)->getGoalAngle();
  lelbow = this->leftArm->getJoint(ELBOW)->getGoalAngle();
  rroll = this->rightArm->getJoint(ARMROLL)->getGoalAngle();
  rpitch = this->rightArm->getJoint(ARMPITCH)->getGoalAngle();
  ryaw = this->rightArm->getJoint(ARMYAW)->getGoalAngle();
  relbow = this->rightArm->getJoint(ELBOW)->getGoalAngle();
  wroll = this->waist->getJoint(WAISTROLL)->getGoalAngle();
  wpitch = this->waist->getJoint(WAISTPITCH)->getGoalAngle();
  wyaw = this->waist->getJoint(WAISTYAW)->getGoalAngle();
  hpan = this->head->getJoint(PAN)->getGoalAngle();
  htilt = this->head->getJoint(TILT)->getGoalAngle();
}

