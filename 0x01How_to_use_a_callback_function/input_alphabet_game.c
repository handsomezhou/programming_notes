/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */
#include "alphabet_game.h"
#include "input_alphabet_game.h"

static int get_m_evt_code(alphabet_game_t *alphabet_game,m_evt_code_t *m_evt_code);

extern int input_alphabet_game(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return AG_FAILED;
	}
	get_m_evt_code(ag,&ag->m_evt_code);
	
#if 0
	switch(ag->status){
		case MAIN_STATUS:
			mvwprintw(stdscr,1+MAIN_STATUS,1+MAIN_STATUS,"%d-%s-%d",__LINE__,__FUNCTION__,MAIN_STATUS);
			break;
		case CHILD_STATUS_START:
			mvwprintw(stdscr,1+CHILD_STATUS_START,1+CHILD_STATUS_START,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_START);
			break;
		case CHILD_STATUS_HELP:
			mvwprintw(stdscr,1+CHILD_STATUS_HELP,1+CHILD_STATUS_HELP,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_HELP);
			break;
		case CHILD_STATUS_EXIT:
			mvwprintw(stdscr,1+CHILD_STATUS_EXIT,1+CHILD_STATUS_EXIT,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_EXIT);
			break;
		default:
			mvwprintw(stdscr,1+CHILD_STATUS_EXIT,1+CHILD_STATUS_EXIT,"%d-%s-default",__LINE__,__FUNCTION__);
			break;
	}
#endif

	return AG_SUCCESS;
}

static int get_m_evt_code(alphabet_game_t *alphabet_game,m_evt_code_t *m_evt_code)
{
	alphabet_game_t *ag=alphabet_game;
	m_evt_code_t *mec=m_evt_code;
	if((NULL==ag)||(NULL==mec)){
		return AG_FAILED;
	}

	init_m_evt_code(mec);

	int chr=NO_INPUT_DATA;
	mousemask(ALL_MOUSE_EVENTS,NULL);
	chr=wgetch(ag->scr.win);
	switch(chr){
		case NO_INPUT_DATA://no need to deal
			mvwprintw(ag->scr.win,8,1,"%s","NO_INPUT_DATA");
			ag->m_evt_code.m_evt_type=M_EVT_NO_INPUT;
			ag->m_evt_code.m_evt_param.other_t.other=NO_INPUT_DATA;
			break;
		case KEY_MOUSE:	//mouse event
			mvwprintw(ag->scr.win,10,1,"%s","KEY_MOUSE");
			ag->m_evt_code.m_evt_type=M_EVT_MOUSE;
			getmouse(&ag->m_evt_code.m_evt_param.mouse_t.mouse);
			break;
		default:		//key event
			mvwprintw(ag->scr.win,12,1,"%s---[%d]","KEY_EVENT",chr);				
			ag->m_evt_code.m_evt_type=M_EVT_KEY;
			ag->m_evt_code.m_evt_param.key_t.key=chr;
			break;
	}
	
	return AG_SUCCESS;
}

