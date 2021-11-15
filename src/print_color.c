#include "../inc/uls.h"

void print_color(char *dir, char *file) {
    struct stat buf;

    char *temp_path = NULL;
    if (dir)
        temp_path = mx_strjoin(dir,"/");
    char *path = mx_strjoin(temp_path, file);
    mx_strdel(&temp_path);

    stat(path, &buf);

    if (S_ISDIR(buf.st_mode)) {
        mx_printstr(BLU);
    }
    else if (buf.st_mode & S_IEXEC) {
        mx_printstr(RED);
    }
    else if (S_ISREG(buf.st_mode)) {
        mx_printstr(WHT);
    }
}
