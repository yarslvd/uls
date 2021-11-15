#include "../inc/uls.h"

void print_tab(int len, int count_tabs) {
    int temp_len = len;
    while (temp_len != count_tabs * 8) {
        mx_printchar('\t');
        if (temp_len % 8 != 0) {
            temp_len += 8 - temp_len % 8;
        }
        else {
            temp_len += 8;
        }
    }
}
