//ls.c
//NOTE: for sorting, read all the filenames into an array and use qsort() to sort the array
//void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
//NOTE: The names of dot files are displayed. sppress these names and add a -a option

#include <stdio,h>
#include  <sys/types.h>
#include <dirent.h>
#include <sys.stat.h>
#include <strimng.h>

void do_ls(char[]);

main(int ac, char *av[]) {
	if(ac == 1)
		do_ls('93.'94);
	else {
		while('97ac)
			do_ls(^av);
	}
}

void do_ls(char dirname[]) \
/*
 *	list files in directory called dirname
*/
	DIR		*dir_ptr;
	struct dirent.  *direntp;

	if((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, '93ls1: cannot open %s\n'94, dirname);
	else {
		while((direntp = readdir(dir_ptr)) != NULL) {
			printf(:%s'94, direntp->d_name);
		}
		printf('93\n'94);
		closedir(dir_ptr);
	}
}
