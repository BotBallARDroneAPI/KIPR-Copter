/*
 *  process.cpp
 *  KiprCopter_Project
 *
 *  Created by administrator on 9/16/12.
 *  Copyright 2012 SIUE. All rights reserved.
 *
 */

#include "process.h"

volatile struct __ptable_entry __process_table[MAX_PROCESSES];
pthread_mutex_t __process_mutex = PTHREAD_MUTEX_INITIALIZER;
volatile int __ptable_initted = 0;

void __init_ptable()
{
	int i;
	
	for(i = 0;i < MAX_PROCESSES;i++)
		__process_table[i].in_use = 0;
	
	__ptable_initted = 1;
}

int start_process(void (*func)())
{
	int i = -1;
	
	pthread_mutex_lock(&__process_mutex);
	
	if(!__ptable_initted)
		__init_ptable();
	
	while(++i < MAX_PROCESSES && __process_table[i].in_use);
	
	if(i == MAX_PROCESSES)
		return -1;
	
	__process_table[i].in_use = 1;
	
	if(pthread_create((pthread_t *)&(__process_table[i].thread), NULL, __run_process, (void *)func)) {
		__process_table[i].in_use = 0;
		return -1;
	}
	
	pthread_mutex_unlock(&__process_mutex);
	
	return i;
}

void kill_process(int pid)
{
	pthread_mutex_lock(&__process_mutex);
	
	if(__process_table[pid].in_use) {
		pthread_cancel(__process_table[pid].thread);
		__process_table[pid].in_use = 0;
	}
	
	pthread_mutex_unlock(&__process_mutex);
}

int is_process_running(int pid)
{
	pthread_mutex_lock(&__process_mutex);
	
	if(pthread_kill(__process_table[pid].thread, 0)) {
		pthread_mutex_unlock(&__process_mutex);
		return 0;
	}
	
	pthread_mutex_unlock(&__process_mutex);
	return 1;
}


void *__run_process(void *ptr)
{
	void (*func)() = ptr;
	func();
	return 0;
}