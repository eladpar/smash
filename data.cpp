#include "data.hpp"  

data::data()
{

}
//**************************************************************************************
// function name: findjob
// Description: findes a job by job id
// Parameters: list of jobs and jobid
// Returns: iterator to spesifisied job - FAILES return to end
//**************************************************************************************
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
//**************************************************************************************
// function name: checkandbreakprocess
// Description: findes a job and checks if alive - if not cleans it from job list
// Parameters: list of jobs 
// Returns:  return to end of jobs
//**************************************************************************************
std::list<job>::iterator data::checkandbreakprocess(std::list<job> &items)
{
    std::list<job>::iterator i = items.begin();
    while (i != items.end())
    {
        waitpid(-1, NULL, WNOHANG);
        if(kill(i->pid ,0) != 0)
        {
            items.erase(i++);
        }
        else
        {
            ++i;
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

