/**
  *  Copyright (C) 2014-05-27  Handsome Zhou
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

student_t *malloc_student()
{
	student_t *p_stu=(student_t *)malloc(sizeof(student_t));
	if(NULL==p_stu){
		printf("malloc student_t failed!\n");
		return NULL;
	}

	return p_stu;
}

void free_student(student_t *p_student)
{
	student_t *p_stu=p_student;
	if(NULL!=p_stu){
		free(p_stu);
		p_stu=NULL;
	}
}

void set_id(student_t *p_student, char *p_id, int id_len)
{
	student_t *p_stu=p_student;
	if((NULL==p_stu)||(NULL==p_id)){
		return;
	}

	int max_id_len=get_max_id_len();
	int cpy_len=(id_len<max_id_len)?(id_len):(max_id_len);
	memset(p_stu->id,0,max_id_len);
	strncpy(p_stu->id,p_id,cpy_len);

	return ;
}

const char *get_id(const student_t *p_student)
{
	const student_t *p_stu=p_student;
	if(NULL==p_stu){
		return NULL;
	}

	return p_stu->id;
}

void set_name(student_t *p_student, char *p_name, int name_len)
{
	student_t *p_stu=p_student;
	if((NULL==p_stu)||(NULL==p_name)){
		return;
	}
	int max_name_len=get_max_name_len();
	int cpy_len=((name_len<max_name_len)?(name_len):(max_name_len));
	memset(p_stu->name,0,max_name_len);
	strncpy(p_stu->name,p_name,cpy_len);
	
	return;
}

const char *get_name(const student_t *p_student)
{
	const student_t *p_stu=p_student;
	if(NULL==p_stu){
		return NULL;
	}

	return p_stu->name;
}

void set_sex(student_t *p_student,char sex)
{
	student_t *p_stu=p_student;
	if(NULL==p_stu){
		return;
	}

	p_stu->sex=sex;
	
	return;
}

char get_sex(const student_t *p_student)
{
	const student_t *p_stu=p_student;
	if(NULL==p_stu){
		return '\0';
	}

	return p_stu->sex;
}

void set_age(student_t *p_student, int age)
{
	student_t *p_stu=p_student;
	if(NULL==p_stu){
		return ;
	}

	p_stu->age=age;
}

int get_age(const student_t *p_student)
{
	const student_t *p_stu=p_student;
	if(NULL==p_stu){
		return -1;
	}

	return p_stu->age;
}

void set_hobby(student_t *p_student, char *p_hobby, int hobby_len)
{
	student_t *p_stu=p_student;
	if((NULL==p_stu)||(NULL==p_hobby)){
		return;
	}
	int max_hobby_len=get_max_hobby_len();
	int cpy_len=((hobby_len<max_hobby_len)?(hobby_len):(max_hobby_len));
	memset(p_stu->hobby,0,max_hobby_len);
	strncpy(p_stu->hobby,p_hobby,cpy_len);
	
}

const char *get_hobby(const student_t *p_student)
{
	const student_t *p_stu=p_student;
	if(NULL==p_stu){
		return NULL;
	}

	return p_stu->hobby;
}

void show_student(const student_t *p_student)
{
	const student_t *p_stu=p_student;
	if(NULL==p_stu){
		return;
	}
	printf("id=[%s];name=[%s];sex=[%c];age=[%d],hobby=[%s]\n",\
		p_stu->id,p_stu->name,p_stu->sex,p_stu->age,p_stu->hobby);
	
	return;
}

int get_max_id_len()
{
	return MAX_ID_LEN;
}

int get_max_name_len()
{
	return MAX_NAME_LEN;
}

int get_max_hobby_len()
{
	return MAX_HOBBY_LEN;
}

