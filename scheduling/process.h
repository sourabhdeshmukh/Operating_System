/*  This header file provides a structure definition for processes, 
function prototypes for creating processes and generating linked lists of processes, 
and includes another header file named "utility.h." To use these declarations and definitions, 
you would typically include this header file in your source code files that require process 
management functionality by using #include "process.h".*/

#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "utility.h"

struct process_s {
	unsigned char _process_id;
	float _arrival_time;
	float _service_time;
	unsigned int _priority; 
};

typedef struct process_s process;

process *createProceses(char _process_id, float _arrival_time, float _service_time, unsigned int _priority);

// The code declares a function prototype for a function named generateProcesses. This function takes an integer n as an argument and returns a pointer to a _linked_list 
_linked_list *generateProceses(int n);

#endif