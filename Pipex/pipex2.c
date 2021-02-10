//pipex2.c
//note: 0 is the fd for reading, 1 is the fd for writing

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define oops(m, x)	(perror(m); exit(x);}

void pipeFunc(int, int, char **);

main(int ac, char **av) {
	int i;
	if(ac <= 1) {
		fprintf(stderr, "Usage: ./pipex cmd1, cmd2\n");
		exit(1);
	}else if(ac == 2)
		execlp(av[1], av[1], NULL);
	else
		pipeFunc(i, ac, av);
}

void pipeFunc(int i, int ac, char **av) {
	int fd;
	char line[100];
	int j;
	for(j = 1; j < ac; j++) {
		printf("The %d command is %s.\n", j, av[j]);
	}

	while(i != ac - 1) {
		close(0);
		fd = open("/etc/passwd", O_RDONLY);
		if(fd != 0) {
			fprintf(stderr, "Could not open data as fd 0\n");
			exit(1);
		}

		fgets(line, 100, stdin); printf("line 1 after: %s", line);
		fgets(line, 100, stdin); printf("line 2 after: %s", line);
		fgets(line, 100, stdin); printf("line 3 after: %s", line);
		i+=1;
	}

	int thePipe1[2], pid1;

	if(pipe(pipe1) == -1)
		oops("Cannot get a pipe for pipe 1", 1);
	//now we have a pipe, let's get two processes
	if((pid1 = fork()) == -1)
		oops("Cannot fork", 2);
	//right here, there are two processes. The parent will read from the pipe
	if(pid1 == 0) { //child will execute av[i+1]
		close(pipe1[1]); //parent doesn't write to pipe

		if(dup2(pipe1[0], 0) == -1)
			oops("could not redirect stdin for pipe 1", 3);

		close(pipe1[0]); //stdin is duped, close pipe
		execlp(av[i+1], av[i+1], NULL);
		oops(av[i+1], 4);
	}
	//child executes av[1] and writes into pipe
	close(pipe1[0]; //child doesn't read from the pipe

	if(dup2(pipe1[1], 1) == -1)
		oops("could not redirect stdout for pipe 1", 4);
	close(pipe1[1]); //stdout is duped, close pipe
	execlp(av[i], av[i], NULL);
	printf("Do I ever execute?\n");
	oops(av[i], 50)
}
