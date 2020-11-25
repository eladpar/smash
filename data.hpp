#include <stdlib.h>
#include <string>
#include <queue>

#pragma once

class data
{
public:
	data();
	std::queue <std::string> history;
	std::string prev_pwd;
	void hist();
	~data();
};