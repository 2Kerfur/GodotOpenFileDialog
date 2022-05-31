#include <stdio.h>
#include "native_dialog.h"

int OpenFileDialog(char filename[])
{
    FILE *file = popen("zenity --file-selection", "r");
    fgets(filename, 1024, file);
    return 0;
}
int OpenFolderDialog(char foldername[])
{
    FILE *file = popen("zenity --file-selection --directory", "r");
    fgets(foldername, 1024, file);
    return 0;
}
