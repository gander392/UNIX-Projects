{\rtf1\ansi\ansicpg1252\cocoartf2577
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww15820\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 //pipesg.c\
\
#include <stdio.h>\
#include <unistd.h>\
\
#define oops(m, x) \{perror(m); exit(x);\}\
\
main(int ac, char **av) \{\
	int thepipe[2], newfd, pid;\
\
	if(ac != 3) \{\
		fprintf(stderr, \'93usage: pipe cmd1 cmd2\\n\'94);\
		exit(1);\
	\}\
	if(pipe(the pipe) == -1)\
		oops(\'93cannot get a pipe\'94, 1);\
\
	if((pid = fork()) == -1)\
		oops(\'93cannot fork\'94, 2);\
	//parent will read from pipe\
	if(pid == 0) \{ //child will execute av[2]\
		close(thepipe[1]; //child doesn\'92t write to pipe\
\
		if(dup2(thepipe[0], 0) == -1)\
			oops(\'93could not redirect stdin\'94, 3);\
\
		close(thepipe[0]); //stdin is duped, close pipe\
		execlp(av[2], av[2], NULL);\
		oops(av[2], 4);\
	\}\
	//parent execs av[1] and writes into pipe\
	close(thepipe[0]); //parent doesn\'92t read from pipe\
	\
	if(dup2(thepipe[1], 1) == -1)\
		oops(\'93could not redirect stdout\'94, 4);\
\
	close(thepipe[1]); //stdout is duped, close pipe\
	execlp(av[1], av[1]. NULL);\
	oops(av[1], 5);\
\}}