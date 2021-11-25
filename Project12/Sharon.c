#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void PrintSubmissions();
void PrintCandidate(char line[]);
void PrintJob(char line[]);
char* SearchJob(char line[], char* _jobName);
char* SearchCandidate(char* _ID);
//void FilterCandidates();

enum CandidateColumns { C_No, C_ID, C_Password, C_FirstName, C_LastName, C_City, C_Birth, C_Phone, C_Email } CandidateColumns;
enum EmployersColumns { E_No, E_ID, E_Password, E_Name, E_City, E_Phone, E_Email } EmployersColumns;
enum JobsColumns { J_No, J_Name, J_Category, J_Hours, J_TimePosition, J_Salary, J_City, J_Description, J_EmployerID } JobsColumns;
enum JobsAndCandidatesColumns { JC_JobNo, JC_CandidateID } JobsAndCandidatesColumns;

//
//int main()
//{
//	PrintSubmissions();
//
//	return 0;
//}


void PrintSubmissions()
{
	char jobName[50];
	printf("Enter job name: ");
	gets(jobName);

	//checkjobIDValidation(jobName) //TODO

	FILE* jobsFile = fopen("C:\\Docs\\JobsData.csv", "r");
	FILE* jobsAndCandidatesFile = fopen("C:\\Docs\\JobsAndCandidatesData.csv", "r");
	FILE* candidatesFile = fopen("C:\\Docs\\CandidatesData.csv", "r");

	if (jobsFile == NULL)
	{
		printf("Error!");
		exit(1);
	}
	if (jobsAndCandidatesFile == NULL)
	{
		printf("Error!");
		exit(1);
	}
	if (candidatesFile == NULL)
	{
		printf("Error!");
		exit(1);
	}

	char line1[1024];
	char line2[1024];
	int first = 0;
	int flag = 0;

	while (fgets(line1, 1024, jobsFile)) // search job
	{
		if (first) // first line is columns headers
		{
			char* job = SearchJob(line1, jobName);

			if (job) // job exist 
			{
				first = 0;
				char* job_arr[9];
				char* value = strtok(line1, ",");
				for (int i = 0; i < 9; i++)
				{
					if (value)
					{
						job_arr[i] = (char*)malloc((strlen(value) + 1) * sizeof(char));
						strcpy(job_arr[i], value);
						value = strtok(NULL, ",");
					}
				}

				int flag2 = 0;

				while (fgets(line2, 1024, jobsAndCandidatesFile)) // search job submissions
				{
					if (first)
					{
						char* value = strtok(line2, ",");
						if (strcmp(value, job_arr[0]) == 0)
						{
							char* candidate = SearchCandidate(strtok(strtok(NULL, ","), "\n"));
							if (candidate)
							{
								PrintCandidate(candidate);
								flag2 = 1;
							}
						}


					}


					first = 1;
				}
				if (flag2 == 0)
					printf("\nThere is no submissions for this job.\n");

				flag = 1;
			}
		}

		first = 1;
	}

	if (flag == 0)
		printf("\nError! Job doesn't exist\n");


	fclose(jobsFile);
	fclose(jobsAndCandidatesFile);
	fclose(candidatesFile);

}

void PrintCandidate(char line[])
{
	char* arr[9];
	char* value = strtok(line, ",");
	for (int i = 0; i < 9; i++)
	{
		if (value)
		{
			arr[i] = (char*)malloc((strlen(value) + 1) * sizeof(char));
			strcpy(arr[i], value);
			value = strtok(NULL, ",");
		}
	}

	printf("\nName: %s %s\n", arr[C_FirstName], arr[C_LastName]);
	printf("ID: %s\n", arr[C_ID]);
	printf("Address: %s\n", arr[C_City]);
	printf("Birth date: %s\n", arr[C_Birth]);
	printf("Phone number: %s\n", arr[C_Phone]);
	printf("Email: %s\n", arr[C_Email]);

	for (int i = 0; i < 9; i++)
		free(arr[i]);
}

void PrintJob(char line[])
{
	char* arr[9];
	char* value = strtok(line, ",");
	for (int i = 0; i < 9; i++)
	{
		if (value)
		{
			arr[i] = (char*)malloc((strlen(value) + 1) * sizeof(char));
			strcpy(arr[i], value);
			value = strtok(NULL, ",");
		}
	}

	printf("\nName: %s\n", arr[J_Name]);
	printf("Category: %s\n", arr[J_Category]);
	printf("Work hours: %s\n", arr[J_Hours]);
	printf("Time position: %s\n", arr[J_TimePosition]);
	printf("Salary per hour: %s\n", arr[J_Salary]);
	printf("Location: %s\n", arr[J_City]);
	printf("Job description: %s\n", arr[J_Description]);

	for (int i = 0; i < 9; i++)
		free(arr[i]);
}

char* SearchJob(char line[], char* _jobName)
{
	char tmp[1024];
	strcpy(tmp, line);
	char* arr[9];
	char* value = strtok(line, ",");
	for (int i = 0; i < 9; i++)
	{
		if (value)
		{
			arr[i] = (char*)malloc((strlen(value) + 1) * sizeof(char));
			strcpy(arr[i], value);
			value = strtok(NULL, ",");
		}
	}

	if (strcmp(arr[J_Name], _jobName) == 0) // arr[1] = column 'Name'
	{
		char* job = (char*)malloc((strlen(line) + 1) * sizeof(char));
		if (job != NULL)
			strcpy(job, line);
		return tmp;
	}

	return NULL;
}

char* SearchCandidate(char* _ID)
{
	FILE* file = fopen("C:\\Docs\\CandidatesData.csv", "r");
	char line[1024];
	int first = 0;
	char tmp[1024];



	while (fgets(line, 1024, file))
	{
		strcpy(tmp, line);
		if (first)
		{
			char* id = strtok(line, ",");
			id = strtok(NULL, ",");

			if (strcmp(id, _ID) == 0)
				return tmp;
		}

		first = 1;
	}

	return NULL;
}


//void FilterCandidates()
//{
//	char jobName[50];
//	printf("Enter job name: ");
//	gets(jobName);
//
//	char candidateID[50];
//	printf("Enter candidate ID to remove: ");
//	gets(candidateID);
//
//	//checkCandidateIDValidation(candidateID) //TODO
//
//	char* candidate = SearchCandidate(candidateID);
//	if (candidate)
//	{
//
//	}
//	else
//		printf("\nError! Candidate doesn't exist\n");
//}