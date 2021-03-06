/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */

#include <stdlib.h>
#include <string.h>
#include "ctrl_tool.h"
#include "alphabet_game.h"
#include "output_alphabet_game.h"

static int clear_status_screen(alphabet_game_t * alphabet_game,p_void_ctrl_tool_t p_void_ctrl_tool);

static int clear_main_status(alphabet_game_t *alphabet_game);
static int clear_child_status_start(alphabet_game_t *alphabet_game);
static int clear_child_status_help(alphabet_game_t *alphabet_game);
static int clear_child_status_exit(alphabet_game_t *alphabet_game);
static int clear_child_status_default(alphabet_game_t *alphabet_game);

static int paint_main_status(alphabet_game_t *alphabet_game);
static int paint_child_status_start(alphabet_game_t *alphabet_game);
static int paint_child_status_help(alphabet_game_t *alphabet_game);
static int paint_child_status_exit(alphabet_game_t *alphabet_game);
static int paint_child_status_default(alphabet_game_t *alphabet_game);

static int update_screen_change(screen_t *screen, bool force_update);
static int set_screen_change(screen_t *screen,bool screen_change);
static bool is_screen_change(const screen_t *screen);
static int show_box(window_t *win,int starty,int startx,int endy,int endx, int attrs);
static int show_title(const screen_t *screen, const char *propmt, int size_propmt);
static int show_level(const screen_t *screen, const char *propmt, int size_propmt, int level);
static int show_time(const screen_t *screen, const char *prompt, int size_propmt, int time);
static int show_help_content(const screen_t *screen);
static int show_exit_content(const screen_t *screen);
static void open_colors(color_t type, int attrs);
static void close_colors(color_t type, int attrs);


int clear_screen(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){		
		return RET_FAILED;
	}
	
	switch(ag->status){
		case MAIN_STATUS:
			clear_main_status(ag);
			break;
		case CHILD_STATUS_START:
			clear_child_status_start(ag);
			break;
		case CHILD_STATUS_HELP:
			clear_child_status_help(ag);
			break;
		case CHILD_STATUS_EXIT:
			clear_child_status_exit(ag);
			break;
		default:
			clear_child_status_default(ag);
			break;
	}
	
	return RET_SUCCESS;
}


int paint_alphabet_game(alphabet_game_t *alphabet_game)
{
 	alphabet_game_t *ag=alphabet_game;
 	if(NULL==ag){
		return RET_FAILED;
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
  
	return RET_SUCCESS;  
}

int refresh_screen(window_t *window)
{
	window_t *win=window;
	if(NULL==win){
		return RET_FAILED;
	}

	wrefresh(win);
	
	return RET_SUCCESS;
}

static int clear_status_screen(alphabet_game_t * alphabet_game,p_void_ctrl_tool_t p_void_ctrl_tool)
{
	
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return RET_FAILED;
	}
	screen_t *scr=&ag->scr;
	p_void_ctrl_tool_t pvct=p_void_ctrl_tool;
	coordinate_t left_vertex;

	if((get_last_status(ag)!=get_cur_status(ag))){
		set_update_screen(ag,TRUE);
		set_last_status(ag,get_cur_status(ag));
	}

	update_screen_change(scr,is_update_screen(ag));
	if(TRUE==is_screen_change(scr)){
		set_screen_change(scr,FALSE);
		if(NULL!=pvct){
			get_left_vertex(scr,&left_vertex);
			set_left_vertex(pvct,&left_vertex);
		}
		//werase(scr->win);
	}

	werase(scr->win);

	return RET_SUCCESS;
}
static int clear_main_status(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return RET_FAILED;
	}

	return clear_status_screen(ag,ag->main_status);
}

static int clear_child_status_start(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return RET_FAILED;
	}
	
	return clear_status_screen(ag,ag->child_status_start);
}

static int clear_child_status_help(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return RET_FAILED;
	}

	return clear_status_screen(ag,ag->child_status_help);
}

static int clear_child_status_exit(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return RET_FAILED;
	}

	return clear_status_screen(ag,NULL);
}

static int clear_child_status_default(alphabet_game_t *alphabet_game)
{
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return RET_FAILED;
	}

	return clear_status_screen(ag,NULL);	
}


static int paint_main_status(alphabet_game_t *alphabet_game)
{	
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return RET_FAILED;
	}
	
	show_foreground(&ag->scr);
	show_title(&ag->scr,GAME_NAME,/*sizeof(GAME_NAME)-1*/strlen(GAME_NAME));
	ctrl_tool_paint(ag,ag->main_status);
	
	return RET_SUCCESS;
}

static int paint_child_status_start(alphabet_game_t *alphabet_game)
{
	//mvwprintw(stdscr,1,1,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_START);
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return RET_FAILED;
	}
	
	show_foreground(&ag->scr);
	show_title(&ag->scr,GAME_NAME,strlen(GAME_NAME));
	show_level(&ag->scr,ALPHABET_GAME_START_LEVEL,strlen(ALPHABET_GAME_START_LEVEL),get_cur_level(ag)+1);
	show_time(&ag->scr,ALPHABET_GAME_START_TIME,strlen(ALPHABET_GAME_START_LEVEL),get_remain_time(ag));
	ctrl_tool_paint(ag,ag->child_status_start);
	
	return RET_SUCCESS;
}

static int paint_child_status_help(alphabet_game_t *alphabet_game)
{
//	mvwprintw(stdscr,2,2,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_HELP);
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return RET_FAILED;
	}
	
	show_foreground(&ag->scr);
	show_title(&ag->scr,GAME_NAME,strlen(GAME_NAME));
	show_help_content(&ag->scr);
	ctrl_tool_paint(ag,ag->child_status_help);

	return RET_SUCCESS;
}

static int paint_child_status_exit(alphabet_game_t *alphabet_game)
{
	//mvwprintw(stdscr,5+CHILD_STATUS_EXIT,5+CHILD_STATUS_EXIT,"%d-%s-%d",__LINE__,__FUNCTION__,CHILD_STATUS_EXIT);
	alphabet_game_t *ag=alphabet_game;
	if(NULL==ag){
		return RET_FAILED;
	}

	const unsigned int usec=DELAY_TIME_MAX;
	show_foreground(&ag->scr);
	show_title(&ag->scr,GAME_NAME,strlen(GAME_NAME));
	show_exit_content(&ag->scr);
	refresh_screen(ag->scr.win);
	sleep_delay_time(usec);
	
	return RET_SUCCESS;
}

static int paint_child_status_default(alphabet_game_t * alphabet_game)
{
	mvwprintw(stdscr,5+CHILD_STATUS_EXIT,5+CHILD_STATUS_EXIT,"%d-%s-default",__LINE__,__FUNCTION__);

	return RET_SUCCESS;
}

int get_left_vertex(const screen_t *screen,coordinate_t *coordinate)
{
	const screen_t *scr=screen;
	coordinate_t *ce=coordinate;
	if((NULL==scr)||(NULL==coordinate)){
		return RET_FAILED;
	}
 
	ce->y=((scr->foreground.top>=0)?(scr->foreground.top):(0));
	ce->x=((scr->foreground.left>=0)?(scr->foreground.left):(0));
	
	return RET_SUCCESS;
}

int show_foreground(const screen_t *screen)
{
	const screen_t *scr=screen;
	if(NULL==scr){
		return RET_FAILED;
	}

	open_colors(COLOR_FOREGROUND,A_BOLD);
	show_box(scr->win,scr->foreground.top,scr->foreground.left,scr->foreground.top+scr->foreground.height-1,scr->foreground.left+scr->foreground.width-1,A_BOLD);
	close_colors(COLOR_FOREGROUND,A_BOLD);
	
	return RET_SUCCESS;
}

int show_prompt(const screen_t *screen, const char *prompt, int size_prompt, color_t color)
{
	int y=1;
	int x=1;
	const screen_t *scr=screen;
	const char *ppt=prompt;
	if((NULL==scr)||(NULL==ppt)){
		return RET_FAILED;
	}
	
	y=scr->foreground.top+scr->foreground.height-2;
	x=scr->foreground.left+(scr->foreground.width-size_prompt)/2;

	open_colors(color,A_BOLD);
	mvwprintw(scr->win,y,x,"%s",ppt);
	close_colors(color,A_BOLD);
		
	return RET_SUCCESS;	
}

int show_pass_msg(const screen_t *screen)
{
	int i=0,y=0,num=0;
	const screen_t *scr=screen;
	if((NULL==scr)){
		return RET_FAILED;
	}

	char pass_msg[][MAX_DATA_LEN_PER_LINE]={
		{"You successfully passed all levels!"},
		{" "},
		{" "},
		{" "},
		{"Congratulation to you!"},
		{" "},
		{" "},
		{" "},
		{"See you next time!"},
	};
		
	y=scr->foreground.top+3;
	num=sizeof(pass_msg)/sizeof(pass_msg[0]);

	open_colors(COLOR_TEXT_CONTENT,A_BOLD);
	for(i=0; i<num; i++){
		mvwprintw(scr->win,y++,scr->foreground.left+(scr->foreground.width-strlen(pass_msg[i]))/2,"%s",pass_msg[i]);
	}
	close_colors(COLOR_TEXT_CONTENT,A_BOLD);
		
	return RET_SUCCESS;
}

int show_button(const screen_t *scr,int offset_y,int offset_x,int sel_flag,const char *text,int attrs)
{
	if(NULL==scr){
		return RET_FAILED;
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
	
	return RET_SUCCESS;
}

static int update_screen_change(screen_t *screen, bool force_update)
{
	screen_t *scr=screen;
	if(NULL==scr){
		return RET_FAILED;
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
	
	return RET_SUCCESS;
}

static int set_screen_change(screen_t *screen,bool screen_change)
{
	screen_t *scr=screen;
	if(NULL==scr){
		return RET_FAILED;
	}

	(FALSE==screen_change)?(scr->screen_change=FALSE):(scr->screen_change=TRUE);
	
	return RET_SUCCESS;
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

static int show_title(const screen_t *screen, const char *propmt, int size_propmt)
{
	int y=1;
	int x=1;
	const screen_t *scr=screen;
	const char *ppt=propmt;
	if((NULL==scr)||(NULL==ppt)){
		return RET_FAILED;
	}
	
	y=scr->foreground.top+1;
	x=scr->foreground.left+(scr->foreground.width-size_propmt)/2;

	open_colors(COLOR_TITLE,A_BOLD);
	mvwprintw(scr->win,y,x,"%s",ppt);
	close_colors(COLOR_TITLE,A_BOLD);
		
	return RET_SUCCESS;
}

static int show_level(const screen_t *screen, const char *propmt, int size_propmt, int level)
{
	int y=1;
	int x=1;
	int lvl=level;
	const screen_t *scr=screen;
	const char *ppt=propmt;
	if((NULL==scr)||(NULL==ppt)){
		return RET_FAILED;
	}
	
	y=scr->foreground.top+3;
	x=scr->foreground.left+(scr->foreground.width-size_propmt)/4;

	open_colors(COLOR_TITLE,A_BOLD);
	mvwprintw(scr->win,y,x,"%s %d",ppt,lvl);
	close_colors(COLOR_TITLE,A_BOLD);
		
	return RET_SUCCESS;
}

static int show_time(const screen_t *screen, const char *prompt, int size_propmt, int time)
{
	int y=1;
	int x=1;
	int tim=time;
	const screen_t *scr=screen;
	const char *ppt=prompt;
	if((NULL==scr)||(NULL==ppt)){
		return RET_FAILED;
	}
	
	y=scr->foreground.top+3;
	x=scr->foreground.left+(scr->foreground.width-size_propmt)/4*3;

	open_colors(COLOR_TITLE,A_BOLD);
	mvwprintw(scr->win,y,x,"%s %d",ppt,tim);
	close_colors(COLOR_TITLE,A_BOLD);
		
	return RET_SUCCESS;	
}

static int show_help_content(const screen_t *screen)
{
	int i=0,y=0,num=0;
	const screen_t *scr=screen;
	if((NULL==scr)){
		return RET_FAILED;
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
		{"UP:    key up,key left,mouse wheel out  "},
		{"DOWN:  key down,key right,mouse wheel in"},
		{"ENTER: key enter,mouse left click       "},
		{"EXIT:  key esc,mouse wheel click        "},
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
		
	return RET_SUCCESS;
}

static int show_exit_content(const screen_t *screen)
{
	int i=0,y=0,num=0;
	const screen_t *scr=screen;
	if(NULL==scr){
		return RET_FAILED;
	}

	char exit_content[][MAX_DATA_LEN_PER_LINE]={
		{"You're out of the game ..."},
		{" "},
		{" "},
		{" "},
		{"See you next time!"},
	};
	num=sizeof(exit_content)/sizeof(exit_content[0]);
	y=scr->foreground.top+(scr->foreground.height-num)/2;

	open_colors(COLOR_TEXT_CONTENT,A_BOLD);
	for(i=0; i<num; i++){
		mvwprintw(scr->win,y++,scr->foreground.left+(scr->foreground.width-strlen(exit_content[i]))/2,"%s",exit_content[i]);
	}
	close_colors(COLOR_TEXT_CONTENT,A_BOLD);
	
	return RET_SUCCESS;
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

