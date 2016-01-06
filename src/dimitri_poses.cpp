#include "Dimitri.h"
#include "Util.h"
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
  // to /dev/ttyUSB0 with 500000bps
  Dimitri robot(0, 3);

  // Sets maximum torque to the joints
  // P.S.: optionally can set for all motors
  //       like this: robot.setMaxTorque(64);
  robot.getHead()->setMaxTorque(64);
  robot.getWaist()->setMaxTorque(384);
  robot.getRightArm()->setMaxTorque(448);
  robot.getLeftArm()->setMaxTorque(448);

  // Enable torque to the joints
  robot.setControlMode(ANGLE);

  // This array stores the pose angles
  float poses[4][13];
  createPoseDeg(poses[0],  0,  0,  0,  0,   0,  0,  0,  0,  0, 0,  0,   0,  0);
  createPoseDeg(poses[1],-60, 60,  0,-90, -60, 60,  0,-90,  0, 0,  0,   0,  0);
  createPoseDeg(poses[2],-63,112, 61,-90, -52, 68, -3,-71,-12, 4, 12,  47, 23);
  createPoseDeg(poses[3],-78,+119,2,0,-38,9,32,-113,-1,-17,-4,27,30);
  int i = 0;

  // Main loop
  while (true)
  {
    // Iterate between 3 poses
    i = (i + 1) % 4;

    // Sets goal positions
    robot.setPose(poses[i]);
    // Performs update
    robot.update();

    // Delay
    usleep(2000000);

  }

  return 0;
}

