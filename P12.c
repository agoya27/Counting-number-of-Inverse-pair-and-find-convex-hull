#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAY_SIZE 50000

int divide_array(int array[], int array_size);
int merge_sorted_array(int array[], int temp[], int start, int end);
int merge(int array[], int temp[], int start, int mid,int end);

//Driver function of the program
int main()
{
	int array[ARRAY_SIZE]; //Array to store data from the file read
	FILE* fptr;
	char name[20];
	int count = 0;
	int inv_count = 0;
	long int now_1, now_2, diff;
	struct timespec now1;
	struct timespec now2;

	printf("Please Enter name of the file to read from: ");
	scanf(" %s",name);

	fptr = fopen(name,"r");  //Open file to read

	if(fptr == NULL)  //If file cannot be opened then will exit the program
	{
		printf("\nFile could not be opened");
		return 0;
	}

	while(!feof(fptr)) //check if we have reached end of file
	{
    	fscanf(fptr, "%d", &array[count]);  //read from file and store data into array
    	count++;
	}

	fclose(fptr);

	timespec_get( &now1, TIME_UTC );
	now_1 = ((long int) now1.tv_sec) * 1000 + ((long int) now1.tv_nsec)/1000000;

	inv_count = divide_array(array,ARRAY_SIZE);

	timespec_get( &now2, TIME_UTC );
	now_2 = ((long int) now2.tv_sec) * 1000 + ((long int) now2.tv_nsec)/1000000;

	diff = now_2 - now_1;

	printf("\nTotal number of inverse pairs: %d",inv_count);
	printf("\nTime Differenc in Millisecond Precision: %ld\n",diff);

	return 0;
}
//Function is used to malloc memory for a temporary array
//temp array is passed as a argument to the merge sort function
int divide_array(int array[], int array_size)
{
    int* temp = (int*)malloc(sizeof(int) * array_size);
    return merge_sorted_array(array, temp, 0, array_size - 1);
}
 
//Function divides the array in half to count numbers of inverses separtely
//After separate counts, function also counts number of inverse in merge of 2 arrays
int merge_sorted_array(int array[], int temp[], int start, int end)
{
    int mid, inv_count = 0;
    if (end > start) {

        mid = (end + start) / 2;
 
       
        inv_count += merge_sorted_array(array, temp, start, mid); //counting inverse pairs in first half
        inv_count += merge_sorted_array(array, temp, mid + 1, end);//counting inverse pair in second half
 
        
        inv_count += merge(array, temp, start, mid + 1, end); //counting inverse pairs while merging arrays
    }
    return inv_count;
}
 

int merge(int array[], int temp[], int start, int mid,
          int end)
{
    int i, j, k;
    int inv_count = 0;
 
    i = start;
    j = mid;
    k = start;
    while ((i <= mid - 1) && (j <= end)) 
	{
        if (array[i] <= array[j]) 
		{
            temp[k] = array[i];
			k++;
			i++;
        }
        else 
		{
            temp[k] = array[j];
			k++;
			j++;
            inv_count = inv_count + (mid - i);
        }
    }
 
    
    while (i <= mid - 1)
	{
		temp[k] = array[i];
		i++;
		k++;
	}
   
    while (j <= end)
	{
		temp[k] =array[j];
		k++;
		j++;
	}
 
    for (i = start; i <= end; i++)
        array[i] = temp[i];

    return inv_count;
}