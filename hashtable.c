#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

#include "duplicates.h"

LIST *list_new(void)
{
    return NULL;
}

bool list_find(LIST *list, char *wanted)
{
    while(list != NULL) {
	    if(strcmp(list->string, wanted) == 0) {
	        return true;
	    }
	    list = list->next;
    }
    return false;
}

LIST *list_new_item(char *newstring)
{
    LIST *new       = calloc(1, sizeof(LIST) );
    CHECK_ALLOC(new);
    new->string     =  strdup(newstring);
    CHECK_ALLOC(new->string);
    new->next       =  NULL;
    return new;
}

LIST *list_add(LIST *list, char *newstring)
{
    if(list_find(list, newstring)) {            // only add each item once
        return list;
    }
    else {                                      // add new item to head of list
        LIST *new   = list_new_item(newstring);
        new->next   = list;
        return new;
    }
}

//-------------------------------------------------------------

uint32_t hash_string(char *string)
{
    uint32_t hash = 0;

    while(*string != '\0') {
        hash = hash*33 + *string;
        ++string;
    }
    return hash;
}

HASHTABLE *hashtable_new(void)
{
    HASHTABLE   *new = calloc(HUGE_INT, sizeof(LIST *));

    CHECK_ALLOC(new);
    return new;
}

void hashtable_add(HASHTABLE *hashtable, char *string)
{
    uint32_t h   = hash_string(string) % HUGE_INT;    // choose list

    hashtable[h] = list_add(hashtable[h], string);
}

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
bool hashtable_find(HASHTABLE *hashtable, char *string)
{
    uint32_t h	= hash_string(string) % HUGE_INT;     // choose list

    return list_find(hashtable[h], string);
}