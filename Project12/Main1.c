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
typedef struct User
{
	char type[15];
	char* ID;
}User;
worker set_new_worker();
employer set_new_employer();
void Create_account();
int Login(User* U);
void upload_file(char* FName, char* NewValue, int row, int col);
void Editing_details(User U);
void _ERR(char a);

int main()
{
	int x;
	User s;
	Create_account();
	x = Login(&s);
	printf("%s,%s\n",s.ID,s.type);
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
int Login(User* U)
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
						printf("You've logged in successfully!\n");
						U->ID = (char*)malloc(strlen(tid) + 1);
						strcpy(U->ID, tid);
						strcpy(U->type, "Employer");
						return 1;
					}
					else
					{
						printf("Username or password incorrect\n");
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
						printf("You've logged in successfully!\n");
						U->ID= (char*)malloc(strlen(tid) + 1);
						strcpy(U->ID, tid);
						strcpy(U->type, "Worker");
						return 1;
					}
					else
					{
						printf("Username or password incorrect\n");
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
void upload_file(char* FName, char* NewValue, int row, int col) {
	int i, r = 1, c, first = 0;
	char line[1024];
	FILE* f;
	char* tmp;
	if (!(f = fopen(FName, "r+"))) _ERR("f");

	while (fgets(line, 1024, f))
	{
		if (first)
		{
			if (!(tmp = _strdup(line))) _ERR("m");
			for (i = 0, c = 1; i < strlen(tmp); i++) {
				if (!(fseek(f, 1, SEEK_CUR))) _ERR("k");
				if (tmp[i] == ",") 
					c++;
				if (r == row && c == col) {
					fprintf(f, "%s", NewValue);
				}
			}
			free(tmp);
			r++;
		}
		first = 1;
	}
	fclose(f);
}
void _ERR(char a) 
{
	if (a == "f") {
		printf("\n\tError File !!\n\n");
	}
	else if (a == "m") {
		printf("\n\tError Memory !!\n\n");
	}
	else {
		printf("\n\tError !!\n\n");
	}
	exit(1);
}
void Editing_details(User U)
{
	char line[1024];
	int first = 0;
	int row = 0;
	int c;
	char newVal[20];
	FILE* emp = fopen(FILENAME2, "r");
	FILE* wor = fopen(FILENAME, "r");
	if (strcmp(U.type, "Employer")==0)
	{
		printf("1 - Change phone number\n2 - Change address\n");
		scanf_s("%d", &c);

		switch (c)
		{
		case 1:
			printf("Please put your new phone number:\n");
			gets(newVal);
			gets(newVal);
			while (fgets(line, 1024, emp))
			{
				if (first)
				{
					char* id = strtok(line, ",");
					if (strcmp(U.ID, id) == 0)
						upload_file(FILENAME2, newVal, row, 4);

				}
				first = 1;
				row++;
			}
			break;

		case 2:
			printf("Please put your new address:\n");
			gets(newVal);
			gets(newVal);
			while (fgets(line, 1024, emp))
			{
				if (first)
				{
					char* id = strtok(line, ",");
					if (strcmp(U.ID, id) == 0)
						upload_file(FILENAME2, newVal, row, 3);

				}
				first = 1;
				row++;
			}
			break;

		default:
			break;
		}

	}
	else
	{
		printf("1 - Change phone number\n2 - Change address\n3 - Change email");
		scanf_s("%d", &c);

		switch (c)
		{
		case 1:
			printf("Please put your new phone number:\n");
			gets(newVal);
			gets(newVal);
			while (fgets(line, 1024, emp))
			{
				if (first)
				{
					char* id = strtok(line, ",");
					if (strcmp(U.ID, id) == 0)
						upload_file(FILENAME2, newVal, row, 5);

				}
				first = 1;
				row++;
			}
			break;

		case 2:
			printf("Please put your new address:\n");
			gets(newVal);
			gets(newVal);
			while (fgets(line, 1024, emp))
			{
				if (first)
				{
					char* id = strtok(line, ",");
					if (strcmp(U.ID, id) == 0)
						upload_file(FILENAME2, newVal, row, 4);

				}
				first = 1;
				row++;
			}
			break;

		case 3:
			printf("Please put your new email:\n");
			gets(newVal);
			gets(newVal);
			while (fgets(line, 1024, emp))
			{
				if (first)
				{
					char* id = strtok(line, ",");
					if (strcmp(U.ID, id) == 0)
						upload_file(FILENAME2, newVal, row, 7);

				}
				first = 1;
				row++;
			}
			break;

		default:
			break;
		}
	}

}
