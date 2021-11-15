#include "../inc/uls.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] != '-') {
                break;
            }
            char illegal = opt_validation(argv[i]);
            if (argv[i][0] == '-' && illegal) {
                mx_printerr("uls: illegal option -- ");
                mx_printerr(&illegal);
                mx_printerr("\nusage: uls [-1AGRSafhlmort] [file...]\n");
                exit(-1);
            }
        }
    }
    t_list *opt_list = NULL;
    t_list *dir_list = NULL;
    t_list *file_list = NULL;

    argv_parser(argc, argv, &opt_list, &dir_list, &file_list);

    if (!dir_list && !file_list) {
        mx_push_back(&dir_list, ".");
    }
    if (opt_list) {
        uls_opt(opt_list, dir_list, file_list);
    }
    else {
        uls(dir_list, file_list, NULL);
    }
    if (opt_list)
        mx_clear_list(&opt_list);
    if (dir_list)
        mx_clear_list(&dir_list);
    if (file_list)
        mx_clear_list(&file_list);

    return 0;
}
