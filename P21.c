#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<math.h>

//Struct to create variable Point with x and y coordinate
typedef struct Point {
  double x;
  double y;
}Point;
 
int ReadFile(struct Point * points_array, FILE * fptr);
int FindHull(struct Point * points_array, struct Point * Hull_Points, int count);
int compare_float(double f1,double f2);
void selectionSort(struct Point * arr,int n);
void selectionSort2(struct Point * arr,int n);
void sort_hullpoints(struct Point * hullPoints,int hullCount);
void find_distance(struct Point * hullPoints,int hullCount,Point s1,Point s2);
double distance(Point s1,Point s2);

//Controller function of the program
int main()
{
    FILE* fptr;
	char name[20];
    Point point_array[30000];
    int num_point = 0;
	long int now_1, now_2, diff;
	struct timespec now1;
	struct timespec now2;

	strcpy(name,"data_A2_Q2.txt");
	fptr = fopen(name,"r");  //File is opened in read mode 
	if(fptr == NULL)   //Exit program if file open fails
	{
		printf("\nFile could not be opened");
		return 0;
	}

    Point s1,s2;

    printf("File Read Successfully. Finding Convx Hull Using Brute Force Approah");
    printf("\nPlease enter x coordinate of S1 with precision of 2 decimal points atleast: ");
    scanf(" %lf",&s1.x);
    printf("\nPlease enter y coordinate of S1 with precision of 2 decimal points atleast: ");
    scanf(" %lf",&s1.y);
    printf("\nPlease enter x coordinate of S2 with precision of 2 decimal points atleast: ");
    scanf(" %lf",&s2.x);
    printf("\nPlease enter y coordinate of S2 with precision of 2 decimal points atleast: ");
    scanf(" %lf",&s2.y);

    num_point = ReadFile(point_array,fptr);
    
    Point hull_array[num_point]; //Hull array to store the point on the hull
    int brute_count =0;

    timespec_get( &now1, TIME_UTC );
	now_1 = ((long int) now1.tv_sec) * 1000 + ((long int) now1.tv_nsec)/1000000;

	brute_count = FindHull(point_array,hull_array,num_point);
    find_distance(hull_array,brute_count,s1,s2);

	timespec_get( &now2, TIME_UTC );
	now_2 = ((long int) now2.tv_sec) * 1000 + ((long int) now2.tv_nsec)/1000000;

	diff = now_2 - now_1;  //Difference to store the time taken to run the program

	printf("\nTotal number of Points is Convex Hull: %d",brute_count);
	printf("\nTime Differenc in Millisecond Precision: %ld\n",diff);

    return 0;
}

int ReadFile(struct Point * points_array, FILE * fptr)
{
    char lines[50];
    int num_point =0;

    while(fgets(lines,sizeof(lines),fptr) != NULL)  //Lines are read from the file one at a time
    {
        char *line_content;
        line_content = strtok(lines, "    ");  //file is broken into 2 parts using string token function
        points_array[num_point].x = atof(line_content);

        line_content = strtok(NULL, "    \n");
        points_array[num_point].y = atof(line_content);

        //First token is stored as x coordinate and 2nd token is y coordinate
        num_point++;
    }
    return num_point;
}

//Function to find the Hull and store points in Hull_Points array
int FindHull(struct Point * points_array, struct Point * Hull_Points, int count)
{
    int i;
    int hull_count =0;
    //Nested For loop to iterate all points and compare one by one
    for(i=0;i<count;i++)
    {
        int in_Hull =0;
        for(int j=0;j<count;j++)
        {
            if(i ==j)
            {
                continue;
            }
            Point p1 = points_array[i];
            Point p2 = points_array[j];

            int p_side,dup_point = 0;

            for(int k=0;k<count;k++)
            {
                if(k != i && k != j)
                {
                    if(((points_array[k].y - p1.y)*(p2.x-p1.x)-(points_array[k].x - p1.x)*(p2.y-p1.y))<0)
                    {
                        p_side++;
                    }
                }
                else
                {
                    dup_point++;
                }
            }
            if(p_side == count-dup_point)
            {
                in_Hull = 1;
                break;
            }
        }
        if(in_Hull == 1)
        {
            Hull_Points[hull_count] = points_array[i];
            hull_count++;
        }
    }
    for(int i=0;i<hull_count;i++)
    {
        printf("%f %f\n",Hull_Points[i].x,Hull_Points[i].y);
    }
    return hull_count;
}

//Function to find minimum distance and optimal path for travelling in Hull
void find_distance(struct Point * hullPoints,int hullCount, Point s1,Point s2)
{
    int s1_pos, s2_pos =-1;

    for (int i = 0; i < hullCount; i++)
    {
      if ((compare_float(hullPoints[i].x,s1.x)) && (compare_float(hullPoints[i].y,s1.y)))
      {
        s1_pos = i;
      }
      if ((compare_float(hullPoints[i].x,s2.x)) && (compare_float(hullPoints[i].y,s2.y)))
      {
        s2_pos = i;
      }
    }
    
    if((s1_pos != -1) && (s2_pos != -1))
    {
      double dist1 = 0;
      double dist2 = 0;
      double min_dist = 0;
      if(s1_pos<s2_pos)
      {
        for(int i=s1_pos;i<s2_pos;i++) //Finding total distance in clockwise direction
        {
          dist1 += distance(hullPoints[i],hullPoints[i+1]);
        }
        int j = s2_pos;
        while(j != (s1_pos))
        {
          if(j == hullCount)
          {
            j =0;
          }
          //finding total distance in anti clockwise direction
          dist2 += distance(hullPoints[j],hullPoints[j+1]);
          j++;
        }
        printf("\nOptimal Path is the Following: \n");
        if(dist1 < dist2)
        {
          min_dist = dist1;
          //Prints the optimal path 
          for(int i=s1_pos;i<s2_pos;i++)
          {
            printf("\n(%lf,%lf)",hullPoints[i].x,hullPoints[i].y);
          }
          printf("\n(%lf,%lf)",s2.x,s2.y);

        }
        else
        {
          min_dist = dist2;
          int j = s2_pos;
          while( j != s1_pos)
          {
            if(j == hullCount)
            {
              j = 0;
            }
            printf("\n(%lf,%lf)",hullPoints[j].x,hullPoints[j].y);
            j++;
          }
          printf("\n(%lf,%lf)",s1.x,s1.y);
        }
        printf("\nMinimum distance between Points s1 and s2 is %lf \n",min_dist);
      }
      else if(s1_pos>s2_pos)
      {
        for(int i=s2_pos;i<s1_pos;i++)
        {
          dist1 += distance(hullPoints[i],hullPoints[i+1]);
        }
        int j = s1_pos;
        while(j != (s2_pos))
        {
          if(j == hullCount)
          {
            j =0;
          }
          dist2 += distance(hullPoints[j],hullPoints[j+1]);
          j++;
        }
        printf("\nOptimal Path is the Following: \n");
        if(dist1 < dist2)
        {
          min_dist = dist1;
          for(int i=s2_pos;i<s1_pos;i++)
          {
            printf("\n(%lf,%lf)",hullPoints[i].x,hullPoints[i].y);
          }
          printf("\n(%lf,%lf)",s1.x,s1.y);
        }
        else
        {
          min_dist = dist2;
          int j = s1_pos;
          while( j != s2_pos)
          {
            if(j == hullCount)
            {
              j = 0;
            }
            printf("\n(%lf,%lf)",hullPoints[j].x,hullPoints[j].y);
            j++;
          }
          printf("\n(%lf,%lf)",s2.x,s2.y);
        }
        printf("\nMinimum distance between Points s1 and s2 is %lf \n",min_dist);
      }
      else
      {
        printf("\nBoth the Points are same, Hence the Distance between points is 0");
      }
    }
    else
    {
      printf("\nThe points you entered were not part of the Hull\n");
    }
}

//function to find distance between 2 points
double distance(Point s1,Point s2)
{
  double dist =0;
  double term1 = (s1.x-s2.x)*(s1.x-s2.x);
  double term2 = (s1.y-s2.y)*(s1.y-s2.y);
  double term = term1+term2;
  dist = sqrt(term);
  return dist;
}

//Function to check if 2 points are equal or not
int compare_float(double f1,double f2)
{
  double precision = 0.01;
  if(((f1 - precision) <f2 ) && ((f1 + precision) > f2))
  {
    return 1;
  }
  return 0;
}

void sort_hullpoints(struct Point * hullPoints,int hullCount)
{
   double x_min = hullPoints[0].x;
   double x_max = hullPoints[0].x;
   int x_min_pos,x_max_pos = 0;

   for(int i=1;i<hullCount;i++)
   {
    if(hullPoints[i].x < x_min)
    {
      x_min = hullPoints[i].x;
      x_min_pos = i;
    }
    if(hullPoints[i].x > x_max)
    {
      x_max = hullPoints[i].x;
      x_max_pos = i;
    }
   }
 
   double y_min = hullPoints[x_min_pos].y;
   double y_max = hullPoints[x_max_pos].y;
   struct Point point_above[hullCount];
   struct Point point_below[hullCount];
   int num_low = 0;
   int num_high = 0;

   for(int i=0;i<hullCount;i++)
   {
    double s = ((y_max-y_min)*hullPoints[i].x) + ((x_min-x_max)*hullPoints[i].y) + ((x_max*y_min)-(x_min*y_max));
    if(s>0 && i!= x_min_pos && i != x_max_pos)
    {
      point_above[num_high].x = hullPoints[i].x;
      point_above[num_high].y = hullPoints[i].y;
      num_high++;
    }
    else
    {
      if(i!= x_min_pos && i != x_max_pos)
      {
        point_below[num_low].x = hullPoints[i].x;
        point_below[num_low].y = hullPoints[i].y;
        num_low++;
      }
    }
   }
   struct Point point_sorted[hullCount];
   point_sorted[0].x = hullPoints[x_min_pos].x;
   point_sorted[0].y = hullPoints[x_min_pos].y;
   int sorted_count = 0;

   selectionSort(point_below,num_low+1);
   selectionSort2(point_above,num_high+1);

   for(int i=0;i<=num_low;i++)
   {
     point_sorted[sorted_count].x = point_below[i].x;
     point_sorted[sorted_count].y = point_below[i].y;
     sorted_count++;
   }
   point_sorted[sorted_count].x = hullPoints[x_max_pos].x;
   point_sorted[sorted_count].y = hullPoints[x_max_pos].y;
   sorted_count++;
   for(int i=0;i<=num_high;i++)
   {
     point_sorted[sorted_count].x = point_above[i].x;
     point_sorted[sorted_count].y = point_above[i].y;
     sorted_count++;
   }
   hullPoints = point_sorted;
}

void selectionSort(struct Point * arr,int n)
{
   int min_idx = 0;

   for(int i=0;i<n-1;i++)
   {
      min_idx = i;
      for(int j=i+1;j<n;j++)
      {
        if(arr[j].x < arr[min_idx].x)
        {
          min_idx = j;
        }
      }
      struct Point temp = arr[min_idx];
      arr[min_idx] = arr[i];
      arr[i] = temp;
   }
}

void selectionSort2(struct Point * arr,int n)
{
   int min_idx = 0;

   for(int i=0;i<n-1;i++)
   {
      min_idx = i;
      for(int j=i+1;j<n;j++)
      {
        if(arr[j].x > arr[min_idx].x)
        {
          min_idx = j;
        }
      }
      struct Point temp = arr[min_idx];
      arr[min_idx] = arr[i];
      arr[i] = temp;
   }
}