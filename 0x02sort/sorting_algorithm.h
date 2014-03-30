/**
  *  Copyright (C) 2014-03-21  Handsome Zhou
  */
#ifndef SORTING_ALGORITHM_H
#define SORTING_ALGORITHM_H
//Reference:	http://zh.wikipedia.org/wiki/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95

/*内部排序大致分为五类:
插入排序;
交换排序;
选择排序;
归并排序;
计数排序;*/

extern void *bubble_sort(void *sort_data, int sort_data_len);
extern void *quick_sort(void *sort_data, int low, int high);

extern void *select_sort(void *sort_data, int sort_data_len);

extern int show_data(const int *data, int data_len);

#endif	/*SORTING_ALGORITHM_H*/

