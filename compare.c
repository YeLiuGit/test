#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "duplicates.h"

//find duplicate file by file's hash and hash of all files in HASHTABLE
bool compare(char *hash){
    //find same hash here
    if(hashtable_find(file_hash, hash)){
        int i = 0;
        //determine the index of duplicate file's pathname in path_name
        while(path_names[i] != NULL){
            if(strcmp(hash, strSHA2(path_names[i])) == 0){
                //if not the indicated file, print it
            	if(strcmp(path_names[i], f_filename) != 0){
            		printf("%s\n", path_names[i]);
            	}
            }
            ++i;
        }
        //decide exit success or failure
        return true;
    }
    else{
        return false;
    }
}

//find all duplicate file pairs
void compare_all(){
    int i = 0;
    //indicate a file is alreadly finded or not
    bool finded[num_of_files];
    while(path_names[i] != NULL){
        //file which havn't find duplicates
        if(!finded[i]){
            int j = 0;
            //use determine file in pathname path_name[i] has dup or not, if has, will print
            //"\n" before next loop, not print otherwise
            bool have_dup = false;
            while(path_names[j] != NULL){
                //file in same pathname is one file
                if(i != j && strcmp(strSHA2(path_names[i]), strSHA2(path_names[j])) == 0){
                    //print first file in duplicate pairs
                    if(!finded[i])  {printf("%s",path_names[i]);}
                    //won't print path_name[i] if find another duplicate file and mark all files has 
                    //duplicate as finded
                    finded[i] = true;
                    have_dup = true;
                    finded[j] = true;
                    //print a tab before pathname
                    printf("\t%s", path_names[j]);
                }
                ++j;
            }
            //if find duplicate, means some thing ptinted, print a "\n" here
            if(have_dup){printf("\n");}
        }
        ++i;
    }

}
