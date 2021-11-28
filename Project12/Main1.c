#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CANDIDATES_FILE ".\\Data Files\\CandidatesData.csv"
#define EMPLOYERS_FILE ".\\Data Files\\EmployersData.csv"
#define JOBS_FILE ".\\Data Files\\JobsData.csv"
#define JOBS_AND_CANDIDATES_FILE ".\\Data Files\\JobsAndCandidatesData.csv"

enum CandidateColumns { C_ID, C_Password, C_FirstName, C_LastName, C_City, C_Phone, C_Email, C_Birth } CandidateColumns;
enum EmployersColumns { E_ID, E_Password, E_Name, E_City, E_Phone } EmployersColumns;
enum JobsColumns { J_No, J_Name, J_Category, J_Hours, J_TimePosition, J_Salary, J_City, J_Description, J_EmployerID } JobsColumns;
enum JobsAndCandidatesColumns { JC_JobNo, JC_CandidateID } JobsAndCandidatesColumns;

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
typedef struct job
{
	char* code;
	char* name;
	char* category;
	char* tposition;
	float salar;
	char* location;
	char* description;
	int workhours;
}job;

void PrintSubmissions();
void PrintCandidate(char line[]);
void PrintJob(char line[]);
char* SearchJob(char line[], char* _jobName);
char* SearchCandidate(char* _ID);
void FilterCandidates();
int IsJobExist(char jobName[]);
int IsCandidateExist(char candidateID[]);
void MainMenu(User* _currentUser);
void PrintCandidateMenu(User* _currentUser);
void PrintCandidateMenuOptions(User* _currentUser);
void PrintEmployerMenu(User* _currentUser);
void PrintEmployerMenuOptions(User* _currentUser);
void DisplayUserManual();
void PrintSalaryData();

worker set_new_worker();
employer set_new_employer();
void Create_account();
int Login(User* U, int user);
void Editing_details(User U);

int SearchJobsByFilters();
int ResumePublish();
void WatchResume();
void InterviewTips();

void clr();
void _ERR(char a);
char* stmm(const char* src);
const char* getfield(char* line, int num);
void edit_file(char* FName, char* NewValue, int row, int col);
void all_jobs(char* id, char* filter, int num);
void lookfor_jobs(char* id);

job publishJob();
job upadteJob();
job addJob();
void edit_filedigits(char* FName, int NewValue, int row, int col);

int main()
{
	User* currentUser = NULL;
	MainMenu(&currentUser);

	return 0;
}


void PrintSubmissions()
{
	char jobName[50];
	printf("Enter job name: ");
	gets(jobName);

	//checkjobIDValidation(jobName) //TODO

	FILE* jobsFile = fopen(JOBS_FILE, "r");
	FILE* jobsAndCandidatesFile = fopen(JOBS_AND_CANDIDATES_FILE, "r");
	FILE* candidatesFile = fopen(CANDIDATES_FILE, "r");

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
				char* job_arr[7];
				char* value = strtok(line1, ",");
				for (int i = 0; i < 7; i++)
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
						if (strcmp(value, job_arr[J_Name]) == 0)
						{
							char* candidate = SearchCandidate(strtok(NULL, "\n"));
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
	char* arr[8];
	char* value = strtok(line, ",");
	for (int i = 0; i < 8; i++)
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

	for (int i = 0; i < 8; i++)
		free(arr[i]);
}

void PrintJob(char line[])
{
	char* arr[7];
	char* value = strtok(line, ",");
	for (int i = 0; i < 7; i++)
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

	for (int i = 0; i < 7; i++)
		free(arr[i]);
}

char* SearchJob(char line[], char* _jobName)
{
	char tmp[1024];
	strcpy(tmp, line);
	char* arr[7];
	char* value = strtok(tmp, ",");
	for (int i = 0; i < 7; i++)
	{
		if (value)
		{
			arr[i] = (char*)malloc((strlen(value) + 1) * sizeof(char));
			strcpy(arr[i], value);
			value = strtok(NULL, ",");
		}
	}

	if (strcmp(arr[J_Name], _jobName) == 0) // arr[1] = column 'Name'
		return line;

	return NULL;
}

char* SearchCandidate(char* _ID)
{
	FILE* file = fopen(CANDIDATES_FILE, "r");
	if (file == NULL)
	{
		printf("Error!");
		exit(1);
	}

	char line[1024];
	int first = 0;
	char tmp[1024];

	while (fgets(line, 1024, file))
	{
		strcpy(tmp, line);
		if (first)
		{
			char* id = strtok(line, ",");
			//id = strtok(NULL, ",");

			if (strcmp(id, _ID) == 0)
				return tmp;
		}

		first = 1;
	}
	return NULL;
}

void FilterCandidates()
{
	char jobName[50];
	printf("Enter job name: ");
	gets(jobName);

	if (!IsJobExist(jobName)) // job dosen't exist 
	{
		printf("\nError! Job dosen't exist\n");
		return;
	}

	char candidateID[50];
	printf("Enter candidate ID to remove: ");
	gets(candidateID);

	//checkCandidateIDValidation(candidateID) //TODO

	if (!IsCandidateExist(candidateID)) // job dosen't exist 
	{
		printf("\nError! Candidate dosen't exist\n");
		return;
	}

	FILE* file = fopen(JOBS_AND_CANDIDATES_FILE, "r");
	if (file == NULL)
	{
		printf("Error!");
		exit(1);
	}

	char line[1024];
	int first = 0;
	int row = 0;

	while (fgets(line, 1024, file))
	{
		if (first) // first line is columns headers
		{
			char* _jobName = strtok(line, ",");
			char* _candidateID = strtok(NULL, "\n");

			if ((strcmp(_jobName, jobName) == 0) && (strcmp(_candidateID, candidateID) == 0))
			{
				edit_file(JOBS_AND_CANDIDATES_FILE, "null, ", row, 0);
				edit_file(JOBS_AND_CANDIDATES_FILE, "null, ", row, 1);
				return;
			}

		}
		first = 1;
		row++;
	}

	fclose(file);
}

int IsJobExist(char jobName[])
{
	FILE* file = fopen(JOBS_FILE, "r");
	char line[1024];
	int first = 0;

	while (fgets(line, 1024, file))
	{
		if (first) // first line is columns headers
		{
			char* job = SearchJob(line, jobName);

			if (job) // job exist 
				return 1;
		}
		first = 1;
	}

	fclose(file);
	return 0;
}

int IsCandidateExist(char candidateID[])
{
	FILE* file = fopen(CANDIDATES_FILE, "r");
	char line[1024];
	int first = 0;

	while (fgets(line, 1024, file))
	{
		if (first) // first line is columns headers
		{
			char* candidate = SearchCandidate(candidateID);

			if (candidate) // candidate exist 
				return 1;
		}
		first = 1;
	}

	fclose(file);
	return 0;
}

void MainMenu(User* _currentUser)
{
	int c;
	printf("Welcome to F.Jobs :)\n");

	do
	{
		//clr();
		printf("Main menu:\nChoose one of the following options:\n1 - if you are a candidate\n2 - if you are an employer\n3 - Display user manual\n4 - Exit\n");
		scanf_s("%d", &c);

		switch (c)
		{
		case 1:
			PrintCandidateMenu(&_currentUser);
			break;

		case 2:
			PrintEmployerMenu(&_currentUser);
			break;

		case 3:
			DisplayUserManual();
			break;

		case 4:
			printf("Have a nice day! :)\n");
			break;

		default:
			printf("Wrong number. Enter again\n");
			scanf_s("%d", &c);
			break;
		}

	} while (c != 4);

}

void PrintCandidateMenu(User* _currentUser)
{
	FILE* wor;
	worker W;
	int c;
	do
	{
		//clr();
		printf("Candidate menu:\nChoose one of the following options:\n1 - Create an account\n2 - Login\n3 - Back to main menu\n");
		scanf_s("%d", &c);

		switch (c)
		{
		case 1:
			wor = fopen(CANDIDATES_FILE, "a");
			W = set_new_worker();
			fprintf(wor, "\n%s,%d,%s,%s,%s,%s,%s,%d.%d.%d", W.id, W.password, W.fname, W.lname, W.city, W.phone, W.email, W.birth.day, W.birth.month, W.birth.year);
			fclose(wor);
			printf("The registration was successful!\n");
			_currentUser->ID = (char*)malloc(strlen(W.id) + 1);
			strcpy(_currentUser->ID, W.id);
			strcpy(_currentUser->type, "Worker");
			PrintCandidateMenuOptions(&_currentUser);
			break;

		case 2:
			if (Login(&_currentUser, 2))
				PrintCandidateMenuOptions(&_currentUser);
			break;

		case 3:
			break;

		default:
			printf("Wrong number. Enter again\n");
			scanf_s("%d", &c);
			break;
		}
	} while (c != 3);
}

void PrintCandidateMenuOptions(User* _currentUser)
{
	int c;
	do
	{
		//clr();
		printf("\nChoose one of the following options:\n1 - Edit profile\n2 - Search job\n3 - Resume submission\n4 - Submission history\n5 - Salary data\n6 - Tips\n7 - Exit\n");
		scanf_s("%d", &c);

		switch (c)
		{
		case 1:
			getchar();
			Editing_details(*_currentUser);
			break;

		case 2:
			getchar();
			SearchJobsByFilters();
			break;

		case 3:
			getchar();
			ResumePublish();
			break;

		case 4:
			getchar();
			WatchResume();
			break;

		case 5:
			getchar();
			PrintSalaryData();
			break;

		case 6:
			getchar();
			InterviewTips();
			break;

		case 7:
			break;

		default:
			printf("Wrong number. Enter again\n");
			scanf_s("%d", &c);
			break;
		}
	} while (c != 7);
}

void PrintEmployerMenu(User* _currentUser)
{
	FILE* emp;
	employer E;
	int c;
	do
	{
		//clr();
		printf("Employer menu:\nChoose one of the following options:\n1 - Create an account\n2 - Login\n3 - Back to main menu\n");
		scanf_s("%d", &c);

		switch (c)
		{
		case 1:
			emp = fopen(EMPLOYERS_FILE, "a");
			E = set_new_employer();
			fprintf(emp, "\n%s,%d,%s,%s,%s", E.Number_deals, E.password, E.name, E.city, E.phone);
			fclose(emp);
			printf("The registration was successful!\n");
			_currentUser->ID = (char*)malloc(strlen(E.Number_deals) + 1);
			strcpy(_currentUser->ID, E.Number_deals);
			strcpy(_currentUser->type, "Employer");
			PrintEmployerMenuOptions(&_currentUser);
			break;

		case 2:
			if (Login(&_currentUser, 1))
				PrintEmployerMenuOptions(&_currentUser);
			break;

		case 3:
			break;

		default:
			printf("Wrong number. Enter again\n");
			scanf_s("%d", &c);
			break;
		}
	} while (c != 3);
}

void PrintEmployerMenuOptions(User* _currentUser)
{
	int c;
	do
	{
		//clr();
		printf("\nChoose one of the following options:\n1 - Edit profile\n2 - Publish new job\n3 - Update job\n4 - View all published jobs\n5 - search job\n6 - View job submissions\n7 - Filter candidates\n8 - Exit\n");
		scanf_s("%d", &c);

		switch (c)
		{
		case 1:
			getchar();
			Editing_details(*_currentUser);
			break;

		case 2:
			getchar();
			publishJob();
			break;

		case 3:
			getchar();
			upadteJob();
			break;

			//case 4:
			//	//remove job
			//	break;

		case 4:
			getchar();
			all_jobs(_currentUser->ID, "", 1);
			break;

		case 5:
			getchar();
			lookfor_jobs(_currentUser->ID);
			break;

		case 6:
			getchar();
			PrintSubmissions();
			break;

		case 7:
			getchar();
			FilterCandidates();
			break;

		case 8:
			break;

		default:
			printf("Wrong number. Enter again\n");
			scanf_s("%d", &c);
			break;
		}
	} while (c != 8);
}

void DisplayUserManual()
{
	//clr();
	printf("-----User manual-----\n");
	printf("Candidate options:\n");
	printf("To create an account press 1->1\n");
	printf("To login press 1->2\n");
	printf("After logging in:\n");
	printf("To edit youe profile press 1\n");
	printf("To look for job press 2\n");
	printf("To send a resume to job press 3\n");
	printf("To view all your resume submmision press 4\n");
	printf("To view salary data press 5\n");
	printf("To view tips for interview press 6\n");
	printf("To back to the main menu press 7\n");

	printf("\nEmployer options:\n");
	printf("To create an account press 1->1\n");
	printf("To login press 1->2\n");
	printf("After logging in:\n");
	printf("To edit youe profile press 1\n");
	printf("To publish new job press 2\n");
	printf("To update published job press 3\n");
	printf("To view all the jobs you have published press 4\n");
	printf("To search job press 5\n");
	printf("To view all submissions for job press 6\n");
	printf("To remove candidates submmisions press 7\n");
	printf("To back to the main menu press 8\n");

	printf("\nPress any key to exit\n");
	getchar();
	getchar();
}

void PrintSalaryData()
{
	//clr();
	printf("Salary data:\n");
	printf(".....\n");

	printf("\nPress any key to exit\n");
	getchar();
	getchar();
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
	scanf_s("%d", &tbirth.day);
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
	FILE* wor, * emp;
	wor = fopen(CANDIDATES_FILE, "a");
	emp = fopen(EMPLOYERS_FILE, "a");
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
		fprintf(wor, "\n%s,%d,%s,%s,%s,%s,%s,%d.%d.%d", W.id, W.password, W.fname, W.lname, W.city, W.phone, W.email, W.birth.day, W.birth.month, W.birth.year);
		fclose(wor);
		printf("The registration was successful!");
		break;
	default:
		break;
	}
}

int Login(User* U, int user)
{
	FILE* wor, * emp;
	char tid[10];
	char tpassword[6];
	int c = user;
	/*printf("1 - Login as an employer \n2 - Login as an worker\n");
	scanf_s("%d", &c);*/
	printf("Enter id :\n");
	gets(tid);
	gets(tid);
	while (strlen(tid) != 9)
	{
		printf("Error ID please try again\n");
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
		emp = fopen(EMPLOYERS_FILE, "r");
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
		wor = fopen(CANDIDATES_FILE, "r");
		while (fgets(line, 1024, wor))
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

void Editing_details(User U)
{
	char line[1024];
	int first = 0;
	int row = 0;
	int c;
	char newVal[20];
	FILE* emp = fopen(EMPLOYERS_FILE, "r");
	FILE* wor = fopen(CANDIDATES_FILE, "r");
	if (strcmp(U.type, "Employer") == 0)
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
						edit_file(EMPLOYERS_FILE, newVal, row, 5);

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
						edit_file(EMPLOYERS_FILE, newVal, row, 4);

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
						edit_file(CANDIDATES_FILE, newVal, row, 5);

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
						edit_file(CANDIDATES_FILE, newVal, row, 4);

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
						edit_file(CANDIDATES_FILE, newVal, row, 7);

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

int SearchJobsByFilters()
{
	FILE* file;
	file = fopen(JOBS_FILE, "r");
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
	file = fopen(JOBS_AND_CANDIDATES_FILE, "a");
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
	file = fopen(JOBS_AND_CANDIDATES_FILE, "r");
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

void InterviewTips()
{

	printf("Here some tops to help you pass your job interview : \n");
	printf("1 - dress respectfully to leave a good impression\n ");
	printf("2 - prepare and practice your professional experience so as notr to encounter question you will not know how to answer\n ");
	printf("3 - Listen carfully yo the interviewer's questions and answer themm fluently\n");
	printf("4 - Maintain energies and a positive attitude!\n");
	printf("GOOD LUCK!\n");
}

void clr()
{
	system("pwd&&clear||cls");
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

char* stmm(const char* src)
{
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

void edit_file(char* FName, char* NewValue, int row, int col)
{
	int i, r = 0, c, j = 1;
	char line[1024];
	FILE* fr, * fw;
	fr = fopen(FName, "r");
	fw = fopen(FName, "r+");
	if (fr == NULL || fw == NULL) _ERR("f");
	while (fgets(line, 1024, fr))
	{
		char* tmp = stmm(line);
		if (tmp == NULL) _ERR("m");
		for (i = 0, c = 1; i < strlen(tmp); i++) {
			if (tmp[i] == 44) c++;
		}
		for (i = 0; i < c; i++) {
			if (r == row && i + 1 == col) {
				fprintf(fw, "%s", NewValue);
			}
			else {
				free(tmp);
				tmp = stmm(line);
				if (tmp == NULL) _ERR("m");
				fprintf(fw, "%s", getfield(tmp, i + 1));
			}
			(i < c - 1) ? fprintf(fw, ",") : fprintf(fw, "\n");
		}
		free(tmp);
		r++;
	}
	fclose(fr);
	fclose(fw);
}

void all_jobs(char* id, char* filter, int num)
{
	char line[1024];

	FILE* j_data = fopen(JOBS_FILE, "r");
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

void lookfor_jobs(char* id)
{
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
	if (select == 1) filter[0] = NULL;
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
			}
			else {
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
		}
		else {
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
				if (filter[i] < 48 || filter[i]>57) help = 1;
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

job publishJob()
{
	char pcode[6];
	char pname[20];
	char pcat[40];
	char ptposition[15];
	char ploc[20];
	char pdisc[140];
	job worke;
	int select;
	int time;
	int sel2;
	float salary;
	printf("Enter code  :\n");
	gets(pcode);
	while (strlen(pcode) != 5)
	{
		printf("Erorr code,it must be 5 carcters, please try again\n");
		gets(pcode);
	}
	worke.code = (char*)malloc(strlen(pcode) + 1);
	strcpy(worke.code, pcode);
	printf("choose from the list the job category by entering the number of the option :\n");
	printf("1-health professions \n 2-engineering\n 3-accounting and business\n 4-mechanics and repairs\n5driver\n6-tchnology");
	scanf("%d", &select);
	getchar();
	while (select > 6 || select < 1)
	{
		printf("Erorr you must choose number from 1 to 6\n");
		scanf("%d", &select);
		getchar();

	}
	switch (select)
	{
	case1:
		worke.category = "health professions";
		break;
	case2:
		worke.category = "engineering";
		break;
	case3:
		worke.category = "accounting and business";
		break;
	case4:
		worke.category = "mechanics and repairs";
		break;
	case5:
		worke.category = "driver";
		break;
	case6:
		worke.category = "technology";
		break;
	default:
		break;

	}

	printf("Enter job name :\n");
	getchar();
	gets(pname);
	worke.name = (char*)malloc(strlen(pname) + 1);
	strcpy(worke.name, pname);
	int flag = 0;
	printf("Enter job location (city) :\n");
	gets(ploc);
	while (flag)
	{
		flag = 0;
		for (int i = 0; i < strlen(ploc); i++)
		{
			if (ploc[i] > 'a' && ploc[i] < 'z' || ploc[i]>'A' && ploc[i] < 'Z')
			{

				printf(" \n");
			}
			else
			{
				printf("error, enter again city by using just capital letter or just small letters, \n");
				gets(ploc);
				flag = 1;
			}
		}
	}
	worke.location = (char*)malloc(strlen(ploc) + 1);
	strcpy(worke.location, ploc);
	printf("enetr 1 if it is full time position\n enter 2 for half position");
	scanf("%d", &sel2);
	while (sel2 > 2 || sel2 < 1)
	{
		printf("Erorr you must choose number1 or 2\n");
		scanf("%d", &sel2);

	}
	switch (sel2)
	{
	case 1:
		worke.tposition = "full";
		break;
	case 2:
		worke.tposition = "half";
		break;
	default:
		break;
	}

	printf("enetr salary per hour");
	scanf("%f", &salary);
	worke.salar = salary;
	printf("enetr hours work");
	scanf("%d", &time);
	worke.workhours = time;
	printf("Enter work description  :\n");
	gets(pdisc);
	worke.description = (char*)malloc(strlen(pdisc) + 1);
	strcpy(worke.description, pdisc);

}

job addJob()
{
	FILE* data;
	data = fopen(JOBS_FILE, "r");
	job work;
	work = publishJob();
	fprintf(data, "\n %s,%s,%s,%d,%s,%f,%d,%s", work.code, work.name, work.category, work.workhours, work.tposition, work.salar, work.location, work.description);
	fclose(data);
	printf("the added to the list sucssefuly");
}

job upadteJob()
{
	char line[1024];
	int first = 0;
	int row = 0;
	FILE* alljobs = fopen(JOBS_FILE, "r");
	int newval;
	float newsal;
	int select;
	char pdisc[140];
	int pflag = 1;
	char ploc[20];
	int help = 1;
	printf("enetr the code of the job what you want to change ");
	char pcode[6];
	gets(pcode);
	int flag = 0;
	while (strlen(pcode) != 5)
	{
		printf("Erorr code,it must be 10 carcters, please try again\n");
		gets(pcode);
	}
	while (help == 0)
	{
		while (fgets(line, 1024, alljobs))
		{
			if (first)
			{
				char* code = strtok(line, ",");
				if (strcmp(pcode, code) == 0)
				{
					help = 1;
				}

			}
			first = 1;
			row++;
		}
		if (help == 0)
		{
			printf("sorry you enter wrong job code,please enter correct value ");
			gets(pcode);
		}
	}

	printf("choose the fields that you want to change by choosing the currect number\n");
	printf("-1-change hours\n-2-change time-position\n-3-change salary\n-4-chnage location\n-5-change descriptions\n-6-end");
	scanf("%d", &select);
	while (select > 5 || select < 1)
	{
		printf("Erorr you must enter a number 1-6\n");
		scanf("%d", &select);
	}
	while (pflag)
	{


		switch (select)
		{
		case 1:
			printf("you chose to change woking hours!! \n so please enter the new working hours\n");
			scanf("%d", &newval);
			while (fgets(line, 1024, alljobs))
			{
				if (first)
				{
					char* code = strtok(line, ",");
					if (strcmp(pcode, code) == 0)
					{
						edit_filedigits(alljobs, newval, row, 4);
					}

				}
				first = 1;
				row++;
			}

			break;
		case 2:
			printf("you chose to change time position!! \n so please enter 1 fo full position and 2 to half position\n");
			scanf("%d", &newval);
			while (newval > 2 || newval < 1)
			{
				printf("Erorr you must choose number1 or 2\n");
				scanf("%d", &newval);

			}
			switch (newval)
			{
			case 1:
				while (fgets(line, 1024, alljobs))
				{
					if (first)
					{
						char* code = strtok(line, ",");
						if (strcmp(pcode, code) == 0)
						{
							edit_file(alljobs, "fulltime", row, 5);
						}

					}
					first = 1;
					row++;
				}
				break;
			case 2:
				while (fgets(line, 1024, alljobs))
				{
					if (first)
					{
						char* code = strtok(line, ",");
						if (strcmp(pcode, code) == 0)
						{
							edit_file(alljobs, "half", row, 5);
						}

					}
					first = 1;
					row++;
				}
				break;
			default:
				break;
			}

			break;
		case 3:
			printf("you chose to change salary!! \n so please enter the new salary\n");
			scanf("%f", &newsal);
			while (fgets(line, 1024, alljobs))
			{
				if (first)
				{
					char* code = strtok(line, ",");
					if (strcmp(pcode, code) == 0)
					{
						edit_filedigits(alljobs, newsal, row, 6);
					}

				}
				first = 1;
				row++;
			}
			break;
		case 4:
			printf("you chose to change the location!! \n so please enter the new location\n");
			gets(ploc);
			while (flag)
			{
				flag = 0;

				for (int i = 0; i < strlen(ploc); i++)
				{
					if (ploc[i] > 'a' && ploc[i] < 'z' || ploc[i]>'A' && ploc[i] < 'Z')
					{

						printf(" \n");
					}
					else
					{
						printf("error, enter again city by using just capital letter or just small letters, \n");
						flag = 1;
						gets(ploc);

					}
				}
			}
			while (fgets(line, 1024, alljobs))
			{
				if (first)
				{
					char* code = strtok(line, ",");
					if (strcmp(pcode, code) == 0)
					{
						edit_file(alljobs, ploc, row, 7);
					}

				}
				first = 1;
				row++;
			}
			break;
		case 5:
			printf("you chose to update the job description!! \n so please enter the new describtions\n");
			gets(pdisc);
			while (fgets(line, 1024, alljobs))
			{
				if (first)
				{
					char* code = strtok(line, ",");
					if (strcmp(pcode, code) == 0)
					{
						edit_file(alljobs, pdisc, row, 8);
					}

				}
				first = 1;
				row++;
			}
			break;
		case 6:
			printf("end!!\n");
			pflag = 0;
			break;



		default:
			break;
		}
	}
}

void edit_filedigits(char* FName, int NewValue, int row, int col)
{
	int i, r = 0, c, j = 1;
	char line[1024];
	FILE* fr, * fw;
	fr = fopen(FName, "r");
	fw = fopen(FName, "r+");
	if (fr == NULL || fw == NULL) _ERR("f");
	while (fgets(line, 1024, fr))
	{
		char* tmp = stmm(line);
		if (tmp == NULL) _ERR("m");
		for (i = 0, c = 1; i < strlen(tmp); i++) {
			if (tmp[i] == 44) c++;
		}
		for (i = 0; i < c; i++) {
			if (r == row && i + 1 == col) {
				fprintf(fw, "%d", NewValue);
			}
			else {
				free(tmp);
				tmp = stmm(line);
				if (tmp == NULL) _ERR("m");
				fprintf(fw, "%d", getfield(tmp, i + 1));
			}
			(i < c - 1) ? fprintf(fw, ",") : fprintf(fw, "\n");
		}
		free(tmp);
		r++;
	}
	fclose(fr);
	fclose(fw);
}