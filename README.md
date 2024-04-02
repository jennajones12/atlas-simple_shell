# simple_shell

## Repository Description

This repository contains files to simulate simple shell implementation with a program is written in C language. It serves as a basic interactive shell that continuously reads commands from the user, executes them, and waits for their completion. It is made to carry out specific funtionality based on the C - Simple Shell project at [Atlas School](https://www.atlasschool.com/welcome).

## Project Requirements

- Allowed editors: vi, vim, emacs.
- All files will be compiled on Ubuntu 14.04 LTS.
- Your C programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic.
- All your files should end with a new line.
- A README.md file, at the root of the folder of the project is mandatory.
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl.
- Your shell should not have any memory leaks.
- No more than 5 functions per file.
- All your header files should be include guarded.
- Use system calls only when you need to.

## Allowed Functions and System Calls

- `access`
- `chdir`
- `close`
- `closedir`
- `execve`
- `exit`
- `_exit`
- `fflush`
- `fork`
- `free`
- `getcwd`
- `getline`
- `isatty`
- `kill`
- `malloc`
- `open`
- `opendir`
- `perror`
- `printf`
- `fprintf`
- `vfprintf`
- `sprintf`
- `putchar`
- `read`
- `readdir`
- `signal`
- `stat`
- `lstat`
- `fstat`
- `strtok`
- `wait`
- `waitpid`
- `wait3`
- `wait4`
- `write`

## Process Description

1. Initialization

The program begins by including necessary header files and defining constants like MAX_INPUT_SIZE and PROMPT. It also declares function prototypes for functions defined in main.h.

2. Main Function (main())

The main() function is the entry point of the program. It initializes variables and checks if the shell is running in an interactive mode using isatty(STDIN_FILENO).

3. Shell Loop: The program enters a while loop that continues indefinitely (while(1)).

4. Interactive Mode: Inside the loop, if the shell is running interactively, it prints a prompt (PROMPT) and flushes the standard output.

_Note_: there are two ways of using the command interpreter:

#### Interactive mode:

```
 $ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

#### Non-interactive mode:

```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```

5. Print Prompt and Read Input

Inside the loop, it prints the shell prompt (PROMPT) and reads input from the user using the read_line() function. The read_line() function dynamically allocates memory to store the input line using getline().

![getline](https://github.com/jennajones12/atlas-simple_shell/assets/116591011/0746f533-7a23-4f77-965c-e42c42088328)

6. Check for End of File or Empty Input

It checks if the input is NULL or if it has reached the end of the file (EOF). If so, and if it's an interactive session, it prints a newline and exits with either success or failure depending on the input.

7. Tokenization

If the input line is not empty, it tokenizes the input line into separate arguments using the split_line() function. The split_line() function dynamically allocates memory for storing tokens and returns an array of pointers to tokens.

![splitline](https://github.com/jennajones12/atlas-simple_shell/assets/116591011/05314932-df6b-4dfb-8bd8-508eac846ee2)

8. Check for Empty Arguments

It checks if the first argument (command) is empty or null. If so, it continues to the next iteration of the loop without executing the command.

9. Forking

The program forks a child process using fork(). 

10. Child Process

In the child process, it attempts to execute the command using execve().
If execve() fails, it prints an error message using perror() and exits the child process with a failure status.

11. Parent Process

In the parent process (pid > 0), it waits for the child process to complete using waitpid().

12. Error Handling:

If fork() fails, it prints an error message using perror().

13. Memory Deallocation

After executing the command, it deallocates the dynamically allocated memory for the input line and the tokens.

14. Memory Cleanup

The allocated memory for the command and arguments is freed before looping back.

15. Loop Continuation

The loop continues indefinitely, allowing the user to enter more commands.

## Compilation

Shell will be compiled this way:
    
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh


## Index

| Files                                | Description and contents                                                                                                                                                               |
| ---------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [man_1_simple_shell](man_1_simple_shell) | This is the manpage for the shell for use on how to use the shell its correct syntaxes. |
| [main.h](main.h)                       | This is the header file with all the prototypes of our functions.  
| [container.c](container.c) | File with function that tokenizes the input string based on the specified delimiter and returns an array of strings containing the separated substrings.
| [get_line.c](get_line.c) | Function to read a line from the standard input (stdin). getline() dynamically allocates memory for line and updates the size in buffer.
| [simple_shell.c](simple_shell.c) | File with main shell function.
| [splitter.c](splitter.c) | File with function that splits a string into tokens based on specified delimiters and returns an array of pointers to these tokens
| [pathfinder.c](pathfinder.c) | File with function that resolves the full path to an executable command based on the PATH environment variable and the provided command name. 

## Authors
[Joshua Cox](Joshua.Cox@atlasschool.com) |
[Jenna Jones](Jenna.Jones@atlasschool.com)
