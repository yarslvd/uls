#include "../inc/uls.h"

void argv_parser(int argc, char **argv, t_list **opt_list, t_list **dir_list, t_list **file_list) {
    bool end_opt = false;
    for (int i = 1; i < argc; i++) {
        if (!end_opt && argv[i][0] != '-') {
            end_opt = true;
        }
        if (argv[i][0] == '-' && !end_opt) {
            mx_push_back(opt_list, argv[i]);
        }
        else {
            struct stat buf;
            if(!stat(argv[i], &buf)) {
                if (S_ISDIR(buf.st_mode)) {
                    mx_push_back(dir_list, argv[i]);
                }
                else if (S_ISREG(buf.st_mode)) {
                    mx_push_back(file_list, argv[i]);
                }
            }
            else {
                mx_printerr("uls: cannot access \'");
                mx_printerr(argv[i]);
                mx_printerr("\': No such file or directory\n");
                mx_push_back(dir_list, NULL);
            }
        }
    }
}
