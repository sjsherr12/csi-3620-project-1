#include "HashTableNIDS.h"
#include "Packet.h"
#include "Timer.h"
#include <iostream>

using namespace std;

int HashTableNIDS::hashFunction(int key) const{
    return key % tableSize;
}

HashTableNIDS::HashTableNIDS(int size){
    table.resize(size);
    tableSize = size;
}

HashTableNIDS::HashTableNIDS(){
    tableSize = 10;
    table.resize(tableSize);
}

void HashTableNIDS::insert(const Packet& packet){
    Timer timer;
    timer.start();
    double elapsed = 0;

    int index = hashFunction(packet.getKey());

    for(Packet& p : table[index]){
        if(p.getKey() == packet.getKey()){
            elapsed = timer.stop();
            cout << "HashTableNIDS::insert() took " << elapsed << " ms." << endl;
            return;
        }
    }

    table[index].push_back(packet);

    elapsed = timer.stop();
    cout << "HashTableNIDS::insert() took " << elapsed << " ms." << endl;
}

Packet* HashTableNIDS::find(int key){
    Timer timer;
    timer.start();
    double elapsed = 0;

    int index = hashFunction(key);
    for(Packet& p : table[index]){
        if(p.getKey() == key){
            elapsed = timer.stop();
            cout << "HashTableNIDS::find() took " << elapsed << " ms." << endl;
            return &p;
        }
    }

    elapsed = timer.stop();
    cout << "HashTableNIDS::find() took " << elapsed << " ms." << endl;
    return nullptr;
}

void HashTableNIDS::remove(int key){
    Timer timer;
    timer.start();

    int index = hashFunction(key);
    auto it = table[index].begin();
    while(it != table[index].end()){
        if(it->getKey() == key){
            it = table[index].erase(it);
            break;
        }
        else{
            ++it;
        }
    }

    double elapsed = timer.stop();
    cout << "HashTableNIDS::remove() took " << elapsed << " ms." << endl;
}

void HashTableNIDS::reassemble(){
    Timer timer;
    timer.start();

    for(int i = 0; i < tableSize; ++i){
        for(auto it = table[i].begin(); it != table[i].end(); ++it){
            bool merged = true;
            while(merged){
                merged = false;
                int nextKey = it->getKey() + it->getLength();
                Packet* nextPacket = find(nextKey);
                if(nextPacket != nullptr){
                    it->setLength(it->getLength() + nextPacket->getLength());
                    remove(nextKey);
                    merged = true;
                }
            }
        }
    }

    double elapsed = timer.stop();
    cout << "HashTableNIDS::reassemble() took " << elapsed << " ms." << endl;
}