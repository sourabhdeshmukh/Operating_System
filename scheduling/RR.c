/*
The followibg C code implements the Round Robin Preemptive (RRP) scheduling algorithm 
to simulate the execution of processes with a time slice. It simulates process execution 
and calculates various statistics related to the scheduling, including response time, wait time, 
and turnaround time. The code handles context switching based on the time slice and ensures that 
processes are scheduled fairly in a round-robin fashion.
*/

#include <stdio.h>
#include <stdlib.h>
#include "stat.h"
#include "utility.h"

proc_stats *generate_Stats(process* proc);

// Round Robin Preemptive Algorithm

_avg_stats RRP(_linked_list * procesList, int timeSlice) {
	
	int t = 0;
    
	// Create the queue
	queue *pQueue = (queue *)createQueue();
	
	// Point to the first process in the list
	node *curr_proces_ptr = procesList -> head;
	
	// First we will check if there are process available to shift
	if(procesList -> head == NULL) {
		fprintf(stderr,"\nNo Process to schedule\n");
	}
      
	proc_stats * currProcess = NULL;
        
	// Create a linkedlist
	_linked_list *linkL = createLinkedList();

	printf("\n___________________________________________________________________________________\n");
	printf("\n\tRound Robin Algorithm:\n");
	printf("\n___________________________________________________________________________________\n\n");

	// Create a pointer which will point to the process which is going to be executed
	node *curr_node = NULL;
	int curr_runing_count = 0;
	printf("\n");
	// Will run the code till time quanta is less than 100 or there's new incoming process
	while(t < 100 || pQueue -> size > 0) {
		if(curr_proces_ptr != NULL && t<100) {
			process *newProcess = (process *)(curr_proces_ptr -> data);
			
			// First will check if the new incoming process has the arrival time <= current time if yes then enqueue the new process
			while(curr_proces_ptr != NULL && newProcess -> _arrival_time <= t) {
				
				enqueue(pQueue, generate_Stats(newProcess));
				curr_proces_ptr = curr_proces_ptr -> next;
				
				if(curr_proces_ptr != NULL) {
					newProcess = (process *)(curr_proces_ptr -> data);
				}	
			}
		}
        
		// If current pointer is not pointing then point to head
		
		if(curr_node == NULL) {
			curr_runing_count = 0;
			curr_node = pQueue -> head;
		} else if(curr_runing_count == timeSlice) {
		
		// It's time to context switch
			curr_runing_count = 0;
			curr_node = curr_node -> next;
			if(curr_node == NULL) {

			// If no other process in the queue then point to head again
				curr_node = pQueue -> head;
			}
		}

		if(curr_node != NULL) {
			currProcess = (proc_stats *) curr_node -> data;
			process *proc = currProcess -> proc;

			if(t >= 100) {
				if(currProcess -> _start_time == -1) {
					free(currProcess);
					node *next = curr_node -> next;
					removeNode(pQueue, curr_node -> data);
					curr_node = next;
					curr_runing_count = 0;
					continue;
				}
			}

			printf("%c", proc -> _process_id);

			curr_runing_count++;

			if(currProcess -> _start_time == -1) {
				currProcess -> _start_time = t;
			}
			currProcess -> _service_time++;

			if(currProcess -> _service_time >= proc -> _service_time) {
				currProcess -> _end_time = t;
				addNode(linkL, currProcess);
				node * next = curr_node -> next;
				removeNode(pQueue, curr_node -> data);
				curr_node = next;
				curr_runing_count = 0;
			}
		} else {
			printf("_");
		}
		t++;
	}

	return printpolicyStats(linkL);
	
}