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

  // Create the camera object
  Camera cam;

  // Create a red object
  Object obj("green");

  // Add tracking of red objects
  cam.addObjectToTrack(&obj);

  // Create the Dimitri robot object connected
  // to /dev/ttyUSB0
  Dimitri robot(0, 4);

  // Add neck to the camera
  cam.setHead(robot.getHead());

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
  createPoseDeg(targetPose,-35,40,50,-90, // arms
                           -35,40,50,-90, //
                            0,-25,0,      // waist
                            0,-40);       // head

  // Sets goal pose
  robot.setPose( targetPose );
  // Waits a little
  robot.delay( 2.0 );

  // Loose a little of the torque in the arms
  robot.getRightArm()->setControlMode(OFF);
  robot.getLeftArm()->setControlMode(OFF);

  // This array will store the actual pose
  // angles read from the motors and also
  // the vision feedback
  float data[13];

  // Main loop
  double sum_times = 0.0;
  int total = 0;
  clock_t initial_time = clock();
  while (true)
  {
    double elapsed_time = double(clock() - initial_time) / CLOCKS_PER_SEC;
    sum_times += elapsed_time;
    total++;
    printf("Time:%1.3f Avg:%1.3f ", elapsed_time, sum_times / (double)total);
    initial_time = clock();

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

    // Print the pose angles 
    for (int i = 0 ; i < 13 ; i++)
    {
      printf("%+01.2f,", data[i]);
    }
    printf("\n");

    // Update the image on the screen
    cv::waitKey(1);

    // Keep sampling time
    robot.tick( 0.070 );

  }

  return 0;
}

