# Unix-Shell
Unix Shell (called nush) -- works the same as bash$

A shell operates as follows:

Accepts an optional script file as the first command line argument.
If there's no script, it shows a prompt "nush$ ".
Command input is accepted on the same line after the prompt.
Reads one line of commands from either stdin or the script.
Executes that line of commands.
Repeats until EOF or an "exit" command.

Command lines are made up of:

Programs to execute.
Built-in commands.
Command line arguments to programs / builtins.
Operators.

My shell does three things:

fork(), to create a new process.
in the child process, exec(), it executes the requested program, passing through the three command line arguments
in the parent process, wait() or waitpid(), it allows the program to finish before executing another command

Some commands aren't programs to execute, they're things that the shell should handle itself.

The "cd" command changes the current directory. This means calling chdir() to change the state of your shell process.
The "exit" command exits the shell.
In bash, lots of commands that are available as programs are actually built-in for efficiency,
like pwd, echo, etc. My shell just runs these as programs.

Operators either modify the behavior of one command or chain together multiple commands into a single command line.

My shell supports seven operators:

Redirect input: sort < foo.txt
Redirect output: sort foo.txt > output.txt
Pipe: sort foo.txt | uniq
Background: sleep 10 &
And: true && echo one
Or: true || echo one
Semicolon: echo one; echo two

The program was checked with valgrind to make sure I had no memory allocation issues.
