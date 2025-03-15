// Implementation of the HashTable class
#include "hash.hpp"


HashTable::HashTable(int size) : tableSize(size) {
    table.resize(size);
}

int HashTable::hashFunction(const string& key) {
    int hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + ch) % tableSize;
    }
    return hash;
}

void HashTable::insert(const string& key, int value) {
    int index = hashFunction(key);
    for (auto& pair : table[index]) {
        if (pair.first == key) {
            pair.second.push_back(value);
            return;
        }
    }
    table[index].emplace_back(key, vector<int>{value});
}

vector<int>* HashTable::get(const string& key) {
    int index = hashFunction(key);
    for (auto& pair : table[index]) {
        if (pair.first == key) {
            return &pair.second;
        }
    }
    return nullptr;
}

//******************************************************************* */


// Constructor for HashTable
hashTable::hashTable(int size) : tableSize(size) {
    table.resize(size);
}

// Simple hash function for integers
int hashTable::hashFunction(int key) {
    return key % tableSize;
}

// Insert a value into the hash table
void hashTable::insert(int key) {
    int index = hashFunction(key);
    for (int val : table[index]) {
        if (val == key) return; // Avoid duplicate entries
    }
    table[index].push_back(key);
}

// Check if a value exists in the hash table
bool hashTable::exists(int key) {
    int index = hashFunction(key);
    for (int val : table[index]) {
        if (val == key) return true;
    }
    return false;
}