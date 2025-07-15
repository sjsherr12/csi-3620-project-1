#ifndef HASHTABLE_NIDS_H
#define HASHTABLE_NIDS_H

#include <vector>
#include <list>
#include "Packet.h"

using namespace std;

class HashTableNIDS{
private:
    vector<list<Packet>> table;
    int tableSize;
    int hashFunction(int key) const;
public:
    HashTableNIDS(int size);
    HashTableNIDS();
    void insert(const Packet& packet);
    Packet* find(int key);
    void remove(int key);
    void reassemble();
};

#endif