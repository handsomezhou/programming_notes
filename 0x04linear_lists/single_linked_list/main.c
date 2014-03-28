/**
  *  Copyright (C) 2014-03-28  Handsome Zhou
  */

#include <stdio.h>
#include "single_linked_list.h"

int main(int argc, char *argv[])
{
	int i=0;
	elem_t elem;
	int node_number=10;
	pf_node_travel node_travel=show_node;
	pf_node_compare node_compare=compare_node;
	linklist_t linklist=init_list();
	for(i=0; i<node_number; i++){
		if(LIST_SUCCEED==list_node_insert(linklist,i+1,i+1)){
			printf("i=%d,success\n",i+1);
		}else{
			printf("i=%d,failed\n",i+1);
		}
	}

	list_travel(linklist,node_travel);

	elem=5;
	i=locate_elem(linklist,elem,node_compare);
	printf("elem=%d,index=%d\n",elem,i);

	elem=11;
	list_node_insert_tail(linklist,elem);
	elem=12;
	list_node_insert_tail(linklist,elem);

	elem=13;
	list_node_delete_tail(linklist,&elem);
	printf("delete tail elem[%d]\n",elem);
	list_node_delete_tail(linklist,&elem);
	printf("delete tail elem[%d]\n",elem);
	list_node_delete_tail(linklist,&elem);
	printf("delete tail elem[%d]\n",elem);
	list_node_delete_tail(linklist,&elem);
	printf("delete tail elem[%d]\n",elem);
	
	printf("list is empty =%d\n",list_is_empty(linklist));
	
	node_number=list_length(linklist);
	for(i=0; i<node_number; i++){
		get_elem(linklist,1,&elem);
		printf("get elem[%d] ===",elem);
		list_node_delete(linklist,1,&elem);
		printf("delete elem[%d]\n",elem);
	}

	free_list(linklist);
	linklist=NULL;
	
	return 0;
}
