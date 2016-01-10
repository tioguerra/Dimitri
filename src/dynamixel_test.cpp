#include <dynamixel.h>
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
  signal(SIGINT, signal_callback_handler);

  if (dxl_initialize(0,7) == 0)
  {
    printf( "Failed to open USB2Dynamixel!\n" );
    return -1;
  }

  while (true)
  {
    for (int i = 1 ; i <= 13 ; i++)
    {
      if (i >= 1 && i <= 8)
      {
        int pos_spring = dxl_read_word( 0x64 + i, 0x24 );
        int result_spring = dxl_get_result();
        if (result_spring != 1) pos_spring = -1;
        int pos = dxl_read_word( i, 0x24 );
        int result = dxl_get_result();
        if (result != 1) pos = -1;
        printf("%d:%d,%d:%d,",
                i, pos, 0x64+i, pos_spring);
      } else {
        int pos = dxl_read_word( i, 0x24 );
        int result = dxl_get_result();
        if (result != 1) pos = -1;
        printf("%d:%d,", i, pos);
      }
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}

