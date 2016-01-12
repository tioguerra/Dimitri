#include "Dimitri.h"
#include <signal.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <dynamixel.h>

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
  // to /dev/ttyUSB0
  Dimitri robot(0, 4);

  // Sets maximum torque to the joints
  // P.S.: optionally can set for all motors
  //       like this: robot.setMaxTorque(64);
  robot.getHead()->setMaxTorque(64);
  robot.getWaist()->setMaxTorque(384);
  robot.getRightArm()->setMaxTorque(384);
  robot.getLeftArm()->setMaxTorque(384);

  // Enable torque to the joints
  robot.setControlMode(ANGLE);

  // This will put the robot in a safe position
  // and nicely reduce torque to the motors
  float pose[13];
  createPoseDeg(pose,-70,30,40,-60,-70,30,40,-60,0,-10,0,0,-50);
  robot.setPose(pose);
  robot.delay(0.5);
  robot.getRightArm()->setMaxTorque(256);
  robot.getLeftArm()->setMaxTorque(256);
  createPoseDeg(pose,-80,45,35,-50,-80,45,35,-50,0,-10,0,0,-50);
  robot.setPose(pose);

  for (int i = 10 ; i >= 0 ; i--)
  {
    robot.setMaxTorque(20*i);
    robot.delay(0.25);
  }

  // Enable torque to the joints
  robot.setControlMode(OFF);

  return 0;
}

