/**
  *  Copyright (C) 2014-03-21  Handsome Zhou
  */
#include <stdio.h>
#include "sorting_algorithm.h"

extern int dt_len;
void *bubble_sort(void *sort_data, int sort_data_len)
{
	int *psd=(int *)sort_data;
	int sd_len=sort_data_len;
	int sort_finish_flag=1;
	int i=0;
	int j=0;
	int tmp_data=0;

	for(i=0; i<sd_len-1; i++){
		sort_finish_flag=1;
		for(j=0; j<sd_len-1-i; j++){
			if(*(psd+j)>*(psd+j+1)){
				tmp_data=*(psd+j);
				*(psd+j)=*(psd+j+1);
				*(psd+j+1)=tmp_data;
				sort_finish_flag=0;
			}
		}
		show_data(psd,sd_len);	//just for debug
		if(1==sort_finish_flag){
			break;
		}
	}

	return psd;
}

void *quick_sort(void *sort_data, int low, int high)
{
	int i,j,pivot;
	int *psd=(int *)sort_data;
	if(low<high){
		pivot=*(psd+low);
		i=low;
		j=high;
		while(i<j){
			while((i<j)&&pivot<*(psd+j))
				j--;
			if(i<j)
				*(psd+i++)=*(psd+j);
			while((i<j)&&pivot>*(psd+i))
				i++;
			if(i<j)
				*(psd+j--)=*(psd+i);
		}
		*(psd+i)=pivot;
		show_data(psd,dt_len);	//just for debug
		quick_sort(psd,low,i-1);
		quick_sort(psd,i+1,high);
	}

	return psd;
}

int show_data(const int *data, int data_len)
{
	int i=0;
	const int *pd=data;
	for(i=0; i<data_len; i++){
		printf("%3d",*(pd+i));
	}
	printf("\n");
	
	return 0;
}

