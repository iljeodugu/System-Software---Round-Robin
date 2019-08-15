#include "TestCase4.h"
 
int
Tc4ThreadProc(int param)
{
	thread_t tid = 0;

	tid = thread_self();
	while (1)
	{
		sleep(2);
		printf("Tc4ThreadProc: my thread id:(%d), arg : %d\n", tid, param);
	}
}

/* 
 * - TestCase4 tests suspending, resuming and deleting Threads. 
 * - Testing API scopes: thread_suspend, thread_resume, thread_cancel,thread_self
 */
 
void
TestCase4(void)
{
	thread_t tid[TOTAL_THREAD_NUM];
	int i = 0;
	int j = 0;
	signal(SIGCHLD,SIG_IGN);
	
	thread_create(&tid[0], NULL, (void*)Tc4ThreadProc, (int*)1);	
	thread_create(&tid[1], NULL, (void*)Tc4ThreadProc, (int*)2);	
	thread_create(&tid[2], NULL, (void*)Tc4ThreadProc, (int*)3);	
    thread_create(&tid[3], NULL, (void*)Tc4ThreadProc, (int*)4);	
    thread_create(&tid[4], NULL, (void*)Tc4ThreadProc, (int*)5);	

	/* Suspend all thread */
	for (i = 0; i < TOTAL_THREAD_NUM;i++)
	{
		sleep(2);
		
		if (thread_suspend(tid[i]) == -1)
		{
			printf("TestCase3: Thread suspending Failed..\n");
			assert(0);
		}
		
		Thread *temp = WaitQHead;
		
		for(j=0;j<i;j++)
			temp=temp->pNext;
		
		if(temp->status != 2)
		{
			printf("TestCase4: Thread is not suspended");
			assert(0);
		}
	}

	/* Resume thread sequentially */
	for (i=0;i<TOTAL_THREAD_NUM;i++)
	{
		sleep(2);
		
		if(thread_resume(tid[i])==-1)
		{
			printf("Testcase4: Thread resume Failed");
			assert(0);
		}
	}

	/* Cancel the thread sequentially */
	for (i=0;i<TOTAL_THREAD_NUM;i++)
	{
		sleep(2);
		
		if(thread_cancel(tid[i])==-1)
		{
			printf("TestCase4: Thread cancel Failed");
			assert(0);
		}
	}
	
	return ;
}
