#include "../inc/uls.h"

void uls_print_newline(char **arr, int count_files, char *dir, bool color){
    for(int i = 0; i < count_files; i++){
        if (color) {
            print_color(dir, arr[i]);
        }
        mx_printstr(arr[i]);
        mx_printchar('\n');
    }
}
