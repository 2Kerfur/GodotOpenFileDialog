#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <string.h>
#include <dirent.h>
#include <stdio.h>

int dirs_count = 0;

int main() {
    //struct stat st = {0};
    //if (stat("/sys/class/tty", &st) == -1) {
    //    printf("Does not exist");
    //}


    char devices[256][32];

    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
    closedir(d);
    }

    printf("-----------\n");
    printf("total items count: ");
    printf("%i", dirs_count);

    strcpy(devices[0], "HI");
    printf(devices[0]);



    //OPEN FILE
    //char filename[1024];
    //FILE *f = popen("zenity --file-selection", "r");
    //fgets(filename, 1024, f);
    //printf(filename);


    //OPEN FOLDER
    //char filename_2[1024];
    //FILE *f_2 = popen("zenity --file-selection --directory", "r");
    //fgets(filename_2, 1024, f_2);
    //printf(filename_2);

    return 0;
}
