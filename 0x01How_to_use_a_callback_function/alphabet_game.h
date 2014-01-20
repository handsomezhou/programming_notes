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
//#define ALPHABET_GAME_WIDGET_NUM		(3)
#define ALPHABET_GAME_WIDGET_OFFSET_Y	(ALPHABET_GAME_FOREGROUND_HEIGHT/(ALPHABET_GAME_WIDGET_NUM+1))
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
/*<==========alphabet game main status event==========*/

/*==========alphabet game child status event start==========>*/
//===========================start===========================>
#define ALPHABET_GAME_START_WIDGET_NUM	(26)
#define ALPHABET_GAME_START_LEVEL_NUM	(3)

#define ALPHABET_GAME_START_LEVEL_ONE	(6)
#define ALPHABET_GAME_START_LEVEL_TWO	(10)
#define ALPHABET_GAME_START_LEVEL_THREE	ALPHABET_GAME_START_WIDGET_NUM

/*A~F;A~N;A~Z*/
/*********************************/
/*					     		 */
/*	   O   G   H   I   J   P	 */		//   O(0,0);G(0,1);H(0,2);I(0,3);J(0,4);P(0,5);
/*								 */
/*   Q   R   A   B   C   S   T	 */		//Q(1,0);R(1,1);A(1,2);B(1,3);C(1,4);S(1,5);T(1,6);
/*								 */
/*   U   V   D   E   F   W   X	 */		//U(2,0);V(2,1);D(2,2);E(2,3);F(2,4);W(2,5);X(2,6);
/*								 */
/*     Y   K   L   M   N   Z  	 */		//   Y(3,0);K(3,1);L(3,2);M(3,3);N(3,4);Z(3,5);
/*								 */
/*********************************/
#define ALPHABET_GAME_ALPHABET_TOP				(ALPHABET_GAME_FOREGROUND_HEIGHT/4)// line=4
#define ALPHABET_GAME_ALPHABET_LEFT				(ALPHABET_GAME_FOREGROUND_WIDTH/7)   // max(row)=7
#define ALPHABET_GAME_ALPHABET_HIGHT			(1)
#define ALPHABET_GAME_ALPHABET_WIDTH			(1)
#define ALPHABET_GAME_ALPHABET_OFFSET_HIGHT		(ALPHABET_GAME_FOREGROUND_HEIGHT/4)
#define ALPHABET_GAME_ALPHABET_OFFSET_WIDTH		(ALPHABET_GAME_FOREGROUND_WIDTH/7)

#define SETTING_ALPHABET_GAME_Y(index)		(ALPHABET_GAME_ALPHABET_TOP+(index)*ALPHABET_GAME_ALPHABET_OFFSET_HIGHT)
#define SETTING_ALPHABET_GAME_X1(index) 	(ALPHABET_GAME_ALPHABET_LEFT+ALPHABET_GAME_ALPHABET_OFFSET_WIDTH/2+(index)*ALPHABET_GAME_ALPHABET_OFFSET_WIDTH)
#define SETTING_ALPHABET_GAME_X2(index) 	(ALPHABET_GAME_ALPHABET_LEFT+(index)*ALPHABET_GAME_ALPHABET_OFFSET_WIDTH)

#define ALPHABET_GAME_ALPHABET_A	"A"
#define ALPHABET_GAME_ALPHABET_B	"B"
#define ALPHABET_GAME_ALPHABET_C	"C"
#define ALPHABET_GAME_ALPHABET_D	"D"
#define ALPHABET_GAME_ALPHABET_E	"E"
#define ALPHABET_GAME_ALPHABET_F	"F"

#define ALPHABET_GAME_ALPHABET_G	"G"
#define ALPHABET_GAME_ALPHABET_H	"H"
#define ALPHABET_GAME_ALPHABET_I	"I"
#define ALPHABET_GAME_ALPHABET_J	"G"
#define ALPHABET_GAME_ALPHABET_K	"K"
#define ALPHABET_GAME_ALPHABET_L	"L"
#define ALPHABET_GAME_ALPHABET_M	"M"
#define ALPHABET_GAME_ALPHABET_N	"N"

#define ALPHABET_GAME_ALPHABET_O	"O"
#define ALPHABET_GAME_ALPHABET_P	"P"
#define ALPHABET_GAME_ALPHABET_Q	"Q"
#define ALPHABET_GAME_ALPHABET_R	"R"
#define ALPHABET_GAME_ALPHABET_S	"S"
#define ALPHABET_GAME_ALPHABET_T	"T"
#define ALPHABET_GAME_ALPHABET_U	"U"
#define ALPHABET_GAME_ALPHABET_V	"V"
#define ALPHABET_GAME_ALPHABET_W	"W"
#define ALPHABET_GAME_ALPHABET_X	"X"
#define ALPHABET_GAME_ALPHABET_Y	"Y"
#define ALPHABET_GAME_ALPHABET_Z	"Z"
//<===========================start===========================

//===========================help===========================>
#define ALPHABET_GAME_HELP_WIDGET_NUM	(1)
//<==========================help============================

//===========================exit===========================>
//<==========================exit============================
/*<==========alphabet game child status event end==========*/


typedef enum{
	MAIN_STATUS=0,		 	//Status that not enter the event of any button
	CHILD_STATUS_START,		//Status that enter the event of start's button
	CHILD_STATUS_HELP,		//Status that enter the event of help's button	
	CHILD_STATUS_EXIT,	 	//Status that enter the event of exit's button
}status_t;

typedef enum{
	MAIN_STATUS_START=0,
	MAIN_STATUS_HELP,
	MAIN_STATUS_EXIT,
	ALPHABET_GAME_WIDGET_NUM,
}main_status_t;
#if 0
typedef enum{

}child_status_start_t;

typedef enum{

}child_status_help_t;

typedef enum{

}child_status_exit_t;
#endif

typedef enum color{
	//window 
	COLOR_FOREGROUND=1,
	//button
	COLOR_ICON_NORMAL,
	COLOR_ICON_SELECT,
	//title
	COLOR_TITLE,
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
	p_void_ctrl_tool_t child_status_start;
	unsigned int delay_time;
}alphabet_game_t;

extern alphabet_game_t *init_alphabet_game(void);
extern void exit_alphabet_game(alphabet_game_t *alphabet_game);
extern int set_alphabet_game_status(status_t *stts, status_t cur_status);
extern void sleep_delay_time(const unsigned int *time);
extern int init_m_evt_code(m_evt_code_t *p_m_evt_code);
#endif	/*ALPHABET_GAME_H*/
