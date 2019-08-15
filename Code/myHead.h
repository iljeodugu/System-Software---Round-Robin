#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "Thread.h"

Thread* curThread;
int join_true;
Thread* keep;
int join_true;

Thread* ready_list_find(int tpid);
void ready_list_insert(Thread* thread);
Thread* ready__list_pop();
int ready_list_count();
Thread* wait_list_find(int tpid);
void wait_list_insert(Thread* thread);
Thread* wait__list_pop();
int wait_list_count();
int zombieCheck(thread_t tid);
