/*	smash.c
main file. This file contains the main function of smash
*******************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <queue>
#include "commands.h"
#include "signals.hpp"
#include "data.hpp"  
#define MAX_LINE_SIZE 80
#define MAXARGS 20
#define MAX_HISTORY 3 // TODO CHANGE TO 50

char* L_Fg_Cmd;
// void* jobs = NULL; //This represents the list of jobs. Please change to a preferred type (e.g array of char*)
char lineSize[MAX_LINE_SIZE];


// data * p_dat = new data;
data dat;


//********************************************
// function name: insertcmd
// Description: insert command into history while checking queue container size if big then remove oldest command
// Parameters: history container and command string
//**************************************************************************************
void insertcmd(std::queue <std::string> &his, char * command)
{
	if (his.size() >= MAX_HISTORY)
	{
		his.pop();
	}

	his.push(command); // TODO "" or error?
}

//**************************************************************************************
// function name: main
// Description: main function of smash. get command from user and calls command functions
//**************************************************************************************
int main(int argc, char **argv)
{
    char cmdString[MAX_LINE_SIZE]; 	 
	signal(SIGTSTP, [](int sig) { return sig_handler(sig, dat); });  
	signal(SIGINT, [](int sig) { return sig_handler(sig, dat); });  


	dat.job_num = 0;
	dat.GPid = -1;

	L_Fg_Cmd =(char*)malloc(sizeof(char)*(MAX_LINE_SIZE+1));
	if (L_Fg_Cmd == NULL) 
			exit (-1); 
	L_Fg_Cmd[0] = '\0';
	
    	while (1)
    	{
		std::cout << "smash > ";
		fgets(lineSize, MAX_LINE_SIZE, stdin);
		strcpy(cmdString, lineSize);    
		cmdString[strlen(lineSize)-1]='\0';

		std::string curr_string (cmdString);
		dat.curr_name = curr_string;

					// background command
			
	 	if(!BgCmd(lineSize, dat)) continue; 

					// built in commands
					// e.g pwd cd ....
		ExeCmd(lineSize, cmdString, dat);
		
		insertcmd(dat.history, cmdString);
		/* initialize for next line read*/
		lineSize[0]='\0';
		cmdString[0]='\0';
	}
    return 0;
}

