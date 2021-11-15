#include "../inc/uls.h"

int max_len_strs(char **s_arr, int size, int start) {
    char *max = s_arr[start];
    for (int i = start; i < size + start; i++) {
        if (!s_arr[i]) {
            break;
        }
        if (mx_strlen(max) < mx_strlen(s_arr[i])) {
            max = s_arr[i];
        }
    }
    
    return mx_strlen(max);
}

int max_len_strs_col(char ***s_arr, int size, int col) {
    char *max = s_arr[0][col];
    for (int i = 0; i < size; i++) {
        if (mx_strlen(max) < mx_strlen(s_arr[i][col])) {
            max = s_arr[i][col];
        }
    }
    
    return mx_strlen(max);
}

