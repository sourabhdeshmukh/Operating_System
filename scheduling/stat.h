/* stat.h file defines enumerations, structures, and function prototypes related to process scheduling 
and statistics. It provides a framework for managing and analyzing process behavior and statistics 
in scheduling scenarios.*/

#ifndef _stat_h_
#define _stat_h_

#include "process.h"

/*
UNUSED: Represents an unused process.
EMBRYO: Represents a new process that is currently being created.
SLEEPING: Represents a process blocked for I/O.
RUNNING: Represents a process that is currently executing.
ZOMBIE: Represents a process whose execution is completed, but it still has an entry in the process table.
*/

enum State {UNUSED, EMBRYO, SLEEPING, RUNNING, ZOMBIE};

// This structure represents statistics related to a process

struct process_stat_schedule {
	process * proc; // A pointer to the associated process.
	float _wait_time; // The wait time of the process.
	float _turn_around_time; // The turnaround time of the process.
	float _response_time; // The response time of the process.

	float _start_time; //  The start time of the process.
	float _end_time; // The end time of the process.
	float _service_time; // The service time of the process.

	enum State state; // The state of the process 
};
typedef struct process_stat_schedule proc_stats;

// This structure represents statistics related to process scheduling.

struct stat_schedule {
	_linked_list * processQueue; // A pointer to a linked list that stores processes.
	_linked_list * time_chart; // A pointer to a linked list that represents a time chart.
	float _avg_turnaround_time; // The average turnaround time of processes.
	float __avg_waiting_time; // The average waiting time of processes.
	float _avg_resp_time; // The average response time of processes.
	float _throughput; // The _throughput of processes.
	int _total_quanta; // The total quanta of processes.
};

typedef struct stat_schedule scheduling_stat;

// This structure is used to store average statistics related to processes. 

struct average_stats_proces{
	float _avg_resp_time; // The average response time of processes.
	float _avg_wait; // average wait time
	float _avg_tat; //  average turnaround time
	float _avg_thrghput; // average _throughput 
};

typedef struct average_stats_proces _avg_stats;

_avg_stats FCFSNP(_linked_list * processes);
_avg_stats SJFNP(_linked_list * processes);
_avg_stats SRTP(_linked_list * processes);
_avg_stats RRP(_linked_list * processes,int time_slice);
_avg_stats HPFP(_linked_list * processes);
_avg_stats HPFNP(_linked_list * processes);
_avg_stats HPFPAging(_linked_list * processes);
_avg_stats HPFNPAging(_linked_list * processes);

// Printing Statistics

_avg_stats printpolicyStats(_linked_list * linkL);
#endif