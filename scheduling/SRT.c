/*
The following C code implements the Shortest Remaining Time to Completion Preemptive (SRTP) 
scheduling algorithm to simulate the execution of processes based on their remaining service time.
It simulates process execution and calculates various statistics related to the scheduling, 
including response time, wait time, and turnaround time. The code ensures that processes are 
selected for execution based on their remaining service time, with the process having the shortest 
remaining time given priority.
*/

#include <stdio.h>
#include <stdlib.h>
#include "stat.h"
#include "utility.h"

proc_stats *generate_Stats(process *proc);

// Function to compare time the completion time of processes while sorting 
int _compare_remaining_time(void *d1, void *d2)
{
  proc_stats *s1 = (proc_stats *) d1;
	proc_stats *s2 = (proc_stats *) d2;
	if(((((process *)s1 -> proc) -> _service_time) - (s1 -> _service_time)) < ((((process *)s2 -> proc) -> _service_time) - (s2 -> _service_time))) {
	  	return -1;
	} else {
	  	return 1;
	}
}

// Function to print contents of queue for testing purpose during shortest remaining time to completion 
void printQueueSRT(queue *q) {
    if (q ->  head != NULL) {
      node *n = q -> head;
      printf("\n\nQueue Contains:\n");
      while(n != NULL) {
        proc_stats *s = n -> data;
        process *p = s -> proc;
        printf("\nProcess Id %c Remaining Time %f\n",p -> _process_id,(p -> _service_time - s -> _service_time));
        n = n -> next;
      }
    }
    return;
}

// Implementation of shortest remaining time to completion preemptive //
_avg_stats SRTP(_linked_list *processes)
{
  int time = 0; // quanta

  // creation of a queue of processes
  queue *_process_que = createQueue();
  
  // creation of linked list for managaing the order of processes in preemeption
  _linked_list *linkL = createLinkedList();

  node *proc_ptr = processes->head;
  
  if(processes -> head == NULL) {
		  fprintf(stderr,"\nNo Process to schedule\n");
	}

  // While process queue is not empty or time quanta is less than 100
  
  proc_stats *_scheduled_proces = NULL;
  
  printf("\n___________________________________________________________________________________\n");
  printf("\n\tShortest Remaining Time Algorithm:\n");
  printf("\n___________________________________________________________________________________\n\n");
  printf("\n");
  while(time < 100 || _scheduled_proces != NULL ) {
    if(_scheduled_proces != NULL) {
        enqueue(_process_que,_scheduled_proces);
        _scheduled_proces = NULL;
    }
    // Check for incoming new process and enqueue it in the queue
		
    if(proc_ptr != NULL) {
			process *newProcess = (process *)(proc_ptr -> data);
			
      while(proc_ptr != NULL && newProcess -> _arrival_time <= time) {
				enqueue(_process_que, generate_Stats(newProcess));
				proc_ptr = proc_ptr -> next;
				
        if(proc_ptr != NULL) {
					newProcess = (process *)(proc_ptr -> data);
        }
			}

      // Sort all the processes that have arrived based on their remaining running time to completion //
      sort(_process_que, _compare_remaining_time);
    }

    // If there is no scheduled process, then check process queue and schedule it 
		
    if(_scheduled_proces == NULL && _process_que -> size > 0) {
			_scheduled_proces = (proc_stats *) dequeue(_process_que);

      // If the process has not started before quanta 100, remove the process from the queue and take the next process in queue for execution //
      while(time >= 100 && _scheduled_proces -> _start_time == -1) {
        _scheduled_proces = (proc_stats *) dequeue(_process_que);
      }
		}
    if(_scheduled_proces != NULL) {
  			process *proc = _scheduled_proces -> proc;

  			// Add the currently running process to the time chart
  			printf("%c",proc -> _process_id);
        
  			// Update the current processes stat
  			if(_scheduled_proces -> _start_time == -1) {
  				_scheduled_proces -> _start_time = time;
  			}

  			_scheduled_proces -> _service_time++;

        if(_scheduled_proces -> _service_time >= proc -> _service_time) {
            _scheduled_proces -> _end_time = time;
            addNode(linkL,_scheduled_proces);
            _scheduled_proces = NULL;
        }
      } else {
    			printf("_");
    	}
  		
      // Incrementing the time
  		time++;
  }
  
  // Print Process Statistics
  return printpolicyStats(linkL);
  
}
