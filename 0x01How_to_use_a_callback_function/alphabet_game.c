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

static int set_status(status_t *stts, status_t cur_status);
static int set_time(unsigned int *time_usec, unsigned int delay_time_usec);
static int set_level(int *level,int cur_level);
static int set_alphabet_num(int *alphabet_num, int cur_alphabet_num);


/*alphabet game main status event*/
static int alphabet_game_paint(p_void_data_t p_void_data, rect_t *p_rect,int index, bool sel_flag);
static int alphabet_game_pen_up(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_pen_down(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_select(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_enter(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_exit(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);

static int alphabet_game_response_focus(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);

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

static int alphabet_game_start_response_focus(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);


ctrl_tool_callback_t alphabet_game_start_event={
	alphabet_game_start_paint,
	alphabet_game_start_pen_up,
	alphabet_game_start_pen_down,
	alphabet_game_start_select,
	alphabet_game_start_enter,
	alphabet_game_start_exit,	
};

ctrl_tool_res_t alphabet_game_start_res[ALPHABET_GAME_START_WIDGET_NUM]={
	{{SETTING_ALPHABET_GAME_Y(1),SETTING_ALPHABET_GAME_X2(2),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_A},

	{{SETTING_ALPHABET_GAME_Y(1),SETTING_ALPHABET_GAME_X2(3),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_B},

	{{SETTING_ALPHABET_GAME_Y(1),SETTING_ALPHABET_GAME_X2(4),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_C},

	{{SETTING_ALPHABET_GAME_Y(2),SETTING_ALPHABET_GAME_X2(2),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_D},

	{{SETTING_ALPHABET_GAME_Y(2),SETTING_ALPHABET_GAME_X2(3),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_E},

	{{SETTING_ALPHABET_GAME_Y(2),SETTING_ALPHABET_GAME_X2(4),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_F},



	{{SETTING_ALPHABET_GAME_Y(0),SETTING_ALPHABET_GAME_X1(1),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_G},

	{{SETTING_ALPHABET_GAME_Y(0),SETTING_ALPHABET_GAME_X1(2),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_H},

	{{SETTING_ALPHABET_GAME_Y(0),SETTING_ALPHABET_GAME_X1(3),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_I},

	{{SETTING_ALPHABET_GAME_Y(0),SETTING_ALPHABET_GAME_X1(4),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_J},

	{{SETTING_ALPHABET_GAME_Y(3),SETTING_ALPHABET_GAME_X1(1),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_K},

	{{SETTING_ALPHABET_GAME_Y(3),SETTING_ALPHABET_GAME_X1(2),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_L},

	{{SETTING_ALPHABET_GAME_Y(3),SETTING_ALPHABET_GAME_X1(3),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_M},

	{{SETTING_ALPHABET_GAME_Y(3),SETTING_ALPHABET_GAME_X1(4),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_N},



	{{SETTING_ALPHABET_GAME_Y(0),SETTING_ALPHABET_GAME_X1(0),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_O},

	{{SETTING_ALPHABET_GAME_Y(0),SETTING_ALPHABET_GAME_X1(5),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_P},

	{{SETTING_ALPHABET_GAME_Y(1),SETTING_ALPHABET_GAME_X2(0),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_Q},

	{{SETTING_ALPHABET_GAME_Y(1),SETTING_ALPHABET_GAME_X2(1),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_R},

	{{SETTING_ALPHABET_GAME_Y(1),SETTING_ALPHABET_GAME_X2(5),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_S},
	
	{{SETTING_ALPHABET_GAME_Y(1),SETTING_ALPHABET_GAME_X2(6),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_T},

	{{SETTING_ALPHABET_GAME_Y(2),SETTING_ALPHABET_GAME_X2(0),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
			COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_U},
	
	{{SETTING_ALPHABET_GAME_Y(2),SETTING_ALPHABET_GAME_X2(1),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_V},

	{{SETTING_ALPHABET_GAME_Y(2),SETTING_ALPHABET_GAME_X2(5),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_W},
	
	{{SETTING_ALPHABET_GAME_Y(2),SETTING_ALPHABET_GAME_X2(6),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_X},

	{{SETTING_ALPHABET_GAME_Y(3),SETTING_ALPHABET_GAME_X1(0),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_Y},
	
	{{SETTING_ALPHABET_GAME_Y(3),SETTING_ALPHABET_GAME_X1(5),ALPHABET_GAME_ALPHABET_HIGHT,ALPHABET_GAME_ALPHABET_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_ALPHABET_Z},	
};

static int alphabet_game_help_paint(p_void_data_t p_void_data, rect_t *p_rect,int index, bool sel_flag);
static int alphabet_game_help_pen_up(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_help_pen_down(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_help_select(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_help_enter(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_help_exit(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);

static ctrl_tool_res_t alphabet_game_help_res[ALPHABET_GAME_HELP_WIDGET_NUM]={
	{{ALPHABET_GAME_HELP_BACK_Y,ALPHABET_GAME_HELP_BACK_X,ALPHABET_GAME_HELP_BACK_HEIGHT,ALPHABET_GAME_HELP_BACK_WIDTH},\
		COLOR_ICON_NORMAL,COLOR_ICON_SELECT,ALPHABET_GAME_HELP_BACK},
};

static ctrl_tool_callback_t alphabet_game_help_event={
	alphabet_game_help_paint,
	alphabet_game_help_pen_up,
	alphabet_game_help_pen_down,
	alphabet_game_help_select,
	alphabet_game_help_enter,
	alphabet_game_help_exit,	
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

	set_cur_status(ag,MAIN_STATUS);
	set_last_status(ag,OTHER_STATUS);
	set_cur_level(ag,LEVEL_ONE);
	set_remain_time(ag,ALPHABET_GAME_START_TIME_ONE);
	set_total_alphabet_num(ag,ALPHABET_GAME_START_LEVEL_ONE_ALPHABET_NUM);
	set_remain_alphabet_num(ag,get_total_alphabet_num(ag));
	set_enter_next_level(ag,TRUE);
	set_delay_time(ag,DELAY_TIME);
	
	ret=init_screen(&ag->scr);
	if(AG_FAILED==ret){
		free(ag);
		ag=NULL;

		return NULL;
	}

	ag->main_status=ctrl_tool_init(ALPHABET_GAME_WIDGET_NUM,alphabet_game_res,&alphabet_game_event);
	if(NULL==ag->main_status){
		free(ag);
		ag=NULL;
		
		return NULL;
	}

	ag->child_status_start=ctrl_tool_init(get_total_alphabet_num(ag),alphabet_game_start_res,&alphabet_game_start_event);
	if(NULL==ag->child_status_start){
		ctrl_tool_free(ag->main_status);
		ag->main_status=NULL;

		free(ag);
		ag=NULL;
		
	}

	ag->child_status_help=ctrl_tool_init(ALPHABET_GAME_HELP_WIDGET_NUM,alphabet_game_help_res,&alphabet_game_help_event);
	if(NULL==ag->child_status_help){
		ctrl_tool_free(ag->child_status_start);
		ag->child_status_start=NULL;
		
		ctrl_tool_free(ag->main_status);
		ag->main_status=NULL;

		free(ag);
		ag=NULL;
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
	
	ctrl_tool_free(ag->child_status_help);	
	ctrl_tool_free(ag->child_status_start);
	ctrl_tool_free(ag->main_status);
	exit_screen(&ag->scr);
	
	free(ag);
	ag=NULL;
	
	return ;
}

int set_cur_status(alphabet_game_t *alphabet_game, status_t status)
{
	alphabet_game_t *ag=alphabet_game;
	status_t stts=status;
	if(NULL==ag){
		return AG_FAILED;
	}

	return set_status(&ag->status,stts);
}

int get_cur_status(const alphabet_game_t *alphabet_game)
{
	const alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return MAIN_STATUS;
	}
	
	return  ag->status;
}

int set_last_status(alphabet_game_t *alphabet_game, status_t status)
{
	alphabet_game_t *ag=alphabet_game;
	status_t stts=status;
	if(NULL==ag){
		return AG_FAILED;
	}

	return set_status(&ag->last_status,stts);
}

int get_last_status(const alphabet_game_t *alphabet_game)
{
	const alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return MAIN_STATUS;
	}
	
	return  ag->last_status;
}

int set_cur_level(alphabet_game_t *alphabet_game, int level)
{
	alphabet_game_t *ag=alphabet_game;
	int lvl=level;
	if(NULL==ag){
		return AG_FAILED;
	}

	return set_level(&ag->level,lvl);
}

int get_cur_level(const alphabet_game_t *alphabet_game)
{
	const alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return LEVEL_ONE;
	}

	return ag->level;
}

int set_remain_time(alphabet_game_t *alphabet_game, int sec)
{
	alphabet_game_t *ag=alphabet_game;
	int sc=sec;
	if(NULL==ag){
		return AG_FAILED;
	}

	ag->remain_time=sc;
	
	return AG_SUCCESS;
}

int get_remain_time(const alphabet_game_t *alphabet_game)
{
	const alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return (ALPHABET_GAME_START_TIME_ZERO);
	}

	return ag->remain_time;
}

int dec_remain_time(alphabet_game_t *alphabet_game, int unit_time_sec)
{
	alphabet_game_t *ag=alphabet_game;
	int sec=unit_time_sec;
	if(NULL==ag){
		return ALPHABET_GAME_START_TIME_ZERO;
	}

	sec=((sec>=ALPHABET_GAME_START_MIN_UNIT_TIME)&&(sec<=ALPHABET_GAME_START_MAX_UNIT_TIME))?(sec):(ALPHABET_GAME_START_MIN_UNIT_TIME);
	ag->remain_time -=sec;
	
	return ag->remain_time;
}
	
int set_total_alphabet_num(alphabet_game_t *alphabet_game, int alphabet_num)
{
	alphabet_game_t *ag=alphabet_game;
	int an=alphabet_num;
	if(NULL==ag){
		return AG_FAILED;
	}

	set_alphabet_num(&ag->total_alphabet_num,an);
	
	return AG_SUCCESS;
}

int get_total_alphabet_num(const alphabet_game_t *alphabet_game)
{
	const alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return ALPHABET_GAME_START_LEVEL_ZERO_ALPHABET_NUM;
	}

	return 	ag->total_alphabet_num;	
}

int set_remain_alphabet_num(alphabet_game_t *alphabet_game, int alphabet_num)
{
	alphabet_game_t *ag=alphabet_game;
	int an=alphabet_num;
	if(NULL==ag){
		return AG_FAILED;
	}

	set_alphabet_num(&ag->remain_alphabet_num,an);
	
	return AG_SUCCESS;
}

int get_remain_alphabet_num(const alphabet_game_t *alphabet_game)
{
	const alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return ALPHABET_GAME_START_LEVEL_ZERO_ALPHABET_NUM;
	}

	return 	ag->remain_alphabet_num;	
}

int dec_remain_alphabet_num(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return ALPHABET_GAME_START_LEVEL_ZERO_ALPHABET_NUM;
	}
	
	return (--ag->remain_alphabet_num);
}

int set_enter_next_level(alphabet_game_t *alphabet_game, bool next_level_start)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return AG_FAILED;
	}

	if(FALSE==next_level_start){
		ag->is_enter_next_level=FALSE;
	}else{
		ag->is_enter_next_level=TRUE;
	}
	
	return AG_SUCCESS;
}

bool is_enter_next_level(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return FALSE;
	}

	return ag->is_enter_next_level;
}

int set_delay_time(alphabet_game_t *alphabet_game, unsigned int usec)
{
	alphabet_game_t *ag=alphabet_game;
	unsigned int us=usec;
	if(NULL==ag){
		return AG_FAILED;
	}

	return set_time(&ag->delay_time,us);
}

unsigned int get_delay_time(const alphabet_game_t *alphabet_game)
{
	const alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return DELAY_TIME_MIN;
	}

	return (ag->delay_time);
}


void sleep_delay_time(unsigned int usec)
{
	unsigned int us=usec;
	usleep(((us<DELAY_TIME_MIN)?(DELAY_TIME_MIN):(us)));	
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
		init_pair(COLOR_TITLE,COLOR_MAGENTA,COLOR_BLACK);
		init_pair(COLOR_TEXT_CONTENT,COLOR_YELLOW,COLOR_BLACK);
		init_pair(COLOR_MSG_WARNING,COLOR_YELLOW,COLOR_BLACK);
		init_pair(COLOR_MSG_ERROR,COLOR_RED,COLOR_BLACK);
		init_pair(COLOR_MSG_RIGHT,COLOR_GREEN,COLOR_BLACK);
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

static int set_status(status_t *status, status_t cur_status)
{
	status_t *stts=status;
	if(NULL==stts){
		return AG_FAILED;
	}
	
	*stts=cur_status;

	return AG_SUCCESS;
}

static int set_time(unsigned int *time_usec, unsigned int delay_time_usec)
{
	unsigned int *tm_us=time_usec;
	unsigned int delay_tm_us=delay_time_usec;
	if(NULL==tm_us){
		return AG_FAILED;
	}
	
	*tm_us=( ((delay_tm_us>=DELAY_TIME_MIN)&&(delay_tm_us<=DELAY_TIME_MAX))?(delay_tm_us):(DELAY_TIME_MIN) );
	
	return AG_SUCCESS;
}


static int set_level(int *level,int cur_level)
{
	int *lvl=level;
	if(NULL==lvl){
		return AG_FAILED;
	}

	*lvl=cur_level;

	return AG_SUCCESS;
}

static int set_alphabet_num(int *alphabet_num, int cur_alphabet_num)
{
	int *an=alphabet_num;
	int cur_an=cur_alphabet_num;
	if(NULL==an){
		return AG_FAILED;
	}

	*an=((cur_an>=ALPHABET_GAME_START_LEVEL_ONE_ALPHABET_NUM)&&(cur_an<=ALPHABET_GAME_START_LEVEL_THREE_ALPHABET_NUM))?\
		(cur_an):(ALPHABET_GAME_START_LEVEL_ONE_ALPHABET_NUM);
	
	return AG_SUCCESS;
}

static int alphabet_game_paint(p_void_data_t p_void_data, rect_t *p_rect, int index, bool sel_flag)
{
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	screen_t *scr=&ag->scr;
	rect_t *rct=p_rect;
	if((NULL==scr)||(NULL==rct)){
		return AG_FAILED;
	}
	
	show_foreground(scr);
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
	return alphabet_game_response_focus(p_void_data,p_m_evt_code,sel_index);
}

static int alphabet_game_select(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_enter(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	return alphabet_game_response_focus(p_void_data,p_m_evt_code,sel_index);
}

static int alphabet_game_exit(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==ag)||(NULL==m_evt_code)){
		return AG_FAILED;
	}

	set_cur_status(ag,CHILD_STATUS_EXIT);
		
	return AG_SUCCESS;
}

static int alphabet_game_response_focus(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	int index=sel_index;
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==ag)||(NULL==m_evt_code)){
		return AG_FAILED;
	}

	switch(index){
		case MAIN_STATUS_START:
			set_cur_status(ag,CHILD_STATUS_START);
			break;
		case MAIN_STATUS_HELP:
			set_cur_status(ag,CHILD_STATUS_HELP);
			break;
		case MAIN_STATUS_EXIT:
			set_cur_status(ag,CHILD_STATUS_EXIT);
			break;
		default:
			break;
	}
	
	return AG_SUCCESS;
}


static int alphabet_game_start_paint(p_void_data_t p_void_data, rect_t *p_rect,int index, bool sel_flag)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	screen_t *scr=&ag->scr;
	rect_t *rct=p_rect;
	if((NULL==scr)||(NULL==rct)){
		return AG_FAILED;
	}
	
	show_button(scr,rct->top,rct->left,sel_flag,alphabet_game_start_res[index].pdata,A_BOLD);

	return AG_SUCCESS;
}

static int alphabet_game_start_pen_up(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_start_pen_down(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	return alphabet_game_start_response_focus(p_void_data,p_m_evt_code,sel_index);
}

static int alphabet_game_start_select(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_start_enter(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	return alphabet_game_start_response_focus(p_void_data,p_m_evt_code,sel_index);
}

static int alphabet_game_start_exit(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==ag)||(NULL==m_evt_code)){
		return AG_FAILED;
	}

	set_cur_status(ag,MAIN_STATUS);
		
	return AG_SUCCESS;
}

static int alphabet_game_start_response_focus(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	const unsigned int usec=DELAY_TIME_MAX;
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==ag)||(NULL==m_evt_code)){
		return AG_FAILED;
	}

	if(sel_index<=ALPHABET_GAME_ALPHABET_Z-ALPHABET_GAME_ALPHABET_A+2){
		ctrl_tool_set_visible(ag->child_status_start,sel_index,FALSE);
		dec_remain_alphabet_num(ag);
		show_prompt(&ag->scr,ALPHABET_GAME_HELP_SELECT_WRONG,strlen(ALPHABET_GAME_HELP_SELECT_WRONG),COLOR_MSG_ERROR);
		refresh_screen(ag->scr.win);
		//sleep_delay_time(get_delay_time(ag));
		sleep_delay_time(usec);
	}else{
		show_prompt(&ag->scr,ALPHABET_GAME_HELP_SELECT_RIGHT,strlen(ALPHABET_GAME_HELP_SELECT_RIGHT),COLOR_MSG_RIGHT);
		refresh_screen(ag->scr.win);		
		//sleep_delay_time(get_delay_time(ag));
		sleep_delay_time(usec);
	}

	if(0>=get_remain_alphabet_num(ag)){//enter next level
		set_enter_next_level(ag,TRUE);
		switch(get_cur_level(ag)){
			case LEVEL_ONE:
				set_cur_level(ag,LEVEL_TWO);
				set_remain_time(ag,ALPHABET_GAME_START_TIME_TWO);
				set_total_alphabet_num(ag,ALPHABET_GAME_START_LEVEL_TWO_ALPHABET_NUM);
				set_remain_alphabet_num(ag,get_total_alphabet_num(ag));	
				break;
			case LEVEL_TWO:
				set_cur_level(ag,LEVEL_THREE);
				set_remain_time(ag,ALPHABET_GAME_START_TIME_THREE);
				set_total_alphabet_num(ag,ALPHABET_GAME_START_LEVEL_THREE_ALPHABET_NUM);
				set_remain_alphabet_num(ag,get_total_alphabet_num(ag));	
				break;
			case LEVEL_THREE:
				set_cur_level(ag,LEVEL_ONE);
				set_remain_time(ag,ALPHABET_GAME_START_TIME_ONE);
				set_total_alphabet_num(ag,ALPHABET_GAME_START_LEVEL_ONE_ALPHABET_NUM);
				set_remain_alphabet_num(ag,get_total_alphabet_num(ag));	

				set_cur_status(ag,MAIN_STATUS);
				break;
			default:
				break;
		}
	}
		
	return AG_SUCCESS;
}

static int alphabet_game_help_paint(p_void_data_t p_void_data, rect_t *p_rect,int index, bool sel_flag)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	screen_t *scr=&ag->scr;
	rect_t *rct=p_rect;
	if((NULL==scr)||(NULL==rct)){
		return AG_FAILED;
	}
	
	show_button(scr,rct->top,rct->left,sel_flag,alphabet_game_help_res[index].pdata,A_BOLD);

	return AG_SUCCESS;
}

static int alphabet_game_help_pen_up(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)	
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_help_pen_down(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)	
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	int index=sel_index;
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==ag)||(NULL==m_evt_code)){
		return AG_FAILED;
	}

	switch(index){
		case CHILD_STATUS_HELP_BACK:
			set_cur_status(ag,MAIN_STATUS);
			break;
		default:
			break;
	}
	
	return AG_SUCCESS;
}

static int alphabet_game_help_select(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)	
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_help_enter(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	int index=sel_index;
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==ag)||(NULL==m_evt_code)){
		return AG_FAILED;
	}

	switch(index){
		case CHILD_STATUS_HELP_BACK:
			set_cur_status(ag,MAIN_STATUS);
			break;
		default:
			break;
	}
	
	return AG_SUCCESS;
}

static int alphabet_game_help_exit(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	alphabet_game_t *ag=(alphabet_game_t *)p_void_data;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==ag)||(NULL==m_evt_code)){
		return AG_FAILED;
	}

	set_cur_status(ag,MAIN_STATUS);
		
	return AG_SUCCESS;
}

