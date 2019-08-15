#ifndef __THREAD_H__
#define __THREAD_H__
#include<unistd.h>

#define TIMESLICE	(1)


typedef void* (*FUNCPTR)(void* arg);
typedef pid_t	thread_t;
typedef void thread_attr_t;


typedef enum{
	THREAD_STATUS_RUN = 0,
	THREAD_STATUS_READY = 1,
	THREAD_STATUS_BLOCKED = 2,
}ThreadStatus;

typedef struct _Thread Thread;
typedef struct _Thread {
	FUNCPTR				entryPt;
	void*				stackAddr;
	int				stackSize;
	ThreadStatus			status;
	pid_t				pid;
	Thread*				pPrev;
	Thread*				pNext;
} Thread;	


/* head and tail pointers for ready queue */ 
Thread* 	ReadyQHead;
Thread*		ReadyQTail;

/* head and tail pointers for waiting queue */
Thread*		WaitQHead;
Thread*		WaitQTail;


int 		thread_create(thread_t *thread, thread_attr_t *attr, void *(*start_routine) (void *), void *arg);
int 		thread_join(thread_t thread, void **retval);
int 		thread_suspend(thread_t tid);
int			thread_resume(thread_t tid);
int 		thread_cancel(thread_t tid);
thread_t 	thread_self();


#endif /* __THREAD_H__ */


