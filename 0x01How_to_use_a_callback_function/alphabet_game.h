/**
  *  Copyright (C) 2013-12-09  Handsome Zhou
  */

#ifndef ALPHABET_GAME_H
#define ALPHABET_GAME_H

#include <stdio.h>
#include <ncurses.h>
#include "data_type.h"


#define GAME_NAME		"Alphabet Game"

#define AG_SUCCESS		(0)
#define AG_FAILED		(-1)

#define DELAY_TIME_MAX	500000//us
#define DELAY_TIME_MIN	 50000//us
#define DELAY_TIME		250000//us






/*==========alphabet game main status event==========>*/
#define ALPHABET_GAME_WIDGET_NUM		(3)

#define ALPHABET_GAME_START_X			1

/*<==========alphabet game child status event==========*/
#define ALPHABET_GAME_START_WIDGET_NUM	(26)
#define ALPHABET_GAME_HELP_WIDGET_NUM	(1)

typedef enum{
	MAIN_STATUS=0,		 	//Status that not enter the event of any button
	CHILD_STATUS_START,		//Status that enter the event of start's button
	CHILD_STATUS_HELP,		//Status that enter the event of help's button	
	CHILD_STATUS_EXIT,	 	//Status that enter the event of exit's button
}status_t;

typedef struct screen{
	WINDOW *win;
	rect_t background;
	rect_t foreground;
	bool screen_change;//Determine whether to change the window size
}screen_t;

typedef struct alphabet_game{
	screen_t scr;
	status_t status;
	unsigned int delay_time;
}alphabet_game_t;

extern alphabet_game_t *init_alphabet_game(void);
extern void exit_alphabet_game(alphabet_game_t *alphabet_game);
extern int set_alphabet_game_status(status_t *stts, status_t cur_status);
extern inline void sleep_delay_time(const unsigned int *time);

#endif	/*ALPHABET_GAME_H*/
