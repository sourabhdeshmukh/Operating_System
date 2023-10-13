/* "utility.h" defines data structures and functions that can be used 
for managing doubly-linked lists and implementing a basic queue*/

#ifndef _utility_h_
#define _utility_h_

struct nodeds {
	struct nodeds *next;
	struct nodeds *prev;
	void *data;
};

typedef struct nodeds node;

struct linked_listds {
	node *head;
	node *tail;
	int size;
};

typedef struct linked_listds _linked_list;

node *createNode(void *data);
_linked_list *createLinkedList();

void addNode(_linked_list *list, void *data);
void removeNode(_linked_list *list, void *data);
void swapNodes(node *a, node *b);
void addAfter(_linked_list *list, node *after_node, void *data);
void sort(_linked_list *list, int (*cmp)(void *data1, void *data2));


// Queue Implementation

typedef struct linked_listds queue;

queue *createQueue();
void enqueue(queue *q, void *data);
void *dequeue(queue *q);

#endif