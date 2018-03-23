README
======

This package includes the following files.

|-- ParentProgram.c [This is the driver program which will create a pipe and also to invoke the child processes]
|-- Executor.c [Executes a UNIX command passed as an argument to it. Should be invoked by the child processes only.]
|-- Makefile [For compiling, cleaning and taring]. This file has been provided
|-- FileOpener.c [This is the program that will be used to open and read the file into the pipe.]
|-- README.txt [This file]

====================================================================================================================================
                                QUESTIONS:
1.) What does pipe( ) do and what does it return? 

    It creates a pipe, which is an a channel of communication between processes. The [0] of the
    pipe is to the read, and the [1] is the writing to the pipe. It returns 0 if successful, -1
    if unsuccessful.

2.) What function is used for opening a shared memory object? What are the possible oflag
values. Give just one line description each oflags value.

    shm_open() is used to open a shared memory object. The possible oflags are:
    O_RDWR - Open with read-wrtie access.
    O_CREAT - Create the shared memory object if it does not exist.
    O_EXCL - Return error if a shared memory object with the given name already exists.
    O_TRUNC - If a shared memory object with the given name already exists truncate it to zero bytes.
    O_RDONLY - Open with read only access.