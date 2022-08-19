
// imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

#define MAX_CMD_SIZE 4096 // DO NOT MODIFY
#define MAX_NB_EXEC 15 // DO NOT MODIFY

// define global variables
extern char line[MAX_CMD_SIZE];
extern char** cmd_tokens;
extern char** cmd_tokens_t;
extern bool parallel;
extern int count;
extern int id;

// DO NOT MODIFY THE PROTOTYPES BELOW - SEE pshell.c FILE FOR FULL SPECIFICATION
bool sequentialExecution(int count, char** cmd_tokens);
bool parallelExecution(int count, char** cmd_tokens);

// ADDITIONAL FUNCTIONS
/*
	help()   			-> display the help for pshell
	pshell() 			-> display a welcome message
	executeCmd(int id)		-> execute the build in cmd
	isBuildInCmd(char* token)	-> set an id to the build in cmd
	parse(char cmd[]) 		-> tokenize the input and set the value of count, parallel and cmd_tokens
	setCount(char* token)		-> take the token related to the count value and convert it into int
	setExecutionType(char* token)	-> take the token related to the special char and set the parallel value
	
*/

void help();
void pshell();
void executeCmd(int id);
void isBuildInCmd(char* token);
void parse(char cmd[]);
int setCount(char* token);
bool setExecutionType(char* token);


