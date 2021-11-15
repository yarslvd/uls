#include "../inc/uls.h"

char *mx_trim_slash(char *str) {
    int i = mx_strlen(str) - 1;
    for (; i > 0; i--) {
        if (str[i] != '/') {
            break;
        }
    }

    return mx_strndup(str, i + 1);
}

//options 0-l 1-a 2-r 3-f 4-1 5-R 6-A 7-h 8-t
void recursion(char *dir, t_opt *options, bool hRead, int *dir_inside) {
    t_list *current_dir_files = NULL;
    DIR *current = opendir(dir);
    if (current) {
        struct dirent *temp = readdir(current);
        while (temp) {
            if (!(options -> a) && !(options -> f)) {
                if ((temp -> d_name)[0] != '.') {
                    mx_push_back(&current_dir_files, temp -> d_name);
                }
            }
            else {
                mx_push_back(&current_dir_files, temp -> d_name);
            }
            temp = readdir(current);
        }
    }
    if (!(options -> f)) {
        if (options -> t || options -> S) {
            if (options -> t && !options -> S) {
                sort_t(dir, current_dir_files);
            }
            if (options -> S && !options -> t) {
                sort_S(dir, current_dir_files);
            }
        }
        else {
            mx_sort_list(current_dir_files, cmp);
        }
    }
    
    t_list *dirs = NULL;
    t_list *current_files = NULL;
    t_list *temp = current_dir_files;
    while (temp) {
        struct stat buf;
        char *temp_str = mx_strjoin(dir, "/");
        char *path = mx_strjoin(temp_str, temp -> data);
        mx_strdel(&temp_str);
        stat(path, &buf);
        if (S_ISDIR(buf.st_mode)) {
            if (mx_strcmp(temp -> data, ".") != 0 && mx_strcmp(temp -> data, "..") != 0) {
                mx_push_back(&dirs, mx_strdup(path));
                (*dir_inside)++;
            }
        }   
        mx_push_back(&current_files, mx_strdup(path));
        mx_strdel(&path);
        temp = temp -> next;
    }
    
    //sort
    if (!(options -> f)) {
        if (options -> t || options -> S) {
            if (options -> t && !options -> S) {
                sort_t(dir, current_files);
            }
            if (options -> S && !options -> t) {
                sort_S(dir, current_files);
            }
        }
        else {
            mx_sort_list(current_files, cmp);
        }
    }

    if (options -> l) {
        char **files = NULL;    
        list_to_arr (current_files, &files);
        if (options -> r && !(options -> f)) { // reversed
            reverse(&files, mx_list_size(current_files));
        }
        char *tr_dir = mx_trim_slash(dir);
        if (mx_strcmp(tr_dir, ".") != 0 && mx_strcmp(tr_dir, "..") != 0) {
            mx_printstr(dir);
            mx_printstr(":\n");
        }
        mx_strdel(&tr_dir);
        bool print_total = true;
        if (!current_files) {
            print_total = false;
        }
        print_files_l(files, mx_list_size(current_files), dir, options -> G, print_total, true, hRead, options->o);
        if ((*dir_inside) > 1)
            mx_printchar('\n');
        for (int i = 0; i < mx_list_size(current_files); i++) {
            mx_strdel(&files[i]);
        }
        (*dir_inside)--;
        free(files);
        files = NULL;
        temp = dirs;
        while (temp) {
            recursion(temp -> data, options, hRead, dir_inside);
            temp = temp -> next;
        }
    }
    else {
        char **names = NULL;
        
        list_to_arr(current_dir_files, &names);
        if (options -> r && !(options -> f)) { // reversed
            reverse(&names, mx_list_size(current_dir_files));
        }
        char *tr_dir = mx_trim_slash(dir);
        if (mx_strcmp(tr_dir, ".") != 0 && mx_strcmp(tr_dir, "..") != 0) {
            mx_printstr(dir);
            mx_printstr(":\n");
        }
        mx_strdel(&tr_dir);
        if(options -> new_line || options -> m){
            if(options -> m){
                uls_print_m(names, mx_list_size(current_dir_files), dir, options -> G);
            }
            if(options -> new_line){
                uls_print_newline(names, mx_list_size(current_dir_files), dir, options -> G);
            }
        }
        else{
            if (options -> G) {
                uls_print_files_G(names, mx_list_size(current_dir_files), dir);
            }
            else {
                uls_print_files(names, mx_list_size(current_dir_files));
            }
        }
        if((*dir_inside) > 1)
            mx_printchar('\n');
        for (int i = 0; i < mx_list_size(current_dir_files); i++) {
            mx_strdel(&names[i]);
        }
        free(names);
        names = NULL;
        temp = dirs;
        (*dir_inside)--;
        while (temp) {
            recursion(temp -> data, options, false, dir_inside);
            temp = temp -> next;
        }
    }

    temp = dirs;
    while(temp) {
        if (malloc_size(temp -> data)) {
            free(temp -> data);
            temp -> data = NULL;
        }
        temp = temp -> next;
    }

    temp = current_files;
    while(temp) {
        if (malloc_size(temp -> data)) {
            free(temp -> data);
            temp -> data = NULL;
        }
        temp = temp -> next;
    }

    if (dirs) {
        mx_clear_list(&dirs);
    }

    if (current_dir_files) {
        mx_clear_list(&current_dir_files);
    }

    if (current_files) {
        mx_clear_list(&current_files);
    }
    closedir(current);
}
