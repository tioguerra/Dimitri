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
  robot.getRightArm()->setMaxTorque(256);
  robot.getLeftArm()->setMaxTorque(256);

  // Enable torque to the joints setting the
  // teaching control mode
  robot.setControlMode(TEACH);

  // This array stores the pose angles
  float pose[13];

  // Main loop
  while (true)
  {
    // Performs update
    robot.update();

    // Gets the pose angles
    robot.getPose( pose );

    // Print the pose angles 
    for (int i = 0 ; i < 13 ; i++)
    {
      printf("%+04.0f,", RAD2DEG(pose[i]));
    }
    printf("\n");
  }

  return 0;
}

