# 📘 Exam-Scheduling-Using-Graph-Algorithms

This project implements an **Exam Scheduling System** using graph-based models and scheduling algorithms. A **conflict graph** is constructed where:
- **Nodes** represent courses/exams.
- **Edges** represent a conflict (shared students between two courses).

The problem is modeled as a **graph coloring** problem and solved using various algorithms:
- ✅ Backtracking  
- ✅ Greedy  
- ✅ DSATUR  
- ✅ Smallest Degree Last  
- ✅ Tabu Search  

The system supports three graph representations:
- Edge List
- Adjacency List
- Adjacency Matrix

---

## 📂 Project Structure

### **Source Files**

| Filename                     | Description                              |
|------------------------------|------------------------------------------|
| `1.cpp`                      | Backtracking Scheduling                  |
| `2.cpp`                      | Greedy Scheduling                        |
| `3.cpp`                      | Smallest Degree Last Scheduling          |
| `4.cpp`                      | DSATUR Scheduling                        |
| `5.cpp`                      | Tabu Search Scheduling                   |
| `main.cpp`                   | Main entry point of the project          |
| `graph.cpp` / `graph.hpp`    | Graph implementation and definitions     |
| `edge.cpp` / `edge.hpp`      | Edge class and related operations        |
| `vertex.cpp` / `vertex.hpp`  | Vertex (course) class and functions      |
| `hash.cpp` / `hash.hpp`      | Custom hash table for fast lookups       |
| `neighbors.cpp` / `.hpp`     | Functions to retrieve conflicting exams  |
| `schedulingAlgorithms.cpp` / `.hpp` | All scheduling logic             |

---

## 📚 Project Workflow

```plaintext
Input File (student-course data)
            ↓
        main.cpp
            ↓
  Construct Graph
   ┌─────────────┴─────────────┐
   │    vertex.cpp             │
   │    edge.cpp               │
   │    graph.cpp              │
   └───────────────────────────┘
            ↓
Select Scheduling Algorithm
   ┌─────────────┬─────────────┬─────────────────────────┬─────────────┬─────────────┐
   │ Backtracking│ Greedy      │ Smallest Degree Last    │ DSATUR      │ Tabu Search │
   │  (1.cpp)    │  (2.cpp)    │      (3.cpp)            │  (4.cpp)    │   (5.cpp)   │
   └─────────────┴─────────────┴─────────────────────────┴─────────────┴─────────────┘
            ↓
Use Helpers
   ┌──────────────┬─────────────┐
   │ neighbors.cpp│  hash.cpp   │
   └──────────────┴─────────────┘
            ↓
Output: Time slots for each exam


## How to Run the Code?
⚠️ You need a properly set up WSL environment to run this project smoothly.
1) Open WSL by using the command: wsl
2) Navigate to your project folder using: cd path-to-your-folder
3) Compile the project using: g++ -o exam_scheduler 1.cpp graph.cpp edge.cpp vertex.cpp hash.cpp neighbors.cpp schedulingAlgorithms.cpp
- The command uses 1.cpp, which means Backtracking Scheduling.
- If you want to try a different algorithm, replace 1.cpp with 2.cpp, 3.cpp, etc.
4) Run the executable using:./exam_scheduler < complete.ip>complete.op
  - The command directly takes input from a file called complete.ip, so you don't need to enter input manually.
  - If you want to test with different cases, such as a bipartite graph or a tree, you can change the input file or enter input manually.
The output will be saved in a file with the .op extension.
