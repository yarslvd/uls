#include "../inc/uls.h"
                                                                    //options[1], options[2], options[3], options[6], options[7]);
void uls_print_l(t_list *dir_list, t_list *file_list, t_opt *options) {//bool all, bool reversed, bool unsorted, bool almAll, bool hRead) {
    bool print_total = true;
    if (file_list) {
        if (dir_list) {
            print_total = false;
        }
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
        print_files_l(arr_files, mx_list_size(file_list), NULL, options -> G, false, false, options -> h, options -> o);

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
                    ////////////////////
                    if (!options -> a && !options -> f && !options -> A) {
                        if ((temp -> d_name)[0] != '.') {
                            char *dir_path = mx_strjoin(output -> data, "/");
                            mx_push_back(&dir_files, mx_strjoin(dir_path, temp -> d_name));
                            mx_strdel(&dir_path);
                        }
                    }
                    else {
                        if(options -> A){
                            if ((temp -> d_name[0] == '.' && mx_strlen(temp -> d_name) == 1) || (temp -> d_name[1] == '.')) {
                                
                            }
                            else{
                                char *dir_path = mx_strjoin(output -> data, "/");
                                mx_push_back(&dir_files, mx_strjoin(dir_path, temp -> d_name));
                                mx_strdel(&dir_path);
                            }
                        }
                        else{
                            char *dir_path = mx_strjoin(output -> data, "/");
                            mx_push_back(&dir_files, mx_strjoin(dir_path, temp -> d_name));
                            mx_strdel(&dir_path);
                        }
                    }
                    /////////////////////////////
                    temp = readdir(current);
                }
            }
            
            if(!options -> f){
                if (options -> t || options -> S) {
                    if (options -> t && !options -> S) {
                        sort_t(NULL, dir_files);
                    }
                    if (options -> S && !options -> t) {
                        sort_S(NULL, dir_files);
                    }
                }
                else {
                    mx_sort_list(dir_files, cmp);
                }
            }

            char **arr_files = NULL;
            list_to_arr(dir_files, &arr_files);
            if (options -> r && !options -> f) { // reversed
               reverse(&arr_files, mx_list_size(dir_files));
            }
            bool print_total = true;
            if (!dir_files) {
                print_total = false;
            }
            print_files_l(arr_files, mx_list_size(dir_files), NULL, options -> G,print_total, true, options -> h, options -> o);
            
            if (output -> next && output -> next -> data) {
                mx_printchar('\n');
            }
            for (int i = 0; i < mx_list_size(dir_files); i++) {
                mx_strdel(&arr_files[i]);
            }
            free(arr_files);
            arr_files = NULL;
            
            t_list *temp = dir_files;
            while (temp) {
                free(temp -> data);
                temp -> data = NULL;
                temp = temp -> next;
            }
            mx_clear_list(&dir_files);
            dir_files = NULL;
            closedir(current);
            output = output -> next;
        }
    }
}
