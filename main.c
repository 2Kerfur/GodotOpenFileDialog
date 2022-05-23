#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include <stdio.h>

int main() {
    struct stat st = {0};
    if (stat("/home/kerfur", &st) == -1) {
        printf("Does not exist");
    }
}

