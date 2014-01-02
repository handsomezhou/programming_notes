/**
  *  Copyright (C) 2013-12-09  Handsome Zhou
  */

#include "message_event.h"
#include "alphabet_game.h"

/*alphabet game main interface event*/
static int alphabet_game_paint(rect_t *p_rect,int index, bool sel_flag);
static int alphabet_game_pen_up(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_pen_down(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_select(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_enter(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_esc(const m_evt_code_t *p_m_evt_code, int sel_index);

static ctrl_tool_callback_t alphabet_game_event={
	alphabet_game_paint,
	alphabet_game_pen_up,
	alphabet_game_pen_down,
	alphabet_game_select,
	alphabet_game_enter,
	alphabet_game_esc,	
};

/*alphabet game child interface event:game start,game help,game exit*/
static int alphabet_game_start_paint(rect_t *p_rect,int index, bool sel_flag);
static int alphabet_game_start_pen_up(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_start_pen_down(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_start_select(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_start_enter(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_start_esc(const m_evt_code_t *p_m_evt_code, int sel_index);

static ctrl_tool_callback_t alphabet_game_start_event={
	alphabet_game_start_paint,
	alphabet_game_start_pen_up,
	alphabet_game_start_pen_down,
	alphabet_game_start_select,
	alphabet_game_start_enter,
	alphabet_game_start_esc,	
};

static int alphabet_game_help_paint(rect_t *p_rect,int index, bool sel_flag);
static int alphabet_game_help_pen_up(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_help_pen_down(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_help_select(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_help_enter(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_help_esc(const m_evt_code_t *p_m_evt_code, int sel_index);

static ctrl_tool_callback_t alphabet_game_help_event={
	alphabet_game_help_paint,
	alphabet_game_help_pen_up,
	alphabet_game_help_pen_down,
	alphabet_game_help_select,
	alphabet_game_help_enter,
	alphabet_game_help_esc,	
};

static int alphabet_game_exit_paint(rect_t *p_rect,int index, bool sel_flag);
static int alphabet_game_exit_pen_up(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_exit_pen_down(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_exit_select(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_exit_enter(const m_evt_code_t *p_m_evt_code, int sel_index);
static int alphabet_game_exit_esc(const m_evt_code_t *p_m_evt_code, int sel_index);

static ctrl_tool_callback_t alphabet_game_exit_event={
	alphabet_game_exit_paint,
	alphabet_game_exit_pen_up,
	alphabet_game_exit_pen_down,
	alphabet_game_exit_select,
	alphabet_game_exit_enter,
	alphabet_game_exit_esc,	
};

int init_alphabet_game(alphabet_game_t **alphabet_game)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

void exit_alphabet_game(alphabet_game_t *alphabet_game)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return ;
}



static int alphabet_game_paint(rect_t *p_rect,int index, bool sel_flag)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}
	
static int alphabet_game_pen_up(const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_pen_down(const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_select(const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_enter(const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_esc(const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}



static int alphabet_game_help_paint(rect_t *p_rect,int index, bool sel_flag)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_help_pen_up(const m_evt_code_t *p_m_evt_code, int sel_index)	
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_help_pen_down(const m_evt_code_t *p_m_evt_code, int sel_index)	
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_help_select(const m_evt_code_t *p_m_evt_code, int sel_index)	
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_help_enter(const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_help_esc(const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}


static int alphabet_game_exit_paint(rect_t *p_rect,int index, bool sel_flag)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_exit_pen_up(const m_evt_code_t *p_m_evt_code, int sel_index)	
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_exit_pen_down(const m_evt_code_t *p_m_evt_code, int sel_index)	
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_exit_select(const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_exit_enter(const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

static int alphabet_game_exit_esc(const m_evt_code_t *p_m_evt_code, int sel_index)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}
