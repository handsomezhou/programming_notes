/**
  *  Copyright (C) 2014-03-31  Handsome Zhou
  */
#include <stdio.h>
#include <string.h>
#include "string.h"

#define MIN_STR_SIZE	20

int main(int argc, char *argv[])
{
	char str1[]="hello w\0orld\0";
	char str2[MIN_STR_SIZE];
	char str3[]="hellp";
	char str4[]="helln";
	char *pstr1=str1;
	char *pstr2=NULL;
	int len1=my_strlen(pstr1);
	int len2=strlen(pstr1);
	printf("my_strlen(str)=%d \tstrlen(str)=%d\n",len1,len2);

	pstr1=str1;
	pstr2=my_strcpy(str2,pstr1);
	printf("pstr1=[%s],pstr2[%s]\n",pstr1,pstr2);

	int result=2;
	result=my_strcmp(pstr1,pstr2);
	printf("[%s]-[%s]=[%d]\n",pstr1,pstr2,result);

	result=my_strcmp(pstr1,str3);
	printf("[%s]-[%s]=[%d]\n",pstr1,str3,result);
	
	result=my_strcmp(pstr1,str4);
	printf("[%s]-[%s]=[%d]\n",pstr1,str4,result);
		
	
	return 0;
}

