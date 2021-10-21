#include  <stdio.h>
#include  <stdlib.h>
#include  <dirent.h>
#include  <string.h>
#include  <sys/stat.h>

#include  "duplicates.h"

void scan_directory(char *dirname)        
{
    DIR             *dirp;
    struct dirent   *dp;

    dirp = opendir(dirname);
    if(dirp == NULL) {
        perror( dirname );
        exit(EXIT_FAILURE);
    }

    while((dp = readdir(dirp)) != NULL) {  
        struct stat     stat_info;
        char            pathname[MAXPATHLEN];

        sprintf(pathname, "%s/%s", dirname, dp->d_name);

        if(stat(pathname, &stat_info) != 0) {
            perror( pathname );
            exit(EXIT_FAILURE);
        }

        if(strcmp(dp->d_name,".")==0 || strcmp(dp->d_name,"..")==0){
            //did nothing here
        }
        //find a directory in current dirname
        else if(dp->d_type == 4){
            printf("found dir %s\n", pathname);
            scan_directory(pathname);
        }
        //find a file in current dirname
        else{
            path_names[num_of_files] = strdup(pathname);
            printf("found file %s\n", path_names[num_of_files]);
            num_of_bytes = num_of_bytes + stat_info.st_size;
            ++num_of_files;
        }
    }
//  CLOSE THE DIRECTORY
    closedir(dirp);
}

void write(char* paths[]){
    int i = 0;
    HASHTABLE *file_hash = hashtable_new();
    // read all files
    while(paths[i] != NULL){
    //printf("filename in array: %s\n", path_names[i]);
        char *hash = strSHA2(paths[i]);
        ++i;
        if(hashtable_find(file_hash, hash)){
            printf("working before a if\n");
            ++num_of_dup;
            struct stat dup_info;
            stat(paths[i], &dup_info);
            bytes_of_dup = bytes_of_dup + dup_info.st_size;
            printf("working after a if\n");
        }
        else{
            printf("working before a else\n");
            hashtable_add(file_hash, hash);
            printf("working after a else\n");
        }
    }
}
