C_SRCS = scheduler.c 
C_OBJS = scheduler.o 

OBJS = ${C_OBJS}
EXE1 = scheduler

GCC = gcc
GCC_FLAGS = -g -Wall -c
LD_FLAGS = - g -Wall


.c:.o
	$(GCC) $(GCC_FLAGS) $<

all: scheduler
scheduler.c: scheduler.o
	$(GCC) $(LD_FLAGS) $(C_SRCS) scheduler.o -o $(EXE1)

$(C_OBJS): $(C_HEADERS)

clean:
	rm -f *.o *~ $(EXE1)
package:
	tar -cvf Armijo-Damian-HW5.tar scheduler.c Makefile README.txt