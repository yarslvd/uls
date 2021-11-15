#include "../inc/uls.h"

void uls_print_m(char **arr, int count_files, char *dir, bool color){
    if (count_files == 0) {
        return;
    }
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    if (!isatty(1)) {
        size.ws_col = 80;
    }
    int size_str = 0;
    for(int i = 0; i < count_files; i++){
        size_str += mx_strlen(arr[i]);
        if (i < count_files - 1) {
            size_str += 2;
        }
        if (size_str >= size.ws_col) {
            mx_printchar('\n');
            size_str = mx_strlen(arr[i]) + 2;
        }

        if (color) {
            print_color(dir, arr[i]);
        }

        mx_printstr(arr[i]);
        
        if (color) {
            mx_printstr(WHT);
        }
        
        if(i < count_files - 1){
            mx_printstr(", ");
        }
    }
    mx_printchar('\n');
}
