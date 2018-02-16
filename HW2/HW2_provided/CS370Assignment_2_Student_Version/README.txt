README
======

This package includes the following files.

|-- ParentProgram.c [This is the driver program which will be used to open and read the file and also to invoke the child processes]
|-- Executor.c [Executes a UNIX command passed as an argument to it. Should be invoked by the child processes only.]
|-- Makefile [For compiling, cleaning and taring]. This file has been provided
|-- README.txt [This file]

====================================================================================================================================
                                QUESTIONS:
1. What are the possible values/ range of values returned by the fork() and
what do they mean?
    
    If fork returns 0 then the process was correctly forked and is a child process. If the fork
returns a value greater than 0 it was correctly forked, and is a parent process. If the value is less
than 0 the fork was not done successfully. 

2. What does the system( ) function do, and what are the possible return
values?

    The system() is a c library function that returns information about the system.
It returns what is returned in the terminal if the same commands are run in the terminal. In other
words it returns information such as date, calender, folder info...etc. The return values are -1 if 
the system() call failed, otherwise it returns exit code of the command.
