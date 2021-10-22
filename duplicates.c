#include  <stdio.h>
#include  <stdlib.h>
#include  <stdint.h>
#include  <sys/stat.h>
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
HASHTABLE *file_hash;
char *f_filename = "";

void print_stat(){
    printf("num_of_file:%i\n", num_of_files);
    printf("num_of_bytes:%i\n", num_of_bytes);
    printf("num_of_unique file:%i\n", num_of_unique);
    printf("bytes_of_unique:%i\n", bytes_of_unique);
}

void usage(){
    printf("some error happens\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        usage();  
        exit(EXIT_FAILURE);
    }

    bool lflag = false;
    int opt;

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
        struct stat stat_info;
            if(stat(optarg, &stat_info) != 0) {
            perror( optarg );
            exit(EXIT_FAILURE);
        }
        f_filename = optarg;
            char *hash = strSHA2(optarg);
            if (compare(hash)){
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
    
    if(aflag){
        argc --;
    }
    
    if(argc < 0) {
        usage();  
        exit(EXIT_FAILURE);
    }

    if(argc == 2){
        print_stat();
    }

    if(lflag){
        compare_all();
    }
    return 0;
}
