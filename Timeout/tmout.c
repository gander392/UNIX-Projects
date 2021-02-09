{\rtf1\ansi\ansicpg1252\cocoartf2577
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww15860\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 //timeout.c\
\
#include <termios.h>\
#include <stdio.h>\
#include <ctype.h>\
#include <stddef.h>\
#include <stdlib.h>\
#include <string.h>\
#include <unistd.h>\
#include <utmp.h>\
#include <fcntl.h>\
#include <time.h>\
#include <sys/types.h>\
#include <dirent.h>\
#include <sys/stat.h>\
\
#ifndef FD\
#define FD 0\
#endif\
\
#define DEL 127\
\
int check_speed(struct termios *, char *);\
int check_spec(struct termios *, char *, char *);\
int check_setting(struct termios *, char *);\
void set_args(struct termios *, int, char *[]);\
void print_all(struct termios *);\
int the_speed(char *);\
void set_speed(struct termios *);\
void print_speed(struct termios *);\
int spec(char *);\
int set_spec(struct termios *, int, char *);\
void print_spec(struct termios *);\
int setting(char *);\
void set_setting(struct termios *, int, int);\
void print_setting(struct termios *);\
\
void showtime(long);\
void show_info(struct untmp *);\
\
struct option \{\
	tcflag_t constant;\
	char *name;\
	void (*print) (struct option *, struct termios *);\
	void (*set) (struct option *, struct termios *, int);\
\};\
\
void t_in(struct option *, struct termios *, int);\
void t_out(struct option *, struct termios *, int);\
void t_local(struct option *, struct term,ios *, int);\
void s_in(struct option *, struct termios *);\
void s_out(struct option *, struct termios *);\
void s_local(struct option *, struct termios *);\
\
struct spec\{tcflag_t constant; char *name;\};\
struct speed\{speed_t constant; char *name;\};\
\
struct spec spec_table[] = \{\
	\{VINTR, \'93intr\'94\},\
	\{VERASE, \'93erase\'94\},\
	\{VKILL, \'93kill\'94\},\
	\{0, NULL\}\
\};\
\
struct option settings_yable[] = \{\
	\{ICRNL, \'93icrnl\'94, s_in, t_in\}.\
	\{ONLCR, \'93onlcr\'94, s_out, t_out\},\
	\{OLCUC, \'93olcuc\'94, s_out, t_out\},\
	\{XTABS, \'93tabs\'94, s_out, t_out\},\
	\{ECHO, \'93echo\'94, s_local, t_local\},\
	\{ECHOE, \'93echoe\'94. s_local, t_local\},\
	\{ICANON. \'93icanon\'94, s_local, t_local\},\
	\{ISIG, \'93isig\'94, s_local, t_local\},\
	\{0, NULL, 0, 0\}\
\};\
\
static char *spec_name;\
\
int main(int ac, char **av) \{\
	struct termios opts;\
	spec_name = av[1];\
\
	if(tcgetattr(FD. &opts) == -1) \{\
		perror(\'93tcgetattr of stdin\'94);\
		exit(1);\
	\}\
\
	if(ac <= 1)\
		printf_all(&opts);\
	else\
		set_args(&opts, ac, av);\
	exit(0);\
\}\
\
void print_all(struct termios *opts) \{\
	print_speed(opts);\
	print_spec(opts);\
	print_setting(opts);\
\}\
\
void set_args(struct termios *opts, int ac, char *av[]) \{\
	int I;\
\
	for(I = 1; I < ac; I++) \{\
		if(check_speed(opts, av[I] == 0)\
			continue;\
		else if(check_spec(opts, av[i], av[I+1]) == 0) \{\
			I++;\
			continue;\
		\}\
		else if(check_setting(opts, av[i) == 0)\
			continue;\
		else\
			fprintf(stderr, \'93Unknown Mode\'94\\n\'94);\
	\}\
\}\
\
int check_speed(struct termios *opts, char *av) \{\
	int i = the_speed(av);\
	if(i != -1) \{\
		set_speed(opts, i)\'92\
		return 0;\
	\}\
	else\
		return -1;\
\}\
\
int check_spec(struct termios *opts, char *av, char *next) \{\
	int i = spec(av);\
	if(i != -1) \{\
		if(next == NULL) \{\
			fprintf(stderr, \'93input character required for %s\\n\'94, spec-name);\
			exit(1);\
		\}\
		if(set_spec(opts, I, next) == -1) \{\
			fprintf(stderr, \'93unknown mode\\n\'94);\
			exit(1);\
		\}\
		return 0;\
	\}\
	return -1;\
\}\
\
int check_setting(struct termios *opts, char *av) \{\
	int on = 1;\
	if(av[0] == \'91-\'91) \{\
		on = 0;\
		av++;\
	\}\
	int i = setting(av);\
	if(i != -1) \{\
		set_setting(opts, i, on);\
		return 0;\
	\}\
	return -1;\
\}\
\
int setting(char *av) \{\
	int i; \
	for(i = 0; settings_table[I].name; i++) \{\
		if(strcmp(settings_table[I].name, av) == 0)\
			return I;\
	\}\
	return -1;\
\}\
\
void set_setting(struct termios *opts, int i, int on) \{\
	settings_table[I].set(&settings_table[I], opts, on);\
\}\
\
void t_opt(struct option *row, struct termios *opts, tcflag_t *flag_p, int on) \{\
	if(on == 1)\
		*flag_p |= row->constant;\
	else\
		*flag_p &= ~(row->constant);\
	if(tcsetattr(FD, TCSANOW), opts) == -1) \{\
		perror(\'93tcsetattr\'94);\
		exit(1);\
	\}\
\}\
\
void t_in(struct option* *row, struct termios *opts, int on) \{\
	t_opt(row, opts, &opts->c_iflag, on);\
\}\
\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 void t_out(struct option* *row, struct termios *opts, int on) \{\
	t_opt(row, opts, &opts->c_oflag, on);\
\}\
\
void t_local(struct option* *row, struct termios *opts, int on) \{\
	t_opt(row, opts, &opts->c_lflag, on);\
\}\
\
void print_setting(struct termios *opts) \{\
	int i;\
	for(i = 0; settings_table[i].name; i++) \{\
		settings_table[i].print(&settings_table[I], opts);\
		printf(\'93 \'93);\
	\}\
	printf(\'93\\n\'94);\
\}\
\
void s_opt(struct option *row, int flag) \{\
	if(flag & row->constant)\
		printf(row->name);\
	else\
		printf(\'93-%s\'94\'94, row->name);\
\}\
\
void s_in(struct option *row, struct termios *opts) \{\
	s_opt(row, opts->c_iflag);\
\}\
\
void s_out(struct option *row, struct termios *opts) \{\
	s_opt(row, opts->c_oflag);\
\}\
\
void s_local(struct option *row, struct termios *opts) \{\
	s_opt(row, opts->c_lflag);\
\}\
\
int spec(char *av) \{\
	int i;\
	for(i = 0; spec_table[I].name; i++) \{\
		if(strcmp(spec_table[I].name, av) == 0)\
			return I;\
	\}\
	return -1;\
\}\
\
int set_spec(struct termios *opts, int I, char *c) \{\
	if(isascii(*c) == 0)\
		return -1;\
	opts->c_cc[spec_table[i].constant] = *c;\
\
	if()tcsetattr(FD, TCSANOW, opts) == -1) \{\
		perror(\'93tcsetattr\'94);\
		exit(1);\
	\}\
	return 0;\
\}\
\
void print_char(int c) \{\
	if(isprint(c) != 0)\
		putchar(c);\
	else if(c == DEL)\
		printf(\'93^?\'94);\
	else if(iscntrl(c) != 0)\
		printf(\'93^%c\'94, c - 1 + \'91A\'92);\
\}\
\
void print_spec(struct termios *opts) \{\
	int i;\
	for(i = 0; spec_table[i].name; i++) \{\
		printf(spec_table[i].name);\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 		printf(\'93 = \'93);\
		print_char(opts->c_cc[spec_table[I].constant[]);\
		printf(\'93; \'93);\
	\}\
	printf(\'93\\n\'94);\
\}\
\
struct speed baud[] = \{\
	\{B0, \'930\'94\},\
	\{B50, \'9350\'94\},\
	\{B75, \'9375\'94\},\
	\{B110, \'93110\},\
	\{B134. \'93134\},\
	\{B150, \'93150\},\
	\{B200, \'93200\'94\},\
	\{B300, \'93300\'94\},\
	\{B600, \'93600\'94\},\
	\{B1200. \'931200\'94\},\
	\{B1800, \'931800\'94\},\
	\{B2400, \'932400\'94\},,\
	\{B4800. \'934800\'94\},\
	\{B9600, \'939600\'94\},\
	\{B19200, \'9319200\'94\},\
	\{B38400, \'9338400\'94\},\
	\{B57600, \'9357600\'94\},\
	\{B115200. \'93115200\'94\},\
	\{B230400, \'93230400\'94\},\
	\{0, NULL\}\
\};\
\
int the_speed(char *av) \{\
	int i; \
	for(i = 0; baud[i].name; i++) \{\
		if(strcmp(baud[i].name, av) == 0)\
			return i;\
	\}\
	return -1;\
\}\
\
void set_speed(struct termios *opts, int i) \{\
	if(cfsetospeed(opts, baud[i].constant) == -1) \{\
		perror(\'93cfsetospeed\'94);\
		exit(1);\
	\}\
	if(tcsetattr(FD, TCSANOW, opts) == -1) \{\
		perror(\'93tcsetattr\'94);\
		exit(1);\
	\}\
\}\
\
void print_speed(struct termios *opts) \{\
	int cfospeed - cfgetospeed(opts);\
	int i;\
\
	for(i = 0; baud[i].name; i++) \{\
		if(cfospeed == baud[i].constant)\
			printf(\'93speed %s baud;]n\'94, baud[i].name);\
	\}\
\}\
\
int main() \{\
	struct utmp utbuf;\
	int utmpfd;\
\
	if(utmpfd = open(UTMP_FILE, O_RDONLY)) == -1_ \{\
		perror(UTMP_FILE);\
		exit(1);\
	\}\
	char *p = getenv(\'93USER\'94);\
	if(p == NULL)\
		return EXIT_FAILURE;\
	printf(\'93%s\\n\'94, p);\
	return 0;\
)\
\
void show_info*(struct ut,p *utbufp) \{\
#ifdef SHOWHOST\
	if(utbufp->ut_host[0] != \'91\\0\'92)\
		printf(\'93(%s)\'94, utbufp->ut_host);\
#endif\
	printf(\'93\\n\'94);\
\}\
\
void showtime(long timeval) \{\
	char *cp\'92\
\
	cp = ctime(&timeval);\
	printf(\'93%12.12s\'94, cp + 4);\
\}\
\
void do_ls(char[]);\
void do_ls1(char[], int, int);\
void dostat(char *);\
void dostat1(char *. int, int);\
void show_file_info(char *, struct stat *);\
void show_file_info1(char *, struct stat *, int, int);\
void mode_to_letters(int, char[]);\
char *uid_to_name(uid_t);\
char *gid_to_name(gid_t);\
\
main(int ac, char *av[]) \{\
	char arr[100];\
	int num - ac;\
	int isLMod = 0;\
	int isUMod = 0;\
	int dir = 0;	\
	char dirName = 100;\
\
	if(ac == 1)\
		do_ls(\'93.\'94);\
	else\
		while(\'97ac) \{\
			*++av;\
			num\'97;\
			strcpy(arr, *av);\
\
			if(arr[0] == \'91-\'91) \{\
				if(arr[1] == \'91l\'92) \{\
					isLMod = 1;\
				\}\
				if(arr[1] == \'91u\'92) \{\
					isUMod = 1;\
				\}\
			\}else if(arr[0] != \'91-\'91) \{\
			dir = 1;\
			strcpy(dirName, \'93-\'93);\
			\}\
		\}\
	do_ls(\'93.\'94, isLMod, isUMod);\
	\}\
	return 0;\
\}\
\
void do_ls(char dirname[]) \{\
	DIR *dir_ptr;\
	struct dirent *direntp;\
\
	if((dir_ptr = opendir(dirname)) == NULL)\
		fprintf(stderr, \'93ls1: cannot open %s\\n\'94, dirname);\
	else\
	\{\
		while((direntp = readdir(dir_ptr)) != NULL)\
			dostat(direntp->d_name);\
		closedir(dir_ptr);\
	\}\
\}\
\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 void do_ls1(char dirname[], int isLMod, int isUMod) \{\
	DIR *dir_ptr;\
	struct dirent *direntp;\
\
	if((dir_ptr = opendir(dirname)) == NULL)\
		fprintf(stderr, \'93ls1: cannot open %s\\n\'94, dirname);\
	else\
	\{\
		while((direntp = readdir(dir_ptr)) != NULL)\
			dostat1(direntp->d_name, isLMod, isUMod);\
		closedir(dir_ptr);\
	\}\
	if(isLMod != 1)\
		printf(\'93n\'94);\
\}\
\
void dostat(char *filename) \{\
	struct stat info;\
\
	if(stat(filename, &info) == -1)\
		perror(filename);\
	else\
		show_file_info(filename, &info);\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 \}\
\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 void dostat1(char *filename, int isLMod, int isUMod) \{\
	struct stat info;\
\
	if(stat(filename, &info) == -1)\
		perror(filename);\
	else\
		show_file_info1(filename, &info, isLMod, isUMod);\
\}\
\
void show_file_info(char *filename, struct stat *info_p) \{\
	char *uid_to_name(), *ctime(), *gid_to_name(), *filenmode();\
	void mode_to_letters();\
	char modestr[11];\
\
	mode_to_letters(info_p->st_mode, modestr);\
\
	printf(\'93%s\'94, modestr);\
	printf(\'934d\'94, (int) info_p->st_nlink);\
	printf(\'93%-8s\'94, uid_to_name(info_p->st_uid));\
	printf(\'93%-8s\'94, gid_to_name(info_p->st_gid));\
	printf(\'93%8ld\'94, (long) info_p->st_size);\
	printf(\'93%.12s\'94, 4+ctime(&info_p->st_mtime));\
	printf(\'93%s\\n\'94, filename);\
\}\
\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 void show_file_info1(char *filename, struct stat *info_p, int isLMod, int isUMod) \{\
	char *uid_to_name(), *ctime(), *gid_to_name(), *filenmode();\
	void mode_to_letters();\
	char modestr[11];\
\
	if(isLMod && isUMod) \{\
\
		mode_to_letters(info_p->st_mode, modestr);\
		printf(\'93%s\'94, modestr);\
		printf(\'934d\'94, (int) info_p->st_nlink);\
		printf(\'93%-8s\'94, uid_to_name(info_p->st_uid));\
		printf(\'93%-8s\'94, gid_to_name(info_p->st_gid));\
		printf(\'93%8ld\'94, (long) info_p->st_size);\
		printf(\'93%.12s\'94, 4+ctime(&info_p->st_atime));\
		printf(\'93%s\\n\'94, filename);\
	\}\
	else if(isLMod) \{\
		mode_to_letters(info_p->st_mode, modestr);\
		printf(\'93%s\'94, modestr);\
		printf(\'934d\'94, (int) info_p->st_nlink);\
		printf(\'93%-8s\'94, uid_to_name(info_p->st_uid));\
		printf(\'93%-8s\'94, gid_to_name(info_p->st_gid));\
		printf(\'93%8ld\'94, (long) info_p->st_size);\
		printf(\'93%.12s\'94, 4+ctime(&info_p->st_mtime));\
		printf(\'93%s\\n\'94, filename);\
	\}\
	else \{\
		printf(\'93%s.     \'93, filename);\
	\}\
\}\
\
void mode_to_letters(int mode, char str[]) \{\
	strcpy(str, \'93\'97\'97\'97\'97\'93);\
\
	if(S_ISDIR(mode)) str[0] = \'91d\'92;\
	if(S_ISCHR(mode)) str[0] = \'91c\'92;\
	if(S_ISBLK(mode)) str[0] = \'91b\'92;\
\
	if(mode & S_IRUSR) str[1] = \'91r\'92;\
	if(mode & S_IWUSR) str[2] = \'91w\'92;\
	if(mode & S_IXUSR) str[3] = \'91x\'92;\
		\
	if(mode & S_IRGRP) str[4] = \'91r\'92;\
	if(mode & S_IWGRP) str[5] = \'91w\'92;\
	if(mode & S_IXGRP) str[6] = \'91x\'92;\
\
	if(mode & S_IROTH) str[7] = \'91r\'92;\
	if(mode & S_IWOTH) str[8] = \'91w\'92;\
	if(mode & S_IXOTH) str[9] = \'91x\'92;\
\}\
\
#include <pwd.h>\
\
char *uid_to_name(uid_t uid) \{\
	struct passwd *getpwuid(), *pw_ptr;\
	static char numstr[10];\
\
	if((pw_ptr = getpwuid(uid)) == NULL) \{\
		sprintf(numstr, \'93%d\'94, uid);\
		return numstr;\
	\}\
	else\
		return pw_ptr->pw_name;\
\}\
\
#include <grp.h>\
\
char *gid_to_name(gid_t gid) \{\
	struct group *getgrgid(), *grp_ptr;\
	static char numstr[10];\
\
	if((grp_ptr = getgrgid(gid)) == NULL) \{\
		sprintf(numstr, \'93%d\'94, gid);\
		return numstr;\
	\}\
	else\
		return grp_ptr->gr_name;\
\}}