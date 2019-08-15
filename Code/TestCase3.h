#ifndef TEST_CASE3_H
#define TEST_CASE3_H
 
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <memory.h>
#include <errno.h>
#include "Init.h"
#include "Thread.h"

#define TOTAL_THREAD_NUM		(5)

int Tc3ThreadProc(int param);
void TestCase3(void);

#endif
