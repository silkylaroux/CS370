# List of files
C_SRCS = ParentProgram.c Executor.c FileOpener.c
C_OBJS = ParentProgram.o Executor.o FileOpener.o
#C_HEADERS
OBJS = ${C_OBJS}
EXE1 = Executor
EXE2 = ParentProgram
EXE3 = FileOpener
#Compiler and loader commands and flags
GCC = gcc
GCC_FLAGS = -std=c11 -g  -Wall -c -I.
LD_FLAGS = -std=c11 -g  -Wall -I.
#Compile .c files to .o files
.c.o:
	$(GCC) $(GCC_FLAGS) $<
#Target is the executable
all: Executor ParentProgram FileOpener
Executor: Executor.o
	$(GCC) $(LD_FLAGS) Executor.o -o $(EXE1) -lrt
ParentProgram: ParentProgram.o
	$(GCC) $(LD_FLAGS) ParentProgram.o -o $(EXE2) -lrt
FileOpener: FileOpener.o
	$(GCC) $(LD_FLAGS) FileOpener.o -o $(EXE3) -lrt
#Recompile C objects if headers change
$(C_OBJS): ${C_HEADERS}
#Clean up the directory
clean:
	rm -f *.o *~ $(EXE1) $(EXE2)
package:
	tar -cvf Armijo-Damian-H4.tar ParentProgram.c Executor.c FileOpener.c Makefile README.txt
