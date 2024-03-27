#include <iostream>
#include <string>

//#include "zany.h"

using namespace std;

// CONSTRUCTOR/DESTRUCTOR

template<typename T>
ZLL<T>::ZLL()
{
    head = nullptr;
    tail = nullptr;
    current = nullptr;
    size = 0;
};

template<typename T>
ZLL<T>::~ZLL() 
{
    empty();
};


// FUNCTION DEFINITIONS

template<typename T>
bool ZLL<T>::front(const T &value)
{
    Node* node = new Node(value);
    //if the node is not valid, return false
    if (node == nullptr) 
    {
        return false;
    }
    //if the head is a nullptr then the list is empty and the new node becems both the head and tail
    if (head == nullptr) 
    {
        head = tail = node;
    }
    //else the nodes next pointer is the head of this and the head's previous node is the new node
    else 
    {
        node->next = head; 
        head->prev = node;
        head = node; //the new head is now the node
    }
    size++;
    return true;
};

template<typename T>
bool ZLL<T>::back(const T &value)
{
    Node* node = new Node(value);
    if (node == nullptr) 
    {
        return false;
    }
    //if the list is empty make the head and tail equal to the new node
    if (tail == nullptr) 
    {
        tail = head = node;
        //node->prev = nullptr;
        //node->next = nullptr;
    }
    else 
    {
        tail->next = node; 
        node->prev = tail;
        //node->next = nullptr;
        tail = node;

    }
    size++;
    return true;
};

template<typename T>
bool ZLL<T>::join(ZLL &other)
{
    //if the 2 lists are the same then return true
    if (this == &other) 
    {
        return true;
    }
    //if the other list is null return true
    if (other.head == nullptr) 
    {
        return true;
    }
    //if this list is null then make this list equal to the other list by setting the heads and tails
    if (head == nullptr) 
    {
        head = other.head;
        tail = other.tail;
    }
    //else the head of the other gets added to the tail of this one and the previous of the other is now the tail of the current
    else 
    {
        tail->next = other.head;
        other.head->prev = tail;
        tail = other.tail; //this tail is now the other tail
    }
    size += other.size;
    other.head = other.tail = nullptr; //reset other to a null list
    other.size = 0;
    return true;
};

template<typename T>
ZLL<T>& ZLL<T>::operator+=(const ZLL &other)
{
    // cannot call list += list
    if (this == &other) 
    {
        return *this;
    }
    
    // if the current list is empty, set its head and tail to other's head and tail
    Node* temp = other.head;
    while(temp != nullptr)
    {
        this->back(temp->data);
        temp = temp->next;
    }
    
    return *this;
};


template<typename T>
ZLL<T>& ZLL<T>::operator-=(const ZLL &other)
{
    // cannot do list -= list
    if (this == &other) 
    {
        return *this;
    }

    // iterate over the elements in the other list and remove any matching elements from this list
    Node* current = head;
    while (current != nullptr) 
    {
        Node* otherCurrent = other.head;
        bool foundMatch = false;
        while (otherCurrent != nullptr)
        {
            if (current->data == otherCurrent->data)
            {
                foundMatch = true;
                break;
            }
            otherCurrent = otherCurrent->next;
        }
        if (foundMatch)
        {
            // remove the current node from this list
            if (current == head)
            {
                head = current->next;
            }
            if (current == tail)
            {
                tail = tail->prev;
            }
            if (current->prev != nullptr)
            {
                current->prev->next = current->next;
            }
            if (current->next != nullptr)
            {
                current->next->prev = current->prev;
            }

            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        else
        {
            current = current->next;
        }
    }
    return *this;
};

template<typename T>
int ZLL<T>::removeZany()
{
    int count = 0;
    Node* current = head;
    while (current != nullptr) 
    {
        Node* temp = current->next;
        //if the current data is odd
        if (isZany(current->data)) 
        {
            //if the the current value is the head
            if (current == head) 
            {
                head = current->next;
                //if the new head is not the nullptr then make the zany value a nullptr
                if (head != nullptr) 
                {
                    head->prev = nullptr;
                }
            } 
            else 
            {
                current->prev->next = current->next;            //get the previous node's pointer to next and point it at the current node's next
                //if the current node is not the last node
                if (current->next != nullptr) 
                {
                    current->next->prev = current->prev;        //set the next node's pointer to previous and point it at the current node's previous
                } 
                //the current node is the last node
                else 
                {
                    tail = current->prev;                       //the previous node is the tail
                }
            }
            delete current;
            count++;
        }
        current = temp;
    }
    return count;
};

template<typename T>
int ZLL<T>::removeNonZany()
{
    int count = 0;
    Node* current = head;
    while (current != nullptr) 
    {
        //if the node is even
        if (!isZany(current->data)) 
        {
            //remove current node
            if (current == head) 
            {
                head = current->next;
                //if the new head is not the nullptr then make the even value a nullptr
                if (head != nullptr)
                { 
                    head->prev = nullptr;
                }
                //If the new head is not null update the previous pointer to null
                else 
                {
                    tail = nullptr;
                }
            }
            else if (current == tail) 
            {
                tail = current->prev;
                tail->next = nullptr;
            }
            //set the previous node's next pointer to the current next node and the next nodes previous pointer to the current previous node
            else 
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            Node* temp = current;
            current = current->next;
            delete temp;
            ++count;
        }
        else 
        {
            current = current->next;
        }
    }
    return count;
};

template<typename T>
bool ZLL<T>::promoteZany()
{
    // list is empty or has only one node
    if (head == nullptr || head == tail) 
    { 
        return false;
    }
    
    // create a new list to hold the zany nodes
    Node* zanyHead = nullptr;
    Node* zanyTail = nullptr;
    Node* nonZanyHead = nullptr;
    Node* nonZanyTail = nullptr;
    
    Node* current = head;
    //loop through the list
    while (current != nullptr) 
    {
        Node* next = current->next;
        if (isZany(current->data)) 
        {
            // move current zany node to the front of the zany list
            current->prev = nullptr;
            current->next = zanyHead;
            if (zanyHead != nullptr) 
            {
                zanyHead->prev = current;
            } 
            else 
            {
                zanyTail = current;
            }
            zanyHead = current;
        } 
        else 
        {
            // move current non-zany node to the end of the non-zany list
            current->prev = nonZanyTail;
            current->next = nullptr;
            if (nonZanyTail != nullptr) 
            {
                nonZanyTail->next = current;
            } 
            else 
            {
                
                nonZanyHead = current;
            }
            
            nonZanyTail = current;
        }
        current = next;
    }
    
    // combine the zany list to the non-zany list
    if (zanyHead != nullptr) 
    {
        zanyTail->next = nonZanyHead;
        if (nonZanyHead != nullptr) 
        {
            nonZanyHead->prev = zanyTail;
        } 
        else 
        {
            //delete tail;
            tail = zanyTail;
        }
        //delete head;
        head = zanyHead;
        return true;
    }
    /*delete zanyHead;
    delete zanyTail;
    delete nonZanyHead;
    delete nonZanyTail;*/
    
    return false;
};



// ITERATOR

template<typename T>
bool ZLL<T>::start()
{
    current = head;
    return (current != nullptr);
};

template<typename T>
bool ZLL<T>::done()
{
    return (current == nullptr);
};

template<typename T>
bool ZLL<T>::isEmpty()
{
    return (head == nullptr);
};

template<typename T>
bool ZLL<T>::empty()
{
    while (head != nullptr) 
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
    return true;
};

template<typename T>
T ZLL<T>::getNext()
{
    //if it is the last node in the list then do I need to have a special case?
    T result = current->data;
    current = current->next;
    return result;
};
    