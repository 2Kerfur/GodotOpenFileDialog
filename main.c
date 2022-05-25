#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>


#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>

int dirs_count = 0;

void append_char(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

int main() {
    //create array for ComPorts
    int dirs_count = 0;
    DIR *ComPortsDir_count;
    struct dirent *dir_2;
    ComPortsDir_count = opendir("/sys/class/tty");
    if (ComPortsDir_count) {
        while ((dir_2 = readdir(ComPortsDir_count)) != NULL) {
            dirs_count += 1;
        }
    closedir(ComPortsDir_count);
    }
    printf("%d\n",dirs_count);

    char devices[dirs_count][32];
    //add values to dirs
    DIR *d;
    int counter_2 = 0;
    struct dirent *dir;
    d = opendir("/sys/class/tty");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
            strcpy(devices[counter_2], dir->d_name);
            counter_2 += 1;
        }
    closedir(d);
    }

    printf("-----------\n");

    char devices_path[dirs_count][32];
    struct stat st = {0};
    int counter_3 = 0;
    for (int i = 2; i < counter_2; i += 1) //starts from 2 because first 2 is . and ..
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


    //arduino input reading
    //-----------------------

    int USB = open( "/dev/ttyACM0", O_RDWR| O_NOCTTY );

    struct termios tty;
struct termios tty_old;
memset (&tty, 0, sizeof tty);

/* Error Handling */
if ( tcgetattr ( USB, &tty ) != 0 ) {
   //std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
}

/* Save old tty parameters */
tty_old = tty;

/* Set Baud Rate */
cfsetospeed (&tty, (speed_t)B9600);
cfsetispeed (&tty, (speed_t)B9600);

/* Setting other Port Stuff */
tty.c_cflag     &=  ~PARENB;            // Make 8n1
tty.c_cflag     &=  ~CSTOPB;
tty.c_cflag     &=  ~CSIZE;
tty.c_cflag     |=  CS8;

tty.c_cflag     &=  ~CRTSCTS;           // no flow control
tty.c_cc[VMIN]   =  1;                  // read doesn't block
tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

/* Make raw */
cfmakeraw(&tty);

/* Flush Port, then applies attributes */
tcflush( USB, TCIFLUSH );
if ( tcsetattr ( USB, TCSANOW, &tty ) != 0) {
   //std::cout << "Error " << errno << " from tcsetattr" << std::endl;
}
    //-----------------------

    while (1)
    {

        int n = 0,
    spot = 0;
char buf = '\0';

/* Whole response*/
char response[1024];
memset(response, '\0', sizeof response);

do {
    n = read( USB, &buf, 1 );
    sprintf( &response[spot], "%c", buf );
    spot += n;
} while( buf != '\r' && n > 0);

if (n < 0) {
    printf("Error reading: ");
}
else if (n == 0) {
    printf("Read nothing!");
}
else {
    printf("Response: ");
    printf(response);
}
    }


    return 0;
}


void OpenFileDialog()
{
    char filename[1024];
    FILE *f = popen("zenity --file-selection", "r");
    fgets(filename, 1024, f);
    printf(filename);
}
void OpenFolderDialog()
{
    char filename_2[1024];
    FILE *f_2 = popen("zenity --file-selection --directory", "r");
    fgets(filename_2, 1024, f_2);
    printf(filename_2);
}
