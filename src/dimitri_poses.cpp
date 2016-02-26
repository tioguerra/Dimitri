#include "Dimitri.h"
#include "Util.h"
#include <signal.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
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
  robot.getHead()->setMaxTorque(90);
  robot.getWaist()->setMaxTorque(550);
  robot.getRightArm()->setMaxTorque(400);
  robot.getLeftArm()->setMaxTorque(400);

  // Enable torque to the joints
  robot.setControlMode(ANGLE);

  // This array stores the pose angles
  float poses[5][13];
  // zero
  createPoseDeg(poses[0],  0,  0,  0,  0,   0,  0,  0,   0,  0,  0,  0, 0, 0);
  // wondering
  createPoseDeg(poses[1],-63,112, 61,-90, -40, 50, 35, -90, -4,-12, 12,47,23);
  // stance
  createPoseDeg(poses[2],-60, 70, 20,-90, -60, 70, 20, -90,  0,  0,  0, 0, 0);
  // sky
  createPoseDeg(poses[3],-42,171,  1,-50, -42,171,  1, -50, 19,-1, -1, 0,53);
  // pointing
  createPoseDeg(poses[4],-78,119,  2,  0, -38, 40, 32,-113, 17,-1, -4,27,30);
  int i = 0;

  // Main loop
  while (true)
  {

    // Iterate between 3 poses
    i = (i + 1) % 5;

    // Sets goal positions
    printf("Pose %d\n", i);
    robot.setPose(poses[i]);
    
    // Busy delay (updating motors)
    robot.delay(4.0);

  }

  return 0;
}

