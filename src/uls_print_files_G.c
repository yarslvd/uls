#include "../inc/uls.h"

void uls_print_files_G(char **arr, int count_files, char *dir) {
    if (!count_files) {
        return;
    }
    int size_str = 0;
    int max = 0;
    for (int i = 0; i < count_files; i++) {
        if (max < mx_strlen(arr[i]))
                max = mx_strlen(arr[i]);
    }

    size_str += (max + 1) * count_files - 1;
    
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    if (!isatty(1)) {
        uls_print_newline(arr, count_files, NULL, false);
        return;
    }
    
    int count_col = count_files;
    int count_rows = 1;
    int temp_size = size_str;
    if (temp_size > size.ws_col) {
        while (temp_size >= size.ws_col) {
            count_rows++;
            temp_size = 0;
            count_col = count_files / count_rows;
            if (count_files % count_rows != 0) {
                count_col++;
            }
            for (int i = 0; i < count_col; i++) {
                temp_size += max + 1;
            }
            temp_size--;
        }
    }
    int count_last_col;

    for (int i = 0; i < count_rows; i++) {
        for (int j = 0; j < count_col; j++) {
            if (j * count_rows + i < count_files) {
                print_color(dir, arr[j * count_rows + i]);
            }
            if (count_rows == 1) {
                    mx_printstr(arr[j * count_rows + i]);
                if (j != count_col - 1) {
                    for (int k = 0; k < max + 1 - mx_strlen(arr[j * count_rows + i]); k++) {
                        mx_printchar(' ');
                    }
                }
            }
            else if (count_files % count_rows == 0 && count_rows > 1) {
                if (j * count_rows + i < count_files) {
                    mx_printstr(arr[j * count_rows + i]);
                }
                else {
                    break;
                }
                if (j != count_col - 1) {
                    for (int k = 0; k < max + 1 - mx_strlen(arr[j * count_rows + i]); k++) {
                        mx_printchar(' ');
                    }
                }
            }
            else if (count_files % count_rows != 0 && count_rows > 1){
                if (i == 0 && j == 0) {
                    count_last_col = count_files % count_rows;
                }
                if (j == count_col - 1 && count_last_col == 0) {
                    break;
                }
                if (j * count_rows + i < count_files) {
                    mx_printstr(arr[j * count_rows + i]);
                }
                else {
                    break;
                }
                if (count_last_col) {
                    if (j != count_col - 1){
                        for (int k = 0; k < max + 1 - mx_strlen(arr[j * count_rows + i]); k++) {
                            mx_printchar(' ');
                        }
                    }
                }
                else {
                    if (j != count_col - 2){
                        for (int k = 0; k < max + 1 - mx_strlen(arr[j * count_rows + i]); k++) {
                            mx_printchar(' ');
                        }
                    }
                }
                if (j == count_col - 1 && count_last_col > 0) {
                    count_last_col--;
                }

            }
            mx_printstr(WHT);
        }
        mx_printchar('\n');
    }
}
