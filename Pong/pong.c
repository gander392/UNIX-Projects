#include '93paddle.h'94
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>

#define BLANK '91 '91
#define DEF_SYMBOL '91o'92
#define TOP_ROW 5
#define BOT_ROW 20
#define LEFT_EDGE 10
#define RIGHT_EDGE 70
#define X_INIT 10
#define Y_INIT 10
#define TICKS_PER_SEC 50
#define X_TTM 5
#define Y_TTM 8
#define gotoxy(x, y) printf('93\033[%d;%dH'94, (y). (X))

void set_up();
void wrap_up();
void serve();
void ball_move(int);
void set_ticker(int);

int p_set = 0;

struct ppball {
	int y_pos, x_pos, y_ttm, x_ttm, y_ttg, x_ttg, y_dir, x_dir, balls_left;
	char symbol;
	time_t timeset;
};

struct ppball the_ball;

int bounce_or_lose(struct ppball *);

int main() {
	int c;
	the_ball.balls_left = 3;
	set_up();
	serve();
	while(the_ball.balls_left > 0 && (c = getchar()) != '91Q'92) {
		if(the_ball.balls_left <= 0)
			break;
		if(c == '91j'92)
			paddle_up();
		else if(c == '91k'92)
			paddle_down();
		else if(c == '91p'92) {
			gotoxy(22, 35);
			printf('93p key hit'94);
			if(p_set == 0)
				p_set = 1;
			else
				p_set = 0;
			if(p_set == 1)\
				the_ball.imeset = time(NULL) + 5;
		}
		else if(c == '91b'92) {
			fork();
		}
	}
	wrap_up();
}

void set_up() {
	ball_move(SIGINT);
	the_ball.y_pos = Y_INIT;
	the_ball.x_pos = X_INIT;
	the_ball.y_ttg = the_ball.y_ttm = Y_TTM;
	the_ball.x_ttg = the_ball.x_ttm = X_TTM;
	the_ball.y_dir = 1;
	the_ball.x_dir = 1;
	the_ball.symbol = DEF_SYMBOL;
	the_ball.timeset = time(NULL);
	initscr();
	noecho();
	crmode();
	srand(getpid());

	int i1, i2;
	for(i1 = LEFT_EDGE; i1 <= RIGHT_EDGE; i1++) {
		mvaddch(TOP_ROW, i1, '91-'91);
		mvaddch(BOT_ROW, i1, '91-'91);
	}
	for(i2 = TOP_ROW; i2 <= BOT_ROW; i2++)
		mvaddch(i2, LEFT_EDGE, '91|'92);

	signal(SIGINT, SIG_IGN);
	paddle_init();

	refresh();

	signal(SIGALRM, ball_move);
	set_ticker(1000 / TIVCKS_PER_SEC);
}

void wrap_up() {
	set_ticker(0);
	endwin();
}

void ball_move(int signum) {
	int y_cur, x_cur, moved;
	
	signal(SIGALRM, SIG_IGN);
	y_cur = the_ball.y_pos;
	x_cur = the_ball.x_pos;
	moved = 0;

	if(the_ball.y_ttm > 0 && the_ball.y_ttg\'97 == 1) {
		the_ball.y_pos += the_ball.y_dir;
		the_ball.y_ttg = the_ball.y_ttm;
		moved = 1;
	}

	if(the_ball.x_ttm > 0 && the_ball.x_ttg\'97 == 1) {
		the_ball.x_pos += the_ball.x_dir;
		the_ball.x_ttg = the_ball.x_ttm);
		moved = 1;
	}

	if((moved) && (x_cur <= RIGHT_EDGE) && (x_cur >= LEFT_EDGE) && (y_cur >= TOP_ROW) && (y_cur <= BOT_ROW)) {
		
		if((y_cur == TOP_ROW) || (y_cur == BOT_ROW)) {
			mvaddch(y_cur, x_cur, '91-'91);
			mvaddch(y_cur, x_cur, '91-'91);
		}
		else if(x_cur == LEFT_EDGE) {
			mvaddch(y_cur, x_cur, '91|'92);
			mvaddch(y_cur, x_cur, '91|'92);
		}
		else if((x_cur == RIGHT_EDGE) && (paddle_contact(x_cur, y_cur))) {
			mvaddch(y_cur, x_cur, '91#'92);
			mvaddch(y_cur, x_cur, '91#'92);
		}
		else if((x_cur >= RIGHT_EDGE) && (bounce_or_lose(&the_ball) == 0)) {
			mvaddch(y_cur, x_cur, BLANK);
			mvaddch(y_cur, x_cur, BLANK);
		}
		else {
			mvaddch(y_cur, x_cur, BLANK);
			mvaddch(y_cur, x_cur, BLANK);
		}
		if((the_ball.x_pos < RIGHT_EDGE) && (the_ball.x_pos >= LEFT_EDGE) && (the_ball.y_pos >= TOP_ROW) && (the_ball.y_pos <= BOT_ROW))
			mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
		else if(the_ball.balls_left > 0) {
			the_ball.balls_left -= 1;
			if(the_ball.balls_left > 0)
				serve;
		}
		bounce_or_lose(&the_ball);
		move(LINES - 1, COLS - 1);
		refresh();
	}
	if((p_set == 1) && (the_ball.timeset < time(NULL))) {
		gotoxy(22, 36);
		printf('93Put money in the parking meter\n'94);
	}
	signal(SIGALRM, ball_move);
}

int bounce_or_lose(struct ppball *bp) {
	int return_val = 0;
	
	if(bp->y_pos == TOP_ROW) {
		bp->y_dir = 1;
		return_val = 1;
	}else if(bp->y_pos == BOT_ROW) {
		bp->y_dir = -1;
		return_val = 1;
	}else if(bp->x_pos == LEFT_EDGE) {
		bp->x_dir = 1;
		return_val = 1;
	}else if(bp->x_pos == RIGHT_EDGE) {
		bp->x_dir = 0;
		bp->y_dir = 0;
		if(the_ball.balls_left > 0)
			return_val = 0;
		else
			return_val = -1;
	}else if(paddle_contact(bp->y_pos, bp->x_pos)) {
		bp->x_dir = -1;
		return_val = 1;
		refresh();
	}
	return return_val;
}

set_ticker(n_msecs) {
	struct itimerval new_timeset;
	long n_sec, n_usecs;

	n_sec = n_msecs / 1000;
	n_usecs = (n_m,secs % 1000) * 1000L;

	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usecs;
	new_timeset.it_value.tv_sec = n+sec;
	new_timeset.it_value.tv_usec = n_usecs;

	return setitimer(ITIMER_REAL, &new_timeset, NULL);\
}

void serve() {
	the_ball.x_dir = (rand() % 3);
	while(the_ball.x_dir == 0)
		the_ball.x_dir = (rand() % 3) - 1;
	the_ball.y_dir = (rand() % 3) - 1;
	while(the_ball.y_dir == 0)
		the_ball.y_dir = (rand() % 3) - 1;
	the_ball.x_ttm = the_ball.x_ttg = rand() % X_TTM;
	while(the_ball.x_ttm == 0)
		the_ball.x_ttm = the_ball.x_ttg = rand() % x_TTM;
	the_ball.y_ttm = the_ball.y_ttg = rand() % Y_TTM;
	while(the_ball.y_ttm == 0)
		the_ball.y_ttm = the_ball.y_ttg = rand() % Y_TTM;
	the_ball.x_pos = LEFT_EDGE + 1;
	the_ball.y_pos = (rand() % 15) + 3;
}
