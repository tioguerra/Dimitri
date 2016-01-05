#include "Dimitri.h"
#include <signal.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <dynamixel.h>

#define RAD2DEG(x) ((x)*180.0/M_PI)
#define DEG2RAD(x) ((x)*M_PI/180.0)

void signal_callback_handler(int signum)
{
  printf("Caught signal %d\n", signum);
  dxl_terminate();
  exit(signum);
}

int main(int argc, char *argv[])
{
  // For handling Ctrl+C nicely
  signal(SIGINT, signal_callback_handler);

  // Create the Dimitri robot object connected
  // to /dev/ttyUSB0 with 115200bps
  Dimitri robot(0, 16);

  // -089,+036,+006,-093|-089,+045,-010,-091|+003,+002|-005,-002,-000
  
  // Sets maximum torque to the joints
  // P.S.: optionally can set for all motors
  //       like this: robot.setMaxTorque(64);
  robot.getHead()->setMaxTorque(64);
  robot.getWaist()->setMaxTorque(384);
  robot.getRightArm()->setMaxTorque(256);
  robot.getLeftArm()->setMaxTorque(256);

  // Enable torque to the joints
  robot.setControlMode(ANGLE);

  // Main loop
  while (true)
  {
    // Sets goal positions
    robot.getLeftArm()->getJoint(ARMROLL)->setGoalAngle(DEG2RAD(0.0));
    robot.getLeftArm()->getJoint(ARMPITCH)->setGoalAngle(DEG2RAD(0.0));
    robot.getLeftArm()->getJoint(ARMYAW)->setGoalAngle(DEG2RAD(0.0));
    robot.getLeftArm()->getJoint(ELBOW)->setGoalAngle(DEG2RAD(0.0));
    robot.getRightArm()->getJoint(ARMROLL)->setGoalAngle(DEG2RAD(0.0));
    robot.getRightArm()->getJoint(ARMPITCH)->setGoalAngle(DEG2RAD(0.0));
    robot.getRightArm()->getJoint(ARMYAW)->setGoalAngle(DEG2RAD(0.0));
    robot.getRightArm()->getJoint(ELBOW)->setGoalAngle(DEG2RAD(0.0));
    robot.getHead()->getJoint(PAN)->setGoalAngle(DEG2RAD(0.0));
    robot.getHead()->getJoint(TILT)->setGoalAngle(DEG2RAD(0.0));
    robot.getWaist()->getJoint(WAISTROLL)->setGoalAngle(DEG2RAD(0.0));
    robot.getWaist()->getJoint(WAISTPITCH)->setGoalAngle(DEG2RAD(0.0));
    robot.getWaist()->getJoint(WAISTYAW)->setGoalAngle(DEG2RAD(0.0));

    // Performs update
    robot.update();

    // Gets the angle values for the left arm
    float lroll = RAD2DEG(robot.getLeftArm()->getJoint(ARMROLL)->getAngle());
    float lpitch = RAD2DEG(robot.getLeftArm()->getJoint(ARMPITCH)->getAngle());
    float lyaw = RAD2DEG(robot.getLeftArm()->getJoint(ARMYAW)->getAngle());
    float lelbow = RAD2DEG(robot.getLeftArm()->getJoint(ELBOW)->getAngle());

    // Gets the angle values for the right arm
    float rroll = RAD2DEG(robot.getRightArm()->getJoint(ARMROLL)->getAngle());
    float rpitch = RAD2DEG(robot.getRightArm()->getJoint(ARMPITCH)->getAngle());
    float ryaw = RAD2DEG(robot.getRightArm()->getJoint(ARMYAW)->getAngle());
    float relbow = RAD2DEG(robot.getRightArm()->getJoint(ELBOW)->getAngle());
    
    // Gets the angle values for the head
    float hpan = RAD2DEG(robot.getHead()->getJoint(PAN)->getAngle());
    float htilt = RAD2DEG(robot.getHead()->getJoint(TILT)->getAngle());
    
    // Gets the angle values for the waist
    float wroll = RAD2DEG(robot.getWaist()->getJoint(WAISTROLL)->getAngle());
    float wpitch = RAD2DEG(robot.getWaist()->getJoint(WAISTPITCH)->getAngle());
    float wyaw = RAD2DEG(robot.getWaist()->getJoint(WAISTYAW)->getAngle());
    /*

    printf("head:%+04.0f,%+04.0f waist:%+04.0f,%+04.0f,%+04.0f left:%+04.0f,%+04.0f,%+04.0f,%+04.0f right:%+04.0f,%+04.0f,%+04.0f,%+04.0f\n",
          hpan, htilt, wroll, wpitch, wyaw, lroll, lpitch, lyaw, lelbow, rroll, rpitch, ryaw, relbow);
    */
    printf("%+04.0f,%+04.0f,%+04.0f,%+04.0f|%+04.0f,%+04.0f,%+04.0f,%+04.0f|%+04.0f,%+04.0f|%+04.0f,%+04.0f,%+04.0f\n",
        lroll,lpitch,lyaw,lelbow,rroll,rpitch,ryaw,relbow,hpan,htilt,wroll,wpitch,wyaw);
  }

  return 0;
}

