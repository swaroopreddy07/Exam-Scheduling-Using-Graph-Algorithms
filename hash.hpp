#ifndef HASH_HPP
#define HASH_HPP

#include "vertex.hpp"
#include "edge.hpp"
#include <bits/stdc++.h>
using namespace std;

/****************************************************************************/


class HashTable {
public:
    HashTable(int size);
    void insert(const string& key, int value);
    vector<int>* get(const string& key);
private:
    int hashFunction(const string& key);
    int tableSize;
    vector<list<pair<string, vector<int>>>> table;
};

class hashTable {
public:
    hashTable(int size);
    void insert(int key);
    bool exists(int key); // New method for existence checking
private:
    int hashFunction(int key);
    int tableSize;
    vector<list<int>> table; // Each slot is a list for separate chaining
};


#endif
