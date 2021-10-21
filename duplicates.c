#include  <stdio.h>
#include  <stdlib.h>
#include  <stdbool.h>
#include  <stdint.h>
#include  <sys/stat.h>
#include  <sys/types.h>
#include  <dirent.h>
#include  <string.h>
#include  <getopt.h>

#include "duplicates.h"

int num_of_files = 0;
int num_of_bytes = 0;
int num_of_dup = 0;
int bytes_of_dup = 0;
char *path_names[HUGE_INT];
bool aflag = false;


int main(int argc, char* argv[]) {

    int opt;

    HASHTABLE *file_hash = hashtable_new();

    printf("dir name is %s\n", argv[argc-1]);
    scan_directory(argv[argc-1]);
    write(path_names[]);

    while((opt = getopt(argc, argv, OPTLIST)) != -1) {
        if(opt == 'a'){
            aflag = !aflag;
        }
        else if(opt == 'A'){
            exit(EXIT_FAILURE);
        }
        else if(opt == 'f'){
            char *file_hash = strSHA2(optarg);
            compare(file_hash);
        }
        else if(opt == 'h'){
            compare(optarg);
        }
        else if(opt == 'l'){
            compare_all();
        }
        else if(opt == 'q'){
            if (compare_all()){
                exit(EXIT_FAILURE);
            }
            else{
                exit(EXIT_SUCCESS);
            }
        }
        else{
            argc = -1;
        }
    }
    if(argc < 0) {
        printf("unexpected option\n");  
        exit(EXIT_FAILURE);
    }

    printf("num_of_file:%i\n", num_of_files);
    printf("num_of_bytes:%i\n", num_of_bytes);
    printf("num_of_dup:%i\n", num_of_dup);
    printf("bytes_of_dup:%i\n", bytes_of_dup);
}
