/*
The following C code is a program that simulates and compares the performance of different process 
scheduling algorithms, such as First-Come-First-Served (FCFS), Round Robin (RR), Shortest Job First (SJF), 
Shortest Remaining Time (SRT), Highest Priority First (HPF) with preemption, and Highest Priority First (HPF) 
without preemption. It generates processes, runs the algorithms on them, and calculates various average 
statistics for each algorithm.
*/

#include <stdio.h>
#include "utility.h"
#include "process.h"
#include "stat.h"
#include <unistd.h>


// void display_queue(queue *q) {
// 	node *ptr = (node *)q->head;
// 				printf("<");
// 				while(ptr!=NULL) {
// 					printf("%c ",((process *) ptr->data)->_process_id);
// 					ptr = ptr->next;
// 				}
// 				printf(">\n");
// }

int main(int argc,char **argv) {
	
	int counter = 0;
	
	//Run 5 times
	_avg_stats fcfs[6],sjf[6],srf[6],rr[6],hpfp[6],hpfnp[6],result[6];

	while (counter < 5) {
		
		printf("\n##################################################################################\n");
		printf("\t\t\t\tRound %d\n", counter + 1);
		printf("#####################################################################################\n");

		_linked_list * proc_list = generateProceses(52);
		node * ptr = proc_list -> head;

		printf("\t-------------------------------------------------\n");
		printf("\tProcess ID | Arrival Time | Run Time | Priority |\n");
		printf("\t-------------------------------------------------\n");
		
		while(ptr != NULL) {
			process *_process = (process *)ptr -> data;
			printf("\t%10c | %12.1f | %8.1f | %8d |\n", _process -> _process_id, _process -> _arrival_time, _process -> _service_time, _process -> _priority);
			ptr = ptr -> next;
		}
		printf("\t--------------------------------------------------\n");
		printf("\tTotal No. of Processes : %d\n", proc_list -> size);
		printf("\t--------------------------------------------------\n");

		fcfs[counter] = FCFSNP(proc_list);
		rr[counter] = RRP(proc_list,1);
		sjf[counter] = SJFNP(proc_list);
		srf[counter] = SRTP(proc_list);
		hpfp[counter] = FCFSNP(proc_list);
		hpfnp[counter] = HPFNP(proc_list);
		counter++;
	}

	for (int i = 0; i < 6; i++) {
		result[i]._avg_resp_time = 0;
		result[i]._avg_wait = 0;
		result[i]._avg_tat = 0;
		result[i]._avg_thrghput = 0;
	}

	// Total of all avaerage values
	for (int i = 0; i < 5; i++) {
		result[0]._avg_resp_time += fcfs[i]._avg_resp_time;
		result[1]._avg_resp_time += sjf[i]._avg_resp_time;
		result[2]._avg_resp_time += srf[i]._avg_resp_time;
		result[3]._avg_resp_time += rr[i]._avg_resp_time;
		result[4]._avg_resp_time += hpfp[i]._avg_resp_time;
		result[5]._avg_resp_time += hpfnp[i]._avg_resp_time;
		
		result[0]._avg_wait += fcfs[i]._avg_wait;
		result[1]._avg_wait += sjf[i]._avg_wait;
		result[2]._avg_wait += srf[i]._avg_wait;
		result[3]._avg_wait += rr[i]._avg_wait;
		result[4]._avg_wait += hpfp[i]._avg_wait;
		result[5]._avg_wait += hpfnp[i]._avg_wait;
		
		result[0]._avg_tat += fcfs[i]._avg_tat;
		result[1]._avg_tat += sjf[i]._avg_tat;
		result[2]._avg_tat += srf[i]._avg_tat;
		result[3]._avg_tat += rr[i]._avg_tat;
		result[4]._avg_tat += hpfp[i]._avg_tat;
		result[5]._avg_tat += hpfnp[i]._avg_tat;

		result[0]._avg_thrghput += fcfs[i]._avg_thrghput;
		result[1]._avg_thrghput += sjf[i]._avg_thrghput;
		result[2]._avg_thrghput += srf[i]._avg_thrghput;
		result[3]._avg_thrghput += rr[i]._avg_thrghput;
		result[4]._avg_thrghput += hpfp[i]._avg_thrghput;
		result[5]._avg_thrghput += hpfnp[i]._avg_thrghput;
	}

	// Calculating average
	for (int i = 0; i < 6; i++) {
		result[i]._avg_resp_time /= 5;
		result[i]._avg_wait /= 5;
		result[i]._avg_tat /= 5;
		result[i]._avg_thrghput /= 5;
	}
	
	printf("\n\n\n");

	printf("------------------------------------------------------------------\n\n");
	printf("The average of the 5 runs of every algorithm is as follows:\n");
	printf("\n");

	printf("------------------------------------------------------------------\n\n");
	sleep(1);
	printf("ALGORITHM: First-come First-served (FCFS) [non-preemptive]:\n");
	printf("\n");
	printf("Average Wait Time: %.1f\n",result[0]._avg_wait);
	printf("Average Response Time: %.1f\n",result[0]._avg_resp_time);
	printf("Average _throughput: %.1f\n",result[0]._avg_thrghput);
	printf("Average Turn Around Time: %.1f\n",result[0]._avg_tat);
	printf("\n");

	printf("------------------------------------------------------------------\n\n");
	sleep(1);
	printf("ALGORITHM: Round robin (RR) [preemptive]:\n");
	printf("\n");
	printf("Average Wait Time: %.1f\n",result[3]._avg_wait);
	printf("Average Response Time: %.1f\n",result[3]._avg_resp_time);
	printf("Average _throughput: %.1f\n",result[3]._avg_thrghput);
	printf("Average Turn Around Time: %.1f\n",result[3]._avg_tat);
	printf("\n");

	printf("------------------------------------------------------------------\n\n");
	sleep(1);
	printf("ALGORITHM: Shortest job first (SJF) [non-preemptive]:\n");
	printf("\n");
	printf("Average Wait Time: %.1f\n",result[1]._avg_wait);
	printf("Average Response Time: %.1f\n",result[1]._avg_resp_time);
	printf("Average _throughput: %.1f\n",result[1]._avg_thrghput);
	printf("Average Turn Around Time: %.1f\n",result[1]._avg_tat);
	printf("\n");

	printf("------------------------------------------------------------------\n\n");
	sleep(1);
	printf("ALGORITHM: Shortest remaining time (SRT) [preemptive]:\n");
	printf("\n");
	printf("Average Wait Time: %.1f\n",result[2]._avg_wait);
	printf("Average Response Time: %.1f\n",result[2]._avg_resp_time);
	printf("Average _throughput: %.1f\n",result[2]._avg_thrghput);
	printf("Average Turn Around Time: %.1f\n",result[2]._avg_tat);
	printf("\n");

	printf("------------------------------------------------------------------\n\n");
	sleep(1);
	printf("ALGORITHM: Highest _priority first (HPF) [preemptive]:\n");
	printf("\n");
	printf("Average Wait Time: %.1f\n",result[4]._avg_wait);
	printf("Average Response Time: %.1f\n",result[4]._avg_resp_time);
	printf("Average _throughput: %.1f\n",result[4]._avg_thrghput);
	printf("Average Turn Around Time: %.1f\n",result[4]._avg_tat);
	printf("\n");

	printf("------------------------------------------------------------------\n\n");
	sleep(1);
	printf("ALGORITHM: Highest _priority first (HPF) [non-preemptive]:\n");
	printf("\n");
	printf("Average Wait Time: %.1f\n",result[5]._avg_wait);
	printf("Average Response Time: %.1f\n",result[5]._avg_resp_time);
	printf("Average _throughput: %.1f\n",result[5]._avg_thrghput);
	printf("Average Turn Around Time: %.1f\n",result[5]._avg_tat);
}
