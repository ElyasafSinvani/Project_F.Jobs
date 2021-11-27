#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <conio.h>

void clr() {
	system("pwd&&clear||cls");
}

void _ERR(char a) {
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

char* stmm(const char* src) {
	char* dst = malloc(strlen(src) + 1);
	if (dst == NULL) return NULL;  
	strcpy(dst, src);
	return dst;
}


const char* getfield(char* line, int num)
{
	const char* tok;
	for (tok = strtok(line, ",");
		tok && *tok;
		tok = strtok(NULL, ",\n"))
	{
		if (!--num)
			return tok;
	}
	return NULL;
}

void edit_file(char* FName, char* NewValue, int row, int col) {
	int i, r = 0, c,j=1;
	char line[1024];
	FILE* fr, * fw;
	fr = fopen(FName, "r");
	fw = fopen(FName, "r+");
	if (fr == NULL|| fw == NULL) _ERR("f");
	while (fgets(line, 1024, fr))
	{
		char* tmp = stmm(line);
		if (tmp == NULL) _ERR("m");
		for (i = 0, c = 1; i < strlen(tmp); i++) {
			if (tmp[i] == 44) c++;
		}
		for (i = 0; i < c; i++) {
			if (r == row && i+1 == col) {
				fprintf(fw,"%s", NewValue);
			} else {
				free(tmp);
				tmp = stmm(line);
				if (tmp == NULL) _ERR("m");
				fprintf(fw,"%s", getfield(tmp, i + 1));
			}
			(i < c - 1) ? fprintf(fw,",") : fprintf(fw,"\n");
		}
		free(tmp);
		r++;
	}
	fclose(fr);
	fclose(fw);
}







void all_jobs(char* id, char* filter, int num) {
	char line[1024];

	FILE* j_data = fopen(".\\JobsData.csv", "r");
	if (j_data == NULL) _ERR("f");

	while (fgets(line, 1024, j_data))
	{
		char* tmp = stmm(line);
		if (tmp == NULL) _ERR("m");
		if (!(strcmp(id, getfield(tmp, 9)))) {
			if (num != 1) {
				free(tmp);
				tmp = stmm(line);
				if (tmp == NULL) _ERR("m");
				if (!(strcmp(filter, getfield(tmp, num)))) PrintJob(line);
			}
			else {
				PrintJob(line);
			}
		}
		free(tmp);
	}
	fclose(j_data);
}

void lookfor_jobs(char* id) {
	int i, j, select, help;
	char filter[128];
	
	printf("\nLooking for your jobs by fiter:\n\n1 - all\n2 - by Name\n3 - by Catego");
	printf("ry\n4 - by Work hours\n5 - by Time Position\n6 - by Salary per hour\n");
	printf("7 - by Location\n8 - by Job description\n\nSelect one option[1-8]:");
	do {
		scanf("%d", &select);
		if (select < 1 || select>8) printf("\nWrong input!!, try again[1-8]:");
	} while (select < 1 || select>8);
	getchar();
	clr();
	if (select == 1) filter[0]=NULL;
	if (select == 2) {
		do {
			printf("\nEnter Name[max 20 characters]: ");
			gets(filter);
			if (strlen(filter) > 20) printf("\nWrong input!!, try again.");
		} while (strlen(filter) > 20);
	}
	if (select == 3) {
		do {
			printf("\nEnter Category[max 50 characters]: ");
			gets(filter);
			if (strlen(filter) > 50) printf("\nWrong input!!, try again.");
		} while (strlen(filter) > 50);

	}
	if (select == 4) {
		do {
			help = 0;
			printf("\nEnter hours[1-12]: ");
			gets(filter);
			if (strlen(filter) == 2) {
				help = (filter[0] - 48) * 10 + filter[1] - 48;
			} else {
				help = (filter[0] - 48);
			}
			if (help > 12 || help < 0 || strlen(filter)>2)
				printf("\nWrong input!! try again.");
		} while (help > 12 || help < 0 || strlen(filter)>2);


	}
	if (select == 5) {
		do {
			printf("\nEnter 1 for 'Full' or 2 for 'Half' :");
			scanf("%d", &help);
			if (help != 1 && help != 2) printf("\nWrong input!!, try again.");
		} while (help != 1 && help != 2);
		if (help == 2) {
			filter[4] = "Half";
		} else {
			filter[4] = "Full";
		}
	}
	if (select == 6) {
		do {
			help = 0;
			printf("\nEnter Salary per hour[max 4 digits]: ");
			gets(filter);
			if (strlen(filter) > 4) help = 1;
			for (i = 0; i < strlen(filter); i++)
				if (filter[i] < 48 || filter[i]>57) help=1;
			if (help) printf("\nWrong input!!, try again.");
		} while (help);

	}
	if (select == 7) {
		do {
			printf("\nEnter Location[max 20 characters]: ");
			gets(filter);
			if (strlen(filter) > 20) printf("\nWrong input!!, try again.");
		} while (strlen(filter) > 20);

	}
	if (select == 8) {
		do {
			printf("\nEnter Job description[max 100 characters]: ");
			gets(filter);
			if (strlen(filter) > 100) printf("\nWrong input!!, try again.");
		} while (strlen(filter) > 100);

	}



	all_jobs(id, filter, select);

}
