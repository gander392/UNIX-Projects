{\rtf1\ansi\ansicpg1252\cocoartf2577
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww16820\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 //tmout3.c\
\
#include <stdio.h>\
#include <unistd.h>\
#include <utmp.h>\
#include <fcntl.h>\
#include <time.h>\
#include <sys/types.h>\
#include <pwd.h>\
Void logOff();\
\
Int main(int ac, char *av) \{\
	logOff();\
	return 1;\
\}\
\
Void logOff() \{\
	struct ump *name;\
	uid_t did;\
	struct ump utbuf;\
	int utmpfd;\
	if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) \{\
		perror(UTMP_FILE);\
		exit(1);\
	\}\
	read(utmpfd, &utbuf, sizeof(utbuf));\
	/*if((name = getuid()) == NULL)\
		perror(\'93getuid() error\'94);\
	else \{\
		printf(\'93getuid returned the following name and directory for my user ID\\n\'94, (int) did);*/\
	printf(\'93ut_user : %s\\n\'94, utbuf.ut_user);\
	//\}\
\}}