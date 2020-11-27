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
// function name: printlist
// Description: prints stl contianer list made from job class
// Parameters: the container
//**************************************************************************************
void printlist(std::list<job> &jobs)
{
    // for (auto &i: jobs) {
		time_t curr_time = time(0);
		for(std::list<job>::iterator it = jobs.begin(); it != jobs.end(); it++ ){
		time_t background_time = curr_time - it->create_time;
		if (it->stopped ==false)
        	std::cout << "[" << it->jobid << "] " <<  it->name << " : "  << it->pid << " " << background_time << " secs" << std::endl;
		else
		{
			std::cout << "[" << it->jobid << "] " <<  it->name << " : "  << it->pid << " " << background_time << " secs" << " (Stopped)" << std::endl;
		}
		
	}
}

//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************
int ExeCmd(char* lineSize, char* cmdString, data &dat)
{
	char* cmd; 
	char* args[MAX_ARG];
	char pwd[MAX_LINE_SIZE];
	std::string del = " \t\n"; 
	char* delimiters = &del[0]; 
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
	// if (!strcmp(cmd, "cd") ) 
	// {			
	// 	std::string path (cmdString+3);
	// 	std::string tmp;
	// 	getcwd(tmp,MAX_LINE_SIZE);

	// 	//if(args[1]=='-')
	// 	if(path == '-')
	// 	{
	// 		if (dat.prev_pwd.empty() == true)
	// 		{
	// 			std::cout << dat.prev_pwd << std::end;
	// 			chdir(dat.prev_pwd);
	// 			dat.prev_pwd = tmp;
	// 		}
	// 	}

	// 	if(chdir(path) == 0)
	// 	{
	// 		dat.prev_pwd = tmp;
	// 	}
	// 	else
	// 	{
	// 		std::cout << "smash error: > \"" << path << "\"- No such file or directory" << endl;
	// 	}
	// }	

/*************************/
if (!strcmp(cmd, "cd") ) 
	{
		std::string path (cmdString+3);
	
		char* curr;
		int flag=0;
		
		curr = new char [MAX_LINE_SIZE];
		getcwd(curr,MAX_LINE_SIZE);
		
		std::string curr_string (curr);

		if(path == "-")
		{
		
			std::cout << dat.prev_pwd << std::endl;			

			if (dat.prev_pwd.empty() == false)
			{
				std::cout << dat.prev_pwd << std::endl;			
				chdir(&dat.prev_pwd[0]);
				dat.prev_pwd = curr_string;
			}
		}
		else
		{
			flag = chdir(&path[0]);
			if(flag != 0)
			{
			 	std::cout << "smash error: > \"" << path << "\"- No such file or directory" << std::endl;
				return 1;
			}
			dat.prev_pwd = curr_string;
		}
		// return 0;
	}
	
	/*************************************************/

	/*************************************************/
	else if (!strcmp(cmd, "diff") )  //TODO diff exieted 
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
	else if (!strcmp(cmd, "pwd"))
	{
		if ( num_arg== 0 )
		{
			char tmp [MAX_LINE_SIZE];
			getcwd(tmp,MAX_LINE_SIZE);
			if (tmp == NULL)
				perror(NULL);
				exit(EXIT_FAILURE);
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
			printhistory(dat.history); // TODO only add history last?// and shoud "" be history?
			return 0;
		}
		else 
		{
			illegal_cmd = true;
		}
	}
	/*************************************************/
	
	else if (!strcmp(cmd, "jobs")) 
	{
 		if (num_arg == 0)
		{
			// job joe;
			// joe.jobid = 1;
			// joe.name = "a.out";
			// joe.pid = 1243;
			// joe.create_time = time(0);
			// // sleep(5);
			// dat.jobs.push_front(joe);
			printlist(dat.jobs);
		}
		else 
		{
			illegal_cmd = true;
		}
	}
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
 		ExeExternal(args, cmdString, dat);
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
void ExeExternal(char *args[MAX_ARG], char* cmdString, data &dat)
{
	int pID;
    switch(pID = fork()) 
	{
    		case -1: 
			{
				perror(NULL);
				exit(EXIT_FAILURE);
			}
        	case 0 :
                	// Child Process
					{
						setpgrp();
						if (execvp(args[0], args) == -1) 
						{	
							perror(NULL); 
							exit(-1);
						}

						break;
					}
			default:
					{
						 std::cout << "got to exee xternal " <<  std::endl ;
						dat.GPid = pID;
						waitpid(pID, NULL, WUNTRACED);
						dat.GPid = -1;
					}
	}
}
// //**************************************************************************************
// // function name: ExeComp
// // Description: executes complicated command
// // Parameters: command string
// // Returns: 0- if complicated -1- if not
// //**************************************************************************************
// int ExeComp(char* lineSize)
// {
// 	char ExtCmd[MAX_LINE_SIZE+2];
// 	char *args[MAX_ARG];
//     if ((strstr(lineSize, "|")) || (strstr(lineSize, "<")) || (strstr(lineSize, ">")) || (strstr(lineSize, "*")) || (strstr(lineSize, "?")) || (strstr(lineSize, ">>")) || (strstr(lineSize, "|&")))
//     {
// 		// Add your code here (execute a complicated command)
			
// 		/* 
// 		your code
// 		*/
// 	} 
// 	return -1;
// }
//**************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char* lineSize, data &dat)
{

	int pID, i;
	std::string del = " \t\n"; 
	char* delimiters = &del[0]; 
	char *args[MAX_ARG];
	if (lineSize[strlen(lineSize)-2] == '&')
	{
	lineSize[strlen(lineSize)-2] = '\0';
		args[0]= strtok(lineSize, delimiters);
		if (!args[0]){
			return 0;
		}
		for (i=1; i<MAX_ARG; i++)
		{
			args[i] = strtok(NULL, delimiters); 
		}
		std::string cmd(args[0]);
		std::cout << cmd << std::endl;
		switch(pID = fork()) 
		{
			case -1: 
				perror(NULL);												
				exit(-1);
			case 0 :
				// Child Process
				setpgrp();
				if (execvp(args[0], args) == -1) {
					perror(NULL);
					exit(-1);
				}
				exit(-1);
			default:
				job curr_job;
				curr_job.create_time = time(0);
				curr_job.pid = pID;
				curr_job.name = cmd;
				curr_job.stopped = false;
				curr_job.jobid = ++ dat.job_num ;
				dat.jobs.push_back(curr_job);

				return 0;
		}
	}
	return -1;
}
