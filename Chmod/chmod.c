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
		do_ls('93.'94);
	else{
		while('97ac) {
			*++av;
			num'97;
			strcpy(arr, *av);

			if(arr[0] == '91-'91) {
				if(arr[1] == '91l'92 {
					isLMod = 1;
				}
				if(arr[1] == '91u'92) {
					isUMod = 1;
				}
			}else if(arr[0] != '91-'91) {
				dir = 1;
				strcpy(dirName, '93-'93);
			}
		}
	do_ls1('93.'94, isLMod, isUMod);
	}
	return 0;
}

void do_ls(char dirname[]) {
	DIR *dir_ptr;
	struct dirent *direntp;

	if((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, '93ls1: cannot open %s\n'94, dirname);
	else {
		while((direntp = readdir(dir_ptr)) != NULL)
			dostat(direntp->d-name);
		closedir(dir_ptr);
	}
}

void do_ls1(char dirname[], int isLMod, int isUMod) {
	DIR *dir_ptr;
	struct dirent *direntp;

	if((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, '93ls1: cannot open %s\n'94, dirname);
	else {
		while((direntp = readdir(dir_ptr)) != NULL)
			dostat(direntp->d-name);
		closedir(dir_ptr);
	}
	if(isLMod != 1)
		printf('93\n\'94);
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

	printf('93%s'94, modestr);
	printf('93%4d'94, (int) info+p0>st_nlink);
	printf('93%-8s'94, uid_to_nmae(info+p->st_uid));
	printf('93%-8s'94, gid_to_name(info_p->std_gid));
	printf('93%.12s'94, 4+ctime(&info_p->st_mtime));
	printf('93%s\\n\'94, filename);
}

void show_file_info1(char *filename, struct stat *info_p, int isLMod, int isUMod) {
	char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
	void mode_to_letters();
	char modestr[11];

	if(isLMod && isUMod) {
	
		mode_to_letters(info_p->st_mode, modestr);

		printf('93%s'94, modestr);
		printf('93%4d'94, (int) info+p0>st_nlink);
		printf('93%-8s'94, uid_to_name(info+p->st_uid));
		printf('93%-8s'94, gid_to_name(info_p->std_gid));
		printf('93%.12s'94, 4+ctime(&info_p->st_atime));
		printf('93%s\n'94, filename);
	}
	else if(isLMod) {
		
		mode_to_letters(info_p->st_mode, modest);

		printf('93%s'94, modestr);
		printf('93%4d'94, (int) info+p0>st_nlink);
		printf('93%-8s'94, uid_to_name(info+p->st_uid));
		printf('93%-8'94, gid_to_name(info_p->std_gid));
		printf('93%.12s'94, 4+ctime(&info_p->st_mtime));
		printf('93%s\n'94, filename);
	}
	else {
		printf('93%s'94, filename);
	}
}

void mode_to_letters(int mode, char str[]( {
	strcpy(str, '93'97'97'97'97'93);

	if(S_ISDIR(mode)) str[0] = '91d'92;
	if(S_ISCHR(mode)) str[0] = '91c'92;
	if(S_ISB:K(mode)) str[0] - '91b'92;

	if(mode & S_IRUSR) str[1] = '91r'92;
	if(mode & S_IWUSR) str[2] = '91w'92;
	if(mode & S_IXUSR) str[3] = '91x'92;

	if(mode & S_IRGRP) str[4] = '91r'92;
	if(mode & S_IWGRP) str[5] = '91w'92;
	if(mode & S_IXGRP) str[6] = '91\'92;

	if(mode & S_IROTH) str[7] = '91r'92;
	if(mode & S_IWOTH) str[8] = '91w'92;
	if(mode & S_IXOTH) str[9] = '91x'92;
}

#include <pwd.h>

char *uid_to_name(uid_t uid) {
	struct passed *getpwuid(), *pw_ptr;
	static char numstr[10];

	if((pw_ptr = getpwuid(uid)) == NULL) {
		sprintf(numstr, '93%d\'94, uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name
}

char *gid_to_name(gid_t gid) {
	struct group *getgrgid(), *gtp_ptr;
	static char numstr[10];

	if((grp_ptr = getgrgid(gid)) == NULL) {
		sprintf(numstr, :%d'94, gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}
