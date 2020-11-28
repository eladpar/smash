#ifndef _SIGS_H
#define _SIGS_H
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "data.hpp"
#include <iostream>
#include <string>

void sig_handler(int sig_num,data& dat);

#endif


