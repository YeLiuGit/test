#include <stdio.h>
#include <stdlib.h>

#include "duplicates.h"

bool compare(char *hash){
    if(hashtable_find(file_hash, hash){
        int i = 0;
        while(path_names[i] != NULL){
            if(hash == strSHA2(path_names[i])){
                printf("%s\n", path_names[i]);
            }
        }
        return true
    }
    else{
        return false;
    }
}

void compare_all(){
    int i = 0;
    bool finded[num_of_files];
    while(path_names[i] != NULL){
        if(!finded[i]){
            int j = 0;
            while(path_names[j] != NULL){
                if(i != j && hash == strSHA2(path_names[j]) ){
                    if(!finded[i])  printf("%s",path_names[i]);
                    finded[i] = true;
                    finded[j] = true;
                    printf("\t%s", path_names[j]);
                }
                ++j;
            }
        }
        ++i;
    }
}