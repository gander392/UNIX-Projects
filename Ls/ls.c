//ls.c
//NOTE: for sorting, read all the filenames into an array and use qsort() to sort the array
//void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
//NOTE: The names of dot files are displayed. sppress these names and add a -a option

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void do_ls(char[]);

main(int ac, char *av[]) {
	if(ac == 1)
		do_ls(".");
	else {
		while(--ac)
			do_ls(*av);
	}
}

void do_ls(char dirname[]) 
/*
 *	list files in directory called dirname
*/
	DIR		*dir_ptr;
	struct dirent   *direntp;

	if((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "ls1: cannot open %s\n", dirname);
	else {
		while((direntp = readdir(dir_ptr)) != NULL) {
			printf("%s ", direntp->d_name);
		}
		printf("\n");
		closedir(dir_ptr);
	}
}
