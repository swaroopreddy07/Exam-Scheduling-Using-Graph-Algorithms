#include <iostream>
#include <vector>
#include <chrono> // Include chrono for timing
#include "graph.hpp"
#include "hash.hpp"
using namespace std;

int main() {
    const int initialTableSize = 1000;
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
                hashTable studentTable(studentsI->size());
                for (int studentI : *studentsI) {
                    studentTable.insert(studentI);
                }
                for (int studentJ : *studentsJ) {
                    if (studentTable.exists(studentJ)) {
                        conflict = true;
                        break;
                    }
                }
            }

            if (conflict) {
                G1->addEdge(i, j);
                G2->addEdge(i, j);
                G3->addEdge(i, j);
            }
        }
    }

    // Perform Tabu Search Scheduling on each graph representation with timing
    cout << "************** TABU SEARCH SCHEDULING **************\n";

    cout << "************** EDGELIST REPRESENTATION **************\n";
    auto start = chrono::high_resolution_clock::now();
    G1->tabuSearchScheduling(numSubjectsInput, subjects);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time taken by Tabu Search Scheduling for EdgeList: " << duration << " ms\n";

    cout << "\n************** ADJLIST REPRESENTATION **************\n";
    start = chrono::high_resolution_clock::now();
    G2->tabuSearchScheduling(numSubjectsInput, subjects);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time taken by Tabu Search Scheduling for AdjList: " << duration << " ms\n";

    cout << "\n************** ADJMATRIX REPRESENTATION **************\n";
    start = chrono::high_resolution_clock::now();
    G3->tabuSearchScheduling(numSubjectsInput, subjects);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time taken by Tabu Search Scheduling for AdjMatrix: " << duration << " ms\n";

    // Clean up
    delete G1;
    delete G2;
    delete G3;

    return 0;
}
