/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */

#include <stdlib.h>
#include <string.h>
#include "ctrl_tool.h"
#include "alphabet_game.h"
#include "output_alphabet_game.h"

static int paint_main_status(alphabet_game_t *alphabet_game);
static int paint_child_status_start(alphabet_game_t *alphabet_game);
static int paint_child_status_help(alphabet_game_t *alphabet_game);
static int paint_child_status_exit(alphabet_game_t *alphabet_game);
static int paint_child_status_default(alphabet_game_t * alphabet_game);

static int update_screen_change(screen_t *screen, bool force_update);
static int set_screen_change(screen_t *screen,bool screen_change);
static bool is_screen_change(const screen_t *screen);
static int show_box(window_t *win,int starty,int startx,int endy,int endx, int attrs);
static int show_title(const screen_t *screen, const char *title, int size_title);
static int show_help_content(const screen_t *screen);
static void open_colors(color_t type, int attrs);
static void close_colors(color_t type, int attrs);




int paint_alphabet_game(alphabet_game_t *alphabet_game)
{
 	alphabet_game_t *ag=alphabet_game;
 	if(NULL==ag){
		return AG_FAILED;
	}
			
	clear_screen(ag);
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

int clear_screen(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){		
		return AG_FAILED;
	}
	p_void_ctrl_tool_t pvct=NULL;
	bool force_update=FALSE;
	screen_t *scr=&ag->scr;
	coordinate_t left_vertex;

	//get address of p_void_ctrl_t
	switch(ag->status){
		case MAIN_STATUS:
			pvct=ag->main_status;
			break;
		case CHILD_STATUS_START:
			pvct=ag->child_status_start;
			break;
		case CHILD_STATUS_HELP:
			pvct=ag->child_status_help;
			break;
		default:
			pvct=NULL;
			break;
	}
	
	if((get_last_status(ag)!=get_cur_status(ag))||(is_enter_next_level(ag)==TRUE)){
		force_update=TRUE;
		set_last_status(ag,get_cur_status(ag));
	}

	update_screen_change(scr,force_update);
	if(TRUE==is_screen_change(scr)){
		set_screen_change(scr,FALSE);
		get_left_vertex(scr,&left_vertex);
		set_left_vertex(pvct,&left_vertex);
		//werase(scr->win);
	}

	werase(scr->win);
	
	return AG_SUCCESS;
}
	


int refresh_screen(window_t *window)
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
	
	show_foreground(&ag->scr);
	show_title(&ag->scr,GAME_NAME,/*sizeof(GAME_NAME)-1*/strlen(GAME_NAME));
	ctrl_tool_paint(ag,ag->main_status);
	
	return AG_SUCCESS;
}

static int paint_child_status_start(alphabet_game_t *alphabet_game)
{
	//mvwprintw(stdscr,1,1,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_START);
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return AG_FAILED;
	}
	
	show_foreground(&ag->scr);
	show_title(&ag->scr,GAME_NAME,strlen(GAME_NAME));
	ctrl_tool_paint(ag,ag->child_status_start);
	
	return AG_SUCCESS;
}

static int paint_child_status_help(alphabet_game_t *alphabet_game)
{
//	mvwprintw(stdscr,2,2,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_HELP);
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return AG_FAILED;
	}
	
	show_foreground(&ag->scr);
	show_title(&ag->scr,GAME_NAME,strlen(GAME_NAME));
	show_help_content(&ag->scr);
	ctrl_tool_paint(ag,ag->child_status_help);

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

int get_left_vertex(const screen_t *screen,coordinate_t *coordinate)
{
	const screen_t *scr=screen;
	coordinate_t *ce=coordinate;
	if((NULL==scr)||(NULL==coordinate)){
		return AG_FAILED;
	}
 
	ce->y=((scr->foreground.top>=0)?(scr->foreground.top):(0));
	ce->x=((scr->foreground.left>=0)?(scr->foreground.left):(0));
	
	return AG_SUCCESS;
}

int show_foreground(const screen_t *screen)
{
	const screen_t *scr=screen;
	if(NULL==scr){
		return AG_FAILED;
	}

	open_colors(COLOR_FOREGROUND,A_BOLD);
	show_box(scr->win,scr->foreground.top,scr->foreground.left,scr->foreground.top+scr->foreground.height-1,scr->foreground.left+scr->foreground.width-1,A_BOLD);
	close_colors(COLOR_FOREGROUND,A_BOLD);
	
	return AG_SUCCESS;
}

int show_prompt(const screen_t *screen, const char *prompt, int size_prompt, color_t color)
{
	int y=1;
	int x=1;
	const screen_t *scr=screen;
	const char *ppt=prompt;
	if((NULL==scr)||(NULL==ppt)){
		return AG_FAILED;
	}
	
	y=scr->foreground.top+scr->foreground.height-2;
	x=scr->foreground.left+(scr->foreground.width-size_prompt)/2;

	open_colors(color,A_BOLD);
	mvwprintw(scr->win,y,x,"%s",ppt);
	close_colors(color,A_BOLD);
		
	return AG_SUCCESS;	
}

static int update_screen_change(screen_t *screen, bool force_update)
{
	screen_t *scr=screen;
	if(NULL==scr){
		return AG_FAILED;
	}

	int16_t height,width;
	height=(int16_t)getmaxy(scr->win);
	width=(int16_t)getmaxx(scr->win);

	if((height!=scr->background.height)||(width!=scr->background.width)||(force_update)){
		scr->background.height=height;
		scr->background.width=width;
		scr->foreground.top=(scr->background.height-scr->foreground.height)/2;
		scr->foreground.left=(scr->background.width-scr->foreground.width)/2;
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

static int show_title(const screen_t *screen, const char *title, int size_title)
{
	int y=1;
	int x=1;
	const screen_t *scr=screen;
	const char *ttl=title;
	if((NULL==scr)||(NULL==ttl)){
		return AG_FAILED;
	}
	
	y=scr->foreground.top+1;
	x=scr->foreground.left+(scr->foreground.width-size_title)/2;

	open_colors(COLOR_TITLE,A_BOLD);
	mvwprintw(scr->win,y,x,"%s",ttl);
	close_colors(COLOR_TITLE,A_BOLD);
		
	return AG_SUCCESS;
}

static int show_help_content(const screen_t *screen)
{
	int y=0;
	int i=0;
	int num=0;
	const screen_t *scr=screen;
	if((NULL==scr)){
		return AG_FAILED;
	}
	char help_titile[]="Game instructions";
	char help_content[][MAX_DATA_LEN_PER_LINE]={
		{"Click on the letters in alphabetical order,"},
		{"within a limited time."},
		{" "},
		{"If you do it, you will pass successfully,"},
		{"otherwise pass failed."},
		{" "},
		{"This game is a total of three level,"},
		{"if all pass, you will win in the game."},
		{" "},
		{" "},
		{" "},
		{"Good luck!"},
	};
	
	y=scr->foreground.top+3;
	num=sizeof(help_content)/sizeof(help_content[0]);

	open_colors(COLOR_TEXT_CONTENT,A_BOLD);
	mvwprintw(scr->win,y++,scr->foreground.left+(scr->foreground.width-strlen(help_titile))/2,"%s",help_titile);
	y++;
	
	for(i=0; i<num; i++){
		mvwprintw(scr->win,y++,scr->foreground.left+(scr->foreground.width-strlen(help_content[i]))/2,"%s",help_content[i]);
	}
	close_colors(COLOR_TEXT_CONTENT,A_BOLD);
		
	return AG_SUCCESS;
}


static void open_colors(color_t type, int attrs)
{
	switch(type){
		case COLOR_FOREGROUND:
			if(has_colors()){attron(COLOR_PAIR(COLOR_FOREGROUND)|attrs);}
			break;
		case COLOR_ICON_NORMAL:
			if(has_colors()){attron(COLOR_PAIR(COLOR_ICON_NORMAL)|attrs);}
			break;
		case COLOR_ICON_SELECT:
			if(has_colors()){attron(COLOR_PAIR(COLOR_ICON_SELECT)|attrs);}
			break;
		case COLOR_TITLE:			
			if(has_colors()){attron(COLOR_PAIR(COLOR_TITLE)|attrs);}
			break;
		case COLOR_TEXT_CONTENT:
			if(has_colors()){attron(COLOR_PAIR(COLOR_TEXT_CONTENT)|attrs);}
			break;
		case COLOR_MSG_WARNING:
			if(has_colors()){attron(COLOR_PAIR(COLOR_MSG_WARNING)|attrs);}
			break;
		case COLOR_MSG_ERROR:
			if(has_colors()){attron(COLOR_PAIR(COLOR_MSG_ERROR)|attrs);}
			break;		
		case COLOR_MSG_RIGHT:
			if(has_colors()){attron(COLOR_PAIR(COLOR_MSG_RIGHT)|attrs);}
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
		case COLOR_ICON_NORMAL:
			if(has_colors()){attroff(COLOR_PAIR(COLOR_ICON_NORMAL)|attrs);}
			break;
		case COLOR_ICON_SELECT:
			if(has_colors()){attroff(COLOR_PAIR(COLOR_ICON_SELECT)|attrs);}
			break;
		case COLOR_TITLE:
			if(has_colors()){attroff(COLOR_PAIR(COLOR_TITLE)|attrs);}						
			break;
		case COLOR_TEXT_CONTENT:
			if(has_colors()){attroff(COLOR_PAIR(COLOR_TEXT_CONTENT)|attrs);}						
			break;
		case COLOR_MSG_WARNING:
			if(has_colors()){attroff(COLOR_PAIR(COLOR_MSG_WARNING)|attrs);}						
			break;
		case COLOR_MSG_ERROR:
			if(has_colors()){attroff(COLOR_PAIR(COLOR_MSG_ERROR)|attrs);}						
			break;		
		case COLOR_MSG_RIGHT:
			if(has_colors()){attroff(COLOR_PAIR(COLOR_MSG_RIGHT)|attrs);}						
			break;
		default:
			break;
	}
		
	return;
}

int show_button(const screen_t *scr,int offset_y,int offset_x,int sel_flag,const char *text,int attrs)
{
	if(NULL==scr){
		return AG_FAILED;
	}
	switch(sel_flag){
		case TRUE:
			open_colors(COLOR_ICON_SELECT,A_BOLD);
			break;
		default:			
			open_colors(COLOR_ICON_NORMAL,A_BOLD);
			break;
	}

	mvwprintw(scr->win,scr->foreground.top+offset_y,scr->foreground.left+offset_x,"%s",text);
	
	switch(sel_flag){
		case TRUE:
			close_colors(COLOR_ICON_SELECT,A_BOLD);
			break;
		default:			
			close_colors(COLOR_ICON_NORMAL,A_BOLD);
			break;
	}		
	
	return AG_SUCCESS;
}

