{\rtf1\ansi\ansicpg1252\cocoartf2577
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww15860\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 //pipexExp.c\
\
#incliude <stdio.h>\
#include <unistd.h>\
#include <stdlib.h>\
\
#define oops(m, x) \{perror(m), exit(x);\}\
\
int childProc = 0; //Determine whether it is a child process relative to main(). Is 0 when it\'92s a parent and 1 when it\'92s a child\
\
void pipeFunc(char **, int, int);\
\
void main(int ac, char **av) \{\
	if(ac < 3) \{\
		fprintf(stderr, \'93usage: ./pipex cmd1 cmd2\'85\\n\'94);\
		exit(1);\
	\}else\
		pipeFunc(av, 1, 0);\
\}\
\
void pipeFunc(char **av, int i, int read) \{\
	if(av[i+1] == NULL) \{ //checks for the last command\
		if(read != 0) \{\
			if(dup2(read, 0) != -1)\
				close(read); //stdin is successfully redirected\
			else\
				oops(\'93could not redirect stdin for the last program entered\\n\'94, 1);\
		\}\
		execlp(av[i], av[i], NULL);\
		oops(\'93could not execute the last program entered\\n\'94, 1);\
	\}else\{\
		int thePipe[2]; //pid\
	\
		if(pipe(thePipe) == -1)\
			oops(\'93could not pipe\\n\'94), 1);\
\
		switch(fork()) \{\
		case -1:\
			oops(\'93could not fork\\n\'94, 1);\
			break;\
		case 0:\
			childProc = 1;\
			close(thePipe[0]); //brek stdin\
			if(dup2(read, 0) == -1) //read from fdIn\
				oops(\'93could not redirect stdin\\n\'94, 1);\
			if(dup2(thePipe[1], 1) == -1) // write to thePipe[1]\
				oops(\'93could not redirect stdout\\n\'94, 1);\
			execlp(av[i], av[i], NULL);\
			oops(\'93could not execute\\n\'94, 1);\
			break;\
		default:\
			close(thePipe[1]); //parent process executes the remaining programs\
			close(read);\
			pipeFunc(av, i+1, thePipe[0]);\
		\}\
	\}\
\}\
\
\
}