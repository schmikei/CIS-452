#include <stdio.h>      
#include <stdlib.h>     /* srand, rand */ 
#include <signal.h>
#include <unistd.h>
#include <iostream>


//function header
void sigHandler(int); 

/**************************************************************************
 * Here is a program that spawns a child process where the parent process
 * will install signal handlers for user-defined signals (SIGUSR1/SIGUSR2)
 * along with SIGINT it will then wait for the child process to send 
 * these signals which it will randomly do so every 1 to 5 seconds. 
 * The sigHandler will then handle the signal and take appropriate action.
 * 
 * @version 1.0 1/25/2018
 * @author Keith Schmitt, Andrew Lawton
 * ************************************************************************/
int main ()
{
  pid_t pid;

  
  if ((pid = fork())< 0){
     perror ("fork failed");
     exit (1);
  }
  
  //parent
  else if (!pid){
    //creating custom signals
    signal(SIGUSR1, sigHandler);
    signal(SIGUSR2, sigHandler); 
    signal(SIGINT, sigHandler);
    std::cout<<"waiting... ";
    pause();
  }
  
  //child
  else{
    std::cout<<"spawned child PID# "<<getpid()<<std::endl;
    
    while (1){
      int ranNum = rand() %5;
      sleep(ranNum);
      int ranSignal = rand()%2;
      if(ranSignal == 0){
	sigHandler(SIGUSR1);
      }
      else{
	sigHandler(SIGUSR2);
      }
    }
  }
  
  
  
  return 0;
}

//custom sigHandler
void sigHandler (int sigNum){
  if(sigNum == SIGUSR1){
    std::cout<<"received a SIGUSR1 signal"<<std::endl;
  }
  else if (sigNum == SIGUSR2){
    std::cout<<"received a SIGUSR2 signal"<<std::endl;
  }
  else if(sigNum == SIGINT){
    std::cout<<"^C received"<<std::endl;
    std::cout<<"That's it, I'm shutting you down..."<<std::endl;
    exit(0); 
  }
}