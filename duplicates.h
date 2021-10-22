//  CITS2002 Project 2 2021
//  Name(s):             Ye Liu
//  Student number(s):   22560064
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

#if	defined(__linux__)
extern	char	*strdup(char *string);
#endif

//declare global constant
//max num of files able to read
#define HUGE_INT 500000
//option list
#define OPTLIST "aAf:h:lq"
//max pathname length
#define MAXPATHLEN 5000

//-----------------data type and data structs-------------------
typedef struct _list {
    char           *string;
    struct _list   *next;
} LIST;

typedef LIST * HASHTABLE;

//-----------------global variables goes here-------------------
//initialized and explained in duplicates.c
extern int num_of_files;
extern int num_of_bytes;
extern int num_of_unique;
extern int bytes_of_unique;
extern bool aflag;
extern bool find_dup;

extern char *dir_name;
extern char *path_names[];
extern int dup[];
extern HASHTABLE *file_hash;
extern char *f_filename;

//-----------------global functions goes here-------------------
//functions abour list, use for build hashtable
//will build in hashtable.c
//creat a new LIST
extern	LIST	*list_new(void);
//add a string to the list
extern	LIST	*list_add(  LIST *list, char *newstring);
//determine is string wanted in the list
extern	bool	 list_find (LIST *list, char *wanted);

//-------------------------------------------------------------
//functions about hashtable
//will build in hashtable.c
extern	HASHTABLE	*hashtable_new(void);

//  ADD A NEW STRING TO A GIVEN HASHTABLE
extern	void		 hashtable_add( HASHTABLE *, char *string);

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
extern	bool		 hashtable_find(HASHTABLE *, char *string);

//-------------------------------------------------------------
//read directory and write file_hash to HASHTABLE, will build in write_data.c
extern void scan_directory(char *dirname);
extern void write(void);
//find and print message about duplicate files, will build in compare.c
extern bool compare(char *hash);
extern void compare_all();
//hash a file to a string
extern char* strSHA2(char* filename);



