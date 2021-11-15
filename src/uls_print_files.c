#include "../inc/uls.h"

void uls_print_files(char **arr, int count_files) {
    if (!count_files) {
        return;
    }
    int size_str = 0;
    int max = 0;
    for (int i = 0; i < count_files; i++) {
        if (max < mx_strlen(arr[i]))
                max = mx_strlen(arr[i]);
    }

    int count_tabs = max/8 + 1;

    size_str += count_files * count_tabs * 8;
    
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
        while (temp_size > size.ws_col) {
            count_rows++;
            temp_size = 0;
            count_col = count_files / count_rows;
            if (count_files % count_rows != 0) {
                count_col++;
            }
            for (int i = 0; i < count_col; i++) {
                temp_size += count_tabs * 8;
            }
        }
    }
    int count_last_col;

    for (int i = 0; i < count_rows; i++) {
        for (int j = 0; j < count_col; j++) {
            if (count_rows == 1) {
                    mx_printstr(arr[j * count_rows + i]);
                if (j != count_col - 1) {
                    print_tab(mx_strlen(arr[j * count_rows + i]), count_tabs);
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
                    print_tab(mx_strlen(arr[j * count_rows + i]), count_tabs);
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
                        print_tab(mx_strlen(arr[j * count_rows + i]), count_tabs);
                    }
                }
                else {
                    if (j != count_col - 2){
                        print_tab(mx_strlen(arr[j * count_rows + i]), count_tabs);
                    }
                }
                if (j == count_col - 1 && count_last_col > 0) {
                    count_last_col--;
                }

            }
        }
        mx_printchar('\n');
    }
}
