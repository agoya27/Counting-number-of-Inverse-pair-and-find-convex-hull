#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Driver function of the program
int main()
{
	int array[50000]; //Array to store the data read from file
	FILE* fptr;       
	char name[20];
	int count = 0;
	int inv_count = 0;
	long int now_1, now_2, diff;
	struct timespec now1;
	struct timespec now2;

	printf("Please Enter name of the file to read from: ");
	scanf(" %s",name);

	fptr = fopen(name,"r");  //Opening the file to read the data

	if(fptr == NULL) //If file could not be opened then will exit program
	{
		printf("\nFile could not be opened");
		return 0;
	}

	while(!feof(fptr)) //check if we have reached end of file
	{
    	fscanf(fptr, "%d", &array[count]); //read file and store store in array 
    	count++;
	}

	fclose(fptr); //close the file

	timespec_get( &now1, TIME_UTC );
	now_1 = ((long int) now1.tv_sec) * 1000 + ((long int) now1.tv_nsec)/1000000;

	//Nested for loop is used to iterate throught the list 
	//Each element is compared with each other as per brute force approach
	for(int i=0;i<49999;i++)  
	{
		for(int j= i+1;j<50000;j++)
		{
			if(array[i] > array[j]) //check id condition of inverse pair is met
			{
				inv_count++;
			}
		}
	}

	timespec_get( &now2, TIME_UTC );
	now_2 = ((long int) now2.tv_sec) * 1000 + ((long int) now2.tv_nsec)/1000000;

	diff = now_2 - now_1;   //difference stores the time taken to run the program

	printf("\nTotal number of inverse pairs: %d",inv_count);
	printf("\nTime Differenc in Millisecond Precision: %ld\n",diff);

	return 0;
}