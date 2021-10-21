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

num_of_files = 0;
num_of_bytes = 0;
num_of_unique = 0;
bytes_of_unique = 0;
char *path_names[HUGE_INT];


int main(int argc, char* argv[]) {

    int opt;

    HASHTABLE *file_hash = hashtable_new();


    while((opt = getopt(argc, argv, OPTLIST)) != -1) {
        if(opt == 'a'){
            command(opt);
        }
        else if(opt == 'A'){
            exit(EXIT_FAILURE)
        }
        else if(opt == 'f'){
            command(opt);
            argument(optarg);
        }
        else if(opt == 'h'){
            command(opt);
            argument(optarg);
        }
        else if(opt == 'l'){
            command(opt);
        }
        else if(opt == 'q'){
            command(opt);
        }
        else{
            argc = -1;
        }
    }
    if(argc < 0) {
        printf("unexpected option\n");  
        exit(EXIT_FAILURE);
    }
    
    printf("dir name is %s\n", argv[optind]);
    scan_directory(argv[optind]);
    //printf("the first file path is %s\n", path_names[0]);
}
