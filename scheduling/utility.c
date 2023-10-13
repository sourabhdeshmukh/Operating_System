/* The following code provides implementations for managing linked lists and queues, 
as well as a function to print statistics related to processes.*/

#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "process.h"
#include "stat.h"


// Linked List Implementation Function Definitions

// Create new _linked_list
_linked_list *createLinkedList() {
	_linked_list *new_list =  (_linked_list *) malloc(sizeof(_linked_list));
	new_list -> head = NULL;
	new_list -> tail = NULL;
	new_list -> size = 0;
	return new_list;
}



// Create a new node
node *createNode(void *data) {
	node *new_node = (node *) malloc(sizeof(node));
	new_node -> data = data;
	new_node -> next = NULL;
	new_node -> prev = NULL;
	return new_node;
}

// Add a node to existing linked list
void addNode(_linked_list *list, void *data) {
	node *new_node = createNode(data);

	if(list -> size == 0) {
		list -> head = new_node;
		list -> tail = new_node;
		list -> size = 1 ;
	} else {
		new_node -> prev = list -> tail;
		list -> tail-> next = new_node;
		list -> tail = new_node;
		list -> size += 1;
	}
}

// Remove a node from existing _linked_list 
void removeNode(_linked_list *list, void *data) {
	node *current_node = list -> head;

	while(current_node != NULL && current_node -> data != data) {
		current_node = current_node -> next;
	}

	if(current_node != NULL) {
		if(current_node -> prev != NULL) {
			current_node -> prev -> next = current_node -> next;
		}
		if(current_node -> next != NULL) {
			current_node -> next -> prev = current_node -> prev;
		}
		if(list -> head == current_node) {
			list -> head = current_node -> next;
		}
		if(list -> tail == current_node) {
			list -> tail = current_node -> prev;
		}
		
		list -> size--;
		
		free(current_node);
	}
}

// Remove a node from existing _linked_list
void removeHead(_linked_list *list) {
	node *current_node = list->head;
	if(current_node != NULL) {
		list -> head = current_node -> next;
		if(list -> tail == current_node) {
			list -> tail = current_node -> prev;
		}
		
		list -> size--;
		free(current_node);
	}
}

// Add a new node after a particular node in an existing _linked_list
void addAfter(_linked_list *list, node *after_node, void *data) {
	node *new_node = createNode(data);

	node *next_node = after_node -> next;
	new_node -> next = next_node;
	if(next_node != NULL) {
		next_node -> prev = new_node;
	}
	
	new_node -> prev = after_node;
	after_node -> next = new_node;

	if(list -> tail == after_node) {
		list -> tail = new_node;
	}

	list -> size++;
}

void sort(_linked_list *list, int (*cmp)(void *data1, void *data2)) {
	node *i = list -> head;
	while(i != NULL) {
		node *j = i -> next;
		while(j != NULL) {
			void *p1 = i -> data;
			void *p2 = j -> data;
			if((*cmp)(p1, p2) > 0) {
				swapNodes(i, j);
			}
			j = j-> next;
		}
		i = i -> next;
	}
}

void swapNodes(node *a, node *b) {
	void *temp = a -> data;
	a -> data = b -> data;
	b -> data = temp;
}

// Queue Implementation
queue *createQueue() {
	return createLinkedList();
}

// Enqueue function to add process at the end of the queue
void enqueue(queue *q, void *data) {
	node *new_node = createNode(data);

	new_node -> prev = q -> tail;
	if(q -> tail != NULL) {
		q -> tail -> next = new_node;
		q -> tail = new_node;
	} else {
		q -> tail = new_node;
		q -> head = new_node;
	}
	q -> size += 1;
}

// Dequeue function to remove process from the end of the queue
void *dequeue(queue *q) {
	if(q -> head != NULL) {
		node *current_node = q -> head;// Address of q->head
		void *data = current_node -> data;

		// Moving Head to next Node
		node *next_node = q -> head -> next;

		if(next_node != NULL) next_node -> prev = NULL;
		q -> head = next_node; //current_node = q->head = next_node


		// Maintaining boundary tail condition
		if(q -> tail == current_node) {
			q -> tail = NULL;
		}

		q -> size--;
		free(current_node);
		return data;
	}
}

_avg_stats printpolicyStats(_linked_list *linkL) {
	_avg_stats avg;

	// Print Process Stat
	
	printf("\n");
	printf("\t-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("\tProcess Name\t| Arrival Time | Start Time | End Time | Run Time | Response Time | Wait Time | Turn Around Time | Priority |\n");
	printf("\t-----------------------------------------------------------------------------------------------------------------------------\n");
	
	node *ptr = linkL -> head;

	float _avg_resp_time = 0;
	float _avg_wait = 0;
	float _avg_tat = 0;
	
	int process_count = 0;
	
	while(ptr != NULL) {
		proc_stats *stat = (proc_stats *)ptr -> data;
		if(stat == NULL) {
			printf("No Stat\n");
		}
		process *proc = (process *)stat->proc;
		
		if(proc == NULL) { 
			printf("No Process\n");
		}
		
		float _arrival_time = proc -> _arrival_time;
		float _service_time = proc -> _service_time;
		float _response_time = stat -> _start_time - _arrival_time;
		float turnaround = stat -> _end_time - proc -> _arrival_time + 1;
		float _wait_time = turnaround - _service_time;
		unsigned int _priority = proc -> _priority;
		_avg_resp_time += _response_time;
		_avg_wait += _wait_time;
		_avg_tat += turnaround;
		process_count++;

		printf("%16c|%14.1f|%12.1f|%10.1f|%10.1f|%15.1f|%11.1f| %17.1f|%10u|\n",
        proc -> _process_id, _arrival_time, stat-> _start_time, stat -> _end_time, _service_time, _response_time, 
        _wait_time, turnaround, _priority);
		ptr = ptr -> next;
	}
	
	avg._avg_thrghput = process_count;
	
	if(process_count == 0) { 
		process_count = 1;
	}
	
	_avg_resp_time = _avg_resp_time / process_count;
	_avg_wait = _avg_wait / process_count;
	_avg_tat = _avg_tat / process_count;
	
	printf("\t-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t%16s|%14.1f|%12.1f|%10.1f|%10.1f|%15.1f|%11.1f| %17.1f|\n"," Average",0.0, 0.0, 0.0,0.0,_avg_resp_time, _avg_wait, _avg_tat);
	printf("\t-----------------------------------------------------------------------------------------------------------------------------\n");
	
	// Compute overall stat
	// Return statistics
	avg._avg_resp_time = _avg_resp_time;
	avg._avg_wait = _avg_wait;
	avg._avg_tat = _avg_tat;

	return avg;
}
