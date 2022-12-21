# OSN
# ASSIGNMENT 3:
### NAME &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; P.ADITYA PAVANI 
### ROLLNO &nbsp; 2021101133
---

## ***REQUIREMENTS***:
- GCC compiler
- LINUX OS (Ubuntu) 

---
* To execute the program:
``` bash
$ make
$ ./main
```
## Specification 1
---
- Specification is handled in io_redirect.c.
- I/O redirection is handled as '<','>','>>'.
- Using execvp command for the commands which are not done in assignment 2.
- It is also handled in main.c

## Specification 2
---
- Specification is handled in pipe.c.
- A pipe, identified by |, redirects the output of the command on the left as input to the command on the right.
- Piping of multiple commands are handled.
- Using execvp command for the commands which are not done in assignment 2.
- It is also handled in main.c

## Specification 3
---
- Specification is handled in pipe.c.
- Input/output redirection occuring with command pipelines is handled.

## Specification 4 :
### For Command jobs :
---
- Specification is handled in jobs.c.
- jobs -  prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with their job number,process ID and their state, which can either be running​ or ​stopped​.
- Flags implemented for the command are -r and -s.

### For Command sig :
---
- This specification is handled in sig.c
- Takes the job number of a running job and sends the signal corresponding to the signal number to that process.
- It will throw error if invalid job number is given.

### For Command fg :
---
- This specification is handled in user_cmnd.c
- This brings the running or stopped background job to the foreground and changes its state to running.
- It will throw error if invalid job number is given.

### For Command bg :
---
- This specification is handled in user_cmnd.c
- It changes the state of a stopped background job to ruuning, which runs in the background.
- It does nothing if the job is already running in the background.
- It will throw error if invalid job number is given.

## Specification 5 :
---
- Handled in main.c
### CTRL-Z : 

- It pushes any currently running foreground job into the background and changes its state from running to stopped.

### CTRL-C : 

- It interrupts any cuurently running foreground job.
- No effect if there is no foreground process running.

### CTRL-D : 

- It logs out of the shell.


