#include "BinaryTreeNIDS.h"
#include "Packet.h"
#include "Timer.h"
#include <iostream>

using namespace std;

BinaryTreeNIDS::BinaryTreeNIDS(){
    root = nullptr;
}

void BinaryTreeNIDS::insert(const Packet& packet){
    Timer timer;
    timer.start();
    double elapsed = 0;

    if(root == nullptr){
        root = new Node(packet);
        elapsed = timer.stop();
        cout << "BinaryTreeNIDS::insert() took " << elapsed << " ms." << endl;
        return;
    }
    Node* current = root;
    Node* parent = nullptr;
    while(current != nullptr){
        parent = current;
        if(packet.getKey() < current->data.getKey()){
            current = current->left;
        }
        else if(packet.getKey() > current->data.getKey()){
            current = current->right;
        }
        else{
            elapsed = timer.stop();
            cout << "BinaryTreeNIDS::insert() took " << elapsed << " ms." << endl;
            return;
        }
    }
    if(packet.getKey() < parent->data.getKey()){
        parent->left = new Node(packet);
    }
    else{
        parent->right = new Node(packet);
    }

    elapsed = timer.stop();
    cout << "BinaryTreeNIDS::insert() took " << elapsed << " ms." << endl;
}

Packet* BinaryTreeNIDS::find(int key){
    Timer timer;
    timer.start();
    double elapsed = 0;

    Node* current = root;
    while(current != nullptr){
        if(key < current->data.getKey()){
            current = current->left;
        }
        else if(key > current->data.getKey()){
            current = current->right;
        }
        else{
            elapsed = timer.stop();
            cout << "BinaryTreeNIDS::find() took " << elapsed << " ms." << endl;
            return &(current->data);
        }
    }

    elapsed = timer.stop();
    cout << "BinaryTreeNIDS::find() took " << elapsed << " ms." << endl;
    return nullptr;
}

void BinaryTreeNIDS::remove(int key){
    Timer timer;
    timer.start();
    double elapsed = 0;

    if(root == nullptr){
        elapsed = timer.stop();
        cout << "BinaryTreeNIDS::remove() took " << elapsed << " ms." << endl;
        return;
    }
    Node* current = root;
    Node* parent = nullptr;
    while(current != nullptr && current->data.getKey() != key){
        parent = current;
        if(key < current->data.getKey()){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }
    if(current != nullptr){
        if(current->left == nullptr && current->right == nullptr){
            if(parent == nullptr){
                root = nullptr;
            }
            else if(parent->left == current){
                parent->left = nullptr;
            }
            else{
                parent->right = nullptr;
            }
            delete current;
        }
        else if(current->left == nullptr || current->right == nullptr){
            Node* child = (current->left != nullptr) ? current->left : current->right;
            if(parent == nullptr){
                root = child;
            }
            else if(parent->left == current){
                parent->left = child;
            }
            else{
                parent->right = child;
            }
            delete current;
        }
        else{
            Node* successorParent = current;
            Node* successor = current->right;
            while(successor->left != nullptr){
                successorParent = successor;
                successor = successor->left;
            }
            current->data = successor->data;
            Node* child = successor->right;
            if(successorParent->left == successor){
                successorParent->left = child;
            }
            else{
                successorParent->right = child;
            }
            delete successor;
        }
    }

    elapsed = timer.stop();
    cout << "BinaryTreeNIDS::remove() took " << elapsed << " ms." << endl;
}

void BinaryTreeNIDS::reassemble(){
    Timer timer;
    timer.start();

    reassemble(root);

    double elapsed = timer.stop();
    cout << "BinaryTreeNIDS::reassemble() took " << elapsed << " ms." << endl;
}

void BinaryTreeNIDS::reassemble(Node* node){
    if(node == nullptr) return;
    reassemble(node->left);
    bool merged = true;
    while(merged){
        merged = false;
        int nextKey = node->data.getKey() + node->data.getLength();
        Packet* nextPacket = find(nextKey);
        if(nextPacket != nullptr){
            node->data.setLength(node->data.getLength() + nextPacket->getLength());
            remove(nextKey);
            merged = true;
        }
    }
    reassemble(node->right);
}