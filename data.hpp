#include <cstdlib>
#include <list>
#include <string>
#include <queue>
#include <vector>

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
	std::string prev_pwd;
	int job_num;
	int GPid;
	void hist();
	~data();
};

