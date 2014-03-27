/**
  *  Copyright (C) 2014-03-28  Handsome Zhou
  */

#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

struct data;
typedef struct data data_t,*pdata_t;

struct node;
typedef struct node node_t,*pnode_t;

typedef void node_proc_fun_t(void*);
node_t *list_new_head_node(void);
node_t *produce_node(data_t *data);
node_t *list_node_append(node_t *list,node_t *node);
void list_travel(const node_t *list, node_proc_fun_t *proc);
void show_node(void *data);
int list_delete(node_t *list);

data_t *malloc_data(void);
void free_data(data_t *data);
int set_number_to_data(data_t *data, int number);
int get_number_from_data(const data_t *data);

#endif	/*SINGLE_LINKED_LIST_H*/