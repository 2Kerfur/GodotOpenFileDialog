#include "main.h"
#include "utils/dir.h"
#include "arduino/com_port.h"

#define MAX_COLS 32

int main() {

    int dirs_count = GetDirsCount("/sys/class/tty");
    char avaliable_devices[dirs_count][MAX_COLS];
    int dev_size = GetAvaliablePorts(dirs_count, MAX_COLS, avaliable_devices);
    printf("%d", dev_size);
    printf("\n");



    int port = OpenComPort(avaliable_devices[2]);

    while (1)
    {
        printf(ReadComPort(port));

    }
    return 0;
}

