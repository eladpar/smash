#include "data.hpp"  

data::data()
{

}

std::list<job>::iterator data::findjob(std::list<job> &jobs, int jobID)
{
    std::cout << "the int we got is: " << jobID << std::endl;
	for(std::list<job>::iterator it = jobs.begin(); it != jobs.end(); it++ ){
            if (it->jobid == jobID)
            {
                std::cout << "the job is is: " << it->jobid << "and the name is: " << it->name << std::endl;
                return it;
            }
	}
    return jobs.end();
}

data::~data()
{

}

job::job()
{

}

job::~job()
{

}

