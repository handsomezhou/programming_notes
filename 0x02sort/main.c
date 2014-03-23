/**
  *  Copyright (C) 2014-03-21  Handsome Zhou
  */
#include <stdio.h>
#include "sorting_algorithm.h"

int dt_len=0;
int main(int argc, char *argv[])
{
	//test sort algorithm
	int data1[]={1,15,0,2,14,9,3,8,16,4,7,5,6,13,11,12};
	int data_len1=sizeof(data1)/sizeof(data1[0]);
	show_data(data1,data_len1);
	printf("bubble_sort\n");
	bubble_sort((void *)data1,data_len1);
	printf("\n\n\n");

	int data2[]={1,15,0,2,14,9,3,8,16,4,7,5,6,13,11,12};
	int data_len2=sizeof(data2)/sizeof(data2[0]);
	dt_len=data_len2;

	show_data(data2,dt_len);
	printf("quick_sort\n");
	quick_sort(data2,0,data_len2-1);
	
	return 0;
}
 

