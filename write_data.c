#include  <stdio.h>
#include  <stdlib.h>
#include  <dirent.h>
#include  <string.h>
#include  <stdbool.h>
#include  <sys/stat.h>

#include  "duplicates.h"

void scan_directory(char *dirname)        
{
    DIR             *dirp;
    struct dirent   *dp;
    
    if(aflag){
    	printf("flag!!!\n");
    }
    else{printf("noe flag\n");}
    
    dirp = opendir(dirname);
    if(dirp == NULL) {
        perror( dirname );
        exit(EXIT_FAILURE);
    }

    while((dp = readdir(dirp)) != NULL) {  
        struct stat     stat_info;
        char            pathname[MAXPATHLEN];
        char   *dots = "......";

        sprintf(pathname, "%s/%s", dirname, dp->d_name);
        //printf("%c\n",dp->d_name[0]);

        if(stat(pathname, &stat_info) != 0) {
            perror( pathname );
            exit(EXIT_FAILURE);
        }

        if(strcmp(dp->d_name,".")==0 || strcmp(dp->d_name,"..")==0){
            //did nothing here
        }
        
        else if(dp->d_name[0] == dots[0]){
        	if(aflag){
        	path_names[num_of_files] = strdup(pathname);
        	printf("found file %s\n", path_names[num_of_files]);
            	num_of_bytes = num_of_bytes + stat_info.st_size;
            	++num_of_files;
        	}
        }
        
        //find a directory in current dirname
        else if(dp->d_type == 4){
            //printf("found dir %s\n", pathname);
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

void write(){
    int i = 0;
    file_hash = hashtable_new();
    // read all files
    while(path_names[i] != NULL){
    //printf("filename in array: %s\n", path_names[i]);
        char *hash = strSHA2(path_names[i]);
        ++i;
        if(!hashtable_find(file_hash, hash)){
            hashtable_add(file_hash, hash);
            ++num_of_unique;
            struct stat unique_info;
            stat(path_names[i], &unique_info);
            bytes_of_unique = bytes_of_unique + unique_info.st_size;
        }
        else{
            find_dup = true;
        }
    }
}
