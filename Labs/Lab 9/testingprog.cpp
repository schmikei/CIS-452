#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double big_one[500];
double small_one[50];


int printout(char* data){
	printf("in printout data is stored at %X\n",&data);
	printf("in printout big_one is stored at %X\n", &big_one);
	printf("in printout the function name printout is stored at %X\n",printout);
	return 0;
}

int main() {
    bool test;
	char* data1;
	char* data2;


	printf ("\nmemory address of data1 is at %X\n", &data1);
	printf ("what data1 is pointing to is at %X\n\n", data1);
	printf ("\nmemory address of data2 is at %X\n", &data2);
	printf ("what data2 is pointing to is at %X\n\n", data2);
	data1 =(char*) malloc (16);
	data2 =(char*) malloc (16);
	printf ("memory address of data1 after the malloc is now at %X\n", &data1);
	printf ("what data1 is pointing to after the malloc is at %X\n", data1);

	printf ("memory address of data2 after the malloc is now at %X\n", &data2);
	printf ("what data2 is pointing to after the malloc is at %X\n", data2);

	printf ("\nstack variable Test is at %X\n", &test);
	printf ("stack variable Test is now at %X\n\n", &test);

    printf ("This main function begins at %X\n", main);
    printf ("The two arrays are allocated at %X and %X\n\n", big_one,
            small_one);

	printf("In main, the function printout is stored at %X\n", printout);
	printout(data1);

	free(data1);

	printf ("\nmemory address of data1 is at after the free()  %X\n", &data1);
	printf ("what data1 is pointing to is at after the free() %X\n\n", data1);







    return 0;
}
