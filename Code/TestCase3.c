#include "TestCase3.h"

int
Tc3ThreadProc(int param)
{
	thread_t tid = 0;
	int count = 0;
	int i;

	tid = thread_self();

	for(i=0;i<10;i++)
	{
		sleep(2);
		printf("Tc3ThreadProc : my thread id (%d), arg is (%d)\n", tid, param);
		count++;
	}
	return count;
}

/* 
 * - Testcase3 tests thread_join works successfully.
 * - 
 */
void
TestCase3(void)
{
	thread_t tid[TOTAL_THREAD_NUM];
	int result[TOTAL_THREAD_NUM];

	int i = 0;
	thread_create(&tid[0], NULL, (void*)Tc3ThreadProc,(int*) 1);	
	thread_create(&tid[1], NULL, (void*)Tc3ThreadProc,(int*) 2);	
	thread_create(&tid[2], NULL, (void*)Tc3ThreadProc,(int*) 3);	
	thread_create(&tid[3], NULL, (void*)Tc3ThreadProc,(int*) 4);	
	thread_create(&tid[4], NULL, (void*)Tc3ThreadProc,(int*) 5);
	
	for(i=0;i<TOTAL_THREAD_NUM;i++)
	{
		thread_join(tid[i],NULL);
		printf("Thread %d is finish\n",tid[i]);
	}

	return ;
}
