# SHELL

## **_REQUIREMENTS_**:

- GCC compiler
- LINUX OS (Ubuntu)

---

- To execute the program:

```bash
$ make main
$ ./main
```

## Specification 1 :

A shell prompt of the following form will appear

```bash
<username@system_name:curr_dir>
```

- Code is written in modular fashion.
- ';' separated commands are handled.
- Tokenisation is handled in main.c.
- All the headers are included in header.c

## Specification 2 :

### For Command cd :

---

The cd commands work assuming the home directory to be the directory from which the shell is invoked.

- This is written in cd.c

* cd &nbsp; :&nbsp; Directs to the home directory.

* cd ~ &nbsp; : &nbsp; Directs to the home directory.

* cd . &nbsp; : &nbsp; Stays in the same directory.

* cd .. &nbsp; : &nbsp; Directs to the previous directory.

* cd - &nbsp; : &nbsp; Directs to the previous cd command. It prints the address from the systems shell.

- All other cd commands are handled.

### For command pwd :

---

- This is written in pwd.c
- Absolute path from our system's home is printed.

### For command echo:

---

- This is written in echo.c
- The text after echo will be printed.
- Spaces and tabs are handled.

## Specification 3 :

### For command ls:

---

- This is written in ls.c
- All the given ls commands are handled.
- Specific colour coding is used to differentiate between file names, directory names and executables.
- File names are printed in white color.
- Directories are printed in Blue color.
- Executables are printed in green color.

## Specification 4 :

---

- Both the background and foreground processes are handled in fbp.c
- The commands which are followed by '&' are done in background.
- After the process is done in the background, it's name along with pid is printed after the execution of the next command.
- If the process is done in foreground .. time taken for it will be printed in the shell.

## Specification 5:

### For command pinfo:

---

- This is written in pinfo.c
- pinfo prints the process-related info of your shell program.
- "pinfo pid" prints the process info of the given pid.
- '+' is printed in the process status indicating it is a foreground process.

## Specification 6:

---

- Both the background and foreground processes are handled in fbp.c
- The commands which are followed by '&' are done in background.
- If the background process exits then the shell displays the appropriate message to the user.

## Specification 7:

## For command discover:

---

- This is written in discover.c
- This command searches for files in the directory hierarchy.

## Specification 8 :

## For command history:

---

- This is written in history.c
- History command prints the previous 10 commands given in the terminal.
- The command is printed only once if it is the exactly same as the previously entered command of it.

## Specification 9

---

- Specification is handled in io_redirect.c.
- I/O redirection is handled as '<','>','>>'.
- Using execvp command for the commands which are not done in assignment 2.
- It is also handled in main.c

## Specification 10

---

- Specification is handled in pipe.c.
- A pipe, identified by |, redirects the output of the command on the left as input to the command on the right.
- Piping of multiple commands are handled.
- Using execvp command for the commands which are not done in assignment 2.
- It is also handled in main.c

## Specification 11

---

- Specification is handled in pipe.c.
- Input/output redirection occuring with command pipelines is handled.

## Specification 12 :

### For Command jobs :

---

- Specification is handled in jobs.c.
- jobs - prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with their job number,process ID and their state, which can either be running​ or ​stopped​.
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

## Specification 13:

---

- Handled in main.c

### CTRL-Z :

- It pushes any currently running foreground job into the background and changes its state from running to stopped.

### CTRL-C :

- It interrupts any cuurently running foreground job.
- No effect if there is no foreground process running.

### CTRL-D :

- It logs out of the shell.
