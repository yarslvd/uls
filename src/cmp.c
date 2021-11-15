#include "../inc/uls.h"

bool cmp(void *a, void *b) {
    if (mx_strcmp((char *)a, (char *)b) > 0) {
        return true;
    }

    return false;
}

bool cmp_r(void *a, void *b) {
    if (mx_strcmp((char *)a, (char *)b) < 0) {
        return true;
    }

    return false;
}

void reverse(char ***arr, int size) {
    int j = size - 1;
    for (int i = 0; i < size / 2; i++) {
        char *temp = (*arr)[i];
        (*arr)[i] = (*arr)[j];
        (*arr)[j] = temp;
        j--;
    }
}

void sort_t(char *dir, t_list* files) {
    struct stat buf_i;
    struct stat buf_j;
    for (t_list *temp_i = files; temp_i != NULL; temp_i = temp_i -> next) {
        for (t_list *temp_j = files; temp_j -> next != NULL; temp_j = temp_j -> next) {
			char *temp_path = NULL;
            if (dir)
                temp_path = mx_strjoin(dir,"/");
            char *path_i = mx_strjoin(temp_path, temp_j -> data);
            char *path_j = mx_strjoin(temp_path, temp_j -> next -> data);
            mx_strdel(&temp_path);
            stat(path_i, &buf_i);
            stat(path_j, &buf_j);
            if (buf_i.st_mtime == buf_j.st_mtime) {
                if (buf_i.st_mtimespec.tv_nsec == buf_j.st_mtimespec.tv_nsec) {
                    if (mx_strcmp(path_i, path_j) > 0) {
                        void *b = temp_j -> data;
                        temp_j -> data = temp_j -> next -> data; 
                        temp_j -> next -> data = b; 
                    }
                }
                else if (buf_i.st_mtimespec.tv_nsec < buf_j.st_mtimespec.tv_nsec) {
                   void *b = temp_j -> data;
                   temp_j -> data = temp_j -> next -> data; 
                   temp_j -> next -> data = b; 
                }
            }
            else if (buf_i.st_mtime < buf_j.st_mtime) {
				void *b = temp_j -> data;
				temp_j -> data = temp_j -> next -> data; 
				temp_j -> next -> data = b; 
			}
            mx_strdel(&path_j);
            mx_strdel(&path_i);
        }
	}
}

void sort_S(char *dir, t_list* files) {
    struct stat buf_i;
    struct stat buf_j;
    for (t_list *temp_i = files; temp_i != NULL; temp_i = temp_i -> next) {
        for (t_list *temp_j = files; temp_j -> next != NULL; temp_j = temp_j -> next) {
			char *temp_path = NULL;
            if (dir)
                temp_path = mx_strjoin(dir,"/");
            char *path_i = mx_strjoin(temp_path, temp_j -> data);
            char *path_j = mx_strjoin(temp_path, temp_j -> next -> data);
            mx_strdel(&temp_path);
            stat(path_i, &buf_i);
            stat(path_j, &buf_j);
            if (buf_i.st_size == buf_j.st_size) {
                if (mx_strcmp(path_i, path_j) > 0) {
                    void *b = temp_j -> data;
                    temp_j -> data = temp_j -> next -> data; 
                    temp_j -> next -> data = b; 
                }
            }
            else if (buf_i.st_size < buf_j.st_size) {
				void *b = temp_j -> data;
				temp_j -> data = temp_j -> next -> data; 
				temp_j -> next -> data = b; 
			}
            mx_strdel(&path_j);
            mx_strdel(&path_i);
        }
	}
}
