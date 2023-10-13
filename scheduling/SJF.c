/*
The following C Code  implements the Shortest Job First Non-Preemptive (SJFNP) 
scheduling algorithm to simulate the execution of processes based on their service time. 
simulates process execution and calculates various statistics related to the scheduling, 
including response time, wait time, and turnaround time. 
The code ensures that processes are selected based on their service times, 
with shorter jobs given priority for execution.
*/

#include <stdio.h>
#include <stdlib.h>
#include "stat.h"
#include "utility.h"

proc_stats *generate_Stats(process* proc);

int _compare_serviceTime(void *_data1, void *_data2) {
	proc_stats *s1 = (proc_stats *) _data1;
	proc_stats *s2 = (proc_stats *) _data2;
	if(((process *)s1 -> proc) ->_service_time < ((process *)s2 -> proc) -> _service_time) {
		return -1;
	} else {
		return 1;
	}
}

_avg_stats SJFNP(_linked_list *processes) {
	int time = 0;

	// Creation of Process Queue

	queue *_process_que = (queue *)createQueue();
	node *ptr = processes -> head;
	
	if(processes -> head == NULL) {
		fprintf(stderr,"\nNo Process to schedule\n");
	}
	// Keep checking while time quanta is less than 100 or the process queue is empty...
	proc_stats *scheduled_proces = NULL;

	_linked_list *linkL = createLinkedList();

	printf("\n___________________________________________________________________________________\n");
	printf("\n\tShortest Job First Algorithm:\n");
	printf("\n___________________________________________________________________________________\n\n");
	printf("\n");
	while(time < 100 || scheduled_proces!=NULL) {
		// Check for incoming new process and do enqueue.
		
		if(ptr != NULL) {
			process *_new_proces = (process *)(ptr -> data);
			while(ptr != NULL && _new_proces->_arrival_time <= time) {
				enqueue(_process_que, generate_Stats(_new_proces));
				sort(_process_que, _compare_serviceTime);
				ptr = ptr -> next;
				if(ptr != NULL)
					_new_proces = (process *)(ptr -> data);
			}
		}

		// Check process queue and schedule it if there is no scheduled process now..
		if(scheduled_proces == NULL && _process_que -> size > 0) {
			scheduled_proces = (proc_stats *) dequeue(_process_que);
		}

		if(scheduled_proces != NULL) {
			process * proc = scheduled_proces -> proc;

			// Add the currently running process to the time chart
			printf("%c", proc -> _process_id);

			// Update the current processes stat
			if(scheduled_proces -> _start_time == -1) {
				scheduled_proces -> _start_time = time;
			}
			
			scheduled_proces -> _service_time++;

			if(scheduled_proces -> _service_time >= proc -> _service_time) {
				scheduled_proces -> _end_time = time;
				addNode(linkL,scheduled_proces);
				scheduled_proces = NULL;
			}
		} else {
			printf("_");
		}
		
		// Keep increasing the time
		time++;
	}
	printf("\n");

	// Printing Process Stat
	return printpolicyStats(linkL);	
}
