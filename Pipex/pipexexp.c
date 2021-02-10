//pipexExp.c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define oops(m, x) {perror(m), exit(x);}

int childProc = 0; //Determine whether it is a child process relative to main(). Is 0 when it's a parent and 1 when it's a child

void pipeFunc(char **, int, int);

void main(int ac, char **av) {
	if(ac < 3) {
		fprintf(stderr, "usage: ./pipex cmd1 cmd2\n");
		exit(1);
	}else
		pipeFunc(av, 1, 0);
}

void pipeFunc(char **av, int i, int read) {
	if(av[i+1] == NULL) { //checks for the last command
		if(read != 0) {
			if(dup2(read, 0) != -1)
				close(read); //stdin is successfully redirected
			else
				oops("could not redirect stdin for the last program entered\n", 1);
		}
		execlp(av[i], av[i], NULL);
		oops("could not execute the last program entered\n", 1);
	}else
		int thePipe[2]; //pid
	
		if(pipe(thePipe) == -1)
			oops("could not pipe\n"), 1);

		switch(fork()) {
		case -1:
			oops("could not fork\n", 1);
			break;
		case 0:
			childProc = 1;
			close(thePipe[0]); //break stdin
			if(dup2(read, 0) == -1) //read from fdIn
				oops("could not redirect stdin\n", 1);
			if(dup2(thePipe[1], 1) == -1) // write to thePipe[1]
				oops("could not redirect stdout\n", 1);
			execlp(av[i], av[i], NULL);
			oops("could not execute\n", 1);
			break;
		default:
			close(thePipe[1]); //parent process executes the remaining programs
			close(read);
			pipeFunc(av, i+1, thePipe[0]);
		}
	}
}
