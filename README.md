These are Algorithm design for solving the 2 problems using
Brute force ANF Divide & Conquer approach respectively. This file also contains proof of the effiency class for each of these algorithm. The 4 programming
files are based on these aglorithms to solve the problem of Counting number of Inverse pair and find convex hull using 2 different algorithm.

P11.c
The program reads input from a file whose name is entered by the user. Program ends with a display message if file cannot be opened. Once opened, the file
is read and data is stored in an array. Brute force approach is used to count the number of inversions in the array and output is displayed on the screen.
Programs also tracks the time taken to implement the counting operation and displays the time taken on the screen as well. During the test run using Brute
force approach on the test file provided it was observed that counting of array using this method took around 10200 Milliseconds.

P12.C
The program reads input from a file whose name is entered by the user. Program ends with a display message if file cannot be opened. Once opened, the file
is read and data is stored in an array. Divede and Conquer approach is used to count the number of inversions in the array and output is displayed on the 
screen.Programs also tracks the time taken to implement the counting operation and displays the time taken on the screen as well. During the test run using 
Divide and Conquer approach on the test file provided it was observed that counting of array using this method took around 13 Milliseconds.

P21.c
The program uses Struct Point which has 2 attributes Point x and Point y. The program reads input from file whose name is hardcoded in the program. 
Program ends with a display message if file cannot be opened. Once opened, the file is read and data is stored in an array of Struct Points. Brute Force
approach is used to find the Convex hull is 2D plane. All the points in the Hull are stored in a separate array called Hull_points. Once filled, the points
is hull_points are sorted to make a circular hull. User is then promted to provide 2 points which they want to know the path along. If the points do not
exist in the Hull, program exits with a error message. otherwise program computes the shortest distance around the Hull and display it on the screen along 
with the Optimal path. The program also keeps a track of time taken to find the Hull and calculation the total distance. It is observed that Brute force 
approach to solve the problem taken around 4 Minutes and 20 seconds when tested with a file containing 30,000 points.

P22.c
The program uses Struct Point which has 2 attributes Point x and Point y. The program reads input from file whose name is hardcoded in the program. 
Program ends with a display message if file cannot be opened. Once opened, the file is read and data is stored in an array of Struct Points. Divide anD
Conquer approach is used to find the Convex hull is 2D plane.All the points in the Hull are stored in a separate array called Hull_points. Once filled, t
he points is hull_points are sorted to make a circular hull. User is then promted to provide 2 points which they want to know the path along. If the points
do not exist in the Hull, program exits with a error message. otherwise program computes the shortest distance around the Hull and display it on the screen
along with the Optimal path. The program also keeps a track of time taken to find the Hull and calculation the total distance. It is observed that Divide
and Conquer approach to solve the problem taken around 2 Milliseconds when tested with a file containing 30,000 points.
