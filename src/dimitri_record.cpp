#include "Dimitri.h"
#include "Camera.h"
#include <signal.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <dynamixel.h>
#include <ctime>

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

  // Check for command line arguments
  if (argc != 2)
  {
    printf("\n");
    printf("This program will record the normalized joint\n");
    printf("positions and focus neck angle at green object.\n");
    printf("\n");
    printf("Usage:\n");
    printf("       %s filename.dat\n", argv[0]);
    printf("\n");
    printf("Hit Ctrl+C to stop recording\n");
    printf("\n");
    exit(EXIT_SUCCESS);
  }

  FILE *fp = fopen(argv[1], "w");
  if (fp == NULL)
  {
    printf("Error opening file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  printf(">> Setting up camera...\n");

  // Create the camera
  Camera cam(1);

  // Create a red object
  Object obj("green");

  // Add tracking of red objects
  cam.addObjectToTrack(&obj);

  // Create the Dimitri robot object connected
  // to /dev/ttyUSB0
  Dimitri robot(0, 4);

  // Add neck to the camera
  cam.setHead(robot.getHead());

  printf(">> Setting up robot posture...\n");

  // Sets maximum torque to the joints
  // P.S.: optionally can set for all motors
  //       like this: robot.setMaxTorque(64);
  robot.getHead()->setMaxTorque(128);
  robot.getWaist()->setMaxTorque(450);
  robot.getRightArm()->setMaxTorque(128);
  robot.getLeftArm()->setMaxTorque(128);

  // Enable torque to the joints
  robot.setControlMode(ANGLE);

  // This array stores the goal pose
  float targetPose[13];
  // stance
  createPoseDeg(targetPose,-60, 70, 20, -90, //arms
                           -60, 70, 20, -90,
                            0,-25,0,      // waist
                            0,-40);       // head

  // Sets goal pose
  robot.setPose( targetPose );
  // Waits a little
  robot.delay( 2.0 );

  // Loose a little of the torque in the arms
  robot.getRightArm()->setMaxTorque(128);
  robot.getLeftArm()->setMaxTorque(128);
  //robot.getRightArm()->setControlMode(OFF);
  //robot.getLeftArm()->setControlMode(OFF);

  // This array will store the actual pose
  // angles read from the motors and also
  // the vision feedback
  float data[13];

  printf(">> Recording! Hit Ctrl+C to stop.\n");

  // Main loop
  int count = 0;
  while (true)
  {

    if (count == 40)
    {
      robot.getRightArm()->setMaxTorque(30);
      robot.getLeftArm()->setMaxTorque(30);
    } else if (count == 200) {
      robot.getRightArm()->setMaxTorque(10);
      robot.getLeftArm()->setMaxTorque(10);
      //robot.getRightArm()->setControlMode(OFF);
      //robot.getLeftArm()->setControlMode(OFF);
    }

    // Process the camera frame
    cam.processFrame();

    // Refresh focus
    cam.moveHeadToFocus();

    // Performs update
    robot.update();

    // Gets the pose angles
    robot.getNormalizedPose( data );
    // Replace neck angles with focus object
    // angles (neck equivalent)
    data[11] = cam.getNormalizedFocusPan();
    data[12] = cam.getNormalizedFocusTilt();

    // Save the pose angles 
    for (int i = 0 ; i < 13 ; i++)
    {
      fprintf(fp, "%1.3f ", data[i]);
    }
    fprintf(fp, "\n");

    // Update the image on the screen
    cv::waitKey(1);

    // Keep sampling time
    robot.tick( 0.070 );

    // Print counter
    printf("count = %d\n", count);
    count++;

  }

  return 0;
}

