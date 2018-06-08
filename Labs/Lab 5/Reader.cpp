#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SIZE    2048

void sigHandler(int sigNum);
bool shutdown;
pid_t* pid_ptr;

/*******************************************************************************
Here is an attempt at a program that will share memory with Writer.cpp and
read out from the shared memory. Prints out the value in shared memory
@version 1.0
@author Keith Schmitt, Andrew Lawton
*******************************************************************************/
int main(){

  //used for identifying the
	int shmId;
	int shmId2;
	int shmId3;
	key_t shmKey;
	key_t shmKey2;
	key_t shmKey3;
	char* shmPtr;



	//used three different shared variables with different keys
  shmKey = ftok("output.txt", 64);
	shmKey2 = ftok("output.txt", 60);
	shmKey3 = ftok("output.txt", 54);


	//signal call
  signal( SIGUSR2, sigHandler);
  if ((shmId = shmget (shmKey, SIZE, S_IRUSR)) < 0) {
      perror ("i can't get no..\n");
      exit (1);
  }
	//get second piece of information used for counter int
	if ((shmId2 = shmget (shmKey2, SIZE, S_IRUSR)) < 0) {
      perror ("i can't get no..\n");
      exit (1);
  }

	/*
	* Now we attach the segment to our data space.
	*/
	if ((shmPtr = (char *)shmat(shmId, 0, 0)) == (char *) -1) {
		std::cerr<<"shmat";
		exit(1);
	}


	//bool to tell if the writer has written
  bool* hasWrote;
  if ((hasWrote = (bool*)shmat(shmId, 0, 0)) == (bool*) -1) {
		std::cerr<<"shmat";
		exit(1);
	}

	//used for pid passing
	if ((shmId3 = shmget (shmKey3, SIZE,
							 IPC_CREAT | S_IRUSR | S_IWUSR)) < 0) {
			perror ("i can't get no..\n");
			exit (1);
	}
	//attach pid for signaling purpose
	pid_ptr  = (pid_t *) shmat(shmId3, 0, 0);
	*pid_ptr = getpid();

	//counter used to count to 2 times
  int* counter;
  if ((counter = (int*)shmat(shmId2, 0, 0)) == (int*) -1) {
    std::cerr<<"shmat";
    exit(1);
  }


  //while not in shutdown
  while (*counter != -1){
		fflush(stdout);
    //and the writer has written

    while (*counter < 2){
      //printout what the writer wrote using std::string constructor
			std::string tempor = shmPtr;
      std::cout<<"The writer wrote: " << tempor<<std::endl;

			//flip haswritten condition
      *hasWrote = false;
			//check to see if signal was sent
			if (*counter == -1){
				break;
			}
			//let the counter know that we had one process read it
			*counter += 1;
			//constantly check if the signal was sent by checking counter
			//semaphore like
			while (*counter !=2){
				if (*counter == -1){
					break;
				};
			}
    }
		//if shutdown is sent from writer we'll shutdown
    if(shutdown){
      break;
    }
  }
	return 0;
}


void sigHandler(int sigNum){
  //sending a signal to back to the parent program to tell it to wait
  if (sigNum == SIGUSR2){
    //test statement
    std::cout<<"CLOSING THIS PROCESS"<<std::endl;
    shutdown = true;
    return;
  }
}
