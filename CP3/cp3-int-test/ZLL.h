#ifndef ZLL_H
#define ZLL_H
#include <iostream>
#include <string>

#include "zany.h"
using namespace std;

template<typename T>
class ZLL
{
    private:
        //template<typename T>
        struct Node 
        {
            T data;
            Node* next;
            Node* prev;
            Node(const T& value)
            {
                data = value;
                next = nullptr;
                prev = nullptr;
            }
        };

        Node* head;
        Node* tail;
        Node* current;
        int size;

    public:

        ZLL();
        //Node(const T& value);
        ~ZLL();
        
        bool front(const T &value);
        bool back(const T &value);
        bool join(ZLL &other);
        ZLL &operator+=(const ZLL &other);
        ZLL &operator-=(const ZLL &other);
        int removeZany();
        int removeNonZany();
        bool promoteZany();
        bool start();
        bool done();
        bool isEmpty();
        bool empty();
        T getNext();
};
#include "ZLL.cpp"
#endif 