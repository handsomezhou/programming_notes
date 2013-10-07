/**
  *  Copyright (C) 2013-10-07  Handsome Zhou
  */

/**
 *@brief	Demo:How to protect the data in struct in C language
 *@author	handsomezhou  
 *@date 	2013-10-07
 */
#include <stdio.h>
#include "date.h"

int main(void)
{
	T_DATE *pdate=NULL;
	//pdate=(T_DATE *)malloc(sizeof(T_DATE));	// error: invalid application of ‘sizeof’ to incomplete type ‘T_DATE’
	init_date(&pdate);
	set_date(pdate,10,7,2013);
	printf("%d-%d-%d\n",get_month(pdate),get_day(pdate),get_year(pdate));
	//printf("%d-%d-%d\n",pdate->month,pdate->day,pdate->year);// error: dereferencing pointer to incomplete type
	
	free_date(pdate);
	
	return 0;
}