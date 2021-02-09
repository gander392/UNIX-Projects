{\rtf1\ansi\ansicpg1252\cocoartf2577
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww15820\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include \'93paddle.h\'94\
#include <ncurses.h>\
#include <signal.h>\
#include <stdio.h>\
#include <stdlib.h>\
#include <sys/time.h>\
\
void paddle_init() \{\
	int currentPos;\
	thePaddle.pad_char = \'91#\'92;\
	thePaddle.pad_bot = 11;\
	thePaddle.pad_top = 16;\
	thePaddle.pad_col = 70;\
	for(currentPos = thePaddle.pad_bot; currentPos < thePaddle.pad_top; currentPos++) \{\
		mvaddch(currentPos, thePaddle.pad_col, thePaddle.pad_char);\
	\}\
\}\
\
void paddle_up() \{\
	int currentPos;\
	if(thePaddle.pad_top <= 19) \{\
		for(currentPos = thePaddle.pad_bot; currentPos < thePaddle.pad_top; currentPos++) \{\
			mvaddch(currentPos, thePaddle.pad_col, \'91 \'91);\
		\}\
		thePaddle.pad_bot++;\
		thePaddle.pad_top++;\
		for(currentPos = thePaddle.pad_bot; currentPos < thePaddle.pad_top; currentPos++) \{\
			mvaddch(currentPos, thePaddle.pad_col, thePaddle.pad_char);\
		\}\
	\}\
\}\
\
void paddle_down() \{\
	int currentPos;\
	if(thePaddle.pad_bot >= 7) \{\
		for(currentPos = thePaddle.pad_bot; currentPos < thePaddle.pad_top; currentPos++) \{\
			mvaddch(currentPos, thePaddle.pad_col, \'91 \'91);\
		\}\
		thePaddle,pad_bot\'97;\
		thePaddle.pad_top\'97;\
		for(currentPos = thePaddle.pad_bot; currentPos < thePaddle.pad_top; currentPos++) \{\
			mvaddch(currentPos, thePaddle.pad_col, thePaddle.pad_char);\
		\}\
	\}\
\}\
\
bool paddle_contact(int y, int x) \{\
	if(x >= thePaddle,pad_col - 1) \{\
		if(y >= thePaddle.pad_bot && y <= thePaddle.pad_top)\
			return true;\
	\}\
	return false;\
\}}