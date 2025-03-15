#include <iostream>
#include <vector>
#include <chrono>
#include "graph.hpp"
#include "hash.hpp"
using namespace std;

int main() {
    const int initialTableSize = 1000;
    HashTable subjectToStudents(initialTableSize);

    int numSubjectsInput;
    cin >> numSubjectsInput;
    vector<string> subjects(numSubjectsInput);

    // Input subjects and student IDs
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

    // Create three graph representations
    graph* G1 = new edgeListGraph(numSubjectsInput);
    graph* G2 = new adjListGraph(numSubjectsInput);
    graph* G3 = new adjMatrixGraph(numSubjectsInput);

    // Populate graphs with conflict edges
    for (int i = 0; i < numSubjectsInput; i++) {
        for (int j = i + 1; j < numSubjectsInput; j++) {
            const string& subjectI = subjects[i];
            const string& subjectJ = subjects[j];

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

    // Measure and print time taken by backtracking scheduling for each representation
    chrono::duration<double, milli> edgeListTime, adjListTime, adjMatrixTime;

    cout << "\n/**************************** BACK TRACKING SCHEDULING ****************************" << endl;

    cout << "*********************************** EDGELIST ************************************* " << endl;
    auto start = chrono::high_resolution_clock::now();
    G1->backTrackScheduling(numSubjectsInput, subjects);
    auto end = chrono::high_resolution_clock::now();
    edgeListTime = end - start;
    cout << "Time taken by EDGELIST backTrackScheduling: " << edgeListTime.count() << " milliseconds" << endl;
    cout << "/*/" << endl;

    cout << "************************************ ADJLIST *************************************** " << endl;
    start = chrono::high_resolution_clock::now();
    G2->backTrackScheduling(numSubjectsInput, subjects);
    end = chrono::high_resolution_clock::now();
    adjListTime = end - start;
    cout << "Time taken by ADJLIST backTrackScheduling: " << adjListTime.count() << " milliseconds" << endl;
    cout << "/*/" << endl;

    cout << "************************************ ADJMATRIX *************************************** " << endl;
    start = chrono::high_resolution_clock::now();
    G3->backTrackScheduling(numSubjectsInput, subjects);
    end = chrono::high_resolution_clock::now();
    adjMatrixTime = end - start;
    cout << "Time taken by ADJMATRIX backTrackScheduling: " << adjMatrixTime.count() << " milliseconds" << endl;
    cout << "/*/" << endl;

    // Print summary of times
    cout << "\n/**************************** SUMMARY OF EXECUTION TIMES ****************************" << endl;
    cout << "Edge List Graph: " << edgeListTime.count() << " milliseconds" << endl;
    cout << "Adjacency List Graph: " << adjListTime.count() << " milliseconds" << endl;
    cout << "Adjacency Matrix Graph: " << adjMatrixTime.count() << " milliseconds" << endl;
    cout << "/*/" << endl;

    return 0;
}