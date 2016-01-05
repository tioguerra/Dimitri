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

  // Sets maximum torque to the joints
  // P.S.: optionally can set for all motors
  //       like this: robot.setMaxTorque(64);
  robot.getHead()->setMaxTorque(64);
  robot.getWaist()->setMaxTorque(384);
  robot.getRightArm()->setMaxTorque(256);
  robot.getLeftArm()->setMaxTorque(256);

  // Enable torque to the joints setting the
  // teaching control mode
  robot.setControlMode(TEACH);

  // Main loop
  while (true)
  {
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

    printf("%+04.0f,%+04.0f,%+04.0f,%+04.0f|%+04.0f,%+04.0f,%+04.0f,%+04.0f|%+04.0f,%+04.0f|%+04.0f,%+04.0f,%+04.0f\n",
        lroll,lpitch,lyaw,lelbow,rroll,rpitch,ryaw,relbow,hpan,htilt,wroll,wpitch,wyaw);
  }

  return 0;
}

