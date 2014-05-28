/**
  *  Copyright (C) 2014-05-27  Handsome Zhou
  */

#include <stdio.h>
#include <string.h>
#include "student.h"

#define STUDENT_NUMBER	8
#define OPEN_FILE_MODE_CREATE_OR_OPEN_TEXT		"wt"
#define OPEN_FILE_MODE_OPEN_TEXT		   		"rt"

#define OPEN_FILE_MODE_CREATE_OR_OPEN_BINARY	"wb"
#define OPEN_FILE_MODE_OPEN_BINARY				"rb"
int main(int argc,char *argv[])
{
	char file_path[]="./student_info.txt";
	char stu_id[STUDENT_NUMBER][MAX_ID_LEN]={{"00000000"},{"00000001"},{"00000010"},{"00000011"},{"00000100"},{"00000101"},{"00000110"},{"00000111"}};
	char stu_name[STUDENT_NUMBER][MAX_NAME_LEN]={{"MasonÍõ"},{"James³Â"},{"LucasÖÜ"},{"Henry"},{"Evan"},{"Parker"},{"Lucy"},{"Eva"}};
	char stu_sex[STUDENT_NUMBER]={'M','F','F','M','F','M','F','M'};
	int stu_age[STUDENT_NUMBER]={12,18,34,23,24,19,35,32};
	char stu_hobby[STUDENT_NUMBER][MAX_HOBBY_LEN]={{"Reading,Watching TV and Family Time"},{"Going to Movies and Fishing"},{"Computer,Gardening and Renting Movies"},{"Walking"},{"Exercise,Listening to Music"},{"Entertaining,Hunting"},{"Team Sports,Shopping and Traveling"},{"Sleeping"}};
	int i=0,j=0;
	student_t *p_student[STUDENT_NUMBER];

	//malloc file
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
		set_id(p_student[i],stu_id[i],strlen(stu_id[i]));
		set_name(p_student[i],stu_name[i],strlen(stu_name[i]));
		set_sex(p_student[i],stu_sex[i]);
		set_age(p_student[i],stu_age[i]);
		set_hobby(p_student[i],stu_hobby[i],strlen(stu_hobby[i]));
	}

	for(i=0; i<STUDENT_NUMBER; i++){
		show_student(p_student[i]);
	}

	printf("write file.....\n");
	FILE *fp=NULL;
	//open file
	fp=fopen(file_path,OPEN_FILE_MODE_CREATE_OR_OPEN_TEXT);
	if(NULL==fp){
		printf("create or open file failed!\n");
		return -1;
	}
	
	//write file
	for(i=0; i<STUDENT_NUMBER; i++){
		fwrite(p_student[i],sizeof(student_t),1,fp);
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
