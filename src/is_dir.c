#include "../inc/uls.h"

int is_dir(t_list *dir_list) {
    int count = 0;
    while (dir_list) {
        if (dir_list -> data) {
            count++;
        }
        dir_list = dir_list -> next;
    }

    return count;
}
