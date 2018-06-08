#include <iostream>
#include <sstream>
#include <unistd.h>
#include <istream>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <vector>
/***********************************************************************
Here is a program that simulates a shell, utilizing fork() and execvp()
to accomplish this task. We time each child process and report back how
long it takes for that process to complete. User can exit by typing
quit. Any Unix commands should be compatible.

@version 1.0
@author Andrew Lawton, Keith Schmitt
***********************************************************************/
int main(){

	//required initialization
	std::string input_line;
	std::string tok;
	char const* myQuit = "quit";
	pid_t pid;
	int status;
	std::vector<std::string> arg;
	//used for timing purposes
	struct rusage myResources;
	double start, end, sysstart, sysend;




	while (true) {
	//parse the command

    /* tok is a single token from input_line */
    std::cout<< "Please enter system calls: ";


	//setup for getting input
    std::getline(std::cin, input_line);
	std::stringstream input_stream(input_line);
	//number is used to get flags
    	int number = 0;
	//if there was anything in the vector, clear it out
	arg.clear();
	//get input
	while(input_stream >> tok){
		arg.push_back(tok);
		++number;
	}

	//If user decided to quit
	if (arg[0] == myQuit){
		break;
	}

	//otherwise handle forking
	else{
		//start clock for process
		getrusage(RUSAGE_SELF, &myResources);
  	start=myResources.ru_utime.tv_usec;
  	sysstart = myResources.ru_stime.tv_usec;

		//fork here
		if ((pid = fork()) < 0) {
        		perror("fork failure");
        		exit(1);
    	}


		//the child process and execution
		else if (pid == 0){
			//converting from vector to char* array
			char* myArgs[20];
			int i = 0;
			for ( i = 0; i < arg.size();i++){
				myArgs[i] =  const_cast<char*> (arg[i].c_str());
			}
			//setting last value to NULL for exec call
			myArgs[i] = NULL;

			//execute the call
			execvp(myArgs[0], myArgs);
			std::cout<<"Not a valid command"<<std::endl;
			exit(0);
		}
		else{
			//parent waits for child
			wait(&status);


			//print cpu time results after stopping the cpu
			getrusage(RUSAGE_SELF, &myResources);
  			end=myResources.ru_utime.tv_usec;
  			sysend = myResources.ru_stime.tv_usec;

  			std::cout<<std::endl;
			std::cout<< "User CPU Time used for Child Process: "<<  end -start <<" microseconds"<<std::endl;
			std::cout<< "Total System Time: "<<  sysend - sysstart <<" microseconds"<<std::endl;
			//getting involuntary context switches
			std::cout<<"Number of involuntary context switches: "<< myResources.ru_nivcsw<<std::endl;
		}

	}
}

	return 0;
}
