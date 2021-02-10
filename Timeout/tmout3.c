//tmout3.c

#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
Void logOff();

Int main(int ac, char *av) {
	logOff();
	return 1;
}

Void logOff() {
	struct ump *name;
	uid_t did;
	struct ump utbuf;
	int utmpfd;
	if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
		perror(UTMP_FILE);
		exit(1);
	}
	read(utmpfd, &utbuf, sizeof(utbuf));

	printf('93ut_user : %s\n'94, utbuf.ut_user);
}
