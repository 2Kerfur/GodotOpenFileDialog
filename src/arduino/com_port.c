#include "com_port.h"
#include "utils/dir.h"

#define MAX_COLS 32
#include <string.h>
#include <sys/stat.h>

int GetAvaliablePorts(int rows, int cols,
                      char avaliable_devices_var[rows][cols])
{
    int avaliable_devices_count = 0;
    char devices[rows][MAX_COLS];
    GetDirsNames("/sys/class/tty", rows, MAX_COLS, devices);

    int counter = rows;
    struct stat st = {0};
    for (int i = 2; i < counter; i += 1) //starts from 2 because first 2 are . and ..
    {
        char str[32] = "/sys/class/tty/";
        strcat(str, devices[i]);
        strcat(str, "/device");
        if (stat(str, &st) == -1) {
        } else {
            strcpy(avaliable_devices_var[avaliable_devices_count], str);
            avaliable_devices_count += 1;
        }
    }
    return avaliable_devices_count;
}
