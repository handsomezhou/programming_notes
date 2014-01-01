/**
  *  Copyright (C) 2013-10-12  Handsome Zhou
  */

#include <stdio.h>
#include "alphabet_game.h"
#include "input_alphabet_game.h"
#include "handle_alphabet_game.h"
#include "output_alphabet_game.h"


int main(int argc,char *argv[])
{
	alphabet_game_t *alphabet_game=NULL;
	int ret;
	
	ret=init_alphabet_game(&alphabet_game);
	do{
		if(AG_FAILED==ret){
			break;
		}
		input_alphabet_game(alphabet_game);
		handle_alphabet_game(alphabet_game);
		paint_alphabet_game(alphabet_game);
		ret=AG_SUCCESS;
	}while(0);
	
	exit_alphabet_game(alphabet_game);
	
	return ret;
}
