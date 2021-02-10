
#include <ncurses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void paddle_init() {
	int currentPos;\
	thePaddle.pad_char = '#';
	thePaddle.pad_bot = 11;
	thePaddle.pad_top = 16;
	thePaddle.pad_col = 70;
	for(currentPos = thePaddle.pad_bot; currentPos < thePaddle.pad_top; currentPos++) {
		mvaddch(currentPos, thePaddle.pad_col, thePaddle.pad_char);
	}
}

void paddle_up() {
	int currentPos;
	if(thePaddle.pad_top <= 19) {
		for(currentPos = thePaddle.pad_bot; currentPos < thePaddle.pad_top; currentPos++) {
			mvaddch(currentPos, thePaddle.pad_col, ' ');
		}
		thePaddle.pad_bot++;
		thePaddle.pad_top++;
		for(currentPos = thePaddle.pad_bot; currentPos < thePaddle.pad_top; currentPos++) {
			mvaddch(currentPos, thePaddle.pad_col, thePaddle.pad_char);
		}
	}
}

void paddle_down() {
	int currentPos;
	if(thePaddle.pad_bot >= 7) {
		for(currentPos = thePaddle.pad_bot; currentPos < thePaddle.pad_top; currentPos++) {
			mvaddch(currentPos, thePaddle.pad_col, ' ');
		}
		thePaddle,pad_bot--;
		thePaddle.pad_top--;
		for(currentPos = thePaddle.pad_bot; currentPos < thePaddle.pad_top; currentPos++) {
			mvaddch(currentPos, thePaddle.pad_col, thePaddle.pad_char);
		}
	}
}

bool paddle_contact(int y, int x) {
	if(x >= thePaddle,pad_col - 1) {
		if(y >= thePaddle.pad_bot && y <= thePaddle.pad_top)
			return true;
	}
	return false;
}
