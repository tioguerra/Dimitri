#include "Dimitri.h"
#include "Camera.h"
#include <dynamixel.h>
#include <signal.h>
#include <unistd.h>

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
  Object obj("red");

  // Add tracking of red objects
  cam.addObjectToTrack(&obj);

  // Create the Dimitri robot object connected
  // to /dev/ttyUSB0 with 250000bps
  Dimitri robot(0, 7);

  // Sets maximum torque to the joints
  // P.S.: optionally can set for all motors
  //       like this: robot.setMaxTorque(64);
  robot.getHead()->setMaxTorque(1023);
  robot.getWaist()->setMaxTorque(384);
  robot.getRightArm()->setMaxTorque(384);
  robot.getLeftArm()->setMaxTorque(384);

  // Enable torque to the joints
  robot.setControlMode(ANGLE);

  // Sets goal position
  robot.setPose(DEG2RAD(-45.0),0,DEG2RAD(40.0),DEG2RAD(-90.0),
                DEG2RAD(-45.0),0,DEG2RAD(40.0),DEG2RAD(-90.0),
                0,DEG2RAD(-25.0),0,
                0,DEG2RAD(-40.0));

  // Get to the pose
  robot.update();
  robot.delay(3.0);

  // Add neck to the camera
  cam.setHead(robot.getHead());

  while (true)
  {

    // Process the camera frame
    cam.processFrame();

    // Update robot
    robot.getHead()->update();

    // Print the focus
    printf( "Focus %+3.0f (%1.2f) %3.0f (%1.2f)\n",
            RAD2DEG(cam.getFocusPan()), cam.getNormalizedFocusPan(),
            RAD2DEG(cam.getFocusTilt()), cam.getNormalizedFocusTilt() );

    // Control framerate
    cv::waitKey(1);

  }

  return 0;

}

