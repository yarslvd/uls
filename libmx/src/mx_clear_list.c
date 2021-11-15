#include "../inc/libmx.h"

void mx_clear_list(t_list **list) {
	if(*list == NULL || list == NULL) {
        return;
    }

    t_list *current = (*list);
    t_list *next;

    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
}

