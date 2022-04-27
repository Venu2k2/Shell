I have implemented the input/output redirection in the original functions by taking a IO_FLAG which will consider input output redirection.
I have implemented pipes by maintaing pipe() function and wrote the code in  pipe.c file with the PIPE_FLAG wihch will consider the piping.
These two were combinedly implemented so that the combination of them works without extra functions.
I have implemented the jobs specification in the jobs.c function which will consider all the required parts.
Signal handling has been handled using extra functions like ctrlz,ctrlc.

Assumptions I took:

1. There are at max 256 possible pipes, redirections possible at a given time.
2. There should be a space before and after a '|' and after '>' 