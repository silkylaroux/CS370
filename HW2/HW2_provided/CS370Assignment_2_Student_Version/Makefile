# List of files
C_SRCS = ParentProgram.c Executor.c
C_OBJS = ParentProgram.o Executor.o
#C_HEADERS
OBJS = ${C_OBJS}
EXE1 = Executor
EXE2 = ParentProgram
#Compiler and loader commands and flags
GCC = gcc
GCC_FLAGS = -std=c11 -g  -Wall -c -I.
LD_FLAGS = -std=c11 -g  -Wall -I.
#Compile .c files to .o files
.c.o:
	$(GCC) $(GCC_FLAGS) $<
#Target is the executable
all: Executor ParentProgram
Executor: Executor.o
	$(GCC) $(LD_FLAGS) Executor.o -o $(EXE1)
ParentProgram: ParentProgram.o
	$(GCC) $(LD_FLAGS) ParentProgram.o -o $(EXE2)
#Recompile C objects if headers change
$(C_OBJS): ${C_HEADERS}
#Clean up the directory
clean:
	rm -f *.o *~ $(EXE1) $(EXE2)
package:
	tar -cvf Lastname-Firstname-HW2.tar ParentProgram.c Executor.c Makefile README.txt
