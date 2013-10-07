/**
  *  Copyright (C) 2013-10-07  Handsome Zhou
  */
  
#include <stdio.h>
#include <stdlib.h>
#include "date.h"

struct DATE{
	int year;
	int month;
	int day;
};

void init_date(T_DATE **pdate)
{
	T_DATE **pd=pdate;
	
	if(NULL!=(*pd)){
		free_date(*pd);
		(*pd)=NULL;
	}
	
	(*pd)=(T_DATE *)malloc(sizeof(T_DATE));
}

void free_date(T_DATE *pdate)
{
	if(NULL!=pdate){
		free(pdate);
		pdate=NULL;
	}
}

int set_date(T_DATE *pdate,int month,int day,int year)
{
	if(NULL==pdate){
		return DT_FAILED;
	}
	pdate->month=month;
	pdate->day=day;
	pdate->year=year;
	
	return DT_SUCCEED;
}

int get_month(const T_DATE *pdate)
{
	int month=pdate->month;
	
	return month;
}

int get_day(const T_DATE *pdate)
{
	int day=pdate->day;
	
	return day;
}

int get_year(const T_DATE *pdate)
{
	int year=pdate->year;
	
	return year;
}
