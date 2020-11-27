#include <stdlib.h>
#include <string>
#include <queue>
#include <list>

#pragma once

class job
{
private:
	/* data */
public:
	job(/* args */);
	std::string name;
	int time;
	int pid;
	~job();
};


class data
{
public:
	data();
	std::queue <std::string> history;
	// list <job> jobs;
	std::string prev_pwd;
	int GPid;
	void hist();
	~data();
};

