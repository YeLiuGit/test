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
int num_of_unique = 0;
int bytes_of_unique = 0;
char *path_names[HUGE_INT];
int dup[HUGE_INT];
bool aflag = false;
bool find_dup = false;

void print_stat(){
    printf("num_of_file:%i\n", num_of_files);
    printf("num_of_bytes:%i\n", num_of_bytes);
    printf("num_of_unique file:%i\n", num_of_files - num_of_unique);
    printf("bytes_of_unique:%i\n", num_of_bytes - bytes_of_unique);
}

void usage(){
    printf("some error happens\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    bool lflag = false;
    int opt;

    printf("dir name is %s\n", argv[argc-1]);
    scan_directory(argv[argc-1]);
    write();

    while((opt = getopt(argc, argv, OPTLIST)) != -1) {
        if(opt == 'a'){
            aflag = !aflag;
        }
        else if(opt == 'A'){
            exit(EXIT_FAILURE);
        }
        else if(opt == 'f'){
            char *file_hash = strSHA2(optarg);
            if (compare(file_hash)){
                exit(EXIT_SUCCESS);
            }
            else{
                exit(EXIT_FAILURE);
            }
        }
        else if(opt == 'h'){
            if (compare(optarg)){
                exit(EXIT_SUCCESS);
            }
            else{
                exit(EXIT_FAILURE);
            }
        }
        else if(opt == 'l'){
            lflag = !lflag;
        }
        else if(opt == 'q'){
            if (find_dup){
                exit(EXIT_SUCCESS);
            }
            else{
                exit(EXIT_FAILURE);
            }
        }
        else{
            argc = -1;
        }
    }
    if(argc < 2) {
        usage();  
        exit(EXIT_FAILURE);
    }

    if(argc == 2 || aflag){
        print_stat();
    }

    if(lflag){
        compare_all();
    }
}
