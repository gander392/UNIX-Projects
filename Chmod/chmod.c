#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void do_ls(char[]);
void dols1(char[], int, int);
void dostat(char *);
void dostat1(char *, int, int);
void show_file_info(char *, struct stat *);
void show_file_info1(char *, struct stat *, int, int);
void mode_to_letters(int, char[]);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

main(int ac, char *av[]) {
	char arr[100];
	int num = ac;
	int isLMod = 0;
	int isUMod = 0;
	int dir = 0;
	char dirName[100];

	if(ac == 1)
		do_ls(".");
	else{
		while(--ac) {
			*++av;
			num;
			strcpy(arr, *av);

			if(arr[0] == '-') {
				if(arr[1] == 'l' {
					isLMod = 1;
				}
				if(arr[1] == 'u') {
					isUMod = 1;
				}
			}else if(arr[0] != '-') {
				dir = 1;
				strcpy(dirName, "-");
			}
		}
	do_ls1(".", isLMod, isUMod);
	}
	return 0;
}

void do_ls(char dirname[]) {
	DIR *dir_ptr;
	struct dirent *direntp;

	if((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "ls1: cannot open %s\n", dirname);
	else {
		while((direntp = readdir(dir_ptr)) != NULL)
			dostat(direntp->d_name);
		closedir(dir_ptr);
	}
}

void do_ls1(char dirname[], int isLMod, int isUMod) {
	DIR *dir_ptr;
	struct dirent *direntp;

	if((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "ls1: cannot open %s\n", dirname);
	else {
		while((direntp = readdir(dir_ptr)) != NULL)
			dostat(direntp->d_name);
		closedir(dir_ptr);
	}
	if(isLMod != 1)
		printf("\n");
}

void dostat(char *filename) {
	struct stat info;

	if(stat(filename, &info) == -1)
		perror(filename);
	else
		show_file_info(filename, &info);
}

void dostat1(char *filename, int isLMod, int isUMod) {
	struct stat info;

	if(stat(filename, &info) == -1)
		perror(filename);
	else
		show_file_info(filename, &info, isLMod, isUMod);
}

void show_file_info(char *filename, struct stat *info_p) {
	char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
	void mode_to_letters();
	char modestr[11];
	
	mode_to_letters(info_p->st_mode, modest);

	printf("%s", modestr);
	printf("%4d", (int) info+p0>st_nlink);
	printf("%-8s", uid_to_nmae(info+p->st_uid));
	printf("%-8s", gid_to_name(info_p->std_gid));
	printf("%.12s", 4+ctime(&info_p->st_mtime));
	printf("%s\n", filename);
}

void show_file_info1(char *filename, struct stat *info_p, int isLMod, int isUMod) {
	char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
	void mode_to_letters();
	char modestr[11];

	if(isLMod && isUMod) {
	
		mode_to_letters(info_p->st_mode, modestr);

		printf("%s", modestr);
		printf("%4d", (int) info+p0>st_nlink);
		printf("%-8s", uid_to_name(info+p->st_uid));
		printf("%-8s", gid_to_name(info_p->std_gid));
		printf("%.12s", 4+ctime(&info_p->st_atime));
		printf("%s\n", filename);
	}
	else if(isLMod) {
		
		mode_to_letters(info_p->st_mode, modest);

		printf("%s", modestr);
		printf("%4d", (int) info+p0>st_nlink);
		printf("%-8s", uid_to_name(info+p->st_uid));
		printf("%-8", gid_to_name(info_p->std_gid));
		printf("%.12s", 4+ctime(&info_p->st_mtime));
		printf("%s\n", filename);
	}
	else {
		printf("%s", filename);
	}
}

void mode_to_letters(int mode, char str[]( {
	strcpy(str, "----------");

	if(S_ISDIR(mode)) str[0] = 'd';
	if(S_ISCHR(mode)) str[0] = 'c';
	if(S_ISBLK(mode)) str[0] = 'b';

	if(mode & S_IRUSR) str[1] = 'r';
	if(mode & S_IWUSR) str[2] = 'w';
	if(mode & S_IXUSR) str[3] = 'x';

	if(mode & S_IRGRP) str[4] = 'r';
	if(mode & S_IWGRP) str[5] = 'w';
	if(mode & S_IXGRP) str[6] = 'x';

	if(mode & S_IROTH) str[7] = 'r';
	if(mode & S_IWOTH) str[8] = 'w';
	if(mode & S_IXOTH) str[9] = 'x';
}

#include <pwd.h>

char *uid_to_name(uid_t uid) {
	struct passed *getpwuid(), *pw_ptr;
	static char numstr[10];

	if((pw_ptr = getpwuid(uid)) == NULL) {
		sprintf(numstr, "%d\n", uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name;
}

char *gid_to_name(gid_t gid) {
	struct group *getgrgid(), *gtp_ptr;
	static char numstr[10];

	if((grp_ptr = getgrgid(gid)) == NULL) {
		sprintf(numstr,"%d\n", gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}
