#ifndef QUEUE_H
#define QUEUE_H
#include<iostream>
using namespace std;

template <typename T>
class Queue {
public:
	template <typename T>
	struct Node_Q {
	public:
		T data;
		Node_Q* next;
		Node_Q() {
			next = nullptr;
		}

		Node_Q(T val) {
			data = val;
			next = nullptr;
		}
	};

	Node_Q<T>* start;
	Node_Q<T>* end;

	Queue() {
		start = nullptr;
		end = nullptr;
	}

	void enqueue(T x) {

		Node_Q<T>* n = new Node_Q<T>(x);
		if (isEmpty()) {
			start = end = n;
			
		}
		else {
			end->next = new Node_Q<T>;
			end->next->data = n->data;
			end = end->next;
			
		}
	}

	void denqueue() {
		if (isEmpty()) {
			return;
		}
		else {
			start = start->next;
		}
	}

	T front() {
		if (isEmpty()) {
			return T();
		}
		else {
			return start->data;
		}
	}

	bool isEmpty() {
		if (start == nullptr) {
			return true;
		}
		return false;
	}

	int size() {
		int total = 0;
		Node_Q<T>* temp = start;
		while (temp) {
			total++;
			temp = temp->next;
		}
		return total;
	}

	void denqueueEnd() {
		if (isEmpty()) {
			return;
		}
		else {
			Node_Q<T>* temp = start;
			if (start == end) {
				start = end = nullptr;
			}
			else if (start->next == end) {
				end = start;
			}
			else {
				while (temp->next != end) {

					temp = temp->next;
				}
				end = temp;

			}

		}
	}
};

#endif