/**
  *  Copyright (C) 2013-12-09  Handsome Zhou
  */
	 
#include "alphabet_game.h"

int init_alphabet_game(alphabet_game_t **alphabet_game)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_SUCCESS;
}

void exit_alphabet_game(alphabet_game_t *alphabet_game)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return AG_FAILED;
}

