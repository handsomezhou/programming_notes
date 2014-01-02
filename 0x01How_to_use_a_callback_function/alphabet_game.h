/**
  *  Copyright (C) 2013-12-09  Handsome Zhou
  */

#ifndef ALPHABET_GAME_H
#define ALPHABET_GAME_H

#include <stdio.h>

#define GAME_NAME		"Alphabet Game"

#define AG_SUCCESS		0
#define AG_FAILED		(-1)

#define ALPHABET_GAME_WIDGET_NUM		(3)
#define ALPHABET_GAME_START_WIDGET_NUM	(26)
#define ALPHABET_GAME_HELP_WIDGET_NUM	(1)

typedef enum{
	ALPHABET_GAME_MAIN_INTERFACE,
	ALPHABET_GAME_CHILD_INTERFACE,
}alphabet_game_interface_t;

typedef enum{
	ALPHABET_GAME_CHILD_INTERFACE_START,
	ALPHABET_GAME_CHILD_INTERFACE_HELP,
	ALPHABET_GAME_CHILD_INTERFACE_EXIT,
}alphabet_game_child_interface_t;

typedef struct alphabet_game{

}alphabet_game_t;

extern int init_alphabet_game(alphabet_game_t **alphabet_game);
extern void exit_alphabet_game(alphabet_game_t *alphabet_game);

#endif	/*ALPHABET_GAME_H*/
