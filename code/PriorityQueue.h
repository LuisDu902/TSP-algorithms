#ifndef DA_PRIORITYQUEUE_H
#define DA_PRIORITYQUEUE_H

#include <vector>
#include "VertexEdge.h"
class Vertex;

class PriorityQueue {
	std::vector<Vertex *> Heap;

    /**
     * This function maintains the heap property by swapping the element at position i with its parent,
     * as long as the parent has a higher priority than the element.
     *
     * @param i The index of the element that may violate the heap property.
     *
     * @par Time complexity
     * O(log n), where n is the number of elements in the queue.
     */
	void heapifyUp(unsigned i);

    /**
     * This function maintains the heap property by swapping the element at position i with its smallest
     * child, as long as the child has a higher priority than the element.
     *
     * @param i The index of the element that may violate the heap property.
     *
     * @par Time complexity
     * O(log n), where n is the number of elements in the queue.
     */
	void heapifyDown(unsigned i);

    /**
     * This function updates the value of an element in the heap and its queueIndex field.
     * @param i The new queueIndex of x.
     * @param x The element to be updated.
     *
     * @par Time complexity
     * O(1)
     */
	inline void set(unsigned i, Vertex* x);
public:
	PriorityQueue();

    /**
     * This function inserts a new element into the priority queue.
     * @param x A pointer to the element to be inserted.
     *
     * @par Time complexity
     * O(log n), where n is the number of elements in the queue.
     */
	void insert(Vertex * x);

    /**
     * This function extracts the minimum element from the priority queue.
     *
     * @return A pointer to the minimum element of the queue.
     *
     * @par Time complexity
     * O(log n), where n is the number of elements in the queue.
     */
    Vertex * extractMin();

    /**
     * This function decreases the priority of an element in the queue.
     * @param x A pointer to the element whose priority is to be decreased.
     *
     * @par Time complexity
     * O(log n), where n is the number of elements in the queue.
     */
	void decreaseKey(Vertex* x);

    /**
     * This function checks whether the priority queue is empty or not.
     *
     * @return True if the size of the heap is 1, which means that there are no elements in the queue
     * (since the 0th index of the heap is not used), false otherwise.
     *
     * @par Time complexity
     * O(1)
     */
	bool empty();
};

#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

#endif //DA_PRIORITYQUEUE_H
