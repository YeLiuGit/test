#include <stdio.h>
#include <stdlib.h>

#include "duplicates.h"
//LIST *file_name = list_new();
//HASHTABLE *file_hash = hashtable_new();


void command(char com){
    printf("%c\n", com);
    LIST *file_name = list_new();
    file_name->next = NULL;
    HASHTABLE *file_hash = hashtable_new();
    file_hash[0] = file_name;
}

void argument(char* arg){
    printf("%s\n", arg);
}
