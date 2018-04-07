C_SRCS = Scheduler.c 
C_OBJS = Scheduler.o 

OBJS = ${C_OBJS}
EXE1 = Scheduler

GCC = gcc
GCC_FLAGS = -g -Wall -c
LD_FLAGS = - g -Wall


.c:.o
	$(GCC) $(GCC_FLAGS) $<

all: Scheduler
Scheduler.c: Scheduler.o
	$(GCC) $(LD_FLAGS) $(C_SRCS) scheduler.o -o $(EXE1)

$(C_OBJS): $(C_HEADERS)

clean:
	rm -f *.o *~ $(EXE1)
package:
	tar -cvf Armijo_Damian_HW5.tar Scheduler.c Makefile README.txt