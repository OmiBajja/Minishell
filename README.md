## 🐚 Minishell: Our Own UNIX Shell

---

![](https://github.com/OmiBajja/Minishell/blob/main/include/MinishellGIF.gif)

### What is Minishell?

Minishell is the first group project in **42 school**. It requires building a **simplified Bash shell**.

This program is a command-line interpreter. It takes user commands, executes them, and manages the output. It works just like your daily terminal. 
Built in C, the project focuses on the core mechanics of operating systems: process management and input/output redirection.
### Key Features Implemented

The goal of Minishell is to correctly handle a core set of shell functionalities, including:

*   **Command Execution:** Running external executables found in the system's `$PATH`.
*   **Command Line Lexing/Parsing:** Breaking down the user input into tokens, handling quotes, and identifying commands and arguments.
*   **Pipes (`|`):** Allowing the output of one command to be used as the input for another (e.g., `ls -l | grep .c`).
*   **Redirections (`<`, `>`, `>>`):** Changing the standard input and output to files.
*   **Environment Variables:** Accessing and managing shell variables (e.g., `$USER`, `$HOME`).
*   **Built-in Commands:** Implementing essential shell commands internally:
    *   `echo`: With the `-n` option.
    *   `cd`: Changing the current directory.
    *   `pwd`: Printing the working directory.
    *   `export`: Setting new environment variables.
    *   `unset`: Removing environment variables.
    *   `env`: Displaying the environment variables.
    *   `exit`: Exiting the shell.

---

### What We Learned 🧠

This project was a deep dive into the core of how operating systems work. The key takeaways and skills acquired include:

*   **Process Management:** Gaining a solid understanding of how to use essential UNIX system calls:
    *   `fork()`: Creating child processes to execute commands.
    *   `execve()`: Replacing the current process with a new program.
    *   `waitpid()`: Waiting for child processes to terminate.
*   **Inter-Process Communication (IPC):** Mastering the use of **pipes** (`pipe()`) to connect the standard output of one process to the standard input of another, which is crucial for the shell's piping feature.
*   **File Descriptors and I/O Redirection:** Learning how to manipulate file descriptors (standard input 0, output 1, error 2) using `dup()` and `dup2()` to implement input/output redirection to/from files.
*   **Memory Management and Robust Parsing:** Developing complex and robust parsing logic to correctly handle quotes, spaces, special characters, and tokenization in the command line, while strictly managing memory allocation and deallocation.
*   **Environment Handling:** Working with the environment list and understanding how built-in commands like `export` and `unset` modify the shell's environment.

Minishell significantly enhanced my proficiency in **C programming**, **system programming**, and understanding the **UNIX architecture**.

---

### Installation and Usage

To compile and run Minishell:

```bash
# Clone the repository
git clone https://github.com/OmiBajja/Minishell.git
cd Minishell

# Compile the project
make

# Run the shell
./minishell
