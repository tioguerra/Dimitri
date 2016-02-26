#include "FireFlyCam.h"
#include <signal.h>
#include <unistd.h>

void signal_callback_handler(int signum)
{
  printf("Caught signal %d\n", signum);
  exit(signum);
}

int main(int argc, char *argv[])
{
  // For handling Ctrl+C nicely
  signal(SIGINT, signal_callback_handler);

  // Create the camera object
  FireFlyCam cam(0);

  // Create a red object
  Object obj("orange");

  // Add tracking of red objects
  cam.addObjectToTrack(&obj);

  while (true)
  {

    // Process the camera frame
    cam.processFrame();

    // Control framerate
    cv::waitKey(30);

  }

  return 0;

}

