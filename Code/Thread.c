#define _GNU_SOURCE
#include "Thread.h"
#include "Init.h"
#include "Scheduler.h"
#include "myHead.h"

#include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define STACK_SIZE 1024*64
thread_t joinThread;
int join_true;

int 	thread_create(thread_t *thread, thread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
	void* stack;
	Thread* temp;

	temp = (Thread *)malloc(sizeof(Thread));
	stack = malloc(STACK_SIZE);
	if(stack==0)
	{
		perror("malloc : could not allocate stack");
		return -1;
	}

	*(thread) = clone(&(*start_routine), (char*)stack+STACK_SIZE, CLONE_VM|CLONE_SIGHAND|CLONE_FS|CLONE_FILES|SIGCHLD , arg);
	kill(*(thread), SIGSTOP);

	temp->pid = *(thread);
	temp->stackSize = STACK_SIZE;
	temp->status = 1;

	temp->entryPt = (*start_routine);

	ready_list_insert(temp);

	return 1;
}

int 	thread_suspend(thread_t tid)
{
	Thread* temp;

	if(ready_list_find(tid) == NULL)
	{
		return -1;
	}

	temp = ready_list_find(tid);
	ready_list_delete(tid);
	wait_list_insert(temp);
	temp->status = 2;

	return 1;
}


int		thread_resume(thread_t tid)
{
	Thread* temp;

	if(wait_list_find(tid) == NULL)
	{
		return -1;
	}

	temp = wait_list_find(tid);
	wait_list_delete(tid);
	ready_list_insert(temp);
	temp->status = 1;

	return 1;
}


int 	thread_cancel(thread_t tid)
{
	Thread* temp =NULL;
	if(ready_list_find(tid) != NULL)
	{
		temp = ready_list_find(tid);
		ready_list_delete(tid);
	}
	if(wait_list_find(tid) != NULL)
	{
		temp = wait_list_find(tid);
		wait_list_delete(tid);
	}
	if(temp == NULL)
		return -1;

	kill(tid, SIGKILL);
	free(temp);

	return 1;
}


thread_t	thread_self()
{
	return getpid();
}

void joinAct(int signo, siginfo_t *info, void *uarg)
{
	if(info->si_pid != keep->pid && join_true ==1)
	{
		wait_list_delete(keep->pid);
		ready_list_insert(keep);
		join_true =0;
	}
}

int thread_join(thread_t thread, void **retval)
{
	struct sigaction act3;
	sigemptyset(&act3.sa_mask);

	act3.sa_handler = (void *)joinAct;
	act3.sa_flags = SA_NOCLDSTOP|SA_SIGINFO;
	sigaction(SIGCHLD, &act3, 0);

	if(zombieCheck(thread) != 1)
	{
		join_true = 1;
		keep = curThread;
		joinThread = thread;
		wait_list_insert(curThread);

		curThread = NULL;
		while(join_true == 1)
		{
			;
		}
		kill(keep->pid , SIGSTOP);
	}
	thread_cancel(thread);
	return 1;
}
