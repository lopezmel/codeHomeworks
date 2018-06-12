#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;

//vector<char> items; 
//vecotr<char *> arguments;

//getting arguments 
void arg_input (char *line, char **args, int arg_num)
{

	int num;

	//making a copy of input with a new line and null character
	//p = pointer 
	char *p = strchr(line, '\n');
	*p = '\0';

	//parse input from user and put into arguament array
	p = strtok (line, " ");
	for(num = 0; num <arg_num; num++)
	{
		args[num] = strdup(p);
		p = strtok(NULL, " ");
	}

	args[num] = NULL;
}

//getting number of arguments 
int arg_num(char *line)
{
	int argn = 0;

	//making a copy of input and replacing with newline and null char	
	//c = copy
	//p = pointer 
	char *c = strdup(line);	
	char *p = strchr(c, '\n');
	p = '\0';

	//counting number of spaces 
	p = strtok(c, " ");
	while(p != NULL)
	{
		argn++;
		p = strtok(NULL, " ");
		
	}

	free(c);
	return argn;
}


int main(int argc, char** argv)
{
	int status;
	int nArgs;
	char line[256];
	char **args;
	char * input;

	while(1){

		//checking cmd line arguments 
		
		//if cmd line argument found will use user "prompt"
		if(argc == 2){
		
			printf("%s> ",argv[1]);

		//if no cmd line argument found will use my_shell>
		}else{
			printf("my_shell> ");
		}
	
		//checking command line argments 
		if(!fgets(line, 256, stdin)){
			fprintf(stderr, "Invalid input!\n");
	
		}

		//exit statement  
        	   if (strcmp(line, "exit\n") == 0)
            	{
                	fflush(stdout);
                	exit(0);
			perror("Could not exit!\n");
            	}



	//using helper functions to fill NULL terminated arg list
	nArgs = arg_num(line);
	
	args = (char **) malloc(sizeof(char *) * nArgs+1);
	
	arg_input(line, args, nArgs);


	FILE *fd, *fd2;
	char *file;


		switch(fork()){

		//fork error
		case -1:
			perror("Fork() not working\n"); 
			exit (1);

		//child
		//file redirection <, >, >>, 2>
		case 0:
			printf("child: executing %s\n", args[0]);

			int i;	
	
			//cheking each cmd line argment 
			for(i=0; i <nArgs; i++){
		

			//redirecint file to stdout 
			if(strcmp(">", args[i]) == 0) { 
    				//printf("test 1");	

				//error checking for fopen			
    				fd = fopen(args[i+1], "w");
				if (fd == NULL) 
				{
					perror("Error file does not exit");
				}
	
				//printf("test 2");
				nArgs-=2;
				args[i] = NULL; //not including first argument 
				args[i+1] = NULL; //not including the seccond argumnet 
    			
				//duplicate stdout onto the file opened
				if (dup2(fileno(fd), fileno(stdout)) < 0)
				{
					perror("Error dup2 not working");

				}
		
				close(fileno(fd));
				//printf("test 3");
				//exit(0);		
				
			}

			//redirecting file to stdin 
			else if(strcmp("<", args[i]) == 0) { 
    				//printf("test 1");	
    				fd = fopen(args[i+1], "r");
				
				//error checking for fopen			
				if (fd == NULL) 
				{
					perror("Error file does not exit");
				}
		
			//	numArgs-=2;
			//	args[i] = NULL; //first argument 
			//	args[i+1] = NULL; //seccond argumnet 
    			
				//duplicate stdin onto the file read
				if (dup2(fileno(fd), fileno(stdin)) < 0)
				{
					perror("Error dup2 not working");
				}


				close(fileno(fd));
	
				//printf("test 3");
		

			}

			//appending to stdout 
			else if(strcmp(">>", args[i]) == 0) { 
    				//printf("test 1");	
    				fd = fopen(args[i+1], "a");
				
				//error checking for fopen			
				if (fd == NULL) 
				{
					perror("Error file does not exit");
				}
	
				nArgs-=2; 
				args[i] = NULL; //not including first argument 
				args[i+1] = NULL; //not including seccond argumnet 
    			
				//duplicate stdout onto the file opened
				if(dup2(fileno(fd), fileno(stdout)) < 0)
				{

					perror("Error dup2 not working");
				}

			
			
				close(fileno(fd));	
				//printf("test 3");
		

			} 
		
			//redirecting stderr to file 
			else if(strcmp("2>", args[i]) == 0) { 
    			
    				fd = fopen(args[i+1], "r+");
	
				//error checking for fopen			
				if (fd == NULL) 
				{
					perror("Error file does not exit");
				}
	
				//printf("test 2");
				nArgs-=2;
				args[i] = NULL; //not including first argument 
				args[i+1] = NULL; //not including seccond argumnet 
    			
				//duplicate stderr to file  
				if (dup2(fileno(fd), fileno(stderr)) < 0)
				{

					perror("Error dup2 not working");

				}

				perror("stderr: ");		
				close(fileno(fd));
		
				//exit(0);		

			}
	
			//cheking fo muliple file redirections 
			else if((strcmp("<", args[i])==0) && (strcmp(">", args[i+1])== 0)) { 

				//left side
    				fd = fopen(args[i+1], "r");
				//rigt side 
    				fd2 = fopen(args[i+2], "W+");
	
				//error checking for fopen			
				if (fd == NULL) 
				{
					perror("Error file does not exit");
				}
				if (fd2 == NULL) 
				{
					perror("Error file does not exit");
				}
	
				nArgs-=3;
				args[i] = NULL; //not including first argument 
				args[i+1] = NULL; //not including seccond argumnet 
    			
				//duplicate stdin onto the file opened
				if (dup2(fileno(fd), fileno(stdin)) < 0)
				{
					perror("Error dup2 not working");
				}

				if (dup2(fileno(fd2), fileno(stdout)) < 0)
				{
					perror("Error dup2 not working");
				}
		
				close(fileno(fd));
				close(fileno(fd2));

				//exit(0);		

			}
	
			}//forloop		
		
			execvp(args[0], args);
			perror("exec() not working");
			exit(1);
		

		//parent 
		default:
			wait(&status);
			printf("Parent done waiting\n");		


		}//Switch: fork

	}//while 


		
return 0;




	
}//main 
