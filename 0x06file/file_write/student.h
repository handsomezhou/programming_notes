/**
  *  Copyright (C) 2014-05-27  Handsome Zhou
  */
#ifndef STUDENT_H
#define STUDENT_H


#define SEX_MAN			'M'
#define SEX_FEMALE		'F'

#define MAX_ID_LEN		(24)
#define MAX_NAME_LEN	(64)
#define MAX_HOBBY_LEN	(256)



typedef struct student{
	char id[MAX_ID_LEN];
	char name[MAX_NAME_LEN];
	char sex;	//'F' or 'M'
	int age;
	char hobby[MAX_HOBBY_LEN];
}student_t;

student_t *malloc_student();
void free_student(student_t *p_student);
void set_id(student_t *p_student, char *p_id, int id_len);
const char *get_id(const student_t *p_student);
void set_name(student_t *p_student, char *p_name, int name_len);
const char *get_name(const student_t *p_student);
void set_sex(student_t *p_student,char sex);
char get_sex(const student_t *p_student);
void set_age(student_t *p_student, int age);
int get_age(const student_t *p_student);
void set_hobby(student_t *p_student, char *p_hobby, int hobby_len);
const char *get_hobby(const student_t *p_student);
void show_student(const student_t *p_student);


int get_max_id_len();
int get_max_name_len();
int get_max_hobby_len();
#endif/*STUDENT_H*/
