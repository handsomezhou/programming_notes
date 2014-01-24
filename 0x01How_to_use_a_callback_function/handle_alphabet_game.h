/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */

#ifndef HANDLE_ALPHABET_GAME_H
#define	HANDLE_ALPHABET_GAME_H

#include "alphabet_game.h"

extern int handle_alphabet_game(alphabet_game_t *alphabet_game);
extern int produce_random_alphabet_sequence(alphabet_game_t *alphabet_game, int alphabet_sequence_num);
extern bool judge_cur_sort_foremost_alphabet(alphabet_game_t *alphabet_game, int index);
extern int exit_child_status_start(alphabet_game_t *alphabet_game);

void signal_process(int signo);
typedef void (*pf_signal_process_call_back)(int);


#endif	/*HANDLE_ALPHABET_GAME_H*/
