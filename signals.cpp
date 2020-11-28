// signals.c
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
   Synopsis: handle the Control-C */
#include "signals.hpp"

// SIGTERM 

// funt ctrl callocsystemcall(sigkill)


void sig_handler(int sig_num,data& dat)
{
   std::cout << "we got sig_handler" << std::endl; /////////////////////////
   if(dat.GPid != -1)
   {
      std::cout << "GPid isn't -1" << std::endl; ////////////////////

      if(sig_num == SIGTSTP)
      {
         if(kill(dat.GPid,SIGTSTP)==-1)
         {
            perror(NULL);
            return;	
         }
         else
         {
            std::cout << "signal SIGTSTP was sent to pid " << dat.GPid << std::endl;
            // insert new job
         	job curr_job; 
				curr_job.create_time = time(0);
				curr_job.pid = (int)getpid();
				curr_job.name = dat.curr_name;
				curr_job.stopped = true;
				curr_job.jobid = ++ dat.job_num ;
				dat.jobs.push_back(curr_job);
            std::cout << dat.history.front() << std::endl; ////// 
            std::cout << "the jbo name is: " << dat.curr_name << std::endl; ////////////

            dat.GPid = -1;
         }

      }
      else if (sig_num == SIGINT)
      {
         if(kill(dat.GPid,SIGINT)==-1)
         {
            perror(NULL);
            return;	
         }
         else
         {
            std::cout << "signal SIGINT was sent to pid " << dat.GPid << std::endl;
            dat.GPid = -1;
         }
      }
      
      


      // else if (sig_num == SIGCONT)
      // {
      //    // if(kill(GPid,SIGTSTP)==-1)
      //    // {
      //    //    perror(NULL);
      //    //    return;	
      //    // }

      //     // std::cout << "signal SIGSTP was sent to pid" << dat.GPid << std::endl;
      //     //find the job
      // }
   }
   return;
}