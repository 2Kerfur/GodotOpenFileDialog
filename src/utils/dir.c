#include <sys/types.h> //dir type
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

#include "dir.h"

int GetDirsCount(char path[])
{
    int dirs_count = 0;
    DIR *ComPortsDir_count;
    struct dirent *dir_2;
    ComPortsDir_count = opendir(path);
    if (ComPortsDir_count) {
        while ((dir_2 = readdir(ComPortsDir_count)) != NULL) {
            dirs_count += 1;
        }
    closedir(ComPortsDir_count);
    }
    return dirs_count;
}

void GetDirsNames(char path[], int rows, int cols, char names_store_var[rows][cols])
{
    DIR *d;
    int counter_2 = 0;
    struct dirent *dir;
    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            strcpy(names_store_var[counter_2], dir->d_name);
            counter_2 += 1;
        }
    closedir(d);
    }
}
