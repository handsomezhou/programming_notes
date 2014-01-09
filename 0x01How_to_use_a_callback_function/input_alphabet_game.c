/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */

#include "alphabet_game.h"
#include "input_alphabet_game.h"

static int get_m_evt_code(m_evt_code_t *m_evt_code);

extern int input_alphabet_game(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return AG_FAILED;
	}
	get_m_evt_code(&ag->m_evt_code);
	
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

static int get_m_evt_code(m_evt_code_t *m_evt_code)
{

	return AG_SUCCESS;
}

