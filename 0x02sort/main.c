/**
  *  Copyright (C) 2014-03-21  Handsome Zhou
  */
#include <stdio.h>
#include "sorting_algorithm.h"

int show_data(const int *data, int data_len);
int main(int argc, char *argv[])
{
	//test sort algorithm
	int data[]={1,15,0,2,14,9,3,8,16,4,7,5,6,13,11,12};
	int data_len=sizeof(data)/sizeof(data[0]);
	bubble_sort((void *)data,data_len);
	show_data(data,data_len);
	
	return 0;
}
 
int show_data(const int *data, int data_len)
{
	int i=0;
	const int *pd=data;
	for(i=0; i<data_len; i++){
		printf("[%d]===>%d\n",i,*(pd+i));
	}
	printf("\n");
	
	return 0;
}
