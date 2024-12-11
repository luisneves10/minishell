# 🐚 Minishell

The "minishell" is a group project at 42 which consists in creating a simple shell (bash is the reference), focusing on parsing, executing commands, and managing processes and environments.

## 🚀 Features

Implements a functional Unix shell that supports basic commands and built-ins.

Handles:

- Command execution: Execute binaries from the PATH and built-in commands.

- Pipes (|) and redirections (>, <, >>).

- Environment variables: Access and modify environment variables.

- Signals: Manage and properly handle Ctrl-C, Ctrl-D, and Ctrl-\ inputs.

- Replicates the behavior of commands like export, unset, exit, and more.

- Handles both double and single quotes.

## 🛠️ Technologies Used

C Programming Language

POSIX System Calls

Readline Library

## 📥 Installation

To run the Minishell project on your local machine, follow these steps:

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/luisneves10/minishell.git
    ```

2. **Navigate to the Project Directory**:
    ```bash
    cd minishell
    ```

3. **Compile the Code**:
    ```bash
    make
    ```

4. **Run the Program**:
    ```bash
    ./minishell
    ```

## 📚 Learning Experience

- **Process Management:** Implementing fork, execve, and wait functions taught me how processes are created and managed in Unix systems.

- **Signal Handling:** Managing interrupts and signals gave me insights into user interactions and system responsiveness.

- **Memory Management:** Ensuring proper allocation and freeing of resources improved my understanding of dynamic memory.

- **Command Parsing:** Handling many edge cases enhanced my parsing skills.

- **Unix Shell Behavior:** Understanding the inner workings of a shell through replicating its functionalities.
