/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */
#ifndef OUTPUT_ALPHABET_GAME_H
#define	OUTPUT_ALPHABET_GAME_H

#include "alphabet_game.h"

extern int paint_alphabet_game(alphabet_game_t *alphabet_game);
extern int clear_screen(alphabet_game_t *alphabet_game);

extern int refresh_screen(window_t *window);
extern int get_left_vertex(const screen_t *screen,coordinate_t *coordinate);
extern int show_foreground(const screen_t *screen);
extern int show_prompt(const screen_t *screen, const char *prompt, int size_prompt, color_t color);
extern int show_button(const screen_t *scr,int offset_y,int offset_x,int sel_flag,const char *text,int attrs);


#endif	/*OUTPUT_ALPHABET_GAME_H*/

