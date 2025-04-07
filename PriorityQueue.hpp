#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

class PriorityQueue
{
private:
    struct Node {
        int value;
        int priority;
    };

    Node* array;
    int size;
    int capacity;

    void swap(Node& a, Node& b);

public:
    // Constructor
    PriorityQueue(int capacity);

    // Destructor
    ~PriorityQueue();

    // Add an element to the queue
    void push(int value, int priority);

    // Remove and return the element with the highest priority
    int pop();

    // Check if the priority queue is empty
    bool isEmpty();
};

#endif // PRIORITY_QUEUE_HPP
