#include  <stdio.h>
#include  <stdlib.h>
#include  <dirent.h>
#include  <string.h>
#include  <stdbool.h>
#include  <sys/stat.h>

#include  "duplicates.h"

//travse all files and sub-directorys in directory dirname recursively, and store
//all file's pathname in global variable path_names[]
//partial copy form solution of workshop 8
void scan_directory(char *dirname)        
{
    DIR             *dirp;
    struct dirent   *dp;
    //open target directory
    dirp = opendir(dirname);
    //if directory not able to be opened, send message to stderr and terminated
    if(dirp == NULL) {
        perror( dirname );
        exit(EXIT_FAILURE);
    }
    //read all files and directorys until the end
    while((dp = readdir(dirp)) != NULL) {
        //use for get size of file for doing stats 
        struct stat     stat_info;
        //pathname will stored
        char            pathname[MAXPATHLEN];
        //use for detect file begin with "."
        char   *dots = "......";
        //build current pathname
        sprintf(pathname, "%s/%s", dirname, dp->d_name);
        //if target file cannot open, send message to stderr and terminated
        if(stat(pathname, &stat_info) != 0) {
            perror( pathname );
            exit(EXIT_FAILURE);
        }
        //find current directory or parent directory
        if(strcmp(dp->d_name,".")==0 || strcmp(dp->d_name,"..")==0){
            //did nothing here
        }
        //file name begin with dot
        else if(dp->d_name[0] == dots[0]){
            //if has option -a, add pathname to path_name[]
        	if(aflag){
                //if find a directory begin with "."
        	    if(dp->d_type == 4){
        	    	scan_directory(pathname);
        	    }
        	    else{
                //if find a file
        		    path_names[num_of_files] = strdup(pathname);
            		//calculate num_of_files and num_of_bytes here
            		num_of_bytes = num_of_bytes + stat_info.st_size;
            		++num_of_files;
            	    }
        	}
        }
        //find a directory in current dirname
        else if(dp->d_type == 4){
            //read sub dir
            scan_directory(pathname);
        }
        //find a file in current dirname
        else{
            path_names[num_of_files] = strdup(pathname);
            //calculate num_of_files and num_of_bytes here
            num_of_bytes = num_of_bytes + stat_info.st_size;
            ++num_of_files;
        }
    }
//  CLOSE THE DIRECTORY
    closedir(dirp);
}

//write hash of all finded file into HASHTABLE
void write(){
    int i = 0;
    //create HASHTABLE here
    file_hash = hashtable_new();
    // read all files
    while(path_names[i] != NULL){
        //hash it
        char *hash = strSHA2(path_names[i]);
        
        //not duplicates files, add hash into HASHTABLE
        if(!hashtable_find(file_hash, hash)){
            hashtable_add(file_hash, hash);
            //calculate num_of_unique file and bytes_of_unique here
            ++num_of_unique;
            struct stat unique_info;
            stat(path_names[i], &unique_info);
            bytes_of_unique = bytes_of_unique + unique_info.st_size;
        }
        else{
            //this global use for option -q
            find_dup = true;
        }
        ++i;
    }
}
