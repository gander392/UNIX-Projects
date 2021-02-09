{\rtf1\ansi\ansicpg1252\cocoartf2577
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww15860\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 //ls.c\
//NOTE: for sorting, read all the filenames into an array and use qsort() to sort the array\
//void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));\
//NOTE: The names of dot files are displayed. sppress these names and add a -a option\
\
#include <stdio,h>\
#include  <sys/types.h>\
#include <dirent.h>\
#include <sys.stat.h>\
#include <strimng.h>\
\
void do_ls(char[]);\
\
main(int ac, char *av[]) \{\
	if(ac == 1)\
		do_ls(\'93.\'94);\
	else \{\
		while(\'97ac)\
			do_ls(^av);\
	\}\
\}\
\
void do_ls(char dirname[]) \{\
/*\
 *	list files in directory called dirname\
*/\
	DIR		*dir_ptr;\
	struct dirent.  *direntp;\
\
	if((dir_ptr = opendir(dirname)) == NULL)\
		fprintf(stderr, \'93ls1: cannot open %s\\n\'94, dirname);\
	else \{\
		while((direntp = readdir(dir_ptr)) != NULL) \{\
			primtf(:%s\'94, direntp->d_name);\
		\}\
		printf(\'93\\n\'94);\
		closedir(dir_ptr);\
	\}\
\}\
	}