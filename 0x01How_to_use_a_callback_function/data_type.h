/**
  *  Copyright (C) 2013-09-10  Handsome Zhou
  */
#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include <stdio.h>	//NULL

#define TEXT_MAX_LEN	255//256-1

typedef signed short T_S16;
typedef char T_TEXT;

#define TRUE	1
#define FALSE	0

typedef int T_BOOL;

#ifndef bool
#define bool int
#endif



typedef struct Coordinate{
	T_S16 y;
	T_S16 x;
}T_COORDINATE,*T_pCOORDINATE;

typedef T_COORDINATE coordinate_t;

typedef struct Rect{
	T_S16 top;
	T_S16 left;
	T_S16 height;
	T_S16 width;
}T_RECT,*T_pRECT;

typedef T_RECT rect_t;

typedef struct Button{
	int id;
	T_RECT option_rect;
	T_TEXT	text[TEXT_MAX_LEN+1];
	struct Button *prev;
	struct Button *next;
}T_BUTTON,*T_pBUTTON;

T_COORDINATE *cpy_coordinate(T_COORDINATE *dst, const T_COORDINATE *src);
T_RECT *cpy_rect(T_RECT *dst, const T_RECT *src);
#endif		/*DATA_TYPE_H*/
