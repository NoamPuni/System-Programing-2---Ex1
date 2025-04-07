#include "Queue.hpp"
#include <iostream>

// Constructor
Queue::Queue()
{
    head = nullptr;
    tail = nullptr;
}

// Destructor
Queue::~Queue()
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Add a new element to the queue
void Queue::push(int data)
{
    Node* newNode = new Node{data, nullptr};
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

// Remove the first element from the queue
int Queue::pop()
{
    if (head == nullptr)
    {
        std::cerr << "Queue is empty" << std::endl;
        return -1;
    }
    Node* temp = head;
    int data = head->data;
    head = head->next;
    delete temp;
    return data;
}

// Check if the queue is empty
bool Queue::isEmpty()
{
    return head == nullptr;
}

// Getter for the tail element
int Queue::getTail() const
{
    return tail->data; // Public getter for tail
}
