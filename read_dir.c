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
            scan_directory(dirname);
        }
        //find a file in current dirname
        else{
            path_names[num_of_files] = pathname;
            printf("found file%s\n", pathname);
            ++num_of_files;
        }
    }

//  CLOSE THE DIRECTORY
    closedir(dirp);
}

