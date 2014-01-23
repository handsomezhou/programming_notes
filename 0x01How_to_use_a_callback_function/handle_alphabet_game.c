/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */
#include <stdlib.h>
#include <time.h>
#include "alphabet_game.h"
#include "handle_alphabet_game.h"

static int handle_main_status(alphabet_game_t *alphabet_game);
static int handle_child_status_start(alphabet_game_t *alphabet_game);
static int handle_child_status_help(alphabet_game_t *alphabet_game);
static int handle_child_status_exit(alphabet_game_t *alphabet_game);
static int handle_child_status_default(alphabet_game_t * alphabet_game);

static int produce_random_number(int start_num, int end_num);


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

int produce_random_alphabet_sequence(alphabet_game_t *alphabet_game, int alphabet_sequence_num)
{	
	alphabet_game_t *ag=alphabet_game;
	int asn=alphabet_sequence_num;
	int i=0,j=0,random=0,rand_num=0;
	bool is_random_success=FALSE;
	if(NULL==ag){
		return AG_FAILED;
	}
	srand((unsigned int)time(NULL));

	ag->alphabet_id[0]=produce_random_number(0,asn-1);
	rand_num=1;
	for(i=rand_num; i<asn; i++){
		while(1){
			is_random_success=TRUE;
			random=produce_random_number(0,asn-1);
			//ag->alphabet_id[i]=produce_random_number(0,asn-1);
			for(j=0; j<rand_num; j++){
				if(random==ag->alphabet_id[j]){
					is_random_success=FALSE;
					break;
				}
			}

			if(TRUE==is_random_success){
				ag->alphabet_id[rand_num]=random;
				rand_num++;
				break;
			}			
		}
	}
	
	return AG_SUCCESS;
}

bool judge_cur_sort_foremost_alphabet(alphabet_game_t *alphabet_game, int index, int sel_index)
{
	alphabet_game_t *ag=alphabet_game;
	int i=0,j=0,total_alphabet_num=0;
	int ndx=index;
	int sel_ndx=sel_index;
	if(NULL==ag){
		return FALSE;
	}

	total_alphabet_num=get_total_alphabet_num(ag);
	for(i=0,j=0; i<total_alphabet_num; i++){
		if(ndx<=ag->alphabet_id[i]){
			j++;
		}
	}

	if(j>=get_remain_alphabet_num(ag)){
		return TRUE;
	}
		
	return FALSE;
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
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return AG_FAILED;
	}
	
	if(ctrl_tool_handle(&ag->scr,ag->child_status_start,&ag->m_evt_code)!=CTRL_TOOL_FAILED){
		if(TRUE==is_enter_next_level(ag)){
			printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
			if(NULL!=ag->child_status_start){
				ctrl_tool_free(ag->child_status_start);
				ag->child_status_start=NULL;
			}
			
			ag->child_status_start=ctrl_tool_init(get_total_alphabet_num(ag),alphabet_game_start_res,&alphabet_game_start_event);
			produce_random_alphabet_sequence(ag,get_total_alphabet_num(ag));
			set_enter_next_level(ag,FALSE);
			set_update_screen(ag,TRUE);
			
		}	
	}
	
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

static int produce_random_number(int start_num, int end_num)
{
	int start,end,rand_num;

	(start_num<=end_num)?(start=start_num,end=end_num):(start=end_num,end=start_num);
	
	rand_num=rand()%(end-start+1)+start;

	return rand_num;
}
