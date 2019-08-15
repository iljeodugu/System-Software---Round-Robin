#ifndef TEST_CASE4_H
#define TEST_CASE4_H
 
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include "Thread.h"


#define TOTAL_THREAD_NUM		(5)
 

int Tc4ThreadProc(int param);
void TestCase4(void);


#endif
