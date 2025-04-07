#ifndef QUEUE_HPP
#define QUEUE_HPP

struct Node
{
    int data;
    Node* next;
};

class Queue
{
private:
    Node* head;
    Node* tail;

public:
    // Constructor
    Queue();

    // Destructor
    ~Queue();

    // Add a new element to the queue
    void push(int data);

    // Remove the first element from the queue
    int pop();

    // Check if the queue is empty
    bool isEmpty();

    // Getter for the tail element
    int getTail() const;
};

#endif // QUEUE_HPP
