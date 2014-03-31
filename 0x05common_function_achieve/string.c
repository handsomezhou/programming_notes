/**
  *  Copyright (C) 2014-03-31  Handsome Zhou
  */
#include <stdio.h>
#include <assert.h>
#include "string.h"

int my_strlen(const char *str)
{
	const char *s=str;
	while(*s++);
	
	return (s-str-1);
}

char *my_strcpy(char *dest, const char *src)
{
	char *address=dest;
	assert((NULL!=dest)&&(NULL!=src));
	while((*dest++=*src++)!='\0');
	
	return address;
}

char *my_strncpy(char *dest, const char *src, int n)
{
	return NULL;
}

int my_strcmp(const char *s1, const char *s2)
{
	int ret=0;
	while(!(ret=*(unsigned char *)s1-*(unsigned char *)s2)&&*s2){
		s1++;
		s2++;
	}
	
	if(ret<0){
		ret=-1;
	}else if(ret>0){
		ret=1;
	}
	
	return ret;
}

int my_strncmp(const char *s1, const char *s2, int n)
{
	return 0;
}

