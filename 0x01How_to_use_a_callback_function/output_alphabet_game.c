/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */

#include <stdlib.h>
#include "alphabet_game.h"
#include "output_alphabet_game.h"

static int clear_screen(screen_t *screen);
static int refresh_screen(window_t *window);

static int paint_main_status(alphabet_game_t *alphabet_game);
static int paint_child_status_start(alphabet_game_t *alphabet_game);
static int paint_child_status_help(alphabet_game_t *alphabet_game);
static int paint_child_status_exit(alphabet_game_t *alphabet_game);
static int paint_child_status_default(alphabet_game_t * alphabet_game);

static int draw_main_status_foreground(screen_t *screen);
static int draw_child_status_start_foreground(screen_t *screen);
static int draw_child_status_help_foreground(screen_t *screen);
static int draw_child_status_exit_foreground(screen_t *screen);
static int draw_child_status_default_foreground(screen_t *screen);


static int update_screen_size(screen_t *screen);
static int set_screen_change(screen_t *screen,bool screen_change);
static bool is_screen_change(const screen_t *screen);
static int show_box(window_t *win,int starty,int startx,int endy,int endx, int attrs);

static void open_colors(color_t type, int attrs);
static void close_colors(color_t type, int attrs);




int paint_alphabet_game(alphabet_game_t *alphabet_game)
{
 	alphabet_game_t *ag=alphabet_game;
 	if(NULL==ag){
		return AG_FAILED;
	}

	clear_screen(&ag->scr);

	switch(ag->status){
		case MAIN_STATUS:
			paint_main_status(ag);
			break;
		case CHILD_STATUS_START:
			paint_child_status_start(ag);
			break;
		case CHILD_STATUS_HELP:
			paint_child_status_help(ag);
			break;
		case CHILD_STATUS_EXIT:
			paint_child_status_exit(ag);
			break;
		default:
			paint_child_status_default(ag);
			break;
	}

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

static int refresh_screen(window_t *window)
{
	window_t *win=window;
	if(NULL==win){
		return AG_FAILED;
	}

	wrefresh(win);
	
	return AG_SUCCESS;
}
static int paint_main_status(alphabet_game_t *alphabet_game)
{	
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return AG_FAILED;
	}
	draw_main_status_foreground(&ag->scr);
	return AG_SUCCESS;
}

static int paint_child_status_start(alphabet_game_t *alphabet_game)
{
	mvwprintw(stdscr,5+CHILD_STATUS_START,5+CHILD_STATUS_START,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_START);

	return AG_SUCCESS;
}

static int paint_child_status_help(alphabet_game_t *alphabet_game)
{
	mvwprintw(stdscr,5+CHILD_STATUS_HELP,5+CHILD_STATUS_HELP,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_HELP);

	return AG_SUCCESS;
}

static int paint_child_status_exit(alphabet_game_t *alphabet_game)
{
	mvwprintw(stdscr,5+CHILD_STATUS_EXIT,5+CHILD_STATUS_EXIT,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_EXIT);

	return AG_SUCCESS;
}

static int paint_child_status_default(alphabet_game_t * alphabet_game)
{
	mvwprintw(stdscr,5+CHILD_STATUS_EXIT,5+CHILD_STATUS_EXIT,"%d-%s-default",__LINE__,__FUNCTION__);

	return AG_SUCCESS;
}

static int draw_main_status_foreground(screen_t *screen)
{
	screen_t *scr=screen;
	if(NULL==scr){
		return AG_FAILED;
	}

	scr->foreground.top=(scr->background.height-scr->foreground.height)/2;
	scr->foreground.left=(scr->background.width-scr->foreground.width)/2;

	open_colors(COLOR_FOREGROUND,A_BOLD);
	show_box(scr->win,scr->foreground.top,scr->foreground.left,scr->foreground.top+scr->foreground.height-1,scr->foreground.left+scr->foreground.width-1,A_BOLD);
	close_colors(COLOR_FOREGROUND,A_BOLD);
	
	return AG_SUCCESS;
}

static int draw_child_status_start_foreground(screen_t *screen)
{

	return AG_SUCCESS;
}

static int draw_child_status_help_foreground(screen_t *screen)
{

	return AG_SUCCESS;
}

static int draw_child_status_exit_foreground(screen_t *screen)
{

	return AG_SUCCESS;
}

static int draw_child_status_default_foreground(screen_t *screen)
{

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

static int show_box(window_t *win,int starty,int startx,int endy,int endx, int attrs)
{
	if(NULL==win||\
		starty<0||starty>=getmaxy(win)||\
		startx<0||startx>=getmaxx(win)||\
		endy<0||endy>=getmaxy(win)||\
		endx<0||endx>=getmaxx(win)||\
		abs(startx-endx)<2||abs(starty-endy)<2){

		return ERR;
	}else{
		mvwhline(win,starty,startx+1,ACS_HLINE|attrs,endx-startx-1);
		mvwhline(win,endy,startx+1,ACS_HLINE|attrs,endx-startx-1);
		mvwvline(win,starty+1,startx,ACS_VLINE|attrs,endy-starty-1);
		mvwvline(win,starty+1,endx,ACS_VLINE|attrs,endy-starty-1);
		mvwaddch(win,starty,startx,ACS_ULCORNER|attrs);
		mvwaddch(win,starty,endx,ACS_URCORNER|attrs);
		mvwaddch(win,endy,startx,ACS_LLCORNER|attrs);
		mvwaddch(win,endy,endx,ACS_LRCORNER|attrs);

		return OK;
	}
}

static void open_colors(color_t type, int attrs)
{
	switch(type){
		case COLOR_FOREGROUND:
			if(has_colors()){attron(COLOR_PAIR(COLOR_FOREGROUND)|attrs);}
			break;
		default:
			break;
	}
	
	return;
}

static void close_colors(color_t type, int attrs)
{
	switch(type){
		case COLOR_FOREGROUND:
			if(has_colors()){attroff(COLOR_PAIR(COLOR_FOREGROUND)|attrs);}
			break;
		default:
			break;
	}
		
	return;
}


