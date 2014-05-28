/**
  *  Copyright (C) 2014-05-27  Handsome Zhou
  */
#include <stdio.h>
#include <string.h>
#include "student.h"

#define STUDENT_NUMBER	16
#define OPEN_FILE_MODE_CREATE_OR_OPEN_TEXT		"wt"
#define OPEN_FILE_MODE_OPEN_TEXT		   		"rt"

#define OPEN_FILE_MODE_CREATE_OR_OPEN_BINARY	"wb"
#define OPEN_FILE_MODE_OPEN_BINARY				"rb"

int main(int argc, char *argv[])
{
	char file_path[]="./student_info.txt";
	student_t *p_student[STUDENT_NUMBER];
	int i=0,j=0,read_student_number=0;
	//malloc student
	for(i=0; i<STUDENT_NUMBER; i++){
		p_student[i]=malloc_student();
		if(NULL==p_student[i]){
			for(j=i-1; j>=0; j--){
				free_student(p_student[j]);
			}

			return -1;
		}
	}
	
	for(i=0; i<STUDENT_NUMBER; i++){
		memset(p_student[i],0,sizeof(student_t));
	}
	
	printf("read file.....\n");
	FILE *fp=NULL;
	//open file 
	fp=fopen(file_path,OPEN_FILE_MODE_OPEN_TEXT);
	if(NULL==fp){
		printf("open file failed!\n");
	}

	size_t size=0;
	//read file 
	for(i=0; i<STUDENT_NUMBER; i++){
		size=fread(p_student[i],sizeof(student_t),1,fp);
		printf("..........size=[%d]..........\n",size);
		if(0==size){
			read_student_number=i;
			break;
		}
	}
	
	for(i=0; i<read_student_number; i++){
		show_student(p_student[i]);
	}

	//close file
	if(NULL==fp){
		fclose(fp);
		fp=NULL;
	}

	//free student
	for(i=0; i<STUDENT_NUMBER; i++){
		free_student(p_student[i]);
		p_student[i]=NULL;
	}
	
	return 0;
}
