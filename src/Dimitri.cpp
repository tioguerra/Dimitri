#include "Dimitri.h"
#include "dynamixel.h"
#include "Util.h"

Dimitri::Dimitri(int deviceIndex, int baudnum)
{
  // Initialize the communications channel
  dxl_initialize(deviceIndex, baudnum);

  // Builds right arm
  this->rightArm = new JointChain();
  this->rightArm->addJoint(new ElasticJoint(1, 101, 1860, 2646));
  this->rightArm->addJoint(new ElasticJoint(2, 102, 4861-4096, 5770));
  this->rightArm->addJoint(new ElasticJoint(3, 103, 5428-4096, 4480));
  this->rightArm->addJoint(new ElasticJoint(4, 104, 6600-3996, 5316));

  // Builds left arm
  this->leftArm = new JointChain();
  this->leftArm->addJoint(new ElasticJoint(8, 108, 7020-4096, 4238));
  this->leftArm->addJoint(new ElasticJoint(7, 107, 5518-4096, 63098));
  this->leftArm->addJoint(new ElasticJoint(6, 106, 6220-4096, 61300));
  this->leftArm->addJoint(new ElasticJoint(5, 105, 5597-4096, 63327));

  // Builds head
  this->head = new JointChain();
  this->head->addJoint(new Joint(9, 2048));
  this->head->addJoint(new Joint(10, 2056));

  // Builds waist
  this->waist = new JointChain();
  this->waist->addJoint(new Joint(11, 2048));
  this->waist->addJoint(new Joint(12, 2048));
  this->waist->addJoint(new Joint(13, 2038));

  // Set the joint limits for the arms
  this->rightArm->getJoint(ARMROLL)->setAngleLimits(DEG2RAD(-90.0),DEG2RAD(80.0));
  this->leftArm->getJoint(ARMROLL)->setAngleLimits(DEG2RAD(-90.0),DEG2RAD(80.0));
  this->rightArm->getJoint(ARMPITCH)->setAngleLimits(DEG2RAD(-150.0),DEG2RAD(210.0));
  this->leftArm->getJoint(ARMPITCH)->setAngleLimits(DEG2RAD(-150.0),DEG2RAD(210.0));
  this->rightArm->getJoint(ARMYAW)->setAngleLimits(DEG2RAD(-30.0),DEG2RAD(190.0));
  this->leftArm->getJoint(ARMYAW)->setAngleLimits(DEG2RAD(-30.0),DEG2RAD(190.0));
  this->rightArm->getJoint(ELBOW)->setAngleLimits(DEG2RAD(-100.0),DEG2RAD(0.0));
  this->leftArm->getJoint(ELBOW)->setAngleLimits(DEG2RAD(-100.0),DEG2RAD(0.0));

  // Set the joint limits for the head
  this->head->getJoint(PAN)->setAngleLimits(DEG2RAD(-135.0),DEG2RAD(135.0));
  this->head->getJoint(TILT)->setAngleLimits(DEG2RAD(-70.0),DEG2RAD(70.0));

  // Set the joint limits for the waist
  this->waist->getJoint(WAISTYAW)->setAngleLimits(DEG2RAD(-25.0),DEG2RAD(25.0));
  this->waist->getJoint(WAISTROLL)->setAngleLimits(DEG2RAD(-20.0),DEG2RAD(20.0));
  this->waist->getJoint(WAISTPITCH)->setAngleLimits(DEG2RAD(-30.0),DEG2RAD(25.0));

  // Records the initial time
  this->initial_time = clock();
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

void Dimitri::setNormalizedPose(float lroll, float lpitch, float lyaw, float lelbow,
         float rroll, float rpitch, float ryaw, float relbow,
         float wroll, float wpitch, float wyaw,
         float hpan, float htilt)
{
  this->leftArm->getJoint(ARMROLL)->setNormalizedGoalAngle(lroll);
  this->leftArm->getJoint(ARMPITCH)->setNormalizedGoalAngle(lpitch);
  this->leftArm->getJoint(ARMYAW)->setNormalizedGoalAngle(lyaw);
  this->leftArm->getJoint(ELBOW)->setNormalizedGoalAngle(lelbow);
  this->rightArm->getJoint(ARMROLL)->setNormalizedGoalAngle(rroll);
  this->rightArm->getJoint(ARMPITCH)->setNormalizedGoalAngle(rpitch);
  this->rightArm->getJoint(ARMYAW)->setNormalizedGoalAngle(ryaw);
  this->rightArm->getJoint(ELBOW)->setNormalizedGoalAngle(relbow);
  this->waist->getJoint(WAISTROLL)->setNormalizedGoalAngle(wroll);
  this->waist->getJoint(WAISTPITCH)->setNormalizedGoalAngle(wpitch);
  this->waist->getJoint(WAISTYAW)->setNormalizedGoalAngle(wyaw);
  this->head->getJoint(PAN)->setNormalizedGoalAngle(hpan);
  this->head->getJoint(TILT)->setNormalizedGoalAngle(htilt);
}

void Dimitri::setPose(float pose[])
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

void Dimitri::setNormalizedPose(float pose[])
{
  for (int i = 0 ; i < 21 ; i++)
  {
    switch (i)
    {
      case LROLL:
        this->leftArm->getJoint(ARMROLL)->setNormalizedGoalAngle(pose[i]);
        break;
      case LPITCH:
        this->leftArm->getJoint(ARMPITCH)->setNormalizedGoalAngle(pose[i]);
        break;
      case LYAW:
        this->leftArm->getJoint(ARMYAW)->setNormalizedGoalAngle(pose[i]);
        break;
      case LELBOW:
        this->leftArm->getJoint(ELBOW)->setNormalizedGoalAngle(pose[i]);
        break;
      case RROLL:
        this->rightArm->getJoint(ARMROLL)->setNormalizedGoalAngle(pose[i]);
        break;
      case RPITCH:
        this->rightArm->getJoint(ARMPITCH)->setNormalizedGoalAngle(pose[i]);
        break;
      case RYAW:
        this->rightArm->getJoint(ARMYAW)->setNormalizedGoalAngle(pose[i]);
        break;
      case RELBOW:
        this->rightArm->getJoint(ELBOW)->setNormalizedGoalAngle(pose[i]);
        break;
      case WROLL:
        this->waist->getJoint(WAISTROLL)->setNormalizedGoalAngle(pose[i]);
        break;
      case WPITCH:
        this->waist->getJoint(WAISTPITCH)->setNormalizedGoalAngle(pose[i]);
        break;
      case WYAW:
        this->waist->getJoint(WAISTYAW)->setNormalizedGoalAngle(pose[i]);
        break;
      case HPAN:
        this->head->getJoint(PAN)->setNormalizedGoalAngle(pose[i]);
        break;
      case HTILT:
        this->head->getJoint(TILT)->setNormalizedGoalAngle(pose[i]);
        break;
    }
  }
}

void Dimitri::getNormalizedPose(float pose[]) //(&pose)[13])
{
  for (int i = 0 ; i < 13 ; i++)
  {
    switch (i)
    {
      case LROLL:
        pose[i] = this->leftArm->getJoint(ARMROLL)->getNormalizedAngle();
        break;
      case LPITCH:
        pose[i] = this->leftArm->getJoint(ARMPITCH)->getNormalizedAngle();
        break;
      case LYAW:
        pose[i] = this->leftArm->getJoint(ARMYAW)->getNormalizedAngle();
        break;
      case LELBOW:
        pose[i] = this->leftArm->getJoint(ELBOW)->getNormalizedAngle();
        break;
      case RROLL:
        pose[i] = this->rightArm->getJoint(ARMROLL)->getNormalizedAngle();
        break;
      case RPITCH:
        pose[i] = this->rightArm->getJoint(ARMPITCH)->getNormalizedAngle();
        break;
      case RYAW:
        pose[i] = this->rightArm->getJoint(ARMYAW)->getNormalizedAngle();
        break;
      case RELBOW:
        pose[i] = this->rightArm->getJoint(ELBOW)->getNormalizedAngle();
        break;
      case WROLL:
        pose[i] = this->waist->getJoint(WAISTROLL)->getNormalizedAngle();
        break;
      case WPITCH:
        pose[i] = this->waist->getJoint(WAISTPITCH)->getNormalizedAngle();
        break;
      case WYAW:
        pose[i] = this->waist->getJoint(WAISTYAW)->getNormalizedAngle();
        break;
      case HPAN:
        pose[i] = this->head->getJoint(PAN)->getNormalizedAngle();
        break;
      case HTILT:
        pose[i] = this->head->getJoint(TILT)->getNormalizedAngle();
        break;
    }
  }
}

void Dimitri::getPose(float pose[]) //(&pose)[13])
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
  lroll = this->leftArm->getJoint(ARMROLL)->getAngle();
  lpitch = this->leftArm->getJoint(ARMPITCH)->getAngle();
  lyaw = this->leftArm->getJoint(ARMYAW)->getAngle();
  lelbow = this->leftArm->getJoint(ELBOW)->getAngle();
  rroll = this->rightArm->getJoint(ARMROLL)->getAngle();
  rpitch = this->rightArm->getJoint(ARMPITCH)->getAngle();
  ryaw = this->rightArm->getJoint(ARMYAW)->getAngle();
  relbow = this->rightArm->getJoint(ELBOW)->getAngle();
  wroll = this->waist->getJoint(WAISTROLL)->getAngle();
  wpitch = this->waist->getJoint(WAISTPITCH)->getAngle();
  wyaw = this->waist->getJoint(WAISTYAW)->getAngle();
  hpan = this->head->getJoint(PAN)->getAngle();
  htilt = this->head->getJoint(TILT)->getAngle();
}

void Dimitri::getNormalizedPose(float &lroll, float &lpitch, float &lyaw, float &lelbow,
                 float &rroll, float &rpitch, float &ryaw, float &relbow,
                 float &wroll, float &wpitch, float &wyaw,
                 float &hpan, float &htilt)
{
  lroll = this->leftArm->getJoint(ARMROLL)->getNormalizedAngle();
  lpitch = this->leftArm->getJoint(ARMPITCH)->getNormalizedAngle();
  lyaw = this->leftArm->getJoint(ARMYAW)->getNormalizedAngle();
  lelbow = this->leftArm->getJoint(ELBOW)->getNormalizedAngle();
  rroll = this->rightArm->getJoint(ARMROLL)->getNormalizedAngle();
  rpitch = this->rightArm->getJoint(ARMPITCH)->getNormalizedAngle();
  ryaw = this->rightArm->getJoint(ARMYAW)->getNormalizedAngle();
  relbow = this->rightArm->getJoint(ELBOW)->getNormalizedAngle();
  wroll = this->waist->getJoint(WAISTROLL)->getNormalizedAngle();
  wpitch = this->waist->getJoint(WAISTPITCH)->getNormalizedAngle();
  wyaw = this->waist->getJoint(WAISTYAW)->getNormalizedAngle();
  hpan = this->head->getJoint(PAN)->getNormalizedAngle();
  htilt = this->head->getJoint(TILT)->getNormalizedAngle();
}

void Dimitri::delay(double seconds)
{

    // Records the initial time for each cycle
    clock_t initial_time = clock();

    double elapsed_time = 0;
    
    do {

      // Performs update
      this->update();

      // Calculates the elapsed time in this cycle so far
      elapsed_time = double(clock() - initial_time) / CLOCKS_PER_SEC;

    } while (elapsed_time < seconds);

}

void Dimitri::tick( double seconds )
{

    double elapsed_time = 0;
    time_t current_time;

    do {

      // Calculates the elapsed time in this cycle so far
      current_time = clock();
      elapsed_time = double(current_time - this->initial_time) / CLOCKS_PER_SEC;

    } while (elapsed_time < seconds);

    this->initial_time = current_time;
}

void Dimitri::tickUpdate( double seconds )
{
  this->update();
  this->tick( seconds );
}

