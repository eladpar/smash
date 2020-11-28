#include "data.hpp"  

data::data()
{

}

std::list<job>::iterator data::findjob(std::list<job> &jobs, int jobID)
{
		for(std::list<job>::iterator it = jobs.begin(); it != jobs.end(); it++ ){
            if (it->jobid == jobID)
                return it;
		
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

