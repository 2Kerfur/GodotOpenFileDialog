#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <dirent.h>

#include <stdio.h>

int main(d) {
    struct stat st = {0};
    if (stat("/home/kerfur", &st) == -1) {
        printf("Does not exist");
    }


    //OPEN FILE
    char filename[1024];
    FILE *f = popen("zenity --file-selection", "r");
    fgets(filename, 1024, f);
    printf(filename);


    //OPEN FOLDER
    //char filename_2[1024];
    //FILE *f_2 = popen("zenity --file-selection --directory", "r");
    //fgets(filename_2, 1024, f_2);
    //printf(filename_2);



    return 0;
}

