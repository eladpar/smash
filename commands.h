#ifndef _COMMANDS_H
#define _COMMANDS_H
#include <unistd.h> 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <queue>
#include <stdint.h>

#include "data.hpp" 


#define MAX_LINE_SIZE 80
#define MAX_ARG 20

// typedef enum { FALSE , TRUE } bool;
// int ExeComp(char* lineSize);
int BgCmd(char* lineSize, data &dat);
int ExeCmd(char* lineSize, char* cmdString, data& dat);
void ExeExternal(char *args[MAX_ARG], char* cmdString, data &dat);

// class data;

// Globals to be reconized in commands.cpp
// extern std::queue <std::string> history;
// extern std::string prev_pwd;
#endif
// extern std::queue <std::string> history;
// extern std::string prev_pwd;
