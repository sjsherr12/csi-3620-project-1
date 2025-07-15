#include "Packet.h"
    
Packet::Packet(int newKey, int newLength){
    key = newKey;
    length = newLength;
}

Packet::Packet() {
    key = 0;
    length = 0;
}

int Packet::getKey() const {
    return key;
}

void Packet::setKey(int newKey){
    key = newKey;
}

int Packet::getLength() const {
    return length;
}

void Packet::setLength(int newLength){
    length = newLength;
}