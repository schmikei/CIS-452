#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>

#define SIZE 16


int main (int argc, char** argv) {
  int status;
  long int i, loop, temp, *shmPtr;
  int shmId;
  pid_t pid;

  //union semun sem_val;

  int semId;
  int semId2;

  struct sembuf sem_lock;
  sem_lock.sem_num = 0;
  sem_lock.sem_op = -1;
  sem_lock.sem_flg = SEM_UNDO;


  struct sembuf sem_unlock;
  sem_unlock.sem_num = 0;
  sem_unlock.sem_op = 1;
  sem_unlock.sem_flg = SEM_UNDO;



  //creating first semaphore for parent safety
  semId = semget (IPC_PRIVATE, 1, 00600 );
  if (semId < 0){
    perror ("sema1 create error..\n");
    exit (1);
  }
  //creating second semaphore for child safety
  semId2 = semget (IPC_PRIVATE, 1, 00600 );
  if (semId2 < 0){
    perror ("sema2 create error..\n");
    exit (1);
  }

  //setting the value of the first semaphore
  semctl(semId, 0, SETVAL, 1);
  //setting the value for the second semaphore
  semctl(semId2, 0, SETVAL, 1);



  if ((loop = atoi(argv[1])) < 0){
    perror("Invalid argument");
  }

  if ((shmId = shmget (IPC_PRIVATE, SIZE,
    IPC_CREAT | S_IRUSR | S_IWUSR)) < 0) {
      perror ("i can't get no..\n");
      exit (1);
    }
  if ((shmPtr = shmat (shmId, 0, 0)) == (void *) -1) {
    perror ("can't attach\n");
    exit (1);
  }


    //initial values
    shmPtr[0] = 0;
    shmPtr[1] = 1;

    if (!(pid = fork ())) {
      for (i = 0; i < loop; i++) {
        //entry section
        //place sema.wait()
        semop(semId, &sem_lock, 1);
	      semop(semId2, &sem_lock, 1);

        //critical section
        temp = shmPtr[0];
        shmPtr[0] = shmPtr[1];
        shmPtr[1] = temp;

        //exit section
        //place sema2.signal();
        semop(semId2, &sem_unlock, 1);
	      semop(semId, &sem_unlock, 1);
      }
      if (shmdt (shmPtr) < 0) {
        perror ("just can 't let go\n");
        exit (1);
      }
      exit (0);
    }
    else {

      for (i = 0; i < loop; i++) {
        //changing sem_lock to wait

        //place sema2.wait()
        semop(semId, &sem_lock, 1);
        semop(semId2, &sem_lock, 1);

        //critical section
        temp = shmPtr[1];
        shmPtr[1] = shmPtr[0];
        shmPtr[0] = temp;

        //place sema.signal();
        semop(semId2, &sem_unlock, 1);
        semop(semId, &sem_unlock, 1);
      }
    }

    wait (&status);
    printf ("values: %li\t%li\n", shmPtr[0], shmPtr[1]);

    semctl (semId, 0, IPC_RMID);

    semctl (semId2, 0, IPC_RMID);

    if (shmdt (shmPtr) < 0) {
      perror ("just can't let go\n");
      exit (1);
    }
    if (shmctl (shmId, IPC_RMID, 0) < 0) {
      perror ("can't deallocate\n");
      exit (1);
    }
    return 0;
  }
