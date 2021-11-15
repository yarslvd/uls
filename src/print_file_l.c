#include "../inc/uls.h"

void print_files_l(char **files, int count_files, char* dir, bool color, bool print_total, bool is_dir, bool hRead, bool o) {
    struct stat buf;
    int total = 0;
    char ***output = (char ***)malloc(count_files * sizeof(char **));
    for (int i = 0; i < count_files; i++) {
        output[i] = (char **)malloc(7 * sizeof(char *));
    }
    
    for (int i = 0; i < count_files; i++) {
        
        stat(files[i], &buf);
        
        total += buf.st_blocks;
        struct passwd *owner = getpwuid(buf.st_uid);
        struct group *gr = getgrgid(buf.st_gid);
        
        char *time_temp = 4 + ctime((time_t *)&buf.st_mtime);
        char *time = mx_strndup(time_temp, mx_strlen(time_temp) - 9);
              
        output[i][0] = file_perm(files[i]);
        output[i][1] = mx_itoa(buf.st_nlink);
        output[i][2] = mx_strdup(owner -> pw_name);

        if (gr) {
            output[i][3] = mx_strdup(gr->gr_name);
        }
        else {
            output[i][3] = mx_itoa(buf.st_gid);
        }
        
        
        if (!hRead) {
            output[i][4] = mx_itoa(buf.st_size);
        }
        else {
            output[i][4] = mx_to_human_readable(buf.st_size);
        }
        output[i][5] = time;
        char *name = files[i];
        if (is_dir)
            while(mx_strchr(name, '/')) {
                name = mx_strchr(name, '/') + 1;
            }
        output[i][6] = mx_strdup(name);
    }
    
    if (print_total) {
        mx_printstr("total ");
        mx_printint(total);
        mx_printchar('\n');
    }
    for (int i = 0; i < count_files; i++) {
        mx_printstr(output[i][0]);
        for (int j = 1; j < 5; j++) { 
            for (int k = 0; k < max_len_strs_col(output, count_files, j) - mx_strlen(output[i][j]) + 1; k++) {
                mx_printchar(' ');
            }
            if(!o && j == 3){
                mx_printchar(' ');
            }     
            if (j == 4) {
                if (hRead) {
                    mx_printstr("  ");
                }
                else if (!o) {
                    mx_printchar(' ');
                }
            }
            if(o && j == 3) {
                //mx_printchar(' ');
            }
            else{
                mx_printstr(output[i][j]);
            }
        }
        mx_printchar(' ');
        mx_printstr(output[i][5]);
        mx_printchar(' ');
        if (color) {
            print_color(dir, output[i][6]);
        }
        mx_printstr(output[i][6]);
        mx_printchar('\n');
        if (color) {
            mx_printstr(WHT);
        }
    }
    
    for (int i = 0; i < count_files; i++) {
        for (int j = 0; j < 7; j++) {
            mx_strdel(&output[i][j]);
        }
        free(output[i]);
        output[i] = NULL;
    }
    free(output);
    output = NULL;
}
