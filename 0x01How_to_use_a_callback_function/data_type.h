/**
  *  Copyright (C) 2013-09-10  Handsome Zhou
  */
#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include <stdio.h>	//NULL

#define TEXT_MAX_LEN	255//256-1

typedef signed short T_S16;
typedef T_S16 int16_t;

typedef char T_TEXT;
typedef T_TEXT text_t;

#define TRUE	1
#define FALSE	0

typedef int T_BOOL;

#ifndef bool
#define bool int
#endif



typedef struct Coordinate{
	int16_t y;
	int16_t x;
}T_COORDINATE,*T_pCOORDINATE;
typedef T_COORDINATE coordinate_t;

typedef struct Rect{
	int16_t top;
	int16_t left;
	int16_t height;
	int16_t width;
}T_RECT,*T_pRECT;
typedef T_RECT rect_t;

typedef struct Button{
	int id;
	rect_t option_rect;
	text_t text[TEXT_MAX_LEN+1];
	struct Button *prev;
	struct Button *next;
}T_BUTTON,*T_pBUTTON;
typedef T_BUTTON button_t;

coordinate_t *cpy_coordinate(coordinate_t *dst, const coordinate_t *src);
rect_t *cpy_rect(rect_t *dst, const rect_t *src);
#endif		/*DATA_TYPE_H*/
