/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */
#include "alphabet_game.h"
#include "handle_alphabet_game.h"

static int handle_main_status(alphabet_game_t *alphabet_game);
static int handle_child_status_start(alphabet_game_t *alphabet_game);
static int handle_child_status_help(alphabet_game_t *alphabet_game);
static int handle_child_status_exit(alphabet_game_t *alphabet_game);
static int handle_child_status_default(alphabet_game_t * alphabet_game);

int handle_alphabet_game(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return AG_FAILED;
	}

	switch(ag->status){
	case MAIN_STATUS:
		handle_main_status(ag);
		break;
	case CHILD_STATUS_START:
		handle_child_status_start(ag);
		break;
	case CHILD_STATUS_HELP:
		handle_child_status_help(ag);
		break;
	case CHILD_STATUS_EXIT:
		handle_child_status_exit(ag);
		break;
	default:		
		handle_child_status_default(ag);
		break;
	}
	
	return AG_SUCCESS;	
}


static int handle_main_status(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return AG_FAILED;
	}
	
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	//mvwprintw(ag->scr.win,3,10,"I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	ctrl_tool_handle(&ag->scr,ag->main_status,&ag->m_evt_code);
	
	return AG_SUCCESS;
}

static int handle_child_status_start(alphabet_game_t *alphabet_game)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return AG_FAILED;
	}

	ctrl_tool_handle(&ag->scr,ag->child_status_start,&ag->m_evt_code);
	
	return AG_SUCCESS;
}

static int handle_child_status_help(alphabet_game_t *alphabet_game)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return AG_FAILED;
	}

	ctrl_tool_handle(&ag->scr,ag->child_status_help,&ag->m_evt_code);

	return AG_SUCCESS;
}

static int handle_child_status_exit(alphabet_game_t *alphabet_game)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int handle_child_status_default(alphabet_game_t * alphabet_game)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}	
