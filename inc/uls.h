#ifndef ULS_H
#define ULS_H

#include "../libmx/inc/libmx.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/xattr.h>
#include <locale.h>
#include <string.h>

#define RED  "\x1B[31m"
#define BLU  "\x1B[34m"
#define WHT  "\x1B[0m"

//options 0-l 1-a 2-r 3-f 4-1 5-R 6-A 7-h 8-t
typedef struct s_opt {
    bool l;
    bool a;
    bool r;
    bool f;
    bool new_line;
    bool R;
    bool A;
    bool h;
    bool t;
    bool S;
    bool m;
    bool G;
    bool o;
}              t_opt;

char opt_validation(char *argv);
void argv_parser(int argc, char **argv, t_list** opt_list, t_list** dir_list, t_list **file_list);

void uls(t_list *dir_list, t_list *file_list, t_opt *options);//bool all, bool reversed, bool unsorted, bool newline, bool almAll);
void uls_print_files(char **arr, int count_files);
void uls_print_newline(char **arr, int count_files, char *dir, bool color);
void uls_print_m(char **arr, int count_files, char *dir, bool color);
void uls_print_files_G(char **arr, int count_files, char *dir);
void uls_opt(t_list *opt_list, t_list *dir_list, t_list *file_list);
t_opt *new_options();
void uls_print_l(t_list *dir_list, t_list *file_list, t_opt *options);//bool all, bool reversed, bool unsorted, bool almAll, bool hRead);

void recursion(char *dir, t_opt *options, bool hRead, int *dir_inside);
void print_files_l(char **files, int count_files, char* dir, bool color, bool print_total, bool is_dir, bool hRead, bool m);
void print_tab(int len, int count_tabs);

void list_to_arr(t_list *list, char ***arr);
int max_len_strs(char **s_arr, int size, int start);
int max_len_strs_col(char ***s_arr, int size, int col);

bool cmp(void *a, void *b);
bool cmp_r(void *a, void *b);
void sort_t(char *dir, t_list* files);
void sort_S(char *dir, t_list* files);
void reverse(char ***arr, int size);

int is_dir(t_list *dir_list);
char *get_acl_str(char *file, char *dst);
char *file_perm(char *file);
void print_color(char *dir, char *file);

char *mx_to_human_readable(int size);

#endif
