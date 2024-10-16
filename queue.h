#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX 27 // Define maximum number of children for each node

// Structure for a tree node

typedef struct node
{
	char value;					// Value stored in the node
	struct node *children[MAX]; // Array of pointers to child nodes
} Node, *Tree;

// Structure for a compact tree node

typedef struct compact_node
{
	char *value;						// Pointer to the value stored in the node
	struct compact_node *children[MAX]; // Array of pointers to child nodes
} CNode, *CTree;

typedef Node *Item;

// Structure for a queue node
typedef struct QueueNode
{
	Item elem;
	struct QueueNode *next;
} QueueNode;

// Structure for a queue
typedef struct Queue
{
	QueueNode *front;
	QueueNode *rear;
	long size; // Current size of the queue
} Queue;

// Type definition for an item in the compact queue

typedef CNode *Item2;
// Structure for a queue node in the compact queue
typedef struct QueueNode2
{
	Item2 elem;
	struct QueueNode2 *next;
} QueueNode2;
// Structure for a compact queue
typedef struct Queue2
{
	QueueNode2 *front;
	QueueNode2 *rear;
	long size;
} Queue2;

// Function to create a new queue
Queue *createQueue(void)
{
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	queue->front = NULL;
	queue->rear = NULL;
	queue->size = 0;
	return queue;
}
// Function to create a new compact queue
Queue2 *createQueue2(void)
{
	Queue2 *queue = (Queue2 *)malloc(sizeof(Queue2));
	queue->front = NULL;
	queue->rear = NULL;
	queue->size = 0;
	return queue;
}
// Function to check if a queue is empty
int isEmpty(Queue *q)
{
	if (q == NULL)
		return 1;
	if ((q->front == NULL) && (q->size == 0))
		return 1;
	return 0;
}
// Function to check if a compact queue is empty
int isEmpty2(Queue2 *q)
{
	if (q == NULL)
		return 1;
	if ((q->front == NULL) && (q->size == 0))
		return 1;
	return 0;
}
// Function to enqueue an element to a normal queue
void enqueue(Queue *q, Item elem)
{
	if (isEmpty(q) == 1)
	{
		QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
		node->elem = elem;
		node->next = NULL;
		q->front = node;
		q->rear = node;
		q->size++;
		return;
	}
	else
	{
		QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
		node->elem = elem;
		node->next = NULL;
		q->rear->next = node;
		q->rear = node;
		q->size++;
		return;
	}
}
// Function to enqueue an element to a compact queue
void enqueue2(Queue2 *q, Item2 elem)
{
	if (isEmpty2(q) == 1)
	{
		QueueNode2 *node = (QueueNode2 *)malloc(sizeof(QueueNode2));
		node->elem = elem;
		node->next = NULL;
		q->front = node;
		q->rear = node;
		q->size++;
		return;
	}
	else
	{
		QueueNode2 *node = (QueueNode2 *)malloc(sizeof(QueueNode2));
		node->elem = elem;
		node->next = NULL;
		q->rear->next = node;
		q->rear = node;
		q->size++;
		return;
	}
}
// Function to get the front element of the queue
Item front(Queue *q)
{
	return q->front->elem;
}

Item2 front2(Queue2 *q)
{
	return q->front->elem;
}
// Function to dequeue an element from a normal queue
void dequeue(Queue *q)
{
	QueueNode *tmp;
	if (isEmpty(q) == 1)
	{
		return;
	}
	else if (isEmpty(q) == 0)
	{
		if (q->front == q->rear)
		{
			tmp = q->front;
			free(tmp);
			q->front = NULL;
			q->rear = NULL;
			q->size = 0;
			return;
		}
		tmp = q->front;
		q->front = q->front->next;
		free(tmp);
		q->size--;
	}
}

void dequeue2(Queue2 *q)
{
	QueueNode2 *tmp;
	if (isEmpty2(q) == 1)
	{
		return;
	}
	else if (isEmpty2(q) == 0)
	{
		if (q->front == q->rear)
		{
			tmp = q->front;
			free(tmp);
			q->front = NULL;
			q->rear = NULL;
			q->size = 0;
			return;
		}
		tmp = q->front;
		q->front = q->front->next;
		free(tmp);
		q->size--;
	}
}
// Function to destroy a normal queue and free its resources
void destroyQueue(Queue *q)
{
	while (!isEmpty(q))
		dequeue(q);
	free(q);
}

void destroyQueue2(Queue2 *q)
{
	while (!isEmpty2(q))
		dequeue2(q);
	free(q);
}

#endif
