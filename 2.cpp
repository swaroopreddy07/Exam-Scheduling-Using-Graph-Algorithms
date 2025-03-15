#include <iostream>
#include <vector>
#include <chrono> 
#include "graph.hpp"
#include "hash.hpp"
using namespace std;

int main() {
    const int initialTableSize = 5000;
    HashTable subjectToStudents(initialTableSize);
    HashTable studentToSubjects(initialTableSize);

    int numSubjectsInput;
    cin >> numSubjectsInput;
    vector<string> subjects(numSubjectsInput);

    // Input subject names and their student roll numbers
    for (int i = 0; i < numSubjectsInput; i++) {
        cin >> subjects[i];
        int numStudents;
        cin >> numStudents;

        for (int j = 0; j < numStudents; j++) {
            int studentID;
            cin >> studentID;
            subjectToStudents.insert(subjects[i], studentID);           
        }
    }

    // Create conflict graphs using different graph representations
    graph* G1 = new edgeListGraph(numSubjectsInput);
    graph* G2 = new adjListGraph(numSubjectsInput);
    graph* G3 = new adjMatrixGraph(numSubjectsInput);

    // Build conflict graphs based on common students
    for (int i = 0; i < numSubjectsInput; i++) {
        for (int j = i + 1; j < numSubjectsInput; j++) {
            const string& subjectI = subjects[i];
            const string& subjectJ = subjects[j];

            // Get the student lists for both subjects
            vector<int>* studentsI = subjectToStudents.get(subjectI);
            vector<int>* studentsJ = subjectToStudents.get(subjectJ);

            bool conflict = false;
            if (studentsI && studentsJ) {
                // Create a custom hash table to store students in studentsI
                hashTable studentTable(studentsI->size());
                // Insert each student from studentsI into the hash table
                for (int studentI : *studentsI) {
                    studentTable.insert(studentI);
                }
                // Check if any student in studentsJ exists in studentTable
                for (int studentJ : *studentsJ) {
                    if (studentTable.exists(studentJ)) { // Found a common student
                        conflict = true;
                        break;
                    }
                }
            }

            if (conflict) {
                G1->addEdge(i, j);  // Add conflict edge
                G2->addEdge(i, j);  // Add conflict edge
                G3->addEdge(i, j);  // Add conflict edge
            }
        }
    }

    // Call greedyScheduling() for each graph representation with timing
    
    cout << "/**************************** GREEDY SCHEDULING ****************************" << endl;
    cout << "*********************************** EDGELIST ************************************* " << endl;
    auto start = chrono::high_resolution_clock::now();
    G1->greedyScheduling(numSubjectsInput, subjects);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time taken by greedyScheduling for EdgeList: " << duration << " ms" << endl;
    cout << "/*********************************************************/" << endl;

    cout << "/**************************** GREEDY SCHEDULING ****************************" << endl;
    cout << "************************************ ADJLIST *************************************** " << endl;
    start = chrono::high_resolution_clock::now();
    G2->greedyScheduling(numSubjectsInput, subjects);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time taken by greedyScheduling for AdjList: " << duration << " ms" << endl;
    cout << "/*********************************************************/" << endl;

    cout << "/**************************** GREEDY SCHEDULING ****************************" << endl;
    cout << "************************************ ADJMATRIX *************************************** " << endl;
    start = chrono::high_resolution_clock::now();
    G3->greedyScheduling(numSubjectsInput, subjects);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time taken by greedyScheduling for AdjMatrix: " << duration << " ms" << endl;
    cout << "/*********************************************************/" << endl;

    return 0;
}
