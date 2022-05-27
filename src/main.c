#include "main.h"
#include "utils/dir.h"
#define MAX_COLS 32

int main() {
    int dirs_count = GetDirsCount("/sys/class/tty");
    char devices[dirs_count][MAX_COLS]; //create syitable space for all devices

    GetDirsNames("/sys/class/tty", dirs_count, MAX_COLS, devices);

    printf("\n-----------\n");
    int counter_4 = dirs_count;
    char devices_path[dirs_count][32];
    struct stat st = {0};
    int counter_3 = 0;
    for (int i = 2; i < dirs_count; i += 1) //starts from 2 because first 2 is . and ..
    {

        char str[32] = "/sys/class/tty/";
        strcat(str, devices[i]);
        strcat(str, "/device");
        if (stat(str, &st) == -1) {
        } else {
            printf(str);
            counter_3 += 1;
            printf("\n");
        }
    }
    printf("%d",counter_3);



    return 0;
}

