#include "pshell.h"

char line[MAX_CMD_SIZE];
char** cmd_tokens = NULL;
char** cmd_tokens_t = NULL;
bool parallel = true;
int count = 1;
int id = 0;

void help(){
	printf("%s", "\n>>> Pshell is a designed shell to run several commands at once\n");
	printf("%s", ">>> command syntax:\n");
	printf("%s", ">>> pShell$ <name> <arg1> . . . <argN> <typeSymbol> <count>\n");
	printf("%s", "***********************\n");
	printf("%s", "<typeSymbol> is either & or %\n");
	printf("%s", ">>> & indicates parallel execution\n");
	printf("%s", ">>> % indicates sequential execution\n");
	printf("%s", "***********************\n");
	printf("%s", ">>> <count> is an integer indicating the number of executions [1 - 15]\n");
	printf("%s", "***********************\n");
	printf("%s", ">>> All shell commands are supported\n");
	printf("%s", ">>> Pipe is not supported and complex commands\n");
}

void pshell(){
    	clear(); // clean the terminal befor starting
    	printf("**********************************************************************************************\n");
	printf("	**********    **********  **      **  **********  **          **        \n");
	printf("	**        *  *            **      **  **          **          **        \n");
	printf("	**        *  *            **      **  **          **          **        \n");
	printf("	**********    **********  **********  *******     **          **        \n");
	printf("	**                      * **      **  **          **          **        \n");
	printf("	**                      * **      **  **          **          **        \n");
	printf("	**            **********  **      **  **********  **********  **********\n");
	printf("********************************************************************************************\n\n");
	help();
}

void executeCmd(int id_value){
    
    char buf[256];
    switch(id_value){
        case 1:
            exit(0);
        case 2:
            // cmd_tokens is a global variable
            chdir(cmd_tokens[1]);
        case 3:
            getcwd(buf, 256);
            printf("%s\n", buf);
    }
}

void isBuildInCmd(char* token){
    int build_in_cmd_id = 0; // we make the assumption that we not are dealing with build in command
    if (strcmp(token, "exit") == 10 || strcmp(token, "exit") == 0){
        build_in_cmd_id = 1;
    }
    else if (strcmp(token, "cd") == 10 || strcmp(token, "cd") == 0){
        build_in_cmd_id = 2;
    }
    else if (strcmp(token, "pwd") == 10 || strcmp(token, "pwd") == 0){
        build_in_cmd_id = 2;
    }
    id = build_in_cmd_id;
}

bool setExecutionType(char* token){
    bool parallel = false;
    if (strcmp(token, "&") == 0) parallel = true;
    else parallel = false;
    return parallel;
}

int setCount(char* token){
    return atoi(token);
}



void display (char **array, size_t s){
	for (int j=0; j<s; j++)
		printf("[%d] --> %s\n", j, array[j]);
}

void formatArray(size_t s){
	cmd_tokens_t = malloc(sizeof(char*) * s);
    	for (int i=0; i<s; i++){
        	cmd_tokens_t[i] = malloc(sizeof(char) * 50);
    	}
    	for (int i=0; i<s-1; i++){
        	strcpy(cmd_tokens_t[i], cmd_tokens[i]);
    	}
    	cmd_tokens_t[s-1] = NULL;
}

void parse(char cmd[]){
    char* token = strtok(cmd, " ");
    // we dynamically allocate space for the input tokens
    // we make the assumption that our input contains 10 tokens or less
    cmd_tokens = malloc(sizeof(char*) * 10);
    for (int i=0; i<10; i++){
        // we make the assumption that each caracter contains 50 char or les
        cmd_tokens[i] = malloc(sizeof(char) * 50);
    }
    int j = 0;
    while (token != NULL){
        strcpy(cmd_tokens[j], token);
        token = strtok(NULL, " ");
        j++;
    }
    isBuildInCmd(cmd_tokens[0]);
    if (id == 1 || id == 2 || id == 3){
    	executeCmd(id);
    }
    else{
    	 if (j >= 3){
    	 	id = 0;
    	 	parallel = setExecutionType(cmd_tokens[j-2]);
    	 	count = setCount(cmd_tokens[j-1]);
   		if (count > 15 || count < 1){
    			printf("Invalid count");
    			id = -1;
    		}	
	    	formatArray(j-1);
    	 }
    	 else{
    	 	id = -1;
    	 	printf("Invalid syntax\nUse this syntax --> <name> <arg1> . . . <argN> <typeSymbol> <count>\n");
    	 }
    }
}

bool sequentialExecution(int count, char** cmd_tokens){	
	for(int i=0; i<count;i++){
        	if(fork() == 0){
        		if (i != 0)
            			sleep(i);
            		for (int a=count-(i+1); a>0; a--) wait(NULL);
            		if (execvp(cmd_tokens[0], cmd_tokens) < 0) {
				printf("execution failed");
			}
        	}
    	}
    	for(int i=0; i<count;i++) wait(NULL);
	return true;
}

bool parallelExecution(int count, char** cmd_tokens){
	bool res = true;
	for (int i=0; i<count; i++){
		pid_t pid;
		if ((pid = fork()) < 0){
			printf("forking child process failed\n");
			res = false;
		}
		else if (pid == 0){
			if (execvp(cmd_tokens[0], cmd_tokens) < 0) {
				printf("execution failed");
			}
		}
	}
	for(int j=0; j<count; j++) wait(NULL);
	return res;
}
