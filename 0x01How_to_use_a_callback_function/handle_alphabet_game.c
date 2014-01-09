/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */

#include "alphabet_game.h"
#include "handle_alphabet_game.h"

int handle_alphabet_game(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return AG_FAILED;
	}

	switch(ag->status){
	case MAIN_STATUS:
		mvwprintw(stdscr,3+MAIN_STATUS,3+MAIN_STATUS,"%d-%s-%d",__LINE__,__FUNCTION__,MAIN_STATUS);
		break;
	case CHILD_STATUS_START:
		mvwprintw(stdscr,3+CHILD_STATUS_START,3+CHILD_STATUS_START,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_START);
		break;
	case CHILD_STATUS_HELP:
		mvwprintw(stdscr,3+CHILD_STATUS_HELP,3+CHILD_STATUS_HELP,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_HELP);
		break;
	case CHILD_STATUS_EXIT:
		mvwprintw(stdscr,3+CHILD_STATUS_EXIT,3+CHILD_STATUS_EXIT,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_EXIT);
		break;
	default:		
		mvwprintw(stdscr,3+CHILD_STATUS_EXIT,3+CHILD_STATUS_EXIT,"%d-%s-default",__LINE__,__FUNCTION__);
		break;
	}
	
	return AG_SUCCESS;	
}

