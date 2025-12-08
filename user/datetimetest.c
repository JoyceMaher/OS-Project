#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    uint64 t = datetime();

    int sec = t % 60;
    int min = (t / 60) % 60;
    int hr  = (t / 3600) % 24;
    int days = t / (24 * 3600);
    int years = days / 365;
    int remaining_days = days % 365;

    printf("It has been %d year(s), %d day(s), %d hour(s), %d minute(s), and %d second(s) since the system was built.\n",
           years, remaining_days, hr, min, sec);

    exit(0);
}
