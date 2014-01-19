/**
  *  Copyright (C) 2013-12-09  Handsome Zhou
  */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "data_type.h"
#include "message_event.h"
#include "ctrl_tool.h"
#include "alphabet_game.h"
#include "output_alphabet_game.h"


static int init_screen(screen_t *screen);
static void exit_screen(screen_t *screen);

static int set_delay_time(unsigned int *time, unsigned int delay_time);

/*alphabet game main status event*/
static int alphabet_game_paint(p_void_data_t p_void_data, rect_t *p_rect,int index, bool sel_flag);
static int alphabet_game_pen_up(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_pen_down(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_select(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_enter(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_exit(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);

static ctrl_tool_callback_t alphabet_game_event={
	alphabet_game_paint,
	alphabet_game_pen_up,
	alphabet_game_pen_down,
	alphabet_game_select,
	alphabet_game_enter,
	alphabet_game_exit,	
};

static ctrl_tool_res_t alphabet_game_res[ALPHABET_GAME_WIDGET_NUM]={
	{{ALPHABET_GAME_START_Y,ALPHABET_GAME_START_X,ALPHABET_GAME_START_HEIGHT,ALPHABET_GAME_START_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_START},

	{{ALPHABET_GAME_HELP_Y,ALPHABET_GAME_HELP_X,ALPHABET_GAME_HELP_HEIGHT,ALPHABET_GAME_HELP_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_HELP},

	{{ALPHABET_GAME_EXIT_Y,ALPHABET_GAME_EXIT_X,ALPHABET_GAME_EXIT_HEIGHT,ALPHABET_GAME_EXIT_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_EXIT},			
};

/*alphabet game child status event:game start,game help,game exit*/
static int alphabet_game_start_paint(p_void_data_t p_void_data, rect_t *p_rect,int index, bool sel_flag);
static int alphabet_game_start_pen_up(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_start_pen_down(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_start_select(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_start_enter(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_start_exit(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);

static ctrl_tool_callback_t alphabet_game_start_event={
	alphabet_game_start_paint,
	alphabet_game_start_pen_up,
	alphabet_game_start_pen_down,
	alphabet_game_start_select,
	alphabet_game_start_enter,
	alphabet_game_start_exit,	
};

static int alphabet_game_help_paint(p_void_data_t p_void_data, rect_t *p_rect,int index, bool sel_flag);
static int alphabet_game_help_pen_up(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_help_pen_down(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_help_select(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_help_enter(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_help_exit(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);

static ctrl_tool_callback_t alphabet_game_help_event={
	alphabet_game_help_paint,
	alphabet_game_help_pen_up,
	alphabet_game_help_pen_down,
	alphabet_game_help_select,
	alphabet_game_help_enter,
	alphabet_game_help_exit,	
};

static int alphabet_game_exit_paint(p_void_data_t p_void_data, rect_t *p_rect,int index, bool sel_flag);
static int alphabet_game_exit_pen_up(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_exit_pen_down(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_exit_select(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_exit_enter(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_exit_exit(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);

static ctrl_tool_callback_t alphabet_game_exit_event={
	alphabet_game_exit_paint,
	alphabet_game_exit_pen_up,
	alphabet_game_exit_pen_down,
	alphabet_game_exit_select,
	alphabet_game_exit_enter,
	alphabet_game_exit_exit,	
};

alphabet_game_t *init_alphabet_game(void)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	alphabet_game_t *ag=NULL;
	int ret=AG_FAILED;

	ag=(alphabet_game_t *)malloc(sizeof(alphabet_game_t));

	if(NULL==ag){
		return NULL;
	}
	
	ret=init_screen(&ag->scr);
	if(AG_FAILED==ret){
		//break;
	}

	set_alphabet_game_status(&ag->status,MAIN_STATUS);
	
	set_delay_time(&ag->delay_time,DELAY_TIME);

	ag->main_status=ctrl_tool_init(ALPHABET_GAME_WIDGET_NUM,alphabet_game_res,&alphabet_game_event);
	if(NULL==ag->main_status){
		free(ag);
		ag=NULL;
		
		return NULL;
	}

	return ag;
}

void exit_alphabet_game(alphabet_game_t *alphabet_game)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return;
	}
	ctrl_tool_free(ag->main_status);
	
	exit_screen(&ag->scr);
	
	free(ag);
	ag=NULL;
	
	return ;
}

int set_alphabet_game_status(status_t *status, status_t cur_status)
{
	status_t *stts=status;
	if(NULL==stts){
		return AG_FAILED;
	}
	*stts=cur_status;

	return AG_SUCCESS;
}

void sleep_delay_time(const unsigned int *time)
{
	usleep(((NULL==time)?(DELAY_TIME_MIN):(*time)));	
}

int init_m_evt_code(m_evt_code_t *p_m_evt_code)
{
	m_evt_code_t *m_evt_code=p_m_evt_code;
	if(NULL==m_evt_code){
		return AG_FAILED;
	}
	
	m_evt_code->m_evt_type=M_EVT_NO_INPUT;
	m_evt_code->m_evt_param.no_input_t.no_input=NO_INPUT_DATA;
	memset(&m_evt_code->m_evt_param.mouse_t.mouse,0,sizeof(m_evt_code->m_evt_param.mouse_t.mouse));
	m_evt_code->m_evt_param.key_t.key=NO_KEY_DATA;
	m_evt_code->m_evt_param.other_t.other=NO_OTHER_DATA;

	return AG_SUCCESS;
}

static int init_screen(screen_t *screen)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	screen_t *scr=screen;
	if(NULL==scr){
		return AG_FAILED;
	}

	//init ncurses
	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);
	clear();
	if(has_colors()){
		start_color();
		init_pair(COLOR_FOREGROUND,COLOR_BLUE,COLOR_BLACK);
		init_pair(COLOR_ICON_NORMAL,COLOR_BLUE,COLOR_BLACK);
		init_pair(COLOR_ICON_SELECT,COLOR_GREEN,COLOR_BLACK);
		
	}

	scr->win=stdscr;

	scr->background.top=ALPHABET_GAME_BACKGROUND_TOP;
	scr->background.left=ALPHABET_GAME_BACKGROUND_LEFT;
	scr->background.height=(int16_t)getmaxy(scr->win);
	scr->background.width=(int16_t)getmaxx(scr->win);

	scr->foreground.height=(int16_t)ALPHABET_GAME_FOREGROUND_HEIGHT;
	scr->foreground.width=(int16_t)ALPHABET_GAME_FOREGROUND_WIDTH;
	scr->foreground.top=(scr->background.height-scr->foreground.height)/2;	
	scr->foreground.left=(scr->background.width-scr->foreground.width)/2;

	wrefresh(scr->win);
	keypad(scr->win,TRUE);
	nodelay(stdscr,TRUE);
	
	return AG_SUCCESS;
}

static void exit_screen(screen_t *screen)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	screen_t *scr=screen;
	if(NULL==scr){
		return;
	}

	werase(scr->win);
	endwin();
	return ;
}

static int set_delay_time(unsigned int *time, unsigned int delay_time)
{
	unsigned int *tm=time;
	if(NULL==tm){
		return AG_FAILED;
	}

	*tm=( ((delay_time>=DELAY_TIME_MIN)&&(delay_time<=DELAY_TIME_MAX))?(delay_time):(DELAY_TIME_MIN) );
	
	return AG_SUCCESS;
}

static int alphabet_game_paint(p_void_data_t p_void_data, rect_t *p_rect, int index, bool sel_flag)
{
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	screen_t *scr=&ag->scr;
	rect_t *rct=p_rect;
	if(NULL==scr||NULL==rct){
		return AG_FAILED;
	}
	
//	draw_main_status_foreground(scr);
	show_button(scr,rct->top,rct->left,sel_flag,alphabet_game_res[index].pdata,A_BOLD);

	return AG_SUCCESS;
}
	
static int alphabet_game_pen_up(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_pen_down(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	int index=sel_index;
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==ag)||(NULL==m_evt_code)){
		return AG_FAILED;
	}

	switch(index){
		case MAIN_STATUS_START:
			ag->status=CHILD_STATUS_START;
			break;
		case MAIN_STATUS_HELP:
			ag->status=CHILD_STATUS_HELP;
			break;
		case MAIN_STATUS_EXIT:
			ag->status=CHILD_STATUS_EXIT;
			break;
		default:
			break;
	}
	

	return AG_SUCCESS;
}

static int alphabet_game_select(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_enter(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	int index=sel_index;
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==ag)||(NULL==m_evt_code)){
		return AG_FAILED;
	}

	switch(index){
		case MAIN_STATUS_START:
			ag->status=CHILD_STATUS_START;
			break;
		case MAIN_STATUS_HELP:
			ag->status=CHILD_STATUS_HELP;
			break;
		case MAIN_STATUS_EXIT:
			ag->status=CHILD_STATUS_EXIT;
			break;
		default:
			break;
	}
	
	return AG_SUCCESS;
}

static int alphabet_game_exit(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==ag)||(NULL==m_evt_code)){
		return AG_FAILED;
	}

	ag->status=CHILD_STATUS_EXIT;
		
	return AG_SUCCESS;
}




static int alphabet_game_start_paint(p_void_data_t p_void_data, rect_t *p_rect,int index, bool sel_flag)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_start_pen_up(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_start_pen_down(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_start_select(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_start_enter(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_start_exit(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}



static int alphabet_game_help_paint(p_void_data_t p_void_data, rect_t *p_rect,int index, bool sel_flag)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_help_pen_up(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)	
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_help_pen_down(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)	
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_help_select(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)	
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_help_enter(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_help_exit(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}


static int alphabet_game_exit_paint(p_void_data_t p_void_data, rect_t *p_rect,int index, bool sel_flag)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_exit_pen_up(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)	
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_exit_pen_down(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)	
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_exit_select(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_exit_enter(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_exit_exit(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}
