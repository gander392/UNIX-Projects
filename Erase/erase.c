{\rtf1\ansi\ansicpg1252\cocoartf2577
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww16820\viewh11860\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 //erase.c\
\
#include <stdio.h>\
#include <termios.h>\
\
main() \{\
	struct terms ttyinfo;\
\
	tcgetattr(0, &ttyinfo);\
\
	printf(\'93The erase character is ascii %d, CRTL-%c\\n\'94, ttyinfo.c_cc[VERASE], ttyinfo.c_cc[VERASE] - 1 + \'91A\'92);\
\}}