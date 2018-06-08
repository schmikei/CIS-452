#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

/*******************************************************************************
A program that mimics the shell command ls, only works for ls -n path, ls -i path
@author Keith Schmitt
*******************************************************************************/
int main(int argc, char* argv[]){
  DIR *dirPtr;
  struct dirent *entryPtr;
  struct stat st;


  if (argc < 2 && argc != 1){
    printf("Sorry but could not open those directory(s) \n");
    return 1;
  }
  //this is for standard ls
  if (argc == 1){
    dirPtr = opendir(".");
    while ((entryPtr = readdir(dirPtr))!=NULL){
      stat(entryPtr->d_name, &st);
      printf("%-20s\n", entryPtr->d_name);
    }
  }
  //make sure it is actually a directory
  else if ((dirPtr = opendir(argv[2])) != NULL){
    //checking to make sure that there are three arguments
    if (argc == 3 ){
      //ls -i
      if (strncmp(argv[1], "-i", 26) == 0){
        printf("Inode#\t\t   Name\n");
        while ((entryPtr = readdir(dirPtr))!=NULL){
          stat(entryPtr->d_name, &st);
          printf("%llu\t   %-20s\n",entryPtr->d_ino, entryPtr->d_name);

        }
        closedir(dirPtr);
      }
      //ls -n
      else if (strncmp(argv[1], "-n", 26) == 0){
        printf("Permission UserId  GrpId   Name\n");
        while ((entryPtr = readdir(dirPtr))!=NULL){
          stat(entryPtr->d_name, &st);
          //printout got from stackoverflow
          //https://stackoverflow.com/questions/10323060/printing-file-permissions-like-ls-l-using-stat2-in-c
          printf( (S_ISDIR(st.st_mode)) ? "d" : "-");
          printf( (st.st_mode & S_IRUSR) ? "r" : "-");
          printf( (st.st_mode & S_IWUSR) ? "w" : "-");
          printf( (st.st_mode & S_IXUSR) ? "x" : "-");
          printf( (st.st_mode & S_IRGRP) ? "r" : "-");
          printf( (st.st_mode & S_IWGRP) ? "w" : "-");
          printf( (st.st_mode & S_IXGRP) ? "x" : "-");
          printf( (st.st_mode & S_IROTH) ? "r" : "-");
          printf( (st.st_mode & S_IWOTH) ? "w" : "-");
          printf( (st.st_mode & S_IXOTH) ? "x" : "-");
          printf(" ");
          printf("%u\t   %u\t   %-20s\n",st.st_uid, st.st_gid, entryPtr->d_name);
        }
        closedir(dirPtr);
      }
      else{
        //if it is neither -n or -i
        printf("Hey this executable doesn't know the command: %s\n" , argv[1]);
      }
    }
    else{
      //standard ls
      while ((entryPtr = readdir(dirPtr))!=NULL){
        stat(entryPtr->d_name, &st);
        printf("%-20s\n", entryPtr->d_name);
      }
    }
  }
  else{
    printf("Sorry could not find that directory\n");
    return 1;
  }
  return 0;
}
