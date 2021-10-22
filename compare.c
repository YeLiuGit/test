#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "duplicates.h"

bool compare(char *hash){
    if(hashtable_find(file_hash, hash)){
        int i = 0;
        //printf("hash is:%s\n", hash);
        while(path_names[i] != NULL){
        //printf("anhash is:%s\n", strSHA2(path_names[i]));
            if(strcmp(hash, strSHA2(path_names[i])) == 0){
            	if(strcmp(path_names[i], f_filename) != 0){
            		printf("%s\n", path_names[i]);
            	}
                
            }
            ++i;
        }
        return true;
    }
    else{
        return false;
    }
}

void compare_all(){
//printf("compared\n");
    int i = 0;
    bool finded[num_of_files];
    while(path_names[i] != NULL){
        if(!finded[i]){
            int j = 0;
            bool have_dup = false;
            while(path_names[j] != NULL){
                if(i != j && strcmp(strSHA2(path_names[i]), strSHA2(path_names[j])) == 0){
                    if(!finded[i])  {printf("%s",path_names[i]);}
                    finded[i] = true;
                    have_dup = true;
                    finded[j] = true;
                    printf("\t%s", path_names[j]);
                }
                ++j;
            }
            if(have_dup){printf("\n");}
        }
        ++i;
    }

}
