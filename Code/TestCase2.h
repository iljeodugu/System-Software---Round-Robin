#ifndef TEST_CASE2_H
#define TEST_CASE2_H
 
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include "Thread.h"

#define TOTAL_THREAD_NUM		(5)

int Tc2ThreadProc(int param);
void TestCase2(void);

#endif
