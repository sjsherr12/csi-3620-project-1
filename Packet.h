#ifndef PACKET_H
#define PACKET_H

class Packet {
private:
    int key;
    int length;
public:
    Packet(int newKey, int newLength);
    Packet();

    int getKey() const;
    void setKey(int newKey);

    int getLength() const;
    void setLength(int newLength);
};

#endif