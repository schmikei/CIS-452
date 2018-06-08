#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SIZE 2048


//method to handle signals
void sigHandler(int sigNum);
pid_t* pid;

//boolean to help with control of process at termination
bool shutdown;

/*******************************************************************************
Here is an attempt at a program that will share memory with Reader.cpp and
write out to output.txt. Prompts user for input to write in and allocates it in
shared memory.
@version 1.0
@author Keith Schmitt, Andrew Lawton
*******************************************************************************/
int main () {
    //the key we will use to attach to
    int shmId;
    int shmId2;
    int shmId3;
    int* counter;
    //the data we will be getting from user
    std::string* shmPtr;

    //key used for shmget
    key_t shmKey;
    key_t shmKey2;
    key_t shmKey3;
    std::ofstream myFile;
    shutdown = false;



    signal(SIGUSR1, sigHandler);

    //getting the key based off of ftok using output.txt and 64 as a key



    shmKey = ftok("output.txt", 64);
    shmKey2 = ftok("output.txt", 60);
    shmKey3 = ftok("output.txt", 54);
    //getting the memory segment for hasWrote
    if ((shmId = shmget (shmKey, SIZE,
                 IPC_CREAT | S_IRUSR | S_IWUSR)) < 0) {
        perror ("i can't get no..\n");
        exit (1);
    }

    //creating shmId2 for counter
    if ((shmId2 = shmget (shmKey2, SIZE,
                 IPC_CREAT | S_IRUSR | S_IWUSR)) < 0) {
        perror ("i can't get no..\n");
        exit (1);
    }
    //creating shmId3 for pid
    if ((shmId3 = shmget (shmKey3, SIZE,
                 IPC_CREAT | S_IRUSR | S_IWUSR)) < 0) {
        perror ("i can't get no..\n");
        exit (1);
    }

    pid  = (pid_t *) shmat(shmId3, 0, 0);

    //bool point being attached to shared memory
    bool* hasWrote;
    if ((hasWrote = (bool*)shmat(shmId, 0, 0)) == (bool*) -1) {
  		std::cerr<<"shmat";
  		exit(1);
  	}


    //attach the counter to shared memory
    if ( (counter = (int*)shmat(shmId2, 0, 0)) == (int*) -1) {
      std::cerr<<"shmat";
      exit(1);
    }


    *hasWrote = false;

    //allocating the memory in the shared section
    if ((shmPtr = (std::string*) shmat (shmId, 0, 0)) == (std::string*) -1) {
      std::cerr<<"shmat";
      exit(1);
    }
    *counter = 2;
    //looping logic while we aren't in shutdown we will continue to loop
    while (!shutdown){
      //while the writer has not written out
      while (*counter == 2){
          //get data from terminal
          std::cout<<"Please enter a input for the file: ";
          std::getline(std::cin, *shmPtr);


          //convert to c-style to use shmat without seg faults
          char tmp[SIZE];
          strcpy(tmp, shmPtr->c_str());


          //opening the file
          myFile.open("output.txt");

          //if the user decides to quit we want to take appropriate aciton
          // most likely with a flag
          if ("quit" == *shmPtr){
            //send signal
            sigHandler(SIGUSR1);
            //close the file if the user quits
            myFile.close();
            //change counter so other processes know you're done
            *counter = -1;
            //shutdown to break out of loop
            shutdown = true;
            break;
          }
          else{
            //write to file
            myFile<< *shmPtr;
            *counter = 0;
            //set that the writer has written
            //close the file
            myFile.close();
      }
      wait(&*pid);
    }
  }
  //remove allocated shared memory
  if (shmctl(shmId, IPC_RMID, 0) < 0){
    perror("Removing shared error");
    exit(1);
  }
  return 0;
}




//signal
void sigHandler(int sigNum){
  //sending a signal to terminate the process using shared memory
  if (sigNum == SIGUSR1){
    std::cout<<"sending signals..."<<std::endl;
    std::cout<<"sending kill to "<<*pid<<std::endl;
    kill(*pid, SIGUSR2);
    return;
  }
  //default behavior
  else if (sigNum == SIGINT){
    exit(0);
  }
}
