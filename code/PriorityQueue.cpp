#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() {
    Heap.push_back(nullptr);
}

bool PriorityQueue::empty() {
    return Heap.size() == 1;
}

Vertex* PriorityQueue::extractMin() {
    auto x = Heap[1];
    Heap[1] = Heap.back();
    Heap.pop_back();
    if(Heap.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

void PriorityQueue::insert(Vertex* x) {
    Heap.push_back(x);
    heapifyUp(Heap.size()-1);
}

void PriorityQueue::decreaseKey(Vertex *x) {
    heapifyUp(x->queueIndex);
}

void PriorityQueue::heapifyUp(unsigned i) {
    auto x = Heap[i];
    while (i > 1 && *x < *Heap[parent(i)]) {
        set(i, Heap[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

void PriorityQueue::heapifyDown(unsigned i) {
    auto x = Heap[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= Heap.size())
            break;
        if (k+1 < Heap.size() && *Heap[k+1] < *Heap[k])
            ++k; // right child of i
        if ( ! (*Heap[k] < *x) )
            break;
        set(i, Heap[k]);
        i = k;
    }
    set(i, x);
}

void PriorityQueue::set(unsigned i, Vertex* x) {
    Heap[i] = x;
    x->queueIndex = i;
}
