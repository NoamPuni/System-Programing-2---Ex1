//noampuni99@gmail.com

#include "PriorityQueue.hpp"
#include <iostream>

void PriorityQueue::swap(Node& a, Node& b) {
    Node temp = a;
    a = b;
    b = temp;
}

// Constructor
PriorityQueue::PriorityQueue(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->array = new Node[capacity];
}

// Destructor
PriorityQueue::~PriorityQueue() {
    delete[] array;
}

// Add an element to the queue
void PriorityQueue::push(int value, int priority) {
    if (size == capacity) {
        std::cerr << "Priority queue is full" << std::endl; // need checking because we are using an array
        return;
    }
    array[size] = {value, priority};
    size++;
    int i = size - 1;

    // Simple bubble sort
    while (i > 0 && array[i].priority < array[i - 1].priority) {
        // Sorting the array by priority, starting from the end
        swap(array[i], array[i - 1]);
        i--;
    }
    // At the end of the sort, the one with the highest priority will be at the beginning of the array
}

// Remove and return the element with the highest priority
int PriorityQueue::pop() {
    if (isEmpty()) {
        std::cerr << "Priority queue is empty" << std::endl;
        return -1; // Error value
    }
    int value = array[0].value; // Save the value of the element with the highest priority to return it
    for (int i = 0; i < size - 1; i++) {
        // Move every element one place to the beginning
        array[i] = array[i + 1];
    }
    size--;
    return value;
}

// Check if the priority queue is empty
bool PriorityQueue::isEmpty() {
    return size == 0;
}
