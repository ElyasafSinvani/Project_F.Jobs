#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
//#include <iostream>
#include <stdlib.h>
#define FILENAME "CandidatesData.csv"
#define FILENAME2 "EmployersData.csv"


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
	int password;
}worker;
typedef struct employer
{
	char* Number_deals;
	char* name;
	char* city;
	char* phone;
	int password;
}employer;
int main()
{
	int x;
	x = Login();
	printf("%d", x);
	return 0;

}
worker set_new_worker()
{
	char tfname[20];
	char tlname[20];
	char tid[10];
	char tphone[11];
	date tbirth;
	char tcity[20];
	char temail[50];
	int tpassword;
	worker w1;
	printf("Enter first name :\n");
	gets(tfname);
	gets(tfname);
	/*getchar();*/
	w1.fname = (char*)malloc(strlen(tfname) + 1);
	strcpy(w1.fname, tfname);
	printf("Enter last name :\n");
	gets(tlname);
	w1.lname = (char*)malloc(strlen(tlname) + 1);
	strcpy(w1.lname, tlname);
	printf("Enter id :\n");
	gets(tid);
	while (strlen(tid) != 9)
	{
		printf("Erorr ID please try again\n");
		printf("Enter id :\n");
		gets(tid);
	}
	w1.id = (char*)malloc(strlen(tid) + 1);
	strcpy(w1.id, tid);
	printf("Enter phone number :\n");
	gets(tphone);
	w1.phone = (char*)malloc(strlen(tphone) + 1);
	strcpy(w1.phone, tphone);
	printf("Enter day of birth :\n");
	scanf_s("%d",&tbirth.day);
	getchar();
	printf("Enter month of birth :\n");
	scanf_s("%d", &tbirth.month);
	getchar();
	printf("Enter year of birth :\n");
	scanf_s("%d", &tbirth.year);
	getchar();
	w1.birth.day = tbirth.day;
	w1.birth.month = tbirth.month;
	w1.birth.year = tbirth.year;
	printf("Enter your city :\n");
	gets(tcity);
	getchar();
	w1.city = (char*)malloc(strlen(tcity) + 1);
	strcpy(w1.city, tcity);
	printf("Enter your email :\n");
	gets(temail);
	getchar();
	w1.email = (char*)malloc(strlen(temail) + 1);
	strcpy(w1.email, temail);
	printf("Enter your password :\n");
	scanf_s("%d", &tpassword);
	w1.password = tpassword;
	return w1;
}
employer set_new_employer()
{
	char tfname[20];
	char tid[10];
	char tphone[11];
	char tcity[20];
	int tpassword;
	employer e1;
	printf("Enter first name :\n");
	gets(tfname);
	gets(tfname);
	e1.name = (char*)malloc(strlen(tfname) + 1);
	strcpy(e1.name, tfname);
	printf("Enter Number_deals :\n");
	gets(tid);
	while (strlen(tid) != 9)
	{
		printf("Erorr Number_deals please try again\n");
		printf("Enter id :\n");
		gets(tid);
	}
	e1.Number_deals = (char*)malloc(strlen(tid) + 1);
	strcpy(e1.Number_deals, tid);
	printf("Enter phone number :\n");
	gets(tphone);
	e1.phone = (char*)malloc(strlen(tphone) + 1);
	strcpy(e1.phone, tphone);
	printf("Enter your city :\n");
	gets(tcity);
	getchar();
	e1.city = (char*)malloc(strlen(tcity) + 1);
	strcpy(e1.city, tcity);
	printf("Enter your password :\n");
	scanf_s("%d", &tpassword);
	e1.password = tpassword;
	return e1;

}
void Create_account()
{
	FILE* wor,*emp;
	wor = fopen(FILENAME, "a");
	emp = fopen(FILENAME2, "a");
	int c;
	worker W;
	employer E;
	printf("1 - Employer \n2 - worker \n");
	scanf_s("%d", &c);
	switch (c)
	{

	case 1:
		E = set_new_employer();
		fprintf(emp, "\n%s,%d,%s,%s,%s", E.Number_deals, E.password, E.name, E.city, E.phone);
		fclose(emp);
		break;
	case 2:
		W = set_new_worker();
		fprintf(wor, "\n%s,%d,%s,%s,%s,%s,%s,%d.%d.%d", W.id, W.password, W.fname, W.lname, W.city, W.phone, W.email , W.birth.day, W.birth.month, W.birth.year);
		fclose(wor);
		printf("The registration was successful!");
		break;
	default:
		break;
	}
}
int Login()
{
	FILE* wor, * emp;
	char tid[10];
	char tpassword[6];
	int c;
	printf("1 - Login as an employer \n2 - Login as an worker\n");
	scanf_s("%d", &c);
	printf("Enter id :\n");
	gets(tid);
	gets(tid);
	while (strlen(tid) != 9)
	{
		printf("Erorr ID please try again\n");
		printf("Enter id :\n");
		gets(tid);
	}
	printf("Enter your password :\n");
	gets(tpassword);
	char line[1024];
	int first = 0;
	switch (c)
	{
	case 1:
		emp = fopen(FILENAME2, "r");
		while (fgets(line, 1024, emp))
		{
			if (first)
			{
				char* id = strtok(line, ",");
				char* password = strtok(NULL, ",");
				if (strcmp(id, tid) == 0)
				{
					if (strcmp(password, tpassword) == 0)
					{
						printf("You've logged in successfully!");
						return 1;
					}
					else
					{
						printf("Username or password incorrect");
						return 0;
					}
				}
			}
			first = 1;
		}
	case 2:
		wor = fopen(FILENAME, "r");
		while (fgets(line, 1024, wor))
		{
			if (first)
			{
				char* id = strtok(line, ",");
				char* password = strtok(NULL, ",");
				if (strcmp(id, tid) == 0)
				{
					if (strcmp(password,tpassword)==0)
					{
						printf("You've logged in successfully!");
						return 1;
					}
					else
					{
						printf("Username or password incorrect");
						return 0;
					}
				}
			}
			first = 1;
		}

	default:
		break;
	}
}
