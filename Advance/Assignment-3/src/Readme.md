# Readme

This repository contains the source code for CSL 7560+7561 Advanced Data Structures and Algorithms.

Submitted by:

Ashish Jacob Sam (M21CS003)

Abhijit Iyer (M21CS001)

Jayesh Budhwani (M21CS007)

## Contents
.
├── FibonacciHeap.cpp
├── FibonacciNode.cpp
├── Graph.cpp
├── M21CS003_M21CS001_M21CS007_Q01a.cpp
├── M21CS003_M21CS001_M21CS007_Q01b.cpp
├── MaxFlow_MPM_Array.cpp
├── MaxFlow_MPM_Heap.cpp
├── Queue.cpp
└── Readme.pdf

- The files `FibonacciNode.cpp` and `FibonacciHeap.cpp` contains implementaion of the Fibonacci heap. 
- The file `Queue.cpp` contains the Queue Data structure for performing BFS in the graph
- The file `Graph.cpp` contains functions related to graph: Initialization, Setting Capacity/Flow value, etc.
- The file `MaxFlow_MPM_Array.cpp` contains the single function `MaxFlow_MPM_Array()` which caluclates the maximum flow in the graph, and return the maximum flow value
- The file `MaxFlow_MPM_Heap.cpp` is similar to the above, but uses Fibonacci heap to find the vertex with the minimum capacity/potential
- The file `M21CS003_M21CS001_M21CS007_Q01a.cpp` contains the main program for demonstrating the `MaxFlow_MPM_Array()` function.
- The file `M21CS003_M21CS001_M21CS007_Q01b.cpp` contains the main program for demonstrating the `MaxFlow_MPM_Heap()` function.

---

## Compilation and execution

Use `g++` to compile the program. Note that there are 2 different executable programs.

Sample output

```
$ g++ M21CS003_M21CS001_M21CS007_Q01a.cpp -o a.out && ./a.out
Enter graph vertices: 5

Taking vertex 0 as source, and 4 as target.
Enter number of directed edges:5


Enter edges as follows: [Source] [Destination] [Capacity]
0 1 10
1 2 11
2 4 12
1 3 12
3 4 11
Total flow going out of source = 10
```

```
$ g++ M21CS003_M21CS001_M21CS007_Q01b.cpp -o a.out && ./a.out
Enter graph vertices: 5

Taking vertex 0 as source, and 4 as target.
Enter number of directed edges:7


Enter edges as follows: [Source] [Destination] [Capacity]
0 1 20
0 2 15
1 2 18
2 3 10
1 4 8
2 4 3
3 4 12
Total flow going out of source = 21
```

