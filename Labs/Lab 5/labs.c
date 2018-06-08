#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 4096

int main () {
    int shmId;
    controller* my_controls;

    if ((shmId =
         shmget (IPC_PRIVATE, SIZE,
                 IPC_CREAT | S_IRUSR | S_IWUSR)) < 0) {
        perror ("i can't get no..\n");
        exit (1);
    }

    //in case the attach goes wrong
    if ((shmPtr = shmat (shmId, 0, 0)) == (void *) -1) {
        perror ("can't attach\n");
        exit (1);
    }

    while (true){
      std::string input;
      //clear the file

      //get data from terminal
      std::cout<<"Please enter a input for the file: ";
      std::getline(std::cin, input);


      if (input == "quit"){
        sigHandler(SIGUSR1);
        return 0;
      }
    }
    if (shmctl (shmId, IPC_RMID, 0) < 0) {
        perror ("can't deallocate\n");
        exit (1);
    }

    return 0;
}
