#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <sys/wait.h>
#include <iostream>
#include <sstream>
#include <fstream>
#define READ 0
#define WRITE 1

void sigHandler(int sigNum);
bool shutdown = false;

/*******************************************************************************
Here is Program 2
It is a program that will first take a list of txt files from the command line.
It then will create processes and appropriate data structures in order to manage
these files. The next thing it will do once it has all the file information
organized is to prompt the user for a word to find in all of these files.
We then create a process for each file and will appropriately get information
via upstream and downstream pipes that connect the two processes.
Once all the searchng is done, the parent gets information from upstream pipes
to print out a summary of the searches.
@author: Keith Schmitt
@version 1.0 2/10/2018
*******************************************************************************/
int main(){
  //my upstream pipe
  int myPipe[2];
  //my downstream pipe
  int my_out_pipe[2];
  int status;
  pid_t pid;
  //vector of my files
  std::vector<std::string> my_files;
  //vector to be in relation to my_files keeping track of the word occurances
  std::vector<int> word_occurs;
  //string for input stream to vector conversion
  std::string files_to_find;
  //string used for parsing files
  std::string single_file;
  //word that we will try to find in the files
  std::string word_to_find;
  //file stream
  std::fstream fs;
  //boolean used for shutdown
  bool shutdown = false;

  signal (SIGUSR2, sigHandler);

  //my upstream pipe being initialized
  if ((pipe(myPipe))<0){
    perror("Pipe error");
    exit(1);
  }
  //my downstream pipe being initialized
  if ((pipe(my_out_pipe))<0){
    perror("Pipe error");
    exit(1);
  }
  // getting the files the children will work on and put them into a vector
  std::cout<<"Please list the text files you would like to scan for: ";

  std::getline(std::cin, files_to_find);
  std::stringstream input_stream(files_to_find);

  //parsing the line into their files by
  while (input_stream >> single_file){
    my_files.push_back(single_file);
    word_occurs.push_back(0);
  }

  //printing out which files they are searching just for clarity sake
  std::cout<<"Files you are searching are: \n";
  for (std::vector<std::string>::iterator printout = my_files.begin() ; printout != my_files.end(); ++printout){
    std::cout << *printout<<std::endl;
  }

  //will exit on non-alphabetic input of -2
  std::cout<<"Please Enter -2 if you would like to quit"<<std::endl;


  while ( !shutdown){
    //parent gets output
    std::cout<<"\nPlease list the word(s) you would like to search for: ";
    std::getline(std::cin, word_to_find);

    //if input is -2 send a signal
    if (word_to_find == "-2"){
      sigHandler(SIGUSR2);
      wait(&status);
      break;
    }
    for (unsigned int i = 0; i < my_files.size(); ++i){
      if ((pid = fork()) < 0){
          perror("fork failure");
          exit(1);
      }
      if (pid == 0){
        //count to keep track of how many times the word comes up in a child file
        int count = 0;
        //open specified file from vector
        fs.open(my_files[i],std::fstream::in);
        //print out child id
        std::cout<<"Child "<<getpid()<< "\tHas opened the file: "<<my_files[i]<<" with a parent of " <<getppid()<<std::endl;
        //string to load file into
        std::string occurs;
        //string variable for the word to find
        std::string correct_word;
        //getting the word to find from downstream pipe child will be blocked
        //until the write from the parent succeeds due to the read() call
        read(my_out_pipe[READ], &correct_word, sizeof(correct_word));
        //going to count from filestream
        while (fs >> occurs ){
          if (occurs == correct_word){
            ++count;
          }
        }
        //close the file
        fs.close();
        //write to upstream pipe
        write(myPipe[WRITE], &count, sizeof(count));
        return 0;
      }
      else{
        //sending downstream pipe for the word_to_find
        write(my_out_pipe[WRITE], &word_to_find, sizeof(word_to_find));
        //responsible parent will wait for children
        wait(&status);
        //read from upstream pipes
        int parent_count = 0;
        //read blocks until child is done writing
        read(myPipe[READ], &parent_count, sizeof(parent_count));
        //for organization purpose, we put it in an array
        word_occurs[i] = parent_count;
      }
    }
    //last thing for the parent to do is do some statistics
    if (pid != 0){

      //parent prints out statistics
      std::cout<<"\nStatistics: "<<std::endl;
      int total_occurrences = 0;
      for (unsigned int i =0; i < my_files.size(); ++i){
        //print results
        std::cout<<my_files[i]<<" has found "<< word_to_find<<" "<<word_occurs[i]<< " times"<<std::endl;
        //sum a total
        total_occurrences += word_occurs[i];
      }
      //print out total
      std::cout<<"Total finds: "<<total_occurrences<<std::endl;
      //averages are nice :)
      std::cout<<"Average find per file: "<< double(total_occurrences)/my_files.size()<<std::endl;
    }

  }
  return 0;
}


void sigHandler(int sigNum){
  //sending a signal to back to the parent program to tell it to wait
  if (sigNum == SIGUSR2){
    shutdown = true;
    return;
  }
  //default behavior
  else if (sigNum == SIGINT){
    exit(0);
  }
}
