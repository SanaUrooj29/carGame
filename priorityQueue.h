#pragma once
#include<iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    int priority;
    Node* next;

    Node()
    {
        priority = 0;
        next = nullptr;
    }

    Node(T data, int priority)
    {
        this->data = data;
        this->priority = priority;
        next = nullptr;
    }
};

template <typename T>
class PriorityQueue {
private:
    Node<T>* front;

public:
    PriorityQueue() {
        front = nullptr;
    }

    void enqueue(T data, int priority) {
        Node<T>* newNode = new Node<T>(data, priority);
        //if front is not null or priority is less than thr priority of front 
        if (!front || priority < front->priority) {
            newNode->next = front;
            front = newNode;
            
        }
        else {
            Node<T>* temp = front;
            while (temp->next && priority <= temp->next->priority) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
            
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
           
        }
        else {
            cout << "Queue is empty. Cannot dequeue.\n";
        }
    }

    T frontElement() {
        if (!isEmpty()) {
            return front->data;
        }
        else {
            cout << "Queue is empty. No front element.\n";
            return T();
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

