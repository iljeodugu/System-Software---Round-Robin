#include "Thread.h"
#include "myHead.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int zombieCheck(thread_t tid)//if zombie -> 1 return
{
	int fd;
	char file_name[64] = "/proc/";
	char temp[16];
	char file_sorce[8] = "n";
	char file_sorce2 = 'n';
	int count =0;

	sprintf(temp, "%d", tid);
	strcat(file_name, temp);
	strcat(file_name, "/stat");

	if((fd = open(file_name, O_RDONLY))==-1)
	{
		return -1;
	}

	while(count <3)//status get
	{
		file_sorce2 = file_sorce[0];
		read(fd, file_sorce, 1);

		if(file_sorce[0] == ' ')
		{
			count ++;
		}
	}

	close(fd);

	if(file_sorce2 == 'Z')//if zomibe return 1
	{
		return 1;
	}
	return 0;
}

Thread* ready_list_find(int tpid)//in ready list find tpid, and return Thread
{
	Thread* temp;

	if(ReadyQHead == NULL)
		return NULL;

	for(temp = ReadyQHead ; temp->pNext != NULL ; temp = temp->pNext)
	{
		if(temp->pid == tpid)
		{
			return temp;
		}
	}
	if(ReadyQTail->pid == tpid)
	{
		return ReadyQTail;
	}

	return NULL;
}

void ready_list_delete(int tid)//if find tid, delete tid, but return -1
{
	Thread* temp;
	Thread* pre;
	Thread* nex;

	temp = ready_list_find(tid);
	if(tid == ReadyQTail->pid)
	{
		ready_list_pop();
	}
	else if( tid == ReadyQHead->pid)
	{
		temp = ReadyQTail;
		if(ReadyQHead != ReadyQTail)
		{
			ReadyQHead = ReadyQHead->pNext;
			ReadyQHead->pPrev =NULL;
		}
	}
	else
	{
		pre = temp->pPrev;
		nex = temp->pNext;
		if(pre != NULL)
		{
			pre->pNext = nex;
		}
		if(nex != NULL)
		{
			nex->pPrev = pre;
		}
		temp->pNext = NULL;
		temp->pPrev = NULL;
	}
}

void ready_list_insert(Thread* thread)//insert thread to readyQ
{
	Thread* temp;
	if(ReadyQHead != NULL)
	{
		ReadyQHead->pPrev = thread;
	}
	else
	{
		ReadyQTail = thread;
	}
	thread->pNext = ReadyQHead;
	ReadyQHead = thread;
}

void ready_list_pop()//remove ReadyQTail
{
	if(ReadyQHead != NULL)
	{
		if(ReadyQHead != ReadyQTail)
		{
			ReadyQTail = ReadyQTail->pPrev;
			ReadyQTail->pNext =NULL;
		}
		else
		{
			ReadyQTail = NULL;
			ReadyQHead = NULL;
		}
	}
}

int ready_list_count()//count how many list
{
	Thread* temp;
	int count=0 ;
	if(ReadyQHead ==NULL)
		return 0;

	for(temp = ReadyQHead ; temp != ReadyQTail ; temp = temp->pNext)
	{
		count ++;
	}

	return ++count ;
}

Thread* wait_list_find(int tpid)
{
	Thread* temp;

	if(WaitQHead == NULL)
		return NULL;

	for(temp = WaitQHead ; temp->pNext != NULL ; temp = temp->pNext)
	{
		if(temp->pid == tpid)
		{
			return temp;
		}
	}
	if(WaitQTail->pid == tpid)
	{
		return WaitQTail;
	}

	return NULL;
}

void wait_list_insert(Thread* thread)
{
	Thread* temp;
	if(WaitQHead != NULL)
	{
		WaitQHead->pPrev = thread;
	}
	else
	{
		WaitQTail = thread;
	}
	thread->pNext = WaitQHead;
	WaitQHead = thread;
}

void wait_list_delete(int tid)
{
	Thread* temp;
	Thread* pre;
	Thread* nex;

	temp = wait_list_find(tid);
	if(tid == WaitQTail->pid)
	{
		wait_list_pop();
	}
	else if( tid == WaitQHead->pid)
	{
		temp = WaitQTail;
		if(WaitQHead != WaitQTail)
		{
			WaitQHead = WaitQHead->pNext;
			WaitQHead->pPrev =NULL;
		}
	}
	else
	{
		pre = temp->pPrev;
		nex = temp->pNext;
		if(pre != NULL)
		{
			pre->pNext = nex;
		}
		if(nex != NULL)
		{
			nex->pPrev = pre;
		}
		temp->pNext = NULL;
		temp->pPrev = NULL;
	}
}

void wait_list_pop()
{
	if(WaitQHead != NULL)
	{
		if(WaitQHead != WaitQTail)
		{
			WaitQTail = WaitQTail->pPrev;
			WaitQTail->pNext =NULL;
		}
		else
		{
			WaitQTail = NULL;
			WaitQHead = NULL;
		}
	}
}

int wait_list_count()
{
	Thread* temp;
	int count=0 ;
	if(WaitQHead ==NULL)
		return 0;

	for(temp = WaitQHead ; temp != WaitQTail ; temp = temp->pNext)
	{
		count ++;
	}

	return ++count ;
}
