/**
  *  Copyright (C) 2013-12-09  Handsome Zhou
  */

#ifndef ALPHABET_GAME_H
#define ALPHABET_GAME_H

#include <stdio.h>
#include <ncurses.h>
#include "data_type.h"
#include "message_event.h"
#include "ctrl_tool.h"


#define GAME_NAME		"Alphabet Game"

#define AG_SUCCESS		(0)
#define AG_FAILED		(-1)

#define DELAY_TIME_MAX	500000//us
#define DELAY_TIME_MIN	 50000//us
#define DELAY_TIME		250000//us





#define ALPHABET_GAME_BACKGROUND_TOP 	(0)
#define ALPHABET_GAME_BACKGROUND_LEFT	(0)
//#define ALPHABET_GAME_BACKGROUND_HEIGHT	(0)	//Get background's width and height according to window size
//#define ALPHABET_GAME_BACKGROUND_WIDTH	(0)	

//#define ALPHABET_GAME_FOREGROUND_TOP	(0)		//Get background's top and left according to background window size
//#define ALPHABET_GAME_FOREGROUND_LEFT	(0)
#define ALPHABET_GAME_FOREGROUND_HEIGHT	(21)
#define ALPHABET_GAME_FOREGROUND_WIDTH	(60)

/*==========alphabet game main status event==========>*/
#define ALPHABET_GAME_WIDGET_NUM		(3)

#define ALPHABET_GAME_WIDGET_OFFSET_Y	(ALPHABET_GAME_FOREGROUND_HEIGHT/ALPHABET_GAME_WIDGET_NUM)
#define ALPHABET_GAME_START 			"start"
#define ALPHABET_GAME_START_Y			(0+ALPHABET_GAME_WIDGET_OFFSET_Y)
#define ALPHABET_GAME_START_X			((ALPHABET_GAME_FOREGROUND_WIDTH-sizeof(ALPHABET_GAME_START))/2)
#define ALPHABET_GAME_START_HEIGHT		(1)
#define ALPHABET_GAME_START_WIDTH		(sizeof(ALPHABET_GAME_START)-1)

#define ALPHABET_GAME_HELP				"help"
#define ALPHABET_GAME_HELP_Y			(ALPHABET_GAME_START_Y+ALPHABET_GAME_WIDGET_OFFSET_Y)
#define ALPHABET_GAME_HELP_X			ALPHABET_GAME_START_X//((ALPHABET_GAME_FOREGROUND_WIDTH-sizeof(ALPHABET_GAME_HELP))/2)
#define ALPHABET_GAME_HELP_HEIGHT		(1)
#define ALPHABET_GAME_HELP_WIDTH		(sizeof(ALPHABET_GAME_HELP)-1)

#define ALPHABET_GAME_EXIT				"exit"
#define ALPHABET_GAME_EXIT_Y			(ALPHABET_GAME_HELP_Y+ALPHABET_GAME_WIDGET_OFFSET_Y)
#define ALPHABET_GAME_EXIT_X			ALPHABET_GAME_START_X//((ALPHABET_GAME_FOREGROUND_WIDTH-sizeof(ALPHABET_GAME_EXIT))/2)
#define ALPHABET_GAME_EXIT_HEIGHT		(1)
#define ALPHABET_GAME_EXIT_WIDTH		(sizeof(ALPHABET_GAME_EXIT)-1)

/*<==========alphabet game child status event==========*/
#define ALPHABET_GAME_START_WIDGET_NUM	(26)
#define ALPHABET_GAME_HELP_WIDGET_NUM	(1)

typedef enum{
	MAIN_STATUS=0,		 	//Status that not enter the event of any button
	CHILD_STATUS_START,		//Status that enter the event of start's button
	CHILD_STATUS_HELP,		//Status that enter the event of help's button	
	CHILD_STATUS_EXIT,	 	//Status that enter the event of exit's button
}status_t;

typedef enum color{
	//window 
	COLOR_FOREGROUND=1,
	//button
	COLOR_ICON_NORMAL,
	COLOR_ICON_SELECT,
}color_t;
typedef WINDOW window_t;
typedef struct screen{
	window_t *win;
	rect_t background;
	rect_t foreground;
	bool screen_change;//Determine whether to change the window size
}screen_t;

typedef struct alphabet_game{
	screen_t scr;
	status_t status;
	m_evt_code_t m_evt_code;
	p_void_ctrl_tool_t main_status;
	unsigned int delay_time;
}alphabet_game_t;

extern alphabet_game_t *init_alphabet_game(void);
extern void exit_alphabet_game(alphabet_game_t *alphabet_game);
extern int set_alphabet_game_status(status_t *stts, status_t cur_status);
extern void sleep_delay_time(const unsigned int *time);
extern int init_m_evt_code(m_evt_code_t *m_evt_code);
#endif	/*ALPHABET_GAME_H*/
