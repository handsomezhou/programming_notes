/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */

#include "alphabet_game.h"
#include "output_alphabet_game.h"

static int clear_screen(screen_t *screen);
static int draw_screen(alphabet_game_t *alphabet_game);
static int refresh_screen(window_t *window);

static int update_screen_size(screen_t *screen);
static int set_screen_change(screen_t *screen,bool screen_change);
static bool is_screen_change(const screen_t *screen);



int paint_alphabet_game(alphabet_game_t *alphabet_game)
{
	// printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
 	alphabet_game_t *ag=alphabet_game;
 	if(NULL==ag){
		return AG_FAILED;
	}

	clear_screen(&ag->scr);

	draw_screen(ag);

	refresh_screen(ag->scr.win);
  
	return AG_SUCCESS;  
}

static int clear_screen(screen_t *screen)
{
	screen_t *scr=screen;
	if(NULL==scr){
		return AG_FAILED;
	}

	update_screen_size(scr);
	if(TRUE==is_screen_change(scr)){
		set_screen_change(scr,FALSE);
		werase(scr->win);
	}
	
	return AG_SUCCESS;
}

static int draw_screen(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return AG_FAILED;
	}
	
	switch(ag->status){
		case MAIN_STATUS:
			mvwprintw(stdscr,5+MAIN_STATUS,5+MAIN_STATUS,"%d-%s-%d",__LINE__,__FUNCTION__,MAIN_STATUS);
			break;
		case CHILD_STATUS_START:
			mvwprintw(stdscr,5+CHILD_STATUS_START,5+CHILD_STATUS_START,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_START);
			break;
		case CHILD_STATUS_HELP:
			mvwprintw(stdscr,5+CHILD_STATUS_HELP,5+CHILD_STATUS_HELP,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_HELP);
			break;
		case CHILD_STATUS_EXIT:
			mvwprintw(stdscr,5+CHILD_STATUS_EXIT,5+CHILD_STATUS_EXIT,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_EXIT);
			break;
		default:
			mvwprintw(stdscr,5+CHILD_STATUS_EXIT,5+CHILD_STATUS_EXIT,"%d-%s-default",__LINE__,__FUNCTION__);
			break;
	}
	
	return AG_SUCCESS;
}
	
static int refresh_screen(window_t *window)
{
	window_t *win=window;
	if(NULL==win){
		return AG_FAILED;
	}

	wrefresh(win);
	
	return AG_SUCCESS;
}

static int update_screen_size(screen_t *screen)
{
	screen_t *scr=screen;
	if(NULL==scr){
		return AG_FAILED;
	}

	int16_t height,width;
	height=(int16_t)getmaxy(scr->win);
	width=(int16_t)getmaxx(scr->win);

	if((height!=scr->background.height)||(width!=scr->background.width)){
		scr->background.height=height;
		scr->background.width=width;
		set_screen_change(scr,TRUE);
	}
	
	return AG_SUCCESS;
}

static int set_screen_change(screen_t *screen,bool screen_change)
{
	screen_t *scr=screen;
	if(NULL==scr){
		return AG_FAILED;
	}

	(FALSE==screen_change)?(scr->screen_change=FALSE):(scr->screen_change=TRUE);
	
	return AG_SUCCESS;
}

static bool is_screen_change(const screen_t *screen)
{
	return ((NULL==screen)?(FALSE):(screen->screen_change));
}

