#include <stdio.h>
#include "linked_list.c"

int main(void) 
{
    LinkedList* list = init();

    if (isEmpty(list)){
        addFront(list, 12);
        printf("added 12 to the list");
    }
    else{
        printf("already something in the list");
    }

    freeList(list);
    return 0;
}
