#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
//#include <iostream>
#include <stdlib.h>

typedef struct date
{
	int day;
	int month;
	int year;
}date;
typedef struct worker
{
	date birth;
	char* fname;
	char* lname;
	char* id;
	char* phone;
	char* email;
	char* city;
}worker;

worker set_new_worker()
{
	char tfname[20];
	char tlname[20];
	char tid[9];
	char tphone[10];
	date tbirth;
	char tcity[20];
	char temail[50];
	worker w1;
	printf("Enter first name :\n");
	gets(tfname);
	getchar();
	w1.fname = (char*)malloc(strlen(tfname) + 1);
	strcpy(w1.fname, tfname);
	printf("Enter last name :\n");
	gets(tlname);
	getchar();
	w1.lname = (char*)malloc(strlen(tlname) + 1);
	strcpy(w1.lname, tlname);
	printf("Enter id :\n");
	gets(tid);
	getchar();
	w1.id = (char*)malloc(strlen(tid) + 1);
	printf("Enter phone number :\n");
	gets(tphone);
	getchar();
	w1.phone = (char*)malloc(strlen(tphone) + 1);
	printf("Enter day of birth :\n");
	scanf_s("%d",&tbirth.day);
	getchar();
	printf("Enter month of birth :\n");
	scanf_s("%d", &tbirth.month);
	getchar();
	printf("Enter year of birth :\n");
	scanf_s("%d", &tbirth.year);
	getchar();
	printf("Enter your city :\n");
	gets(tcity);
	getchar();
	w1.city = (char*)malloc(strlen(tcity) + 1);
	printf("Enter your email :\n");
	gets(temail);
	getchar();
	w1.email = (char*)malloc(strlen(temail) + 1);
	return w1;
}


int main()
{
	worker W;
	W = set_new_worker();
	puts(W.fname);
}