# Exam-Scheduling-Using-Graph-Algorithms
This project implements an Exam Scheduling System using graph-based models and scheduling algorithms. A conflict graph is built where nodes represent subjects, and edges indicate shared students. The scheduling problem is solved using Backtracking, Greedy, DSATUR, Smallest Degree Last, and Tabu Search. The system supports three graph representations—Edge List, Adjacency List, and Adjacency Matrix, each offering different trade-offs in memory usage and performance.


## 📂 Exam-Scheduling-Using-Graph-Algorithms

### **Source Files**
- 📄 **1.cpp** - Backtracking Scheduling  
- 📄 **2.cpp** - Greedy Scheduling  
- 📄 **3.cpp** - Smallest Degree Last Scheduling  
- 📄 **4.cpp** - DSATUR Scheduling  
- 📄 **5.cpp** - Tabu Search Scheduling  
- 📄 **graph.cpp** - Graph Implementations  
- 📄 **edge.cpp** - Edge Management  
- 📄 **vertex.cpp** - Vertex Representation  
- 📄 **hash.cpp** - Hash Table for Fast Lookup  
- 📄 **neighbors.cpp** - Neighbor Retrieval Functions  
- 📄 **schedulingAlgorithms.cpp** - All Scheduling Methods  
- 📄 **main.cpp** - Entry Point  
- 📄 **graph.hpp** - Graph Class Definitions  
- 📄 **edge.hpp** - Edge Class  
- 📄 **vertex.hpp** - Vertex Class  
- 📄 **hash.hpp** - Hash Table Header  
- 📄 **neighbors.hpp** - Neighbor Functions  
- 📄 **schedulingAlgorithms.hpp** - Scheduling Headers  

## How to Run the Code?
⚠️ You need a properly set up WSL environment to run this project smoothly.
1) Open WSL by using the command: wsl
2) Navigate to your project folder using: cd path-to-your-folder
3) Compile the project using: g++ -o exam_scheduler 1.cpp graph.cpp edge.cpp vertex.cpp hash.cpp neighbors.cpp schedulingAlgorithms.cpp
- The command uses 1.cpp, which means Backtracking Scheduling.
- If you want to try a different algorithm, replace 1.cpp with 2.cpp, 3.cpp, etc.
4) Run the executable using:./exam_scheduler < complete.ip
  - The command directly takes input from a file called complete.ip, so you don't need to enter input manually.
  - If you want to test with different cases, such as a bipartite graph or a tree, you can change the input file or enter input manually.
The output will be saved in a file with the .op extension.
