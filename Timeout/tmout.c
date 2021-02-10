//timeout.c

#include <termios.h>
#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#ifndef FD
#define FD 0
#endif

#define DEL 127

int check_speed(struct termios *, char *);
int check_spec(struct termios *, char *, char *);
int check_setting(struct termios *, char *);
void set_args(struct termios *, int, char *[]);
void print_all(struct termios *);
int the_speed(char *);
void set_speed(struct termios *);
void print_speed(struct termios *);
int spec(char *);
int set_spec(struct termios *, int, char *);
void print_spec(struct termios *);
int setting(char *);
void set_setting(struct termios *, int, int);
void print_setting(struct termios *);

void showtime(long);
void show_info(struct untmp *);

struct option {
	tcflag_t constant;
	char *name;
	void (*print) (struct option *, struct termios *);
	void (*set) (struct option *, struct termios *, int);
};

void t_in(struct option *, struct termios *, int);
void t_out(struct option *, struct termios *, int);
void t_local(struct option *, struct term,ios *, int);
void s_in(struct option *, struct termios *);
void s_out(struct option *, struct termios *);
void s_local(struct option *, struct termios *);

struct spec{tcflag_t constant; char *name;};
struct speed{speed_t constant; char *name;};

struct spec spec_table[] = {
	{VINTR, "intr"},
	{VERASE, "erase"},
	{VKILL, "kill"},
	{0, NULL}
};

struct option settings_table[] = {
	{ICRNL, "icrnl", s_in, t_in}.
	{ONLCR, "onlcr", s_out, t_out},
	{OLCUC, "olcuc", s_out, t_out},
	{XTABS, "tabs", s_out, t_out},
	{ECHO, "echo", s_local, t_local},
	{ECHOE, "echoe", s_local, t_local},
	{ICANON. "icanon", s_local, t_local},
	{ISIG, "isig", s_local, t_local},
	{0, NULL, 0, 0}
};

static char *spec_name;

int main(int ac, char **av) {
	struct termios opts;
	spec_name = av[1];

	if(tcgetattr(FD. &opts) == -1) {
		perror("tcgetattr of stdin");
		exit(1);
	}

	if(ac <= 1)
		printf_all(&opts);
	else
		set_args(&opts, ac, av);
	exit(0);
}

void print_all(struct termios *opts) {
	print_speed(opts);
	print_spec(opts);
	print_setting(opts);
}

void set_args(struct termios *opts, int ac, char *av[]) {
	int i;

	for(i = 1; i < ac; i++) \{\
		if(check_speed(opts, av[i] == 0)
			continue;
		else if(check_spec(opts, av[i], av[i+1]) == 0) {
			i++;
			continue;
		}
		else if(check_setting(opts, av[i) == 0)
			continue;
		else
			fprintf(stderr, "Unknown Mode\n");
	}
}

int check_speed(struct termios *opts, char *av) {
	int i = the_speed(av);
	if(i != -1) {
		set_speed(opts, i);
		return 0;
	}
	else
		return -1;
}

int check_spec(struct termios *opts, char *av, char *next) {
	int i = spec(av);
	if(i != -1) {
		if(next == NULL) {
			fprintf(stderr, "Input character required for %s\n", spec_name);
			exit(1);
		}
		if(set_spec(opts, i, next) == -1) {
			fprintf(stderr, "Unknown mode\n");
			exit(1);
		}
		return 0;
	
	return -1;
}

int check_setting(struct termios *opts, char *av) {
	int on = 1;
	if(av[0] == '-') {
		on = 0;
		av++;
	}
	int i = setting(av);
	if(i != -1) {
		set_setting(opts, i, on);
		return 0;
	}
	return -1;
}

int setting(char *av) {
	int i; 
	for(i = 0; settings_table[i].name; i++) {
		if(strcmp(settings_table[i].name, av) == 0)
			return i;
	}
	return -1;
}

void set_setting(struct termios *opts, int i, int on) {
	settings_table[i].set(&settings_table[i], opts, on);
}

void t_opt(struct option *row, struct termios *opts, tcflag_t *flag_p, int on) {
	if(on == 1)
		*flag_p |= row->constant;
	else
		*flag_p &= ~(row->constant);
	if(tcsetattr(FD, TCSANOW), opts) == -1) {
		perror("tcsetattr");
		exit(1);
	}
}

void t_in(struct option *row, struct termios *opts, int on) {
	t_opt(row, opts, &opts->c_iflag, on);
}

void t_out(struct option *row, struct termios *opts, int on) {
	t_opt(row, opts, &opts->c_oflag, on);
}

void t_local(struct option *row, struct termios *opts, int on) {
	t_opt(row, opts, &opts->c_lflag, on);
}

void print_setting(struct termios *opts) {
	int i;
	for(i = 0; settings_table[i].name; i++) {
		settings_table[i].print(&settings_table[i], opts);
		printf(" ");
	}
	printf("\n");
}

void s_opt(struct option *row, int flag) {
	if(flag & row->constant)
		printf(row->name);
	else
		printf("-%s", row->name);
}

void s_in(struct option *row, struct termios *opts) {
	s_opt(row, opts->c_iflag);
}

void s_out(struct option *row, struct termios *opts) {
	s_opt(row, opts->c_oflag);
}

void s_local(struct option *row, struct termios *opts) {
	s_opt(row, opts->c_lflag);
}

int spec(char *av) {
	int i;
	for(i = 0; spec_table[i].name; i++) {
		if(strcmp(spec_table[i].name, av) == 0)
			return i;
	}
	return -1;
}

int set_spec(struct termios *opts, int i, char *c) {
	if(isascii(*c) == 0)
		return -1;
	opts->c_cc[spec_table[i].constant] = *c;

	if()tcsetattr(FD, TCSANOW, opts) == -1) {
		perror("tcsetattr");
		exit(1);
	}
	return 0;
}

void print_char(int c) {
	if(isprint(c) != 0)
		putchar(c);
	else if(c == DEL)
		printf("^?");
	else if(iscntrl(c) != 0)
		printf("^%c", c - 1 + 'A');
}

void print_spec(struct termios *opts) {
	int i;
	for(i = 0; spec_table[i].name; i++) {
		printf(spec_table[i].name);
		printf(" = ");
		print_char(opts->c_cc[spec_table[i].constant[]);
		printf("; ");
	}
	printf("\n");
}

sruct speed baud[] = {
	{B0, "0"},
	{B50, "50"},
	{B75, "75"},
	{B110, "110"},
	{B134, "134"},
	{B150, "150"},
	{B200, "200"},
	{B300, "300"},
	{B600, "600"},
	{B1200, "1200"},
	{B1800, "1800"},
	{B2400, "2400"},
	{B4800, "4800"},
	{B9600, "9600"},
	{B19200, "19200"},
	{B38400, "38400"},
	{B57600, "57600"},
	{B115200,"115200"},
	{B230400,"230400"},
	{0, NULL}
};

int the_speed(char *av) {
	int i; 
	for(i = 0; baud[i].name; i++) {
		if(strcmp(baud[i].name, av) == 0)
			return i;
	}
	return -1;
}

void set_speed(struct termios *opts, int i) {
	if(cfsetospeed(opts, baud[i].constant) == -1) {
		perror("cfsetospeed");
		exit(1);
	}
	if(tcsetattr(FD, TCSANOW, opts) == -1) {
		perror("tcsetattr");
		exit(1);
	}
}

void print_speed(struct termios *opts) {
	int cfospeed - cfgetospeed(opts);
	int i;

	for(i = 0; baud[i].name; i++) {
		if(cfospeed == baud[i].constant)
			printf("speed %s baud\n", baud[i].name);
	}
}

int main() {
	struct utmp utbuf;
	int utmpfd;

	if(utmpfd = open(UTMP_FILE, O_RDONLY)) == -1 {
		perror(UTMP_FILE);
		exit(1);
	}
	char *p = getenv("USER");
	if(p == NULL)
		return EXIT_FAILURE;
	printf("%s\n", p);
	return 0;
)

void show_info*(struct utmp *utbufp) {
#ifdef SHOWHOST
	if(utbufp->ut_host[0] != '\0')
		printf("(%s)", utbufp->ut_host);
#endif
	printf("\n");
}

void showtime(long timeval) {
	char *cp;

	cp = ctime(&timeval);
	printf("%12.12s", cp + 4);
}

void do_ls(char[]);
void do_ls1(char[], int, int);
void dostat(char *);
void dostat1(char *. int, int);
void show_file_info(char *, struct stat *);
void show_file_info1(char *, struct stat *, int, int);
void mode_to_letters(int, char[]);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

main(int ac, char *av[]) {
	char arr[100];
	int num - ac;
	int isLMod = 0;
	int isUMod = 0;
	int dir = 0;	
	char dirName = 100;

	if(ac == 1)
		do_ls('.');
	else
		while(--ac) {
			*++av;
			num--;
			strcpy(arr, *av);

			if(arr[0] == '-') {
				if(arr[1] == 'l') {
					isLMod = 1;
				}
				if(arr[1] == 'u') {
					isUMod = 1;
				}
			}else if(arr[0] != '-') {
			dir = 1;
			strcpy(dirName, '-');
			}
		}
	do_ls('.', isLMod, isUMod);
	}
	return 0;
}

void do_ls(char dirname[]) {
	DIR *dir_ptr;
	struct dirent *direntp;

	if((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "ls1: cannot open %s\n", dirname);
	else
	{
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
	else
	{
		while((direntp = readdir(dir_ptr)) != NULL)
			dostat1(direntp->d_name, isLMod, isUMod);
		closedir(dir_ptr);
	}
	if(isLMod != 1)
		printf('n');
}

void dostat(char *filename) {
	struct stat info;

	if(stat(filename, &info) == -1)
		perror(filename);
	else
		show_file_info(filename, &info);

void dostat1(char *filename, int isLMod, int isUMod) {
	struct stat info;

	if(stat(filename, &info) == -1)
		perror(filename);
	else
		show_file_info1(filename, &info, isLMod, isUMod);
}

void show_file_info(char *filename, struct stat *info_p) {
	char *uid_to_name(), *ctime(), *gid_to_name(), *filenmode();
	void mode_to_letters();
	char modestr[11];

	mode_to_letters(info_p->st_mode, modestr);

	printf("%s", modestr);
	printf("4d", (int) info_p->st_nlink);
	printf("%-8s", uid_to_name(info_p->st_uid));
	printf("%-8s", gid_to_name(info_p->st_gid));
	printf("%8ld", (long) info_p->st_size);
	printf("%.12s", 4+ctime(&info_p->st_mtime));
	printf("%s\n", filename);
}

void show_file_info1(char *filename, struct stat *info_p, int isLMod, int isUMod) {
	char *uid_to_name(), *ctime(), *gid_to_name(), *filenmode();
	void mode_to_letters();
	char modestr[11];

	if(isLMod && isUMod) {

		mode_to_letters(info_p->st_mode, modestr);
		printf("%s", modestr);
		printf("4d", (int) info_p->st_nlink);
		printf("%-8s", uid_to_name(info_p->st_uid));
		printf("%-8s", gid_to_name(info_p->st_gid));
		printf("%8ld", (long) info_p->st_size);
		printf("%.12s", 4+ctime(&info_p->st_atime));
		printf("%s\n", filename);
	}
	else if(isLMod) {
		mode_to_letters(info_p->st_mode, modestr);
		printf("%s", modestr);
		printf("4d", (int) info_p->st_nlink);
		printf("%-8s", uid_to_name(info_p->st_uid));
		printf("%-8s", gid_to_name(info_p->st_gid));
		printf("%8ld", (long) info_p->st_size);
		printf("%.12s", 4+ctime(&info_p->st_mtime));
		printf("%s\n", filename);
	}
	else {
		printf("%s     ", filename);
	}
}

void mode_to_letters(int mode, char str[]) {
	strcpy(str, '----------');

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
	struct passwd *getpwuid(), *pw_ptr;
	static char numstr[10];

	if((pw_ptr = getpwuid(uid)) == NULL) {
		sprintf(numstr, "%d", uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name;
}

#include <grp.h>

char *gid_to_name(gid_t gid) {
	struct group *getgrgid(), *grp_ptr;
	static char numstr[10];

	if((grp_ptr = getgrgid(gid)) == NULL) {
		sprintf(numstr, "%d", gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}
