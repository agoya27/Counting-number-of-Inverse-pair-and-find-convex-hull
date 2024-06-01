#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//Struct Point represents each input point
typedef struct Point {
  double x;
  double y;
}Point;

int ReadFile(struct Point * points_array, FILE * fptr);
int compare_float(double f1,double f2);
void find_distance(struct Point * hullPoints,int hullCount,Point s1,Point s2);
int GenerateHull(struct Point * points, struct Point * hullPoints, int count);
int findSide (struct Point p1, struct Point p2, struct Point p);
double distance(Point s1,Point s2);
void selectionSort(struct Point * arr,int n);
void selectionSort2(struct Point * arr,int n);
void sort_hullpoints(struct Point * hullPoints,int hullCount);
int findHull (struct Point * points, struct Point * hullPoints, struct Point p1, struct Point p2, int count, int hullCounter, int side);

//Drived code to control the program
int main() 
{
 
  FILE* fp = fopen("data_A2_Q2.txt","r");
  if (fp == NULL){
    printf("The file could not be opened\n");
    exit(0);
  }
  //Arrary of points to store 30000 input points
  struct Point points[30000];
  int count = ReadFile(points, fp);

  //Arry of points which are part of the Hull
  struct Point hullPoints[count];
  long int now_1=0, now_2 =0, diff =0;
	struct timespec now1;
	struct timespec now2;
  Point s1,s2;

  //Generate Hull is called to Find the Hull and Print it
  int hullCount = GenerateHull(points, hullPoints, count);
  printf("The Convex Hull has %d points\n", hullCount);
  printf("Please enter x coordinate of S1 with precision of 2 decimal points atleast: ");
  scanf(" %lf",&s1.x);
  printf("Please enter y coordinate of S1 with precision of 2 decimal points atleast: ");
  scanf(" %lf",&s1.y);
  printf("Please enter x coordinate of S2 with precision of 2 decimal points atleast: ");
  scanf(" %lf",&s2.x);
  printf("Please enter y coordinate of S2 with precision of 2 decimal points atleast: ");
  scanf(" %lf",&s2.y);

  timespec_get( &now1, TIME_UTC );
	now_1 = ((long int) now1.tv_sec) * 1000 + ((long int) now1.tv_nsec)/1000000;
  //Find distance is called to find the distance between 2 points and print the optimal path
  find_distance(hullPoints,hullCount,s1,s2);
  timespec_get( &now2, TIME_UTC );
	now_2 = ((long int) now2.tv_sec) * 1000 + ((long int) now2.tv_nsec)/1000000;

	diff = now_2 - now_1;  //difference stores the time taken to run the program
  printf("\n Process of finding Hux and calulating distance completed in: %ld Milliseconds\n",diff);

  printf("-----------------------------\n");

  fclose(fp);

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
   for(int i=0;i<hullCount;i++)
   {
    hullPoints[i].x = point_sorted[i].x;
    hullPoints[i].y = point_sorted[i].y;
   }
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

//Function finds the closest distance between S1 and S2
//Also prints the optimal path required to travel from S1 to S2
void find_distance(struct Point * hullPoints,int hullCount, Point s1,Point s2)
{
    int s1_pos, s2_pos =-1;
    sort_hullpoints(hullPoints,hullCount);

    //check if point s1 and s2 are part of the Hull
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
      if(s1_pos<s2_pos) //check if s2 lies after s1 in the list
      {
        for(int i=s1_pos;i<s2_pos;i++) //Find total distance between S1 and s2 clockwise
        {
          dist1 += distance(hullPoints[i],hullPoints[i+1]);
        }
        int j = s2_pos;
        while(j != (s1_pos)) //Find total distance between S1 and s2 anti clockwise
        {
          if(j == hullCount)
          {
            j =0;
          }
          dist2 += distance(hullPoints[j],hullPoints[j+1]);
          j++;
        }
        printf("\nOptimal Path is the Following: \n");
        if(dist1 < dist2)  //Check which distance is smaller
        {
          min_dist = dist1;
          for(int i=s1_pos;i<s2_pos;i++) //Printing optimal path to travel in hull
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
        for(int i=s2_pos;i<s1_pos;i++) //Finding distance between S1 and S2
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
        //Printing optimal path to travel from S1 to S2
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

//Function to calculate distance between 2 points
double distance(Point s1,Point s2)
{
  double dist =0;
  double term1 = (s1.x-s2.x)*(s1.x-s2.x);
  double term2 = (s1.y-s2.y)*(s1.y-s2.y);
  double term = term1+term2;
  dist = sqrt(term);
  return dist;
}

//Function to compare if 2 double values are equal or not
int compare_float(double f1,double f2)
{
  double precision = 0.01;
  if(((f1 - precision) <f2 ) && ((f1 + precision) > f2))
  {
    return 1;
  }
  return 0;
}

//Function to find hull and store points in Hullpoints array
int GenerateHull(struct Point * points, struct Point * hullPoints, int count){
  int i;
  // find the min and max x
  int min = 0;
  int max = 0;
  for (i = 1; i < count; i++) {
    if (points[i].x < points[min].x){
      min = i;
    }
    if (points[i].x > points[max].x){
      max = i;
    }
  }
  int hullCounter = 0;
  //Recursive approah to find hull in left and right Hull
   hullCounter = findHull(points, hullPoints, points[min], points[max], count, hullCounter, 1);
   hullCounter = findHull(points, hullPoints, points[min], points[max], count, hullCounter, -1);
   
   for (int j = 0; j < hullCounter; j++) {
     
     printf("%f,%f\n", hullPoints[j].x, hullPoints[j].y);
   }
   return hullCounter;
}

//Algorithm called by Create Hull to identify if points are in Hull or not
int findHull (struct Point * points, struct Point * hullPoints, struct Point p1, struct Point p2, int count, int hullCounter, int side){
  int index = -1;
  int max_dist = 0;
  for (int i=0; i<count; i++){
    int temp = abs((points[i].x - p1.x) * (p2.y - p1.y) - (points[i].y - p1.y) * (p2.x - p1.x));
    if (findSide(p1, p2, points[i]) == side && temp > max_dist){
        index = i;
        max_dist = temp;
    }
  }
  
  if (index == -1){
    int isP1 = 0;
    int isP2 = 0;
    if (hullCounter == 0){
      hullPoints[hullCounter] = p1;
      hullCounter ++;

      hullPoints[hullCounter] = p2;
      hullCounter ++;
    } else {
      int i;
      for (i = 0; i < hullCounter; i++) {
        if (p1.x == hullPoints[i].x && p1.y == hullPoints[i].y){
          isP1 = 1;
        }
        if (p2.x == hullPoints[i].x && p2.y == hullPoints[i].y){
          isP2 = 1;
        }
      }
      if (isP1 == 0){
        hullPoints[hullCounter] = p1;
        hullCounter ++;
      }
      if (isP2 == 0) {
        hullPoints[hullCounter] = p2;
        hullCounter ++;
      }
    }
    return hullCounter;
  }
  hullCounter = findHull(points, hullPoints, points[index], p1, count, hullCounter, -findSide(points[index], p1, p2));
  hullCounter = findHull(points, hullPoints, points[index], p2, count, hullCounter, -findSide(points[index], p2, p1));
  return hullCounter;
}

int findSide (struct Point p1, struct Point p2, struct Point p)
{
  int number = (p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
  if (number > 0)
  {
    return 1;
  }
  return -1;
}

//Function to read the file and store points in Points_array
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
   
