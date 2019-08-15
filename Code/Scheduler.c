#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include "myHead.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void SchedulerAction()
{
	printf("\n");
	while(ReadyQHead != NULL && (zombieCheck(ReadyQHead->pid) ==1 )) 
	{
		thread_cancel(ReadyQHead->pid);
	}
	if(curThread == NULL)
	{
		if(ReadyQHead != NULL)
		{
			curThread = ReadyQHead;
			ready_list_delete(curThread->pid);
			curThread->status = 0;
			kill(curThread->pid, SIGCONT);
		}
	}
	if(ReadyQHead != NULL)
	{
		_ContextSwitch(curThread->pid, ReadyQTail->pid);
	}
	alarm(TIMESLICE);
}

int 	RunScheduler( void )
{
	struct sigaction act;

	sigemptyset(&act.sa_mask);

	act.sa_handler = SchedulerAction;
	act.sa_flags = 0;

	sigaction(SIGALRM, &act, 0);
	alarm(TIMESLICE);
}

void	_ContextSwitch(int curpid, int tpid)
{
	kill(curpid, SIGSTOP);
	ready_list_insert(curThread);
	curThread->status = 1;

	kill(tpid, SIGCONT);
	curThread = ready_list_find(tpid);
	curThread->status = 0;
	ready_list_pop();
}
