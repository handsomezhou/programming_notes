/**
  *  Copyright (C) 2014-03-28  Handsome Zhou
  */
#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H
//Reference:	http://zh.wikipedia.org/wiki/%E5%8F%8C%E5%90%91%E9%93%BE%E8%A1%A8

typedef int bool_t;

#define TRUE	1
#define FALSE	0

#define LIST_SUCCEED	0
#define LIST_FAILED		(-1)

typedef int elem_t;
typedef struct dbl_node{
	elem_t elem;
	struct dbl_node *prev,*next;
}dbl_node_t,*dbl_link_list_t;

typedef int (*pf_node_compare)(const void *, const void *);
typedef int (*pf_node_travel)(void *);

dbl_link_list_t init_list(void);
void free_list(dbl_link_list_t dbl_link_list);
void clear_list(dbl_link_list_t dbl_link_list);
bool_t list_is_empty(dbl_link_list_t dbl_link_list);  
int list_length(dbl_link_list_t dbl_link_list);
int get_elem(dbl_link_list_t dbl_link_list, int i, elem_t *elem);
int locate_elem(dbl_link_list_t dbl_link_list, elem_t elem, pf_node_compare node_compare);
int prior_elem(dbl_link_list_t dbl_link_list, elem_t cur_elem, elem_t *prev_elem);
int next_elem(dbl_link_list_t dbl_link_list, elem_t cur_elem, elem_t *next_elem);
int list_node_insert(dbl_link_list_t dbl_link_list, int i, elem_t elem);
int list_node_delete(dbl_link_list_t dbl_link_list, int i, elem_t *elem);
int list_travel(dbl_link_list_t dbl_link_list,pf_node_travel node_travel);
int list_travel_back(dbl_link_list_t dbl_link_list,pf_node_travel node_travel);

#endif	/*DOUBLE_LINKED_LIST_H*/
