/**
  *  Copyright (C) 2014-07-28  Handsome Zhou
  */

#include <stdio.h>
#include "variable_parameter.h"

int main(int arg, char *argv[])
{
	char question[]="How old are you?";
	int answer=12;
	int i=print("%s\n%d\n",question,answer);
	print("i=%d\n",i);
	
	return 0;
}

