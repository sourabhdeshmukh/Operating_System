/* The following program implements the High Priority First Non-Preemptive (HPFNP) scheduling algorithm 
for a set of processes with different priorities. This algorithm schedules processes based on their priority 
and executes them non-preemptively, meaning that a process runs until it completes or is blocked. */

#include <stdio.h>
#include <stdlib.h>
#include "stat.h"
#include "utility.h"

proc_stats *generate_Stats(process *proc);

int comparePriority(void *data1, void *data2);
void printqueue(queue *q);

_avg_stats HPFNP(_linked_list *_process)
{
  
  // Create linked list to manage process order in preemeption

  _linked_list *_linked_list1 = createLinkedList();
  _linked_list *_linked_list2 = createLinkedList();
  _linked_list *_linked_list3 = createLinkedList();
  _linked_list *_linked_list4 = createLinkedList();
  
  // Create a queue of processes.
  queue *queue1 = createQueue();
  queue *queue2 = createQueue();
  queue *queue3 = createQueue();
  queue *queue4 = createQueue();

  int _time_quanta = 0; // quanta

  node *procptr = _process->head;

  if (_process -> head == NULL) {
    fprintf(stderr, "\nCurrently, scheduling cannot be done as there are no processes available\n");
  }

  printf("\n___________________________________________________________________________________\n");
  printf("\n\tExecuting HPF Non-preemptive Algorithm:\n");
  printf("\n___________________________________________________________________________________\n\n");

  // Continuously monitor the time quantum and the process queue to ensure that either the time quantum is not greater than 100 or the process queue is not devoid of any elements.
  printf("\n");
  proc_stats *planned_proces = NULL;
  while (_time_quanta < 100 || planned_proces != NULL)
  {

    if (procptr != NULL) // Examine the new process and based on _priority, put them in queue.

    {
      process *_newprocesess = (process *)(procptr -> data);

      // Continuously verify that the process pointer is not empty and that the arrival time of any new process is less than or equal to the time quantum.      while (procptr != NULL && _newprocesess->_arrival_time <= _time_quanta)
      {

        if (_newprocesess -> _priority == 1) {
            enqueue(queue1, generate_Stats(_newprocesess));
        }
        if (_newprocesess -> _priority == 2) {
            enqueue(queue2, generate_Stats(_newprocesess));
        }
        if (_newprocesess -> _priority == 3) {
            enqueue(queue3, generate_Stats(_newprocesess));
        }
        if (_newprocesess -> _priority == 4) {
            enqueue(queue3, generate_Stats(_newprocesess));
        }

        // sort(processQueue,comparePriority);
        procptr = procptr -> next;
        
        if (procptr != NULL) {
          _newprocesess = (process *)(procptr -> data);
        }
      }
      // sorting arrived _process based on _priority.
      // sort(processQueue,comparePriority);
    }

    // printqueue(processQueue);
    // check process queue and schedule it based on _priority. //

    if (planned_proces == NULL) {

      // dequeue _process based on their sizes...
      if (queue1 -> size > 0) {
          planned_proces = (proc_stats *)dequeue(queue1);
      } else if (queue2 -> size > 0) {
        planned_proces = (proc_stats *)dequeue(queue2);
      } else if (queue3 -> size > 0) {
        planned_proces = (proc_stats *)dequeue(queue3);
      } else if (queue4 -> size > 0) {
        planned_proces = (proc_stats *)dequeue(queue4);
      } 
      // If the process has not started before quanta 100, remove the process from the queue and take the next process in queue for execution //

      // if the time > = 100 an startime -1,null the scheduled process.

      if (_time_quanta >= 100 && planned_proces -> _start_time == -1) {
        // free(planned_proces);
        planned_proces = NULL;
        continue;
      }
    }

    if (planned_proces != NULL) {

      process *proc = planned_proces->proc;

      // add  the currently running process to the time chart
      printf("%c", proc -> _process_id);

      // updating the  current _process stat
      if (planned_proces -> _start_time == -1) {
        planned_proces -> _start_time = _time_quanta;
      }

      planned_proces -> _service_time++;

      if (planned_proces -> _service_time >= proc -> _service_time) {

        planned_proces -> _end_time = _time_quanta;

        // add nodes to the linked list based on their _priority.

        if (planned_proces -> proc ->_priority == 1) {
            addNode(_linked_list1, planned_proces);
        } else if (planned_proces->proc->_priority == 2) {
            addNode(_linked_list2, planned_proces);
        } else if (planned_proces->proc->_priority == 3) {
            addNode(_linked_list3, planned_proces);
        } else if (planned_proces->proc->_priority == 4) {
            addNode(_linked_list4, planned_proces);
        }
        // addNode(ll,planned_proces);
        planned_proces = NULL;
        // free(planned_proces);
      }
    } else {
      printf("_");
    }
    // keep incrementing the time.
    _time_quanta++;
  }

  // Print Process Status
  _avg_stats avg1, avg2, avg3, avg4, avg;
  
  printf("\n\t\tFor the  Priority Queue 1\n");
  avg1 = printpolicyStats(_linked_list1);
  
  printf("\n\t\tFor the  Priority Queue 2\n");
  avg2 = printpolicyStats(_linked_list2);
  
  printf("\n\t\tFor the  Priority Queue 3\n");
  avg3 = printpolicyStats(_linked_list3);
  
  printf("\n\t\tFor the Priority Queue 4\n");
  avg4 = printpolicyStats(_linked_list4);

  // calcultaing average response time ,wait time,turnaround time and _throughput.
  avg._avg_resp_time = (avg1._avg_resp_time + avg2._avg_resp_time + avg3._avg_resp_time + avg4._avg_resp_time) / 4;
  avg._avg_wait = (avg1._avg_wait + avg2._avg_wait + avg3._avg_wait + avg4._avg_wait) / 4;
  avg._avg_tat = (avg1._avg_tat + avg2._avg_tat + avg3._avg_tat + avg4._avg_tat) / 4;
  avg._avg_thrghput = (avg1._avg_thrghput + avg2._avg_thrghput + avg3._avg_thrghput + avg4._avg_thrghput);

  printf("\n\nThe average statistics high _priority first non-preemptive considering all _priority queues is:\n");
  printf("The average Response Time: %.1f\n", avg._avg_resp_time);
  printf("The average Wait Time: %.1f\n", avg._avg_wait);
  printf("The average Turn Around Time: %.1f\n", avg._avg_tat);

  return avg;
}
