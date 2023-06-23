#include <stdio.h>
#include <string.h>
#include "utils.h"

// user functions
int  user_exists(FILE *, const char *);
int  user_authen(FILE *, const char *, const char *);
void get_creds(char *, char *);
void sign_in(FILE *);
void sign_up(FILE *);

// base functions
void print_menu();
int  get_choice(int, int);
int  main_loop(FILE *);

int main(void)
{
	FILE * ptr = fopen("archive.txt","a+");
	main_loop(ptr);
	fclose(ptr);
	return 0;
}

void sign_in(FILE * ptr)
{
	clrscr();
	char user[255], pass[255];
	get_creds(user, pass);

	if(user_authen(ptr, user, pass))
		printf("Hi %s\n", user);
	else
		printf("Incorrect credentials\n");
}

void sign_up(FILE * ptr)
{
	clrscr();
	char user[255], pass[255];
	get_creds(user, pass);
	printf("%s\t%s\n", user, pass);

	if(user_exists(ptr, user)) {
		printf("User exists, choose another username.\n");
	} else {
		fseek(ptr, 0L, SEEK_END);
		fprintf(ptr, "%s\t%s\n", user, pass);
		printf("Sign up successful.\n");
		rewind(ptr);
	}
}

int user_exists(FILE * ptr, const char * user)
{
	char line[1024], *state, *data;
	int ret = -1;
	while(!feof(ptr)) {
		getstr(line, 1024, ptr);
		data = strtok_r(line, "\t", &state);
		ret = strncmp(user, data, 1024);
		if(ret == 0) break;
	}
	rewind(ptr);
	return ret == 0;
}

int user_authen(FILE * ptr, const char * user, const char * pass)
{
	char line[1024], *state, *data;
	int ret1 = -1, ret2 = -1;
	while(!feof(ptr)) {
		getstr(line, 1024, ptr);
		data = strtok_r(line, "\t", &state);
		ret1 = strncmp(user, data, 255);
		if(ret1 == 0) {
			data = strtok_r(NULL, "\t", &state);
			ret2 = strncmp(pass, data, 255);
			if(ret2 == 0) break;
		}
	}
	rewind(ptr);
	return ret1 == 0 && ret2 == 0;
}

void print_menu()
{
	printf(
	    "1. SIGN UP\n"
	    "2. SIGN IN\n"
	    "3. EXIT\n"
	);
}

int main_loop(FILE * ptr)
{
	while (1) {
		print_menu();
		switch(get_choice(1, 3)) {
		case 1:
			sign_up(ptr);
			break;
		case 2:
			sign_in(ptr);
			break;
		case 3:
			return printf("EXITED!\n");
		}
	}
}

void get_creds(char * user, char * pass)
{
	printf("username> ");
	scanf("%s", user);
	printf("password> ");
	scanf("%s", pass);
}

int get_choice(int min, int max)
{
	int res = min - 1;
	while (res < min || res > max) {
		printf("\r%schoice: ", (min - 1 == res)?"":"Invalid input, ");
		scanf("%d",&res);
	}
}
