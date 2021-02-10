//erase.c

#include <stdio.h>
#include <termios.h>

main() {
	struct terms ttyinfo;

	tcgetattr(0, &ttyinfo);

	printf('93The erase character is ascii %d, CRTL-%c\n\'94, ttyinfo.c_cc[VERASE], ttyinfo.c_cc[VERASE] - 1 + '91A'92);
}
