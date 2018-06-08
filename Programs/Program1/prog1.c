#include <stdio.h> 
#include <termios.h>
#include <stdlib.h>
#define SIZE 20

/*******************************************************
This is a program that will ask for input from a user one
time with echo disabled and another time with echo 
re-enabled
CIS 452-10
@author Keith Schmitt
*********************************************************/
int main(){
	struct termios temp, oldTerminal;

	/*******************************************************
	here I am grabbing the current settings of the terminal
	*********************************************************/
	tcgetattr(0, &temp);

	//setting to the old terminal
	oldTerminal = temp;
	char* userPhrase;
	printf("Disabling Echo!\n");
	printf("Enter Your Password: ");


	//disabling echo on the temp termios
	temp.c_lflag &= ~ECHO;
	//setting the temp termios immediately to echo off

	tcsetattr(0, TCSANOW, &temp);
	//allocating memory for the phrase
	userPhrase = malloc(SIZE * sizeof(char));

	//input from the terminal until the newline character
	scanf("%[^\n]s\n", userPhrase);
	

	printf("\nYou entered: %s\n", userPhrase);


	//free memory from first phrase
	free (userPhrase);
	//flush out stdin and clear out old input
	fflush(stdin);
	char* secondPhrase;
	
	secondPhrase = malloc(SIZE * sizeof(char));
	//restoring old terminal immediately
	tcsetattr(0, TCSANOW, &oldTerminal);
	printf("\nDefault Behavior Restored.\n");
	printf("enter a passphrase: ");
	scanf(" %[^\n]s\n", secondPhrase);

	printf("\nYou entered: ");
	printf("%s\n", secondPhrase);
	free(secondPhrase);
	return 0;
}