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
		return 0;
	}
	
	/*************************************************/

	/*************************************************/
	else if (!strcmp(cmd, "diff") )  
	{

		if (num_arg == 2)
		{
			FILE *f1 = fopen(args[1], "r");
			if (!f1) {  perror(args[1]); return -1;  };
			FILE *f2 = fopen(args[2], "r");
			if (!f2) {  perror(args[2]); return -1;  };
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
			{
				perror(NULL);
				return -1;
			}
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
		else if (!strcmp(cmd, "history"))
	{
		FILE *src, *dst;
		char ch;

		if ( num_arg != 0 ) 
		{
			illegal_cmd = true;
		}

		/* openning source file */
		// rb mode in order to open non -text file 
		if((src = fopen(args[1], "rb"))==NULL) {
			perror("Cannot open src file");
			return -1;
		}

		/* opening destination file */
		// wb mode in order to open non -text file 
		if((dst = fopen(args[2], "wb"))==NULL) {
			perror("Cannot open dest file");
			return -1;
		}

		/* copy the file */
		while(!feof(src)) {
			ch = fgetc(src);
			if(ferror(src)) 
			{
			perror("error reading src file");
			return -1;
			}
			if(!feof(src)) fputc(ch, dst);
			if(ferror(dst)) 
			{
			perror("error reading dst file");
			return -1;
			}
		}

		if((fclose(src)==EOF) || (fclose(dst)==EOF)) 
		{
			perror("Cannot open src file");
			return -1;
		}
	}
	// /*************************************************/
	else if (!strcmp(cmd, "history"))
	{
 		if (num_arg == 0)
		{
			printhistory(dat.history); 
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
	else if (!strcmp(cmd, "fg")) 
	{
		if (num_arg == 1 || num_arg == 0)
		{
			std::list<job>::iterator tmp = dat.findjob(dat.jobs ,dat.job_num); // if num_arg == 0

			if(num_arg == 1)
			{
				std::list<job>::iterator tmp = dat.findjob(dat.jobs ,atoi(args[1]));
			}
			
			
			// if (num_arg == 0)
			// {
			// 	tmp = dat.findjob(dat.jobs ,dat.job_num);
			// }
			if(tmp == dat.jobs.end() || dat.job_num == 0) 
			{
				std::cout << "There isn't a process at the backgroung \ isnt such process" << std::endl;
				return -1;
			}
			if(tmp->stopped == true)
			{
				if(kill(tmp->pid,SIGCONT) == -1)
				{
					std::cout << "The process fails continue" << std::endl;
				}
				tmp->stopped = false;
			}

			dat.GPid = tmp->pid;
			waitpid(tmp->pid, NULL, WUNTRACED);
			dat.GPid = -1;
		}
		else
		{
			illegal_cmd = true;
		}
		
	} 
	// /*************************************************/
	// else if (!strcmp(cmd, "bg")) 
	// {
  		
	// }
	// /*************************************************/
	else if (!strcmp(cmd, "quit"))
	{
		if (!strcmp(args[1], "kill") && (num_arg ==1) && (dat.job_num > 0))
		{
			bool not_killed = false;

			// for (auto &i: jobs) {
			for(std::list<job>::iterator it = dat.jobs.begin(); it != dat.jobs.end(); it++ )
			{
				bool not_killed = false;
				time_t start_time = time(0);

				if (kill(it->pid , SIGTERM) == -1)
					std::cout << "Could not send signal to jobid" << it->jobid << std::endl;
				std::cout << "[" << it->jobid << "] " <<  it->name << " - " << "Sending SIGTERM...";
				waitpid(-1, NULL, WNOHANG);
				while (!kill(it->pid ,0))
				{
					if ((int)(time(0) - start_time) >= 10)
					{
						not_killed = true;
						break;
					}
						
				}
				if (not_killed == true)
				{
					std::cout << " (5 sec passed) Sending SIGKILL... Done" << std::endl;
					kill(it->pid , SIGKILL);
				}
				else
				{
					std::cout << " Done" << std::endl;
				}
				
			}
			int res = kill((int)getpid(), SIGKILL);
			// check all jobs if one was not killed send sig kiill;
		}
		else
		{
   		int res = kill((int)getpid(), SIGKILL);
		}

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
	else if (!strcmp(cmd, "kill"))
	{
		if (num_arg==2)
		{
			std::list<job>::iterator tmp = dat.findjob(dat.jobs ,atoi(args[2]));
			if(tmp == dat.jobs.end()) 
			{
				std::cout << "smash error:> kill " << tmp->jobid << " - job does not exist" << std::endl;
				return -1;
			}
			int job_pid = tmp->pid;
			if(kill(tmp->pid,atoi(args[1]+1)) == -1) // the  +1 is to skip the "-"
			{
				std::cout << "smash error:> kill " << tmp->jobid << " - cannot send signal" << std::endl;
			}

			if(atoi(args[1]+1) == SIGCONT)
			{
				tmp->stopped = false;
			}
		}
		else
		{
			illegal_cmd = true;
		}
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
				return ;
			}
        	case 0 :
                	// Child Process
					{
						setpgrp();
						if (execvp(args[0], args) == -1) 
						{	
							perror(NULL); 
							return ;
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
				return -1;
			case 0 :
				// Child Process
				setpgrp();
				if (execvp(args[0], args) == -1) {
					perror(NULL);
					return -1;
				}
				return -1;
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
