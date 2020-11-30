#include <iostream> 
#include <signal.h>
using namespace std; 
  void catch_SIGTERM (int sig)
{
	std::cout << "caught SIGTERM" << std::endl;
}
int main(int argc, char** argv) 
{ 
	struct sigaction sig_term;

	sig_term.sa_handler = &catch_SIGTERM;
	// sig_cont.sa_handler = &catch_SIGCONT;

	sigaction(SIGTERM,&sig_term,NULL);
	while(1){
		// cout << "Hello World! " << endl;
	}
		// cout << "You have entered " << argc 
		// 		<< " arguments:" << "\n"; 

		// for (int i = 0; i < argc; ++i) 
		// 	cout << argv[i] << "\n"; 

		return 0; 
} 
// #include <iostream> 
// #include <list> 
// #include <iterator> 
// #include <stdlib.h>
// #include <string>
// using namespace std; 

// class job
// {
// private:
// 	/* data */
// public:
// 	job(/* args */);
// 	std::string neme;
// 	int time;
// 	int pid;
// 	~job();
// };

// //function for printing the elements in a list 
// void showlist(list <job> g) 
// { 
// 	list <job> :: iterator it; 
// 	for(it = g.begin(); it != g.end(); ++it) 
// 		cout << '\t' << *it; 
// 	cout << '\n'; 
// } 

// int main() 
// { 

// 	list <job> gqlist1; 


// 	// for (int i = 0; i < 10; ++i) 
// 	// { 
// 	// 	gqlist1.push_back(i * 2); 
// 	// 	gqlist2.push_front(i * 3); 
// 	// } 
//     job joe;
//     joe.pid = 298;
//     joe.time = 2;
//     joe.neme = "hana";
//     gqlist1.push_back(joe); 
// 	cout << "\nList 1 (gqlist1) is : "; 
// 	showlist(gqlist1); 

// 	// cout << "\nList 2 (gqlist2) is : "; 
// 	// showlist(gqlist2); 

// 	// cout << "\ngqlist1.front() : " << gqlist1.front(); 
// 	// cout << "\ngqlist1.back() : " << gqlist1.back(); 

// 	// cout << "\ngqlist1.pop_front() : "; 
// 	// gqlist1.pop_front(); 
// 	// showlist(gqlist1); 

// 	// cout << "\ngqlist2.pop_back() : "; 
// 	// gqlist2.pop_back(); 
// 	// showlist(gqlist2); 

// 	// cout << "\ngqlist1.reverse() : "; 
// 	// gqlist1.reverse(); 
// 	// showlist(gqlist1); 

// 	// cout << "\ngqlist2.sort(): "; 
// 	// gqlist2.sort(); 
// 	// showlist(gqlist2); 

// 	return 0; 

// } 
