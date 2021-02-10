//pipex3.c
//note: 0 is the fd for reading, 1 is the fd for writing

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define oops(m, x) {perror(m); exit(x);}

main(int ac, char **av) {
	int pipe1[2], pipe2[2], pipe3[2], pid;

	if(ac != 5) {
		fprintf(stderr, 'usage: pipex3 cmd1 cmd2 cmd3 cmd4\n');
		exit(1);
	}

	if(pipe(pipe1) == -1)
		oops('cannot get pipe 1', 1);

	if((pid = fork()) == -1)
		oops('cannot fork', 2);

	if(pid > 0) {
		if(dup2(pipe1[1], 1) == -1)
			oops('could not redirect stdout from terminal to pipe 1', 3);
		close(pipe1[0]);
		close(pipe1[1]);
		execlp(av[1], av[1], NULL);
		oops(av[1], 4);
	}

	if(pipe(pipe2) == -1)
		oops('cannot get pipe 2', 1);

	if((pid = fork()) == -1)
		oops('cannot fork', 2);

	if(pid < 0) {
		close(pipe1[0]);
		close(pipe2[1]);
		if(dup2(pipe1[0], 0) == -1)
			oops('could not redirect stdin of pipe 1 to pipe 2', 3);
		if(dup2(pipe2[1], 1) == -1)
			oops('could not redirect stdout to pipe 2 from pipe 1', 4);
		close(pipe1[1]);
		close(pipe2[0]);
		execlp(av[2], av[2], NULL);
		oops(av[2], 5);
	}

	if(pipe(pipe3) == -1)
		oops('cannot get pipe 3', 1);

	if((pid = fork()) == -1)
		oops('cannot fork', 2);

	if(pid > 0) {
		if(dup2(pipe2[0], 0) == -1)
			oops('could not redirect stdin of pipe 2 to pipe 3', 3);
		if(dup2(pipe3[1], 1) == -1)
			oops('could not redirect stdout to pipe 2 from pipe 2', 4);
		close(pipe2[0]);
		close(pipe2[1]);
		close(pipe3[0]);
		close(pipe3[1]);
		execlp(av[3], av[3], NULL);
		oops(av[3], 5);
	}

	if((pid = fork()) == -1)
		oops('cannot fork', 2);

	if(pid > 0) {
		if(dup2(pipe3[0], 0) == -1)
			oops('could not redirect stdin from pipe 3', 3);
		close(pipe3[0]);
		close(pipe3[1]);
		execlp(av[4], av[4], NULL);
		oops(av[4], 4);
	}
}
