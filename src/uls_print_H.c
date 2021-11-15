#include "../inc/uls.h"

static char *convert(int size, char *type, int n);
static char *convert_float(int size, char *type, int n);

int mx_len_integer(int n) {
    int len = 1;
    
    while(n /= 10){
        len++;
    }
    return len;
}

static void indirect(char* str, int len) {
    int i = 0;
    int j = len - 1;
    int temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

static int mx_int_to_Str(int x, char str[], int d) {
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x /= 10;
    }
    while (i < d){
        str[i++] = '0';
    }
    indirect(str, i);
    str[i] = '\0';
    return i;
}

void ftoa(float n, char *res, int comma) {
    int ipart = (int)n;
    float fpart = n - (float)ipart;
    int i = mx_int_to_Str(ipart, res, 0);
    if (comma != 0) {
        res[i] = '.';
        fpart = fpart * mx_pow(10, comma);
        mx_int_to_Str((int)fpart, res + i + 1, comma);
    }
}

char *mx_to_human_readable(int size) {
    char *result = NULL;
    if (size < 0 || size > 2147483647) {
        return NULL;
    }
    if (size == 0) {
        result = mx_strnew(2);
        result = mx_strcpy(result, "0B");
        return result;
    }

    else if (size > 0 && size <= 1024) {
        result = convert(size, "B", 1);
    }
    else if (size > 1024 && size <= 1024 * 1024) {
        if (size < 10240){
            result = convert_float(size, "K", 1024);
        }
        else{
            result = convert(size, "K", 1024);
        }
    }
    else if (size > 1024 * 1024 && size <= 1024 * 1024 * 1024) {
        if (size < 10485760){
            result = convert_float(size, "M", 1024 * 1024);
        }
        else{
            result = convert(size, "M", 1024 * 1024);
        }
    }
    else {
        result = convert_float(size, "G", 1024 * 1024 * 1024);
    }
    return result;
}

static char *convert(int size, char *type, int n) {
    char *result;
    char *temp;
    int temp_size = size;
    size /= n;
    if (temp_size % n) {
        size++;
    }
    result = mx_strnew(mx_len_integer(size) + 1);
    temp = mx_itoa(size);
    result = mx_strcpy(result, temp);
    result = mx_strcat(result, type);
    mx_strdel(&temp);
    return result;
}

static char *convert_float(int size, char *type, int n) {
    char *result = NULL;
    float f_size;
    f_size = (float)size / (float)n;
    int temp_size = f_size * 100;
    if (temp_size % ((mx_len_integer(f_size) + 2) * 10) >= 5) {
        f_size += 0.05;
    }
    size /= n;
    result = mx_strnew(mx_len_integer(size) + 3);
    ftoa(f_size, result, 1);
    result = mx_strcat(result, type);
    return result;
}
