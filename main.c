#include "src/pshell.c"


int main(){
    // display the welcome message
    pshell();

    while(true){
        
        /* ---- DO NOT MODIFY THIS SECTION ----*/
        printf("pShell$ ");
        fflush(stdout);
        
        /* ---- PROTECTED SECTION END ----*/

        // read input cmd
        fgets(line, MAX_CMD_SIZE, stdin);

        // parse the input
        parse(line);
        
        if (id == 0){
        	/* ---- DO NOT MODIFY THIS SECTION ----*/
			
		bool success;

		if(!parallel){

			success = sequentialExecution(count, cmd_tokens_t);
		}

		else{

			success = parallelExecution(count, cmd_tokens_t);
		}

		if(!success){
			    
			fprintf(stderr, "Invalid command\n");
		}
			
		/* ---- PROTECTED SECTION END ----*/
        }
         
    }
    return 0;
}

