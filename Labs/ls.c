#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char* argv[])
{
  DIR *dirPtr;
  struct dirent *entryPtr;
	struct stat st;
	if (argc != 1){
		printf("Sorry but please input only one file path");
	}
    if ((dirPtr = opendir(argv[1])) < 0){
		printf("Sorry that file was not found");
	}
	else{
    	while ((entryPtr = readdir(dirPtr))){
			if (stat(entryPtr->d_name, &st) == 0){
				printf("%-20s has %lu KB\n", entryPtr->d_name, st.st_size);
			}
		}
		closedir(dirPtr);
	}
    return 0;
}
