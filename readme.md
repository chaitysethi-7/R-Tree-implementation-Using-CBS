Instructions To Compile and Run:
1. Download the File and keep it in a directory say 'X'. Keep the file data.txt containing the data points in the same directory.
2. Open the directory on Terminal.
3. Run the File using the following instructions
    a. gcc -c DSA_assignment_group_14.c
    b. gcc -o run.exe DSA_assignment_group_14.o
    c. ./run.exe

Output Observed:
1. As mentioned in the problem statement, the current version of the code takes the 21 points database(data.txt) as the input
2. The code inserts all the 21 points and then prints ther MBR in pre-order traversal manner.
3. The code faces a segmentation fault if we try to input all the 1 lakh points at once, so it is advisable to input 10000 points at a time. We verified that the code runs perfectly for an input of size 10000 or less.
