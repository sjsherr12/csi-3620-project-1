#ifndef BINARYTREE_NIDS_H
#define BINARYTREE_NIDS_H

#include <vector>
#include "Packet.h"

class Node{
public:
    Packet data;
    Node* left;
    Node* right;

    Node(const Packet& packet){
        data = packet;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTreeNIDS{
private:
    Node* root;
    void reassemble(Node* node);
public:
    BinaryTreeNIDS();
    void insert(const Packet& packet);
    Packet* find(int key);
    void remove(int key);
    void reassemble();
};

#endif