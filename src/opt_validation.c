#include "../inc/uls.h"

char opt_validation(char *argv) {
    for (int i = 1; i < mx_strlen(argv); i++) {
        if (argv[i] == 'l' || argv[i] == 'a' || argv[i] == 'r' || argv[i] == 'f'
        || argv[i] == '1' || argv[i] == 'R' || argv[i] == 'A' || argv[i] == 'h'
        || argv[i] == 't' || argv[i] == 'm' || argv[i] == 'S' || argv[i] == 'G'
        || argv[i] == 'o') {
            continue;
        }
        else {
            return argv[i]; //error
        }
    }

    return 0;
}
