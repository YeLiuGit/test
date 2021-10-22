#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

#if	defined(__linux__)
extern	char	*strdup(char *string);
#endif

//declare global constant
#define HUGE_INT 10000
#define OPTLIST "aAf:h:lq"
#define MAXPATHLEN 2000

//-----------------data type and data structs-------------------
typedef struct _list {
    char           *string;
    struct _list   *next;
} LIST;

typedef LIST * HASHTABLE;

//-----------------global variables goes here-------------------
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
//functions abour list
extern	LIST	*list_new(void);

extern	LIST	*list_add(  LIST *list, char *newstring);

extern	bool	 list_find (LIST *list, char *wanted);

//-------------------------------------------------------------
//functions about hashtable
extern	HASHTABLE	*hashtable_new(void);

//  ADD A NEW STRING TO A GIVEN HASHTABLE
extern	void		 hashtable_add( HASHTABLE *, char *string);

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
extern	bool		 hashtable_find(HASHTABLE *, char *string);

//-------------------------------------------------------------
extern void scan_directory(char *dirname);
extern void write(void);
extern bool compare(char *hash);
extern void compare_all();
extern char* strSHA2(char* filename);



