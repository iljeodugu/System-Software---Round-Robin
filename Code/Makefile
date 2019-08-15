Siso : init.o Scheduler.o TestCase1.o TestCase2.o TestCase3.o TestCase4.o Thread.o TestMain.o myHead.o
	gcc -o Siso init.o Scheduler.o TestCase1.o TestCase2.o TestCase3.o TestCase4.o Thread.o TestMain.o myHead.o
init.o : init.c Init.h
	gcc -c init.c
Scheduler.o : Scheduler.c Init.h Thread.h Scheduler.h myHead.h
	gcc -c Scheduler.c
TestCase1.o : TestCase1.c TestCase1.h
	gcc -c TestCase1.c
TestCase2.o : TestCase2.c TestCase2.h
	gcc -c TestCase2.c
TestCase3.o : TestCase3.c TestCase3.h
	gcc -c TestCase3.c
TestCase4.o : TestCase4.c TestCase4.h
	gcc -c TestCase4.c
TestMain.o : TestMain.c TestCase1.h TestCase2.h TestCase3.h TestCase4.h Init.h Scheduler.h Thread.h
	gcc -c TestMain.c
Thread.o : Thread.c Thread.h Init.h Scheduler.h myHead.h
	gcc -c Thread.c
myHead.o : myHead.c Thread.h myHead.h
	gcc -c myHead.c
