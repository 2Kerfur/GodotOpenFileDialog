#include "com_port.h"
#include "linux/utils/dir.h"

#define MAX_COLS 32
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>


// Linux headers for com reading
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

char read_buf [256];

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
        char str_1[32] = "";
        strcat(str_1, devices[i]);
        char str[32] = "/sys/class/tty/";
        strcat(str, devices[i]);
        strcat(str, "/device");
        if (stat(str, &st) == -1) {
        } else {
            strcpy(avaliable_devices_var[avaliable_devices_count], str_1);
            printf(str_1);
            printf("\n");
            avaliable_devices_count += 1;
        }
    }
    return avaliable_devices_count;
}

int OpenComPort(char device_name[])
{
    char str[32] = "/dev/";
    strcat(str, device_name);
    printf(str);

    int serial_port = open(str, O_RDWR);
    struct termios tty;

    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return 1;
    }
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ECHONL;
    tty.c_lflag &= ~ISIG;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

    tty.c_oflag &= ~OPOST;
    tty.c_oflag &= ~ONLCR;
    tty.c_cc[VTIME] = 10;
    tty.c_cc[VMIN] = 0;

    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        //return 1;
    }
    memset(&read_buf, '\0', sizeof(read_buf));
    return serial_port;
}

int CloseComPort(int serial_port)
{
    close(serial_port);
    return 0;
}

char* ReadComPort(int serial_port)
{
  // Write to serial port
  //unsigned char msg[] = { 'H', 'e', 'l', 'l', 'o', '\r' };
  //write(serial_port, msg, sizeof(msg));


    read(serial_port, &read_buf, sizeof(read_buf));

    //if (num_bytes < 0) {
      //printf("Error reading: %s", strerror(errno));
      //return 1;
    //}

    return read_buf;
}

int WriteComPort(int serial_port, char message[])
{
    write(serial_port, message, sizeof(message));
    return 0;
}

