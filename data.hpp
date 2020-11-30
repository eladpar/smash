#include <cstdlib>
#include <list>
#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <signal.h>
#include <wait.h>


#pragma once

class job
{
public:
	job();
	std::string name;
	time_t create_time;
	int pid;
	int jobid;
	bool stopped; // intialize to stopped
	~job();
};


class data
{
public:
	data();
	std::queue <std::string> history;
	std::list <job> jobs;
	std::list<job>::iterator findjob(std::list<job> &jobs, int jobID);
	std::list<job>::iterator checkandbreakprocess(std::list<job> &jobs);
	std::string prev_pwd;
	int job_num;
	int GPid;
	std::string curr_name;
	void hist();
	~data();
};



