//		commands.c
//********************************************
#include "commands.h"

//********************************************
// function name: printhistory
// Description: prints stl contianer queue made from strings
// Parameters: the container

//**************************************************************************************
void printhistory (std::queue <std::string> hy)
{
	while (!hy.empty())
	{
		std::cout << hy.front() << std::endl;
		hy.pop();
	}
}


//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure

//**************************************************************************************
int ExeCmd(void* jobs, char* lineSize, char* cmdString, std::queue <std::string> &histo)
{
	char* cmd; 
	char* args[MAX_ARG];
	char pwd[MAX_LINE_SIZE];
	char* delimiters = " \t\n";  
	int i = 0, num_arg = 0;
	bool illegal_cmd = false; // illegal command
	
    	cmd = strtok(lineSize, delimiters);
	if (cmd == NULL)
		return 0; 
   	args[0] = cmd;
	for (i=1; i<MAX_ARG; i++)
	{
		args[i] = strtok(NULL, delimiters); 
		if (args[i] != NULL) 
			num_arg++; 
 
	}
/*************************************************/
// Built in Commands PLEASE NOTE NOT ALL REQUIRED
// ARE IN THIS CHAIN OF IF COMMANDS. PLEASE ADD
// MORE IF STATEMENTS AS REQUIRED
/*************************************************/
	if (!strcmp(cmd, "cd") ) 
	{

		if (num_arg == 1)
		{
			// if (prev_pwd.empty() == true)
			// {
			// 	//First time changing directory --> CHANGE DIR
				
			// }
			//std::cout << prev_pwd << std::endl;


		}
		else 
		{
			illegal_cmd = true;
		}
	} 
	
	/*************************************************/

	/*************************************************/
	if (!strcmp(cmd, "diff") ) 
	{

		if (num_arg == 2)
		{
			FILE *f1 = fopen(args[1], "r");
			if (!f1) {  perror(args[1]); exit(EXIT_FAILURE);  };
			FILE *f2 = fopen(args[2], "r");
			if (!f2) {  perror(args[2]); exit(EXIT_FAILURE);  };
			bool samefile = true;
			int c1, c2;
			while (samefile && ((c1 = getc(f1)) != EOF) || ((c2 = getc(f2)) != EOF))
			{
			if (c1 != c2) samefile = false;
			}
			fclose (f1), fclose (f2);
			
			if (samefile)
				std::cout << "0" << std::endl; // if files are the same print 0
			else
				std::cout << "1" << std::endl;//bad - the files are different

			
		}
		else 
		{
			illegal_cmd = true;
		}
	} 
	
	/*************************************************/
	// else if (!strcmp(cmd, "pwd")) 
	if (!strcmp(cmd, "pwd"))
	{
		if ( num_arg== 0 )
		{
			char tmp [MAX_LINE_SIZE];
			getcwd(tmp,MAX_LINE_SIZE);
			if (tmp == NULL)
				printf("perror/n"); // @TODO PERROR
			else
			{
				std::cout << tmp << std::endl;
			}			
		}

		else
		{
			illegal_cmd = true;
		}
	}
	
	// /*************************************************/
	// else if (!strcmp(cmd, "mkdir"))
	// {
 		
	// }
	// /*************************************************/
	// /*************************************************/
	else if (!strcmp(cmd, "history"))
	{
 		if (num_arg == 0)
		{
			printhistory(histo);
		}
		else 
		{
			illegal_cmd = true;
		}
	}
	/*************************************************/
	
	// else if (!strcmp(cmd, "jobs")) 
	// {
 		
	// }
	// /*************************************************/
	else if (!strcmp(cmd, "showpid")) 
	{
		if (num_arg == 0)
		{
			int pid =  getpid();
			std::cout << "smash pid is " << pid <<  std::endl ;
		}
		else 
		{
			illegal_cmd = true;
		}
	}
	// /*************************************************/
	// else if (!strcmp(cmd, "fg")) 
	// {
		
	// } 
	// /*************************************************/
	// else if (!strcmp(cmd, "bg")) 
	// {
  		
	// }
	// /*************************************************/
	else if (!strcmp(cmd, "quit"))
	{
   		int res = kill((int)getpid(), SIGKILL);

		// /* cases when error  */
		// switch (res)
		// {
		// case EINVAL:
		// 	/* code */
		// 	break;
		
		// default:
		// 	break;
		// }
	} 
	// /*************************************************/
	else // external command
	{
 		ExeExternal(args, cmdString);
	 	return 0;
	}
	if (illegal_cmd == true)
	{
		std::cout << "smash error: > \"" << cmdString << "\"" <<  std::endl ;
		return 1;
	}
    return 0;
}
//**************************************************************************************
// function name: ExeExternal
// Description: executes external command
// Parameters: external command arguments, external command string
// Returns: void
//**************************************************************************************
void ExeExternal(char *args[MAX_ARG], char* cmdString)
{
	int pID;
    	switch(pID = fork()) 
	{
    		case -1: 
					// Add your code here (error)
					
					/* 
					your code
					*/
        	case 0 :
                	// Child Process
               		setpgrp();
					
			        // Add your code here (execute an external command)
					
					/* 
					your code
					*/
			
			default:
                	// Add your code here
					std::cout << "got to exee xternal " <<  std::endl ;
					/* 
					your code
					*/
	}
}
//**************************************************************************************
// function name: ExeComp
// Description: executes complicated command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(char* lineSize)
{
	char ExtCmd[MAX_LINE_SIZE+2];
	char *args[MAX_ARG];
    if ((strstr(lineSize, "|")) || (strstr(lineSize, "<")) || (strstr(lineSize, ">")) || (strstr(lineSize, "*")) || (strstr(lineSize, "?")) || (strstr(lineSize, ">>")) || (strstr(lineSize, "|&")))
    {
		// Add your code here (execute a complicated command)
				
		/* 
		your code
		*/
	} 
	return -1;
}
//**************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char* lineSize, void* jobs)
{

	char* Command;
	char* delimiters = " \t\n";
	char *args[MAX_ARG];
	if (lineSize[strlen(lineSize)-2] == '&')
	{
		lineSize[strlen(lineSize)-2] = '\0';
		// Add your code here (execute a in the background)
					
		/* 
		your code
		*/
		
	}
	return -1;
}

