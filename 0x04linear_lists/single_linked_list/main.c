/**
  *  Copyright (C) 2014-03-28  Handsome Zhou
  */

#include <stdio.h>
#include "single_linked_list.h"

int main(int argc, char *argv[])
{
	int i=0;
	int node_number=10;
	node_t *plist=NULL;
	node_t *pnode=NULL;
	data_t *pdata=malloc_data();
	int number=1;
	
	
	plist=list_new_head_node();

	for(i=0; i<node_number; i++){
		set_number_to_data(pdata,++number);
		pnode=produce_node(pdata);
		list_node_append(plist,pnode);
	}

	list_travel(plist,&show_node);
	
	list_delete(plist);
	plist=NULL;
	
	return 0;
}
