/* The code as a whole is primarily focused on generating random processes, 
sorting them by arrival time, and assigning process IDs. */

#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "utility.h"
#include <time.h>

int compare(void *data1, void *data2) {
	process *p1 = (process *)data1;
	process *p2 = (process *)data2;
	if(p1 -> _arrival_time < p2 -> _arrival_time) {
		return -1;
	} else if(p1 -> _arrival_time == p2 -> _arrival_time){
		return 0;
	} else {
		return 1;
	}
}

_linked_list *generateProceses(int n) {
	
	_linked_list *process_list = createLinkedList();
	char _process_id = 'A';
	unsigned int _priority;
	float _arrival_time, _service_time;

   // Intializes random number generator 
   
    int seed = time(NULL); 
    srand(seed); 

	if(process_list == NULL) {
		fprintf(stderr,"\nUnable to create Linked List\n");
	}

	while(n--) {
		// Rand function will return num between 0 and 99
		_arrival_time = rand() % 100; 

		// Rand function will return num between 0 and 10
        _service_time = (rand() % 11); 
        
		if (_service_time == 0) {
			// Assigning _service_time = 0.1...10
            _service_time += 0.1;  
        }

        _priority = rand() % 5; 
		// Assigning _priority between 1...4
        
		if (_priority == 0) _priority += 1; 

		process *p = createProceses(_process_id, _arrival_time, _service_time, _priority);

		addNode(process_list, p);
		_process_id++;
	}

	// Linked List is sorted based on arrival time and the process IDs are assigned sequentially.
	sort(process_list, compare);

	node *ptr = process_list -> head;
	_process_id = 'A';
	
	while(ptr != NULL) {
		((process *)ptr -> data) -> _process_id = _process_id;
		if(_process_id == 'Z') _process_id = 'a' - 1;
		_process_id++;
		ptr = ptr -> next;
	}

	return process_list;
}

// The following function is responsible for creating a new process

process *createProceses(char _process_id, float _arrival_time, float _service_time, unsigned int _priority) {
	process *proc = (process *) malloc(sizeof(process)); // Allocating memory for Process.
	proc -> _process_id = _process_id;
	proc -> _arrival_time = _arrival_time;
	proc -> _service_time = _service_time;
	proc -> _priority = _priority;
	return proc;
}
