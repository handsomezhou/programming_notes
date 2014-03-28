/**
  *  Copyright (C) 2014-03-28  Handsome Zhou
  */
#include <stdio.h>
#include "double_linked_list.h"

dbl_link_list_t init_list(void)
{
	return NULL;
}

void free_list(dbl_link_list_t dbl_link_list)
{
	return ;
}

void clear_list(dbl_link_list_t dbl_link_list)
{
	return ;
}
	
bool_t list_is_empty(dbl_link_list_t dbl_link_list)
{
	return FALSE;
}

int list_length(dbl_link_list_t dbl_link_list)
{
	return 0;
}

int get_elem(dbl_link_list_t dbl_link_list, int i, elem_t *elem)
{
	return 0;
}

int locate_elem(dbl_link_list_t dbl_link_list, elem_t elem, pf_node_compare node_compare)	
{
	return 0;
}

int prior_elem(dbl_link_list_t dbl_link_list, elem_t cur_elem, elem_t *prev_elem)
{
	return 0;
}

int next_elem(dbl_link_list_t dbl_link_list, elem_t cur_elem, elem_t *next_elem)
{
	return 0;
}

int list_node_insert(dbl_link_list_t dbl_link_list, int i, elem_t elem)	
{
	return 0;
}

int list_node_delete(dbl_link_list_t dbl_link_list, int i, elem_t *elem)	
{
	return 0;
}

int list_travel(dbl_link_list_t dbl_link_list,pf_node_travel node_travel)
{
	return 0;
}

int list_travel_back(dbl_link_list_t dbl_link_list,pf_node_travel node_travel)	
{
	return 0;
}

