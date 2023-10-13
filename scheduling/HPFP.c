/*
The Following C program implements the Highest Priority First Preemptive (HPFP) scheduling algorithm 
for a set of processes with different priorities. This algorithm schedules processes based on their 
priority and allows preemption, meaning that higher-priority processes can interrupt the execution 
of lower-priority ones. Code imulates the execution of processes, and calculates and prints statistics related to the scheduling. 
The program uses linked lists and queues to manage processes with different priorities, allowing higher-priority processes 
to preempt lower-priority ones during execution.
*/

#include "stat.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>

proc_stats *generate_Stats(process *proc);

// Function to compare the _priority and arrival time
int compare_prior(void *_data1, void *_data2)
{
  proc_stats *p1 = (proc_stats *) _data1;
	proc_stats *p2 = (proc_stats *) _data2;
	
	// Priorities of processes are being compared
	
  if(((((process *)p1 -> proc) -> _priority)) < ((((process *)p2 -> proc) -> _priority))) {
	  	return -1;
	} else if (((((process *)p1->proc)->_priority)) == ((((process *)p2->proc)->_priority)) &&  (((process *)p1->proc)->_arrival_time < (((process *)p2->proc)->_arrival_time))) {
      return -1;
  } else {
		  return 1;
	}
}

// Implementation of algorithm
_avg_stats hpfp(_linked_list * procs) {
  int quanta = 0;
  
  // Creation of 4 Linked Lists for managaing order of processes in preemeption
  
  _linked_list *_list1 = createLinkedList();
  _linked_list *_list2 = createLinkedList();
  _linked_list *_list3 = createLinkedList();
  _linked_list *_list4 = createLinkedList();

  // Creation of 4 process queues
  
  queue *process_que1 = createQueue();
  queue *process_que2 = createQueue();
  queue *process_que3 = createQueue();
  queue *process_que4 = createQueue();

  node *ptr = procs -> head;
  if(procs -> head == NULL) {
		fprintf(stderr,"\nThere is no Process to schedule\n");
	}
	
  printf("\n___________________________________________________________________________________\n");
  printf("\n\tHighest Priority First Preemptive:\n");
  printf("\n___________________________________________________________________________________\n\n");
  printf("\n");
  // Comparing if the time quanta is less than 100 or the process queue is empty...
  proc_stats *scheduled_proceses = NULL;
  while(quanta < 100 || scheduled_proceses != NULL )
  {
    if(scheduled_proceses != NULL)
    {
		// Enqueue based on _priority.
      if(scheduled_proceses -> proc -> _priority == 1) {
          enqueue(process_que1, scheduled_proceses);
      }
      if(scheduled_proceses -> proc -> _priority == 2) { 
          enqueue(process_que2, scheduled_proceses);
      }
      if(scheduled_proceses -> proc -> _priority == 3) { 
          enqueue(process_que3, scheduled_proceses);
      }
      if(scheduled_proceses -> proc -> _priority == 4) { 
          enqueue(process_que3, scheduled_proceses);
      }
    }
    // If new process comes, we enqueue it in the queue
		
    if(ptr != NULL) {
			process *_new_proc = (process *)(ptr -> data);
			
			// Checking the new process arrival time..
			
      while(ptr != NULL && _new_proc -> _arrival_time <= quanta) {
        if(_new_proc -> _priority == 1) {
            enqueue(process_que1, generate_Stats(_new_proc));
        }
        if(_new_proc -> _priority == 2) {
            enqueue(process_que2, generate_Stats(_new_proc));
        }
        if(_new_proc -> _priority == 3) {
            enqueue(process_que3, generate_Stats(_new_proc));
        }
        if(_new_proc -> _priority == 4) {
            enqueue(process_que3, generate_Stats(_new_proc));
        }

		    // Sort the queues based on _priority comparison.
				
        sort(process_que1, compare_prior);
        sort(process_que2, compare_prior);
        sort(process_que3, compare_prior);
        sort(process_que4, compare_prior);
		
				ptr = ptr -> next;
				
        if(ptr != NULL) {
					_new_proc = (process *)(ptr -> data);
        }
			}
    }

    // If there are no scheduled processes, we check process queue and schedule it.
    if(scheduled_proceses == NULL) {
      if (process_que1 -> size > 0) { 
          scheduled_proceses = (proc_stats *) dequeue(process_que1);
      } else if (process_que2 -> size > 0) {
          scheduled_proceses = (proc_stats *) dequeue(process_que2);
      } else if (process_que3 -> size > 0) {
          scheduled_proceses = (proc_stats *) dequeue(process_que3);
      } else if (process_que4 -> size > 0) {
          scheduled_proceses = (proc_stats *) dequeue(process_que4);
      }
      
      // If the process has not started before quanta 100, we remove it from the queue and take the next one in queue for execution//
      if (quanta >= 100 && scheduled_proceses -> _start_time == -1) {
        scheduled_proceses = NULL;
        continue;
      }
		}
    if(scheduled_proceses != NULL) {
  			process * proc = scheduled_proceses->proc;
  
  			// Add the currently  running process to  the time chart
  			printf("%c", proc -> _process_id);

  			// Update the current process stat
  			
        if(scheduled_proceses -> _start_time == -1) {
  				scheduled_proceses -> _start_time = quanta;
  			}

  			scheduled_proceses -> _service_time++;

        if(scheduled_proceses -> _service_time >= proc -> _service_time) {
          scheduled_proceses -> _end_time = quanta;
		      
          // Adding to the linked list based on _priority.
          
          if(scheduled_proceses -> proc ->_priority == 1) { 
              addNode(_list1, scheduled_proceses);
          } else if(scheduled_proceses -> proc -> _priority == 2) { 
              addNode(_list2, scheduled_proceses);
          } else if(scheduled_proceses -> proc -> _priority == 3) { 
              addNode(_list3, scheduled_proceses);
          } else if(scheduled_proceses -> proc -> _priority == 4) { 
              addNode(_list4,scheduled_proceses);
          }
          scheduled_proceses = NULL;
        }
      } else {
    			printf("_");
  		}
  		
      // Increase the Quanta
  		quanta++;
    }
    
    // Print Process Statistics
    _avg_stats average1, average2, average3, average4, average;
    
    printf("\n\t\tFor the  Priority Queue 1\n");
    average1 = printpolicyStats(_list1);
    
    printf("\n\t\tFor the Priority Queue 2\n");
    average2 = printpolicyStats(_list2);
    
    printf("\n\t\tFor the  Priority Queue 3\n");
    average3 = printpolicyStats(_list3);
    
    printf("\n\t\tFor the Priority Queue 4\n");
    average4 = printpolicyStats(_list4);

    average._avg_resp_time = (average1._avg_resp_time + average2._avg_resp_time + average3._avg_resp_time + average4._avg_resp_time)/4 ;
    average._avg_wait = (average1._avg_wait + average2._avg_wait + average3._avg_wait + average4._avg_wait)/4 ;
    average._avg_tat = (average1._avg_tat + average2._avg_tat + average3._avg_tat + average4._avg_tat)/4 ;
    average._avg_thrghput = (average1._avg_thrghput + average2._avg_thrghput + average3._avg_thrghput + average4._avg_thrghput) ;

    printf("\nThe average times of Highest Priority First Preemptive for all queues:\n");
    printf("The Average Response Time: %.1f\n",average._avg_resp_time);
    printf("The Average Wait Time: %.1f\n",average._avg_wait);
    printf("The Average Turn Around Time: %.1f\n",average._avg_tat);

    return average;
}