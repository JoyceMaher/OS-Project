#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int t = datetime();
  printf("Unix timestamp: %d\n", t);
  
  int sec = t % 60;
  int min = (t / 60) % 60;
  int hr = (t / 3600) % 24;
  int days = t / (24 * 3600);
  
  printf("Days: %d\n", days);
  printf("Time: %d hours, %d minutes, %d seconds\n", hr, min, sec);
  
  exit(0);
}
