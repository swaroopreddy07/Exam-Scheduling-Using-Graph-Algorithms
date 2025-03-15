#include "graph.hpp"
#include <bits/stdc++.h>
using namespace std;




//"**************************** BACK TRACKING SCHEDULING *********************************************************"
/**
 * Function to print all unique exam scheduling solutions with the minimum number of time slots.
 * 
 * @param uniqueSolutions Set of unique solutions, where each solution is a vector of integers
 * representing assigned time slots for each subject.
 * @param numSubjects Total number of subjects.
 * @param subjects Vector containing subject names.
 * @param m Minimum number of time slots required for the exam scheduling.
 */
void printAllSolutions(const set<vector<int>>& uniqueSolutions, int numSubjects, vector<string>& subjects, int m) {
    cout << "Minimum time slots required for exams scheduling (" << m << "):\n";
    cout << "Number of possible exam schedules with minimum time slots: " << uniqueSolutions.size() << endl;

    int solutionCount = 1;
    for (const auto& solution : uniqueSolutions) {
        cout << "Solution " << solutionCount++ << ":\n";  

        for (int c = 1; c <= m; c++) {
            cout << "Time Slot " << c << ": ";
            for (int i = 0; i < numSubjects; i++) {
                if (solution[i] == c) {
                    cout << subjects[i] << " ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

/**
 * Helper function to check if it is safe to assign a time slot (color) to a subject (vertex) in the graph.
 * 
 * @param v Index of the vertex (subject) to be colored.
 * @param G Pointer to the graph object.
 * @param color Array holding the assigned colors (time slots) for each subject.
 * @param c Color (time slot) to be assigned.
 * @return true if the color can be assigned safely, false otherwise.
 */
bool isSafe(int v, graph* G, int color[], int c) {
    vertex* vertV = G->getVertex(v);
    vertexList* neighbors = G->neighbors(vertV);  
    vertexNode* temp = neighbors->getHead();

    while (temp != nullptr) {
        int neighborId = temp->getVertex()->getId();
        if (color[neighborId] == c) 
            return false;
        temp = temp->getNext();
    }
    return true;
}

/**
 * Stores the current color assignment (solution) in a set of unique solutions.
 * 
 * @param color Array representing the assigned colors (time slots) for each subject.
 * @param numSubjects Total number of subjects.
 * @param uniqueSolutions Set to store unique exam schedules (solutions).
 */
void storeSolution(int color[], int numSubjects, set<vector<int>>& uniqueSolutions) {
    vector<int> currentSolution(numSubjects);
    for (int i = 0; i < numSubjects; i++) {
        currentSolution[i] = color[i];
    }
    uniqueSolutions.insert(currentSolution);  
}

/**
 * Recursive utility function to try all possible time slot assignments for exam scheduling (graph coloring).
 * 
 * @param G Pointer to the graph object.
 * @param m Number of available colors (time slots).
 * @param color Array holding the assigned colors (time slots) for each subject.
 * @param v Current vertex (subject) to color.
 * @param numSubjects Total number of subjects.
 * @param uniqueSolutions Set to store unique exam schedules (solutions).
 */
void graphColoringUtil(graph* G, int m, int color[], int v, int numSubjects, set<vector<int>>& uniqueSolutions) {
    if (v == numSubjects) {
        storeSolution(color, numSubjects, uniqueSolutions);  // Store unique solution when all vertices are colored
        return;
    }
    for (int c = 1; c <= m; c++) {
        if (isSafe(v, G, color, c)) {
            color[v] = c;
            graphColoringUtil(G, m, color, v + 1, numSubjects, uniqueSolutions);
            color[v] = 0; 
        }

    }
}

/**
 * Initiates the graph coloring (exam scheduling) process.
 * 
 * @param G Pointer to the graph object.
 * @param m Initial number of colors (time slots) to attempt.
 * @param color Array to store assigned colors for each subject.
 * @param numSubjects Total number of subjects.
 * @param uniqueSolutions Set to store unique exam schedules (solutions).
 * @return true if at least one valid solution exists, false otherwise.
 */
bool graphColoring(graph* G, int m, int color[], int numSubjects, set<vector<int>>& uniqueSolutions) {
    for (int i = 0; i < numSubjects; i++) {
        color[i] = 0;
    }

    uniqueSolutions = set<vector<int>>(); 
    graphColoringUtil(G, m, color, 0, numSubjects, uniqueSolutions);
    
    return uniqueSolutions.size() > 0;
}

/**
 * Main function to find the minimum number of time slots required to schedule all exams
 * without conflicts and to print all possible unique scheduling solutions.
 * 
 * @param numSubjects Total number of subjects.
 * @param subjects Vector containing subject names.
 */
void graph::backTrackScheduling(int numSubjects, vector<string>& subjects) {
    int color[numSubjects];
    int m = 1;
    set<vector<int>> uniqueSolutions;

    while (true) {
        if (graphColoring(this, m, color, numSubjects, uniqueSolutions)) {
            break;
        }
        m++;
    }

    printAllSolutions(uniqueSolutions, numSubjects, subjects, m); 
}

//**************************************** GREEDY SCHEDULING *************************************************************
/**
 * Mark the time slots of neighbors as unavailable
 * @param v The current vertex
 * @param color The color array representing assigned time slots
 * @param available The array marking available time slots
 */
void markUnavailableSlots(vertex* v, vector<int>& color, vector<bool>& available, graph* G) {
    vertexList* neighbors = G->neighbors(v);
    vertexNode* temp = neighbors->getHead();

    while (temp != nullptr) {
        int neighborId = temp->getVertex()->getId();
        if (color[neighborId] != -1) {
            available[color[neighborId]] = true;  // Mark as unavailable
        }
        temp = temp->getNext();
    }
}

/**
 * Reset the availability of time slots after assigning a slot to the current vertex
 * @param v The current vertex
 * @param color The color array representing assigned time slots
 * @param available The array marking available time slots
 */
void resetAvailableSlots(vertex* v, vector<int>& color, vector<bool>& available, graph* G) {
    vertexList* neighbors = G->neighbors(v);
    vertexNode* temp = neighbors->getHead();

    while (temp != nullptr) {
        int neighborId = temp->getVertex()->getId();
        if (color[neighborId] != -1) {
            available[color[neighborId]] = false;  // Reset availability
        }
        temp = temp->getNext();
    }

}

/**
 * Assign the lowest available time slot to the current subject
 * @param available The array marking available time slots
 * @param numSubjects The total number of subjects (vertices)
 * @return The lowest available time slot
 */
int findAvailableSlot(vector<bool>& available, int numSubjects) {
    for (int slot = 1; slot <= numSubjects; slot++) {
        if (!available[slot]) {
            return slot;
        }
    }
    return -1;  // Just a safeguard; this should never be reached
}

/**
 * Print the results of the exam scheduling
 * @param numSubjects The total number of subjects
 * @param subjects The list of subject names
 * @param color The color array representing assigned time slots
 */
void printSchedulingResults(int numSubjects, vector<string>& subjects, vector<int>& color) {
    cout << "\nSubjects scheduled in each time slot: \n";

    int maxSlot = 0;
    for (int i = 0; i < numSubjects; i++) {
        if (color[i] > maxSlot) {
            maxSlot = color[i];
        }
    }
    for (int slot = 1; slot <= maxSlot; slot++) {
        cout << "Time Slot " << slot << ": ";
        for (int i = 0; i < numSubjects; i++) {
            if (color[i] == slot) {
                cout << subjects[i] << " ";
            }
        }
        cout << "\n";
    }
}

/**
 * Greedy algorithm for scheduling exams (graph coloring)
 * Assigns the lowest possible color (time slot) to each subject
 * @param G The conflict graph
 * @param numSubjects The number of subjects (vertices)
 * @param subjects The list of subject names
 */
void graph::greedyScheduling(int numSubjects, vector<string>& subjects) {
    vector<int> color(numSubjects, -1);  // Store time slot (color) for each subject
    vector<bool> available(numSubjects+1, false);  // Mark available time slots for neighbors

    // Assign the first time slot to the first subject
    color[0] = 1;

    // Assign time slots to the remaining subjects
    for (int u = 1; u < numSubjects; u++) {
        vertex* v = getVertex(u);

        // Mark unavailable time slots for the current subject's neighbors
        markUnavailableSlots(v, color, available, this);

        // Find the lowest available time slot for the current subject
        int slot = findAvailableSlot(available, numSubjects);
        color[u] = slot;  // Assign the found time slot

        // Reset the availability of time slots for the next iteration
        resetAvailableSlots(v, color, available, this);
    }

    // Print the results using the new print function
    printSchedulingResults(numSubjects, subjects, color);
}


//**************************** SmallestDegreeLastScheduling**************************************************;
int findNumberOfNeighbors(vertexList* L) {
    vertexNode* temp = L->getHead();
    int count = 0;
    while (temp != nullptr) {
        count++;
        temp = temp->getNext();
    }
    return count;
}


/**
 * Swaps two integer values.
 *
 * @param a Reference to the first integer.
 * @param b Reference to the second integer.
 */
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

/**
 * Partition function for quicksort, used to sort vertices based on degree in descending order.
 *
 * @param sortedVertices Vector of vertices to be sorted by degree.
 * @param degree Vector representing the degree of each vertex.
 * @param low Starting index for the partition.
 * @param high Ending index for the partition.
 * @return The partition index.
 */
int partition(vector<int>& sortedVertices, const vector<int>& degree, int low, int high) {
    int pivot = degree[sortedVertices[high]];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (degree[sortedVertices[j]] > pivot) { // Change here for descending order
            i++;
            swap(sortedVertices[i], sortedVertices[j]);
        }
    }
    swap(sortedVertices[i + 1], sortedVertices[high]);
    return (i + 1);
}

/**
 * Quicksort function to sort vertices based on degree in descending order.
 *
 * @param sortedVertices Vector of vertices to be sorted by degree.
 * @param degree Vector representing the degree of each vertex.
 * @param low Starting index for the sort.
 * @param high Ending index for the sort.
 */
void quickSort(vector<int>& sortedVertices, const vector<int>& degree, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(sortedVertices, degree, low, high);

        quickSort(sortedVertices, degree, low, pivotIndex - 1);
        quickSort(sortedVertices, degree, pivotIndex + 1, high);
    }
}

/**
 * Initializes the degree of each vertex in the graph.
 *
 * @param G Pointer to the graph object.
 * @param degree Vector to store the degree of each vertex.
 * @param numSubjects Total number of subjects (vertices).
 */
void initializeDegrees(graph* G, vector<int>& degree, int numSubjects) {
    for (int i = 0; i < numSubjects; i++) {
        vertex* v = G->getVertex(i);
        degree[i] = findNumberOfNeighbors(G->neighbors(v));
    }
}

/**
 * Sorts vertices by degree in ascending order using quicksort.
 *
 * @param degree Vector representing the degree of each vertex.
 * @param numSubjects Total number of subjects (vertices).
 * @return Vector of vertex indices sorted by degree.
 */
vector<int> sortVerticesByDegree(const vector<int>& degree, int numSubjects) {
    vector<int> sortedVertices(numSubjects);
    for (int i = 0; i < numSubjects; i++) {
        sortedVertices[i] = i;
    }
    quickSort(sortedVertices, degree, 0, numSubjects - 1);
    return sortedVertices;
}

/**
 * Finds the smallest available color that can be assigned to a vertex, ensuring no conflicts.
 *
 * @param G Pointer to the graph object.
 * @param u Index of the vertex to be colored.
 * @param color Vector representing the assigned colors of each vertex.
 * @param numSubjects Total number of subjects (vertices).
 * @return The smallest available color for the vertex.
 */
int findSmallestAvailableColor(graph* G, int u, const vector<int>& color, int numSubjects) {
    vector<bool> available(numSubjects + 1, false);
    vertex* v = G->getVertex(u);
    vertexList* neighborsList = G->neighbors(v);
    vertexNode* temp = neighborsList->getHead();

    while (temp != nullptr) {
        int neighborId = temp->getVertex()->getId();
        if (color[neighborId] != -1) {
            available[color[neighborId]] = true;
        }
        temp = temp->getNext();
    }

    for (int colorChoice = 1; colorChoice <= numSubjects; colorChoice++) {
        if (!available[colorChoice]) {
            return colorChoice;
        }
    }
    return 1;
}

/**
 * Main scheduling function using the Smallest Degree Last heuristic.
 *
 * @param numSubjects Total number of subjects (vertices).
 * @param subjects Vector containing the names of each subject.
 */
void graph::SmallestDegreeLastScheduling(int numSubjects, vector<string>& subjects) {
    vector<int> color(numSubjects, -1);
    vector<int> degree(numSubjects, 0);

    initializeDegrees(this, degree, numSubjects);

    vector<int> sortedVertices = sortVerticesByDegree(degree, numSubjects);

    for (int u : sortedVertices) {
        color[u] = findSmallestAvailableColor(this, u, color, numSubjects);
    }

    printSchedulingResults(numSubjects, subjects, color);
}




/**********************************************************************************************************/


 //***************************************** DSATURScheduling *********************************************

/**
 * Finds the number of neighbors (degree) of a vertex (subject).
 *
 * @param L Pointer to the vertex list (neighbor list) of the subject.
 * @return The number of neighbors (degree) of the subject.
 */
// int findNumberOfNeighbors(vertexList* L) {
//     vertexNode* temp = L->getHead();
//     int count = 0;
//     while (temp != nullptr) {
//         count++;
//         temp = temp->getNext();
//     }
//     return count;
// }




/**
 * Initializes the degree of each vertex (subject) by counting the number of conflicts (edges).
 *
 * @param numSubjects Total number of subjects.
 * @param degree Vector to store the degree (number of neighbors) of each subject.
 * @param G Reference to the graph object.
 */
void initializeDegrees(int numSubjects, vector<int>& degree, graph& G) {
    for (int i = 0; i < numSubjects; i++) {
        vertex* v = G.getVertex(i);
        degree[i] = findNumberOfNeighbors(G.neighbors(v));
    }
}

/**
 * Finds the vertex with the highest saturation degree and degree.
 * Saturation degree is the number of different colors among the neighbors.
 *
 * @param color Vector indicating the assigned colors for each subject (-1 if uncolored).
 * @param saturation Vector indicating the saturation degree for each subject.
 * @param degree Vector indicating the degree (number of neighbors) for each subject.
 * @param numSubjects Total number of subjects.
 * @return Index of the vertex with the highest saturation degree (or degree if tied).
 */
int getHighestSaturation(const vector<int>& color, const vector<int>& saturation, const vector<int>& degree, int numSubjects) {
    int maxSaturation = -1, maxDegree = -1, chosenVertex = -1;
    for (int i = 0; i < numSubjects; i++) {
        if (color[i] == -1) {
            if (saturation[i] > maxSaturation || (saturation[i] == maxSaturation && degree[i] > maxDegree)) {
                maxSaturation = saturation[i];
                maxDegree = degree[i];
                chosenVertex = i;
            }
        }
    }
    return chosenVertex;
}

/**
 * Updates the saturation degree of the neighbors of a given vertex.
 *
 * @param u Index of the vertex whose neighbors' saturation degrees will be updated.
 * @param saturation Vector indicating the saturation degree for each subject.
 * @param G Reference to the graph object.
 * @param color Vector indicating the assigned colors for each subject (-1 if uncolored).
 */
void updateSaturation(int u, vector<int>& saturation, graph& G, const vector<int>& color) {
    vertex* v = G.getVertex(u);
    vertexList* neighborsList = G.neighbors(v);
    vertexNode* temp = neighborsList->getHead();
    
    while (temp != nullptr) {
        int neighborId = temp->getVertex()->getId();
        if (color[neighborId] == -1) {
            saturation[neighborId]++;
        }
        temp = temp->getNext();
    }
}

/**
 * Finds the lowest available color (time slot) for a vertex, ensuring no conflicts.
 *
 * @param u Index of the vertex for which an available color is sought.
 * @param color Vector indicating the assigned colors for each subject (-1 if uncolored).
 * @param G Reference to the graph object.
 * @param numSubjects Total number of subjects.
 * @return The smallest available color (time slot) for the vertex.
 */
int getAvailableColor(int u, const vector<int>& color, graph& G, int numSubjects) {
    vector<bool> available(numSubjects + 1, false);
    vertex* v = G.getVertex(u);
    vertexList* neighborsList = G.neighbors(v);
    vertexNode* temp = neighborsList->getHead();

    while (temp != nullptr) {
        int neighborId = temp->getVertex()->getId();
        if (color[neighborId] != -1) {
            available[color[neighborId]] = true;
        }
        temp = temp->getNext();
    }

    int colorChoice;
    for (colorChoice = 1; colorChoice <= numSubjects; colorChoice++) {
        if (!available[colorChoice]) {
            break;
        }
    }
    return colorChoice;
}

/**
 * Main DSATUR (Degree of Saturation) scheduling function.
 * This algorithm assigns time slots to subjects using a saturation-based heuristic.
 *
 * @param numSubjects Total number of subjects.
 * @param subjects Vector containing subject names.
 */
void graph::DSATURScheduling(int numSubjects, vector<string>& subjects) {
    vector<int> color(numSubjects, -1);
    vector<int> degree(numSubjects, 0);
    vector<int> saturation(numSubjects, 0);

    initializeDegrees(numSubjects, degree, *this);

    int u = getHighestSaturation(color, saturation, degree, numSubjects);
    color[u] = 1;

    for (int count = 1; count < numSubjects; count++) {
        updateSaturation(u, saturation, *this, color);
        u = getHighestSaturation(color, saturation, degree, numSubjects);
        int colorChoice = getAvailableColor(u, color, *this, numSubjects);
        color[u] = colorChoice;
    }

    printSchedulingResults(numSubjects, subjects, color);
}

/*******************************************************************************************************************/


//************************************ TABU SEARCH SCHEDULING *****************************************************

// Utility function to calculate conflicts based on a schedule using graph neighbors directly
int calculateConflicts(graph* g, const vector<int>& schedule) {
    int conflicts = 0;

  
    for (int i = 0; i < schedule.size(); ++i) {
        vertex* vert = g->getVertex(i);
        vertexList* neighborList = g->neighbors(vert);
        vertexNode* neighborNode = neighborList->getHead();

        while (neighborNode != nullptr) {
            int neighborId = neighborNode->getVertex()->getId();
            if (schedule[i] == schedule[neighborId]) {
                conflicts++;
            }
            neighborNode = neighborNode->getNext();
        }
        delete neighborList;
    }

    return conflicts / 2;
}

// Tabu Search Scheduling Algorithm

bool isTabu(const deque<vector<int>>& tabuList, const vector<int>& solution) {
    for (const auto& tabuSolution : tabuList) {
        if (tabuSolution == solution) {
            return true;
        }
    }
    return false;
}

vector<int> tabuSearch(graph* g, int numExams, int numSlots, int maxIterations, int tabuTenure) {
    vector<int> bestSolution(numExams, 0);
    vector<int> currentSolution = bestSolution;
    int bestConflicts = calculateConflicts(g, bestSolution);
    deque<vector<int>> tabuList;
 
    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        vector<int> bestNeighbor = currentSolution;
        int bestNeighborConflicts = numeric_limits<int>::max();

      
        for (int exam = 0; exam < numExams; exam++) {
            int originalSlot = currentSolution[exam];
            for (int newSlot = 0; newSlot < numSlots; newSlot++) {
                if (newSlot == originalSlot) continue;
 
                currentSolution[exam] = newSlot;
                int conflicts = calculateConflicts(g, currentSolution);

             
                if (!isTabu(tabuList, currentSolution) || (conflicts < bestConflicts)) {
                    if (conflicts < bestNeighborConflicts) {
                        bestNeighbor = currentSolution;
                        bestNeighborConflicts = conflicts;
                    }
                }
            }  
            currentSolution[exam] = originalSlot; 
        }

        currentSolution = bestNeighbor;
        tabuList.push_back(bestNeighbor);

       
        if (tabuList.size() > tabuTenure) {
            tabuList.pop_front();
        }

    
        if (bestNeighborConflicts < bestConflicts) {
            bestSolution = bestNeighbor;
            bestConflicts = bestNeighborConflicts;
        }

      
        if (bestConflicts == 0) {
            break;
        }
    }

    return bestSolution;
}


// Print function to display the scheduling solution with only non-empty slots
void printSchedule(vector<int>& schedule, int numSlots, vector<string>& subjects) {
    cout << "Solution with " << numSlots << " time slots:\n";
    for (int slot = 0; slot < numSlots; slot++) {
        bool slotHasExams = false;
        for (int exam = 0; exam < subjects.size(); exam++) {
            if (schedule[exam] == slot) {
                if (!slotHasExams) {
                    cout << "Time Slot " << slot + 1 << ": ";
                    slotHasExams = true;
                }
                cout << subjects[exam] << " ";
            }
        }
        if (slotHasExams) cout << endl; 
    }
}
 
// Tabu Search Scheduling for each graph type
void graph::tabuSearchScheduling(int numSubjects,  vector<string>& subjects) {
    int maxIterations = 100;
    int tabuTenure = 100;
    int minSlotsUsed = numSubjects;


    bool solutionFound = false;
    for (int numSlots = 1; numSlots <= numSubjects; ++numSlots) {
        vector<int> bestSchedule = tabuSearch(this, numSubjects, numSlots, maxIterations, tabuTenure);
        int conflicts = calculateConflicts(this, bestSchedule);

        if (conflicts == 0) {
            minSlotsUsed = numSlots;
            printSchedule(bestSchedule, minSlotsUsed, subjects);
            solutionFound = true;
            break; 
        }
    }

    if (!solutionFound) {
        cout << "No feasible solution found with the current Tabu Search configuration.\n";
    }
}