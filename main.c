#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <string.h>
#include <dirent.h>
#include <stdio.h>

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
    for (int i = 0; i < counter_2; i += 1)
    {

        char str[32] = "/sys/class/tty/";
        printf(strcat(str, devices[i]));
        printf("\n");
    }



    struct stat st = {0};
    if (stat("/sys/class/tty/", &st) == -1) {
        printf("Does not exist");
    }
//    printf("\n");
//    printf(devices[0]); printf("\n");
//    printf(devices[1]); printf("\n");
//    printf(devices[2]); printf("\n");
//    printf(devices[3]); printf("\n");
//
//    printf(devices[4]); printf("\n");
//    printf(devices[5]); printf("\n");
//    printf(devices[6]); printf("\n");
//    printf(devices[7]); printf("\n");

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
