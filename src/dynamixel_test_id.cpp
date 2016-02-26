#include "dynamixel.h"
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <cstdio>

void signal_callback_handler(int signum)
{
  printf("Caught signal %d\n", signum);
  dxl_terminate();
  exit(signum);
}

int main(int argc, char *argv[])
{

  // Checks command line arguments
  if (argc != 2)
  {
    printf("\nYou must specify an id!\n");
    printf("Usage: %s id\n\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  // Get the id of the servo or spring from
  // the command line
  int id = atoi(argv[1]);

  // This is for handling CTRL+C nicely
  signal(SIGINT, signal_callback_handler);

  // Initialize the communication with the
  // Dynamixel network bus
  if (dxl_initialize(0,4) == 0)
  {
    printf( "Failed to open USB2Dynamixel!\n" );
    return -1;
  }

  while (true)
  {
      int pos = dxl_read_word( id, 0x24 );
      int result = dxl_get_result();
      if (result != 1) pos = -1;
      printf("%d:%d\n", id, pos);
  }

  return EXIT_SUCCESS;
}

