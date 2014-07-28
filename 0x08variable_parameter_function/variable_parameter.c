/**
  *  Copyright (C) 2014-07-28  Handsome Zhou
  */
#include "variable_parameter.h"
#include <stdio.h>
#include <stdarg.h>


int print(const char *format,...)
{
	int i=0;
	va_list args;

	va_start(args,format);
	i=vprintf(format,args);
	va_end(args);

	return i;
}

