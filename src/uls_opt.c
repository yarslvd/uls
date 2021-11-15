#include "../inc/uls.h"
//options 0-l 1-a 2-r 3-f 4-1 5-R 6-A 7-h 8-t
void uls_opt(t_list *opt_list, t_list *dir_list, t_list *file_list) {
    t_opt *options = new_options();
    t_list *temp = opt_list;

    while (temp) {
        for (int i = 1; i < mx_strlen(temp -> data); i++) {
            if (((char *)(temp -> data))[i] == 'l') {
                if(options -> new_line == true){
                    options -> new_line = false;
                }
                options -> l = true;
            }
            if (((char *)(temp -> data))[i] == 'a') {
                if(options -> A == true){
                    options -> A = false;
                }
                options -> a = true;
            }
            if (((char *)(temp -> data))[i] == 'r') {
                options -> r = true;
            }
            if (((char *)(temp -> data))[i] == 'f') {
                if(options->A == true){
                    options->A = false;
                }
                options -> f = true;
            }
            if (((char *)(temp -> data))[i] == '1') {
                if(options -> m == true){
                    options -> m = false;
                }
                else if(options -> o == true){
                    options -> o = false;
                }
                else if(options -> l == true){
                    options -> l = false;
                }
                else{
                    options -> new_line = true;
                }
            }
            if (((char *)(temp -> data))[i] == 'R') {
                options -> R = true;
            }
            if (((char *)(temp -> data))[i] == 'A') {
                if(options->a == true){
                    options->A = false;
                }
                else if(options->new_line == true){
                    options -> A = true;
                }
                else if(options -> f == true){
                    options -> A = false;
                }
                else{
                    options -> A = true;
                }
            }
            if (((char *)(temp -> data))[i] == 'h') {
                options -> h = true;
            }
            if (((char *)(temp -> data))[i] == 't') {
                if(options -> S == true){
                    options -> t = false;
                }
                else{
                    options -> t = true;
                }
            }
            if (((char *)(temp -> data))[i] == 'm') {
                if(options -> new_line == true){
                    options -> new_line = false;
                }
                if(options -> o == true){
                    options -> o = false;
                }
                if(options -> l == true){
                    options -> l = false;
                }
                options -> m = true;
            }
            if (((char *)(temp -> data))[i] == 'S') {
                if(options -> t == true){
                    options -> t = false;
                }
                options -> S = true;
            }
            if (((char *)(temp -> data))[i] == 'G') {
                options -> G = true;
            }
            if (((char *)(temp -> data))[i] == 'o') {
                if(options -> m == true){
                    options -> m = false;
                }
                if(options -> new_line == true){
                    options -> new_line = false;
                }
                options -> o = true;
            }
        }
        temp = temp -> next;
    }
    
    if (options -> R) {
        temp = dir_list;
        int dir_inside = mx_list_size(dir_list);
        if (file_list) {
            if (options -> l) {
                uls_print_l(NULL, file_list, options);
            }
            else {
                uls(NULL, file_list, options);
            }
            if (dir_inside)
                mx_printchar('\n');
        }
        while (temp) {
            recursion(temp -> data, options, options -> h, &dir_inside);
            temp = temp -> next;
        }
        free(options);
        options = NULL;
        return;
    }
    if (options -> l || options -> o) { // -l -f -a -r
        uls_print_l(dir_list, file_list, options);
    }
    else {
        uls(dir_list, file_list, options);
    }
    free(options);
    options = NULL;
}

t_opt *new_options() {
    t_opt *options = (t_opt *)malloc(sizeof(t_opt));
    (options) -> l = false;
    (options) -> a = false;
    (options) -> r = false;
    (options) -> f = false;
    (options) -> new_line = false;
    (options) -> R = false;
    (options) -> A = false;
    (options) -> h = false;
    (options) -> t = false;
    (options) -> m = false;
    (options) -> S = false;
    (options) -> G = false;
    (options) -> o = false;
    return options;
}
