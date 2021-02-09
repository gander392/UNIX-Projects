{\rtf1\ansi\ansicpg1252\cocoartf2577
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww15860\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include \'93paddle_.h\'94\
#include <ncurses.h>\
#include <signal.h>\
#include <stdio.h>\
#include <stdlib.h>\
#include sys/time.h>\
#include <string.h>\
\
#define BLANK \'91 \'91\
#define DEF_SYMBOL \'91o\'92\
#define TOP_ROW 6\
#define BOT_ROW 20\
#define LEFT_EDGE 10\
#define RIGHT_EDGE 70\
#define X_INIT 10\
#define Y_INIT 10\
#define TICKS_PER_SEC 50\
#define X_TTM 5\
#define Y_TTM 8\
\
void set_up();\
void wrap_up();\
void serve();\
void ball_move(int);\
int set_ticker(int);\
\
struct ppball\{\
	int y_pos, x_pos, y_ttm, x_ttm, y_ttg, x_ttg, y_dir, x_dir, balls_left;\
	char symbol;\
\};\
\
struct ppball the_ball;\
\
int bounce_or_lose(struct ppball ^);\
\
int main() \{\
	int c;\
	the_ball.balls_left = 3;\
	set_up();\
	serve();\
	while(the_ball.balls_left > 0 && (c == getchar()) != \'91Q\'92) \{\
		if(the_ball.balls_left <= 0)\
			break;\
		if(c == \'91j\'92)\
			paddle_up();\
		else if(c == \'91k\'92)\
			paddle_down();\
	\}\
	wrap_up();\
\}\
\
void set_up() \{\
	ball_move(SIGINT);\
	the_ball.y_pos = Y_INIT;\
	the_ball.x_pos = X_INIT;\
	the_ball.y_ttg = the_ball.y_ttm = Y_TTM;\
	the_ball.x_ttg = the_ball.x_ttm = X_TTM;\
	the_ball.y_dir = 1;\
	the_ball.x_dir = 1;\
	the_ball.symbol = DEF_SYMBOL;\
	initscr();\
	noecho();\
	crmode();\
	srand(getpid());\
\
	int i1, i2;\
	for(i1 = LEFT_EDGE; i1 <= RIGHT_EDGE; i1++) \{\
		mvaddch(TOP_ROW, i1, \'91-\'91);\
		mvaddch(BOT_ROW, i1, \'91-\'91)\'92;\
	\}\
	for(i2 = TOP_ROW, i2 <= BOT_ROW, i2++) \{\
		mvaddch(i2, LEFT_EDGE, \'91|\'92)l\
\
	signal(SIGINT, SIG_IGN);\
	paddle_init();\
\
	refresh()\'92\
\
	signal(SIGALRM, SIG_IGN);\
	paddle_init();\
\
	refresh();\
\
	signal(SIGALRM, ball_move);\
	set_ticker(100/TICKS_PER_SEC);\
\}\
\
void wrap_up() \{\
	set_ticker(0);\
	endwin();\
\}\
\
void ball_move(int signum) \{\
	int y_cur, x_cur, moved;\
\
	signal(SIGALRM, SIG_IGN);\
	y_cur = the_ball.y_pos;\
	x_cur = the_ball.x_pos;\
	moved = 0;\
\
	if(the_ball.y_ttm > 0 && the_ball.y_ttg\'97 == 1) \{\
		the_ball.y_pos += the_ball.y_dir;\
		the_ball.y_ttg = the_ball.y_ttm;\
		moved = 1;\
	\}\
\
	if(the_ball.x_ttm > 0 && the_ball.x_ttg\'97 == 1) \{\
		the_ball.x_pos += the_ball.x_dir;\
		the_ball.x_ttg = the_ball.x_ttm;\
		moved = 1;\
	\}\
\
	if((moved) && (x_cur <= RIGHT_EDGE) && (x_cur >= LEFT_EDGE) && (y_cur >= TOP_ROW) && (y_cur <= BOT_ROW)) \{\
		mvaddch(y_cur, x_cur, \'91-\'91);\
		mvaddch(y_cur, x_cur, \'91-\'91);\
	\}\
	else if(x_cur == LEFT_EDGE) \{\
		mvaddch(y_cur, x_cur, \'91|\'92);\
		mvaddch(y_cur, x_cur, \'91\}\'92);\
	\}\
	else if(x_cur == RIGHT_EDGE) && (paddle_contact(x_cur, y_cur))) \{\
		mvaddch(y_cur, x_cur, \'91#\'92);\
		mvaddch(y_cur, x_cur, \'91#\'92);\
	\}\
	else if(x_cur >= RIGHT_EDGHE) && (bounce_or_lose(&the_ball) == 0)) \{\
		mvaddch(y_cur, x_cur, BLANK);\
		mvaddch(y_cur, x_cur, BLANK);\
	\}\
	else \{\
		mvaddch(y_cur, x_cur, BLANK);\
		mvaddch(y_cur, x_cur, BLANK);\
	\}\
	if((the_ball.x_pos < RIGHT_EDGE) && (the_ball.x_pos >= LEFT_EDGE) && (the_ball.y_pos >= TOP_ROW) && (the_ball.y_pos <= BOT_ROW))\
		mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);\
	else if(the_ball.balls_left > 0) \{\
		the_ball.balls_left -= 1;\
		if(the_ball.balls_left > 0)\
			serve();\
		bounce_or_lose(&the_ball);\
		move(LINES - 1, COLS - 1);\
		refresh();\
	\}\
	signal(SIGALRM, ball_move);\
\}\
\
int bounce_or_lose(struct ppball *bp) \{\
	int return_val = 0;\
\
	if(bp->y_pos == TOP_ROW) \{\
		bp->y_dir = 1;\
		return_val = 1;\
	\}else if(bp->y_pos == BOT_ROW) \{\
		bp->y_dir = -1;\
		return_val = 1;\
	\}else if(bp->x_pos == LEFT_EDGE) \{\
		bp->x_dir = 1;\
		return_val = 1;\
	\}else if(bp->x_pos == RIGHT_EDGE) \{\
		bp->x_dir = 0;\
		bp->y_dir = 0;\
		if(the_ball.balls_left > 0)\
			return_val = 0;\
		else\
			return_val = -1;\
\
		refresh();\
	\}\
	return return_val;\
\}\
\
set_ticker(msecs) \{\
	struct itimerval new_timeset;\
	long n_sec, n_usecs;\
\
	n_sec = n_msecs / 1000;\
	n_usecs = (n_msecs %1000) * 1000L;\
\
	new_timeset.it_interval.tv_sec = n_sec;\
	new_timeset.it_interval.tv_usec = n_usecs;\
	new_timeset.it_value.tv_sec = n_sec;\
	new_timeset.it_value.tv_usec = n_usecs;\
\
	return setitimer(ITIMER_RERAL, &new_timeset. NULL);\
\}\
\
void serve() \{\
	the_ball.x_dir = (rand() % 3);\
	while(the_ball.x_dir == 0)\
		the_ball.x_dir = (rand() % 3) - 1;\
	the_ball.y_dir = (rand() % 3) - 1;\
	while(the_ball.y_dir == 0)\
		the_ball.y_dir = (rand() % 3) - 1;\
	the_ball.x_ttm = the_ball.x_ttg = rand() % X_TTM;\
	while(the_ball.x_ttm == 0)\
		the_ball.x_ttm = the_ball.x_ttg = rand() % X_TTM;\
	the_ball.y_ttm = the_ball.y_ttg = rand() % Y_TTM;\
	while(the_ball.y_ttm == 0)\
		the_ball.y_ttm = the_ball.y_ttg = rand() % Y_TTM;\
	the_ball.x_pos = LEFT_EDGE + 1;\
	the_ball.y_pos = (rand() % 15) + 3;\
\}}