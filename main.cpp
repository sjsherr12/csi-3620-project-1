#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Packet.h"
#include "HashTableNIDS.h"
#include "BinaryTreeNIDS.h"

using namespace std;


vector<Packet> generateRandomPackets(int count, int keyMin, int keyMax, int lenMin, int lenMax){
    vector<Packet> packets;
    for (int i = 0; i < count; ++i) {
        int key = rand() % (keyMax - keyMin + 1) + keyMin;
        int len = rand() % (lenMax - lenMin + 1) + lenMin;
        packets.emplace_back(key, len);
    }
    return packets;
}

int main(){
    srand(time(0));

    int numPackets = 100;
    vector<Packet> packets = generateRandomPackets(numPackets, 0, 1000, 1, 100);

    HashTableNIDS hashNIDS(500);
    BinaryTreeNIDS treeNIDS;

    cout << "--------Initiating insert sequence for hash table-------" << endl;
    for(const Packet& p : packets){
        hashNIDS.insert(p);
    }

    cout << "--------Initiating insert sequence for binary tree-------" << endl;
    for(const Packet& p : packets){
        treeNIDS.insert(p);
    }

    vector<int> testKeys = {20, 40, 80, 160, 320, 640, 720, 831, 903, 994};

    cout << "--------Testing find method for hash table----------" << endl;
    for(int key : testKeys){
        Packet* foundHash = hashNIDS.find(key);
        if(foundHash != nullptr){
            cout << "Found key of " << key << " in hash table with packet length of " << foundHash->getLength() << endl;
        } else{
            cout << "Couldn't find key of " << key << " in hash table" << endl;
        }
    }

    cout << "--------Testing find method for both binary tree----------" << endl;
    for(int key : testKeys){
        Packet* foundTree = treeNIDS.find(key);
        if(foundTree != nullptr){
            cout << "Found key of " << key << " in binary tree with packet length of " << foundTree->getLength() << endl;
        } else{
            cout << "Couldn't find key of " << key << " in binary tree" << endl;
        }
    }

    cout << "--------Testing remove method for hash table----------" << endl;
    vector<int> removeKeys = {831, 903, 994};
    for(int key : removeKeys){
        cout << "Removing key " << key << " from hash table..." << endl;
        hashNIDS.remove(key);
        Packet* foundHash = hashNIDS.find(key);
        if(foundHash == nullptr){
            cout << "Confirmed key " << key << " was removed from hash table." << endl;
        } else {
            cout << "Key " << key << " still exists in hash table!" << endl;
        }
    }
    
    cout << "--------Testing remove method for binary tree----------" << endl;
    for(int key : removeKeys){
        cout << "Removing key " << key << " from binary tree..." << endl;
        treeNIDS.remove(key);
        Packet* foundTree = treeNIDS.find(key);
        if(foundTree == nullptr){
            cout << "Confirmed key " << key << " was removed from binary tree." << endl;
        } else {
            cout << "Key " << key << " still exists in binary tree!" << endl;
        }
    }

    cout << "--------Testing reassemble method for hash table----------" << endl;

    HashTableNIDS reassembleHashNIDS(3);

    reassembleHashNIDS.insert(Packet(10, 10));
    reassembleHashNIDS.insert(Packet(20, 10));
    reassembleHashNIDS.insert(Packet(30, 5));

    Packet* reassembleHash30Found = reassembleHashNIDS.find(30);
    cout << "Found key of 30 in hash table with length " << reassembleHash30Found->getLength() << endl;
    cout << "Now initiating reassemble method for hash table" << endl;
    reassembleHashNIDS.reassemble();
    Packet* reassembleHashNIDS10 = reassembleHashNIDS.find(10);
    cout << "Now, found key of 10 in reassembled hash table with length " << reassembleHashNIDS10->getLength() << endl;

    cout << "--------Testing reassemble method for binary tree----------" << endl;

    BinaryTreeNIDS reassembleTreeNIDS;

    reassembleTreeNIDS.insert(Packet(10, 10));
    reassembleTreeNIDS.insert(Packet(20, 10));
    reassembleTreeNIDS.insert(Packet(30, 5));

    Packet* reassembleTree30Found = reassembleTreeNIDS.find(30);
    cout << "Found key of 30 in binary tree with length " << reassembleTree30Found->getLength() << endl;
    cout << "Now initiating reassemble method for binary tree" << endl;
    reassembleTreeNIDS.reassemble();
    Packet* reassembleTreeNIDS10 = reassembleTreeNIDS.find(10);
    cout << "Now, found key of 10 in reassembled binary tree with length " << reassembleTreeNIDS10->getLength() << endl;

    
    return 0;
}