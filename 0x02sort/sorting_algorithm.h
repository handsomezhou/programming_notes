/**
  *  Copyright (C) 2014-03-21  Handsome Zhou
  */
#ifndef SORTING_ALGORITHM_H
#define SORTING_ALGORITHM_H
/*�ڲ�������·�Ϊ����:
��������;
��������;
ѡ������;
�鲢����;
��������;*/

extern void *bubble_sort(void *sort_data, int sort_data_len);
extern void *quick_sort(void *sort_data, int low, int high);
extern int show_data(const int *data, int data_len);

#endif	/*SORTING_ALGORITHM_H*/

