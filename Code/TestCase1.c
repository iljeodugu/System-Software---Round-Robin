#include "TestCase1.h"


 
int
Tc1ThreadProc(int param)
{
	int tid = 0;
	int count = 0;

	tid = thread_self();

	count = 5;
	while (count > 0)
	{
		/* sleep for 1 seconds */
		sleep(2);
		printf("Tc1ThreadProc: my thread id (%d), arg is (%d)\n", tid, param);
		count--;
	}
}

/* 
 * - TestCase1 tests a round-robin scheduling of thread  
 * - Testing API scopes: thread_create
 */
void
TestCase1(void)
{
	thread_t tid[TOTAL_THREAD_NUM];
	
	thread_create(&tid[0], NULL, (void*)Tc1ThreadProc, (int*)1);
	thread_create(&tid[1], NULL, (void*)Tc1ThreadProc, (int*)2);
	thread_create(&tid[2], NULL, (void*)Tc1ThreadProc, (int*)3);
	thread_create(&tid[3], NULL, (void*)Tc1ThreadProc, (int*)4);
	thread_create(&tid[4], NULL, (void*)Tc1ThreadProc, (int*)5);

	while(1){}
	
	return ;
}

