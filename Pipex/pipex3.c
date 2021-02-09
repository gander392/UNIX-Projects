{\rtf1\ansi\ansicpg1252\cocoartf2577
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww15880\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 //pipex3.c\
//note: 0 is the fd for reading, 1 is the fd for writing\
\
#include <stdio.h>\
#include <unistd.h>\
#include <stdlib.h>\
\
#define oops(m, x) \{perror(m); exit(x);\}\
\
main(int ac, char **av) \{\
	int pipe1[2], pipe2[2], pipe3[2], pid;\
\
	if(ac != 5) \{\
		fprintf(stderr, \'93usage: pipex3 cmd1 cmd2 cmd3 cmd4\\n\'94);\
		exit(1);\
	\}\
\
	if(pipe(pipe1) == -1)\
		oops(\'93cannot get pipe 1\'94, 1);\
\
	if((pid = fork()) == -1)\
		oops(\'93cannot fork\'94, 2);\
\
	if(pid > 0) \{\
		if(dup2(pipe1[1], 1) == -1)\
			oops(\'93could not redirect stdout from terminal to pipe 1\'94, 3);\
		close(pipe1[0]);\
		close(pipe1[1]);\
		execlp(av[1], av[1], NULL);\
		oops(av[1], 4);\
	\}\
\
	if(pipe(pipe2) == -1)\
		oops(\'93cannot get pipe 2\'94, 1);\
\
	if((pid = fork()) == -1)\
		oops(\'93cannot fork\'94, 2);\
\
	if(pid < 0) \{\
		close(pipe1[0]);\
		close(pipe2[1]);\
		if(dup2(pipe1[0], 0) == -1)\
			oops(\'93could not redirect stdin of pipe 1 to pipe 2\'94, 3);\
		if(dup2(pipe2[1], 1) == -1)\
			oops(\'93could not redirect stdout to pipe 2 from pipe 1\'94, 4);\
		close(pipe1[1]);\
		close(pipe2[0]);\
		execlp(av[2], av[2], NULL);\
		oops(av[2], 5);\
	\}\
\
	if(pipe(pipe3) == -1)\
		oops(\'93cannot get pipe 3\'94, 1);\
\
	if((pid = fork()) == -1)\
		oops(\'93cannot fork\'94, 2);\
\
	if(pid > 0) \{\
		if(dup2(pipe2[0], 0) == -1)\
			oops(\'93could not redirect stdin of pipe 2 to pipe 3\'94, 3);\
		if(dup2(pipe3[1], 1) == -1)\
			oops(\'93could not redirect stdout to pipe 2 from pipe 2\'94, 4);\
		close(pipe2[0]);\
		close(pipe2[1]);\
		close(pipe3[0]);\
		close(pipe3[1]);\
		execlp(av[3], av[3], NULL);\
		oops(av[3], 5);\
	\}\
\
	if((pid = fork()) == -1)\
		oops(\'93cannot fork\'94, 2);\
\
	if(pid > 0) \{\
		if(dup2(pipe3[0], 0) == -1)\
			oops(\'93could not redirect stdin from pipe 3\'94, 3);\
		close(pipe3[0]);\
		close(pipe3[1]);\
		execlp(av[4], av[4], NULL);\
		oops(av[4], 4);\
	\}\
\}}