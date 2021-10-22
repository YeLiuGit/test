//  CITS2002 Project 2 2021
//  Name(s):             Ye Liu
//  Student number(s):   22560064
#include  <stdio.h>
#include  <stdlib.h>
#include  <stdint.h>
#include  <sys/stat.h>
#include  <dirent.h>
#include  <string.h>
#include  <getopt.h>

#include "duplicates.h"

//initialize four int variables for default output or -a options only
int num_of_files = 0;
int num_of_bytes = 0;
int num_of_unique = 0;
int bytes_of_unique = 0;
//array of string store all file's pathname
char *path_names[HUGE_INT];
//flag for option a
bool aflag = false;
//identify is there is a duplicate file use for p option
bool find_dup = false;
//hashtable to store hash of each file
HASHTABLE *file_hash;
//store file name for f option, use to avoid print indicate file
char *f_filename = "";

//print stat i for if no options or only -a option
void print_stat(){
    printf("%i\n", num_of_files);
    printf("%i\n", num_of_bytes);
    printf("%i\n", num_of_unique);
    printf("%i\n", bytes_of_unique);
}

//usage function to print information when errors happens
void usage(){
    printf("Usage: duplicates-basic [options] dirname1\n");
    printf("where options are:\n");
    printf("-a		        mode for check all files, including hidden files beginning with '.'\n");
    printf("-A		        report if this program attempts advanced features\n");
    printf("-f filename     find and list all files same with file filename\n");
    printf("-h hash         find and list all files has same hash with hash\n");
    printf("-l		        list all duplicates found, one line per all relative pathnames\n");
    printf("-q	            duplicates executes quietly, test if there are any duplicate files\n");
    exit(EXIT_FAILURE);
}

//main function
int main(int argc, char* argv[]) {
    //argc < 2 means give no options and directory name
    if(argc < 2) {
        usage();  
        exit(EXIT_FAILURE);
    }

    //flags for some options
    bool fflag = false;
    bool hflag = false;
    bool qflag = false;
    bool lflag = false;
    //for getopt() function
    int opt;
    //determine options
    while((opt = getopt(argc, argv, OPTLIST)) != -1) {
        if(opt == 'a'){
            aflag = !aflag;
        }
        else if(opt == 'A'){
            exit(EXIT_FAILURE);
        }
        else if(opt == 'f'){
            fflag = !fflag;
        }
        else if(opt == 'h'){
            hflag = !hflag;
        }
        else if(opt == 'l'){
            lflag = !lflag;
        }
        else if(opt == 'q'){
            qflag = !qflag;
        }
        else{
            argc = -1;
        }
    }
    //in valid option finded
    if(argc < 0) {
        usage();  
        exit(EXIT_FAILURE);
    }
    //call other functions to store all pathnames in path_names[]
    scan_directory(argv[argc-1]);
    //call other functions to store file's hash value in HASHTABLE file_hash
    //also if detect one duplicates, give true value to find_dup
    write();
    //if there is only one option, -a, argc will equal to 2
    if(aflag){
        argc --;
    }
    //if there are no arguments, or only has -a option, print stats
    if(argc == 2){
        print_stat();
    }
    //if has -f option, convert file to hash and use compare to find all duplicate file
    if(fflag){
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
    //same above
    if(hflag){
        if (compare(optarg)){	
            exit(EXIT_SUCCESS);
        }
        else{
           exit(EXIT_FAILURE);
        }
    }
    //if has qflag
    if(qflag){
        if (find_dup){
            exit(EXIT_SUCCESS);
        }
        else{
            exit(EXIT_FAILURE);
        }
    }
    //lflag goes in the end, becsue other options will exit the program
    if(lflag){
        compare_all();
    }
    return 0;
}
