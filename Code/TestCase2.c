#include "TestCase2.h"

 
int
Tc2ThreadProc(int param)
{
	thread_t tid = 0;

	tid = thread_self();

	while (1)
	{
		sleep(2);
		printf("Tc2ThreadProc: my thread id (%d) arg (%d)\n", tid, param);
	}
	return 0;
}

/* 
 * - TestCase2 checks wether running Thread can be normally deleted.
 * - Tesing API scopes: thread_create, thread_cancel
 */
void
TestCase2(void)
{
	thread_t tid[TOTAL_THREAD_NUM];
	int i = 0;
	signal(SIGCHLD,SIG_IGN);

	thread_create(&tid[0], NULL, (void*)Tc2ThreadProc, (int*)1);	
	thread_create(&tid[1], NULL, (void*)Tc2ThreadProc, (int*)2);	
	thread_create(&tid[2], NULL, (void*)Tc2ThreadProc, (int*)3);	
	thread_create(&tid[3], NULL, (void*)Tc2ThreadProc, (int*)4);	
	thread_create(&tid[4], NULL, (void*)Tc2ThreadProc, (int*)5);	

	
	for (i = 0;i < TOTAL_THREAD_NUM;i++)
	{
		sleep(2);	
		thread_cancel(tid[i]);
	}

	return ;
}

