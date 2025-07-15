#include "HashTableNIDS.h"
#include "Packet.h"

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
    int index = hashFunction(packet.getKey());

    for(Packet& p : table[index]){
        if(p.getKey() == packet.getKey()){
            return;
        }
    }

    table[index].push_back(packet);
}

Packet* HashTableNIDS::find(int key){
    int index = hashFunction(key);
    for(Packet& p : table[index]){
        if(p.getKey() == key){
            return &p;
        }
    }
    return nullptr;
}

void HashTableNIDS::remove(int key){
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
}

void HashTableNIDS::reassemble(){
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
}