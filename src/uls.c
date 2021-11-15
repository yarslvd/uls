#include "../inc/uls.h"
//options 0-l 1-a 2-r 3-f 4-1 5-R 6-A 7-h                       //options[1], options[2], options[3], options[4], options[6]);
void uls(t_list *dir_list, t_list *file_list, t_opt *options) {//bool all, bool reversed, bool unsorted, bool newline, bool almAll) {
    bool is_opt = true;
    if (!options) {
        is_opt = false;
        options = new_options();
    }
    
    if (file_list) {
        if(!options -> f){
            if (options -> t || options -> S) {
                if (options -> t && !options -> S) {
                    sort_t(NULL, file_list);
                }
                if (options -> S && !options -> t) {
                    sort_S(NULL, file_list);
                }
            }
            else {
                mx_sort_list(file_list, cmp);
            }
        }
        char **arr_files = NULL;
        list_to_arr(file_list, &arr_files);

        if (options -> r && !options -> f) { // reversed
            reverse(&arr_files, mx_list_size(file_list));
        }
        if (options -> G && !options -> new_line && !options -> m) {
            uls_print_files_G(arr_files, mx_list_size(file_list), NULL);
        }
        else {
            uls_print_files(arr_files, mx_list_size(file_list));
        }

        for (int i = 0; i < mx_list_size(file_list); i++) {
            mx_strdel(&arr_files[i]);
        }
        free(arr_files);
        arr_files = NULL;
        if (is_dir(dir_list)) {
            mx_printchar('\n');
        }
    }

    if(dir_list) {
        t_list *output = dir_list;
        
        while (output) {
            if (mx_list_size(dir_list) + mx_list_size(file_list) > 1 && output -> data) {
                mx_printstr(output -> data);
                mx_printstr(":\n");
            }
            if (!output -> data) {
                output = output -> next;
                continue;
            }
            t_list *dir_files = NULL;
            DIR *current = opendir(output -> data);
            if (current) {
                struct dirent *temp = readdir(current);
                while (temp) {
                    //////////////
                    if (!options -> a && !options -> f && !options -> A) {
                        if ((temp -> d_name)[0] != '.') {
                            mx_push_back(&dir_files, temp -> d_name);
                        }
                    }
                    else {
                        if(options -> A){
                            if ((temp -> d_name[0] == '.' && mx_strlen(temp -> d_name) == 1) || (temp -> d_name[1] == '.')) {
                                
                            }
                            else{
                                mx_push_back(&dir_files, temp -> d_name);
                            }
                        }
                        else{
                            mx_push_back(&dir_files, temp -> d_name);
                        }
                    }
                    /////////////////
                    temp = readdir(current);
                }
            }
            if (!dir_files) {
                if (output -> next && output -> next -> data) {
                    mx_printchar('\n');
                }
                output = output -> next;
                continue;
            }
            
            if(!options -> f){
                if (options -> t || options -> S) {
                    if (options -> t && !options -> S) {
                        sort_t(output -> data, dir_files);
                    }
                    if (options -> S && !options -> t) {
                        sort_S(output -> data, dir_files);
                    }
                }
                else {
                    mx_sort_list(dir_files, cmp);
                }
            }

            char **arr_files = NULL;
            list_to_arr(dir_files, &arr_files);

            if (options -> r && !options -> f) { // reversed sorting
                reverse(&arr_files, mx_list_size(dir_files));
            }

            if(options -> new_line || options -> m) {
                if(options -> m){
                    uls_print_m(arr_files, mx_list_size(dir_files), output -> data, options -> G);
                }
                if(options -> new_line){
                    uls_print_newline(arr_files, mx_list_size(dir_files), output -> data, options -> G);
                }
            }
            else{
                if (options -> G) {
                    uls_print_files_G(arr_files, mx_list_size(dir_files), output -> data);
                }
                else {
                    uls_print_files(arr_files, mx_list_size(dir_files));
                }
            }

            if (output -> next && output -> next -> data) {
                mx_printchar('\n');
            }
            for (int i = 0; i < mx_list_size(dir_files); i++) {
                mx_strdel(&arr_files[i]);
            }
            free(arr_files);
            arr_files = NULL;

            mx_clear_list(&dir_files);
            dir_files = NULL;
            closedir(current);
            output = output -> next;
        }
    }
    if (!is_opt) {
        free(options);
    }
}

