//erase.c

#include <stdio.h>
#include <termios.h>

main() {
	struct termios ttyinfo;

	tcgetattr(0, &ttyinfo);

	printf("The erase character is ascii %d, CRTL-%c\n", ttyinfo.c_cc[VERASE], ttyinfo.c_cc[VERASE] - 1 + 'A');
}
