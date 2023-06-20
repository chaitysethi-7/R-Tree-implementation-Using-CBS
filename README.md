# R-Tree-implementation-Using-CBS
This project implements the Corner-Based Splitting (CBS) (2014), an improved node-splitting algorithm for the R-Trees(first introduced by Antonin Guttman in 1984).  Basic structures, a variety of helper and main functions to implement creation, insertion and appropriate adjustment of R-trees for mapping spatial coordinates have been covered.

Instructions To Compile and Run:

Download the File and keep it in a directory, say 'X'. Keep the file data.txt containing the data points in the same directory.
Open the directory on Terminal.
Run the File using the following instructions a. gcc -c DSA_assignment_group_14.c b. gcc -o run.exe DSA_assignment_group_14.o c. ./run.exe
Output Observed:

As mentioned in the problem statement, the current version of the code takes the 21 points database(data.txt) as the input
The code inserts all the 21 points and then prints the MBR in a pre-order traversal manner.
The code faces a segmentation fault if we try to input all the 1 lakh points at once, so it is advisable to input 10000 points at a time. We verified that the code runs perfectly for an input of size 10000 or less.
