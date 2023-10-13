/* The following code implements the First-Come, First-Serve (FCFS) scheduling algorithm, 
simulates the execution of processes, and calculates and prints statistics related to the scheduling. 
The program uses the provided utility functions and structures to manage processes and statistics.*/

#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "stat.h"

/* The algorithm schedules processes based on their arrival times and processes them in the order they arrive. */

// The following function allocates memory for a proc_stats object, initializes its fields to zero or default values, 
// and returns a pointer to the created proc_stats object.

proc_stats *generate_Stats(process *proc) {

	proc_stats *psState = (proc_stats *) malloc(sizeof(proc_stats));

	psState -> proc = proc;
	psState -> _wait_time = 0;
	psState -> _turn_around_time = 0;
	psState -> _response_time = 0;

	psState -> _service_time = 0;
	psState -> _start_time = -1;
	psState -> _end_time = -1;

	return psState;
}

_avg_stats FCFSNP(_linked_list *processes) {

	int time = 0;

	// Creation of queue to hold processes that are ready to be scheduled.

	queue *process_que = (queue *)createQueue();
	node * ptr = processes -> head;

	if(processes -> head == NULL) {
		fprintf(stderr,"\nThere is no Process to schedule\n\n");
	}
	
	// keep checking while time quanta is less than 100 or the process queue is empty.
	proc_stats * scheduled_proces = NULL;

	_linked_list *linkL = createLinkedList();

	printf("\n___________________________________________________________________________________\n");
	printf("\n\t First-Come First-Serve Algorithm \n\t");
	printf("\n___________________________________________________________________________________\n\n");
	printf("\n");
	
	while(time < 100 || scheduled_proces != NULL) {

		// Check for incoming new process and do enqueue.
		if(ptr != NULL) {
			process * _new_proces = (process *)(ptr -> data);
			if(_new_proces -> _arrival_time <= time) {
				enqueue(process_que, generate_Stats(_new_proces));
				ptr = ptr -> next;
			}
		}

		// Check process queue and schedule it if there is no scheduled process now.
		if(scheduled_proces == NULL && process_que -> size > 0) {
			scheduled_proces = (proc_stats *) dequeue(process_que);
		}

        
		if(scheduled_proces != NULL) {
			process * proc = scheduled_proces -> proc;
	
			// Add  the currently running process to the time chart
			printf("%c", proc -> _process_id);
	
			// Update current processes statistics
			if(scheduled_proces -> _start_time == -1) {
				scheduled_proces -> _start_time = time;
			}

			scheduled_proces -> _service_time++;
    
	        // Check if scheduled process service time is greater than the currently running process service time.
			
			if(scheduled_proces -> _service_time >= proc -> _service_time) {
				scheduled_proces -> _end_time = time;
				
				// Add the scheduled process.
				
				addNode(linkL, scheduled_proces);
				scheduled_proces = NULL;
			}
		} else {
			printf("_");
		}
		
		// Incrementing the time.
		time++;
	}

	// Printing the Statistics of the process.
	return printpolicyStats(linkL);
	
}
