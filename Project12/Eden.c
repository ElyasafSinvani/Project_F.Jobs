#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int SearchJobsByFilters();
int ResumePublish();
void WatchResume();


int SearchJobsByFilters()
{
	FILE* file;
	file = fopen("C:\\Users\\97250\\Downloads\\JobsData.csv", "r");
	char area[20];
	char profession[20];
	char position[20];
	char word[20];
	int flag;
	char buffer[256];
	int n, m, i, j, line;
	char employer[20];
	char description[20];
	char city[20];
	char hours[20];
	char salary[20];
	char time_position[20];
	char category[20];
	char name[20];
	char number[20];


	printf("enter your area\n");
	gets(area);
	printf("enter your proffesion\n");
	gets(profession);
	printf("enter your position\n");
	gets(position);


	printf("which filter you want to use?\n");
	printf("for area press 1\n");
	printf("for proffesion press 2\n");
	printf("for position press 3\n");
	scanf("%d", &flag);

	char buf[500];
	if (flag == 1)
	{
		while (fscanf(file, "%s", buf) == 1)
		{

			sscanf(buf, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", number, name, category, hours, time_position, salary, city, description, employer);

			if (strcmp(area, city) == 0)
			{
				printf("jobs for you : \n");
				puts(buf);
			}



		}
	}
	else if (flag == 2)
	{
		while (fscanf(file, "%s", buf) == 1)
		{
			sscanf(buf, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", number, name, category, hours, time_position, salary, city, description, employer);

			if (strcmp(profession, category) == 0)
			{
				printf("jobs for you : \n");
				puts(buf);
			}
		}
	}
	else if (flag == 3)
	{
		while (fscanf(file, "%s", buf) == 1)
		{
			sscanf(buf, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", number, name, category, hours, time_position, salary, city, description, employer);

			if (strcmp(position, time_position) == 0)
			{
				printf("jobs for you : \n");
				puts(buf);
			}
		}
	}
	else
	{
		printf("error,enter valid digit");
	}
}

int ResumePublish()
{
	char resume[200];
	FILE* file;
	file = fopen("C:\\Users\\97250\\Downloads\\JobsAndCandidatesData.csv", "a");
	printf("enter your  details -use ',' to move between columns : \n");
	fgets(resume, sizeof(resume), stdin);
	fprintf(file, "%s", resume);
	printf("the resume published!");
	fclose(file);
	return 0;
}

void WatchResume()
{
	FILE* file;
	char buffer[256];
	file = fopen("C:\\Users\\97250\\Downloads\\JobsAndCandidatesData.csv", "r");
	if (file == NULL)
	{
		printf("no resume to show");
		exit(0);
	}
	else
	{
		printf("resumes that found : \n");
		while ((fgets(buffer, 255, file)) != NULL)
		{
			puts(buffer);
		}
		fclose(file);
	}
	return 0;
}


//int main()
//{
//	//SearchJobsByFilters();
//	ResumePublish();
//	WatchResume();
//
//
//}