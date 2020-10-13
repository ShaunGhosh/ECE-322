General Overview of Unix Shells

A shell is an interactive command-line interpreter that runs programs on behalf of the user. A shell repeatedly prints a prompt, waits for a command line on stdin, and then carries out some action, as directed by the contents of the command line.

The command line is a sequence of ASCII text words delimited by whitespace. The first word in the command line is either the name of a built-in command or the pathname of an executable file. The remaining words are command-line arguments. If the first word is a built-in command, the shell immediately executes the command in the current process. Otherwise, the word is assumed to be the pathname of an executable program. In this case, the shell forks a child process, then loads and runs the program in the context of the child. The child processes created as a result of interpreting a single command line are known collectively as a job. In general, a job can consist of multiple child processes connected by Unix pipes.

If the command line ends with an ampersand "&", then the job runs in the background, which means that the shell does not wait for the job to terminate before printing the prompt and awaiting the next command line. Otherwise, the job runs in the foreground, which means that the shell waits for the job to terminate before awaiting the next command line. Thus, at any point in time, at most one job can be running in the foreground. However, an arbitrary number of jobs can run in the background.

For example, typing the command line

tsh> jobs

causes the shell to execute the built-in jobs command.  Typing the command line

tsh> /bin/ls -l -d

runs the ls program in the foreground. By convention, the shell ensures that when the program begins executing its main routine

int main(int argc, char *argv[])

the argc and argv arguments have the following values

- argc == 3
- argv[0] = "/bin/ls"
- argv[1] = "-l"
- argv[2] = "-d"

Alternatively, typing the command line

tsh> /bin/ls -l -d &

runs the ls program in the background.

Unix shells support the notion of job control, which allows users to move jobs back and forth between the background and foreground, and to change the process state (running, stopped, or terminated) of the processes in a job. Typing Ctrl-c causes a SIGINT signal to be delivered to each process in the foreground job. The default action for SIGINT is to terminate the process. Similarly, typing Ctrl-z causes a SIGTSTP signal to be delivered to each process in the foreground job. The default action for SIGTSTP is to place a process in the stopped state, where it remains until it is awakened by the receipt of a SIGCONT signal. Unix shells also provide various built-in commands that support job control. For example:

- jobs: List the running and stopped background jobs.
- bg <job>: Change a stopped background job to a running background job.
- fg <job>: Change a stopped or running background job to running in the foreground.
- kill <job>: Terminate a job.

The tsh Specification

Your tsh shell should have the following features:

- The prompt should be the string "tsh>".

- The command line typed by the user should consist of a name and zero or more arguments, all separated by one or more spaces. If name is a built-in command, then tsh should handle it immediately and wait for the next command line. Otherwise, tsh should assume that name is the path of an executable file, which it loads and runs in the context of an initial child process (in this context, the term job refers to this initial child process).

- tsh need not support pipes (|) or I/O redirection (< and >).  However, if you are interested in how pipes and redirection are implemented, a brief guide on how to implement them is here. 

- Typing ctrl-c (ctrl-z) should cause a SIGINT (SIGTSTP) signal to be sent to the current foreground job, as well as any descendants of that job (e.g., any child processes that it forked). If there is no foreground job, then the signal should have no effect.

- If the command line ends with an ampersand &, then tsh should run the job in the background. Otherwise, it should run the job in the foreground.

- Each job can be identified by either a process ID (PID) or a job ID (JID), which is a positive integer assigned by tsh. JIDs should be denoted on the command line by the prefix "%". For example, "%5" denotes JID 5, and "5" denotes PID 5. (We have provided you with all of the routines you need for manipulating the job list.)

- tsh should support the following built-in commands:
    1. The quit command terminates the shell.
    2. The jobs command lists all background jobs.
    3. The bg <job> command restarts <job> by sending it a SIGCONT signal, and then runs it in the background. The <job> argument can either be a PID or a JID.
    4. The fg <job> command restarts <job> by sending it a SIGCONT signal, and then runs it in the foreground.  The <job> argument can be either a PID or a JID.

- tsh should reap all of its zombie children. If any job terminates because it receives a signal that it didn't catch, then tsh should recognize this event and print a message with the job's PID and a description of the offending signal.

Checking Your Work

We have provided some tools to help you check your work.

Reference solution. The Linux executable tshref is the reference solution for the shell. Run this program to resolve any questions you have about how your shell should behave. Your shell should emit output that is identical to the reference solution (except for PIDs, of course, which change from run to run).

Shell driver. The sdriver.pl program executes a shell as a child process, sends it commands and signals as directed by a trace file, and captures and displays the output from the shell.

Use the -h argument to find out the usage of sdriver.pl:

unix> ./sdriver.pl -h
Usage: sdriver.pl [-hv] -t <trace> -s <shellprog> -a <args>
Options:
    -h                  Print this message
    -v                  Be more verbose
    -t <trace>    Trace file
    -s <shell>     Shell program to test
    -a <args>     Shell arguments
    -g                  Generate output for autograder

We have also provided 16 trace files (trace{01-16}.txt) that you will use in conjunction with the shell driver to test the correctness of your shell. The lower-numbered trace files do very simple tests, and the higher-numbered tests do more complicated tests.

You can run the shell driver on your shell using trace file trace01.txt (for instance) by typing:

unix> ./sdriver.pl -t trace01.txt -s ./tsh -a "-p"

(the -a "-p" argument tells your shell not to emit a prompt), or

unix> make test01

Similarly, to compare your result with the reference shell, you can run the trace driver on the reference shell by typing:

unix> ./sdriver.pl -t trace01.txt -s ./tshref -a "-p"

or

unix> make rtest01

For your reference, tshref.out gives the output of the reference solution on all traces. This might be more convenient for you than manually running the shell driver on all trace files.

The neat thing about the trace files is that they generate the same output you would have gotten had you run your shell interactively (except for an initial comment that identifies the trace). For example:

ece373> make test15
./sdriver.pl -t trace15.txt -s ./tsh -a "-p" #
# trace15.txt - Putting it all together
#
tsh> ./bogus
./bogus: Command not found.
tsh> ./myspin 10
Job (9721) terminated by signal 2
tsh> ./myspin 3 &
[1] (9723) ./myspin 3 &
tsh> ./myspin 4 &
[2] (9725) ./myspin 4 &
tsh> jobs
[1] (9723) Running ./myspin 3 & [2] (9725) Running ./myspin 4 & tsh> fg %1
Job [1] (9723) stopped by signal 20 tsh> jobs
[1] (9723) Stopped
[2] (9725) Running
tsh> bg %3
%3: No such job
tsh> bg %1
[1] (9723) ./myspin 3 &
tsh> jobs
[1] (9723)
[2] (9725)
tsh> fg %1
tsh> quit
ece373>