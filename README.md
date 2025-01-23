# Shell Command Executor

## Overview
The **Shell Command Executor** is a lightweight, custom shell program written in C. It allows users to execute basic shell commands, identify built-in shell commands, and locate external commands using the system's `PATH` environment variable.

## Features
- **Execute Built-in Commands**: Recognizes and runs built-in commands like `echo`, `type`, and `exit`.
- **Locate External Commands**: Searches for external commands in the system's `PATH` and executes them if found.
- **Fork and Execute**: Handles command execution using `fork()` and `execv()`.
- **Robust Error Handling**: Provides clear feedback when commands are not found or invalid inputs are provided.

## How It Works
1. **Command Input**:
   - Users input commands via the terminal.
   - Input is processed to remove trailing newlines and unnecessary characters.
2. **Command Parsing**:
   - The input is tokenized to separate the command and its arguments.
3. **Built-in Commands**:
   - The program identifies and handles built-in commands like:
     - `echo`: Prints the arguments provided.
     - `type`: Identifies whether a command is built-in or external.
     - `exit`: Terminates the shell program.
4. **External Commands**:
   - If the command is not built-in, the program searches for it in the `PATH`.
   - Executes the command using `fork()` and `execv()`.
5. **Error Handling**:
   - If a command is not found or execution fails, the program provides appropriate error messages.

## Usage
1. **Compile the Program**:
   ```bash
   gcc -o shell shell.c
   ```
2. **Run the Shell**:
   ```bash
   ./shell
   ```
3. **Use Commands**:
   - **Built-in Examples**:
     - `echo Hello, World!`
     - `type echo`
     - `exit 0`
   - **External Commands**:
     - `ls`
     - `pwd`

## Code Structure
### Functions
- `int is_executable(const char *path)`
  - Checks if a file at the given path is executable.
- `char *find_in_path(const char *command)`
  - Searches for a command in the `PATH` environment variable.
- `void fork_and_exec_cmd(char *full_path, int argc, char **argv)`
  - Forks a new process and executes the given command.
- `int main()`
  - Main loop handling user input and command execution.

### Built-in Commands
| Command | Description                           |
|---------|---------------------------------------|
| `echo`  | Prints the provided arguments.        |
| `type`  | Identifies if a command is built-in or external. |
| `exit`  | Exits the shell program.              |

## Example Session
```bash
$ echo Hello, World!
Hello, World!
$ type echo
echo is a shell builtin
$ ls
file1.txt  file2.c  shell_command_executor
$ type ls
ls is /bin/ls
$ exit 0
```

## Error Handling
- **Command Not Found**:
  - Input: `unknowncommand`
  - Output: `unknowncommand: command not found`
- **Invalid Built-in Usage**:
  - Input: `type`
  - Output: `type: command not found`

## License
This project is licensed under the MIT License.

## Author
[Raj Chhatwani]
- GitHub: [https://github.com/rajchhatwani]
- Email: [rajchhatwani39@gmail.com]

---
Thank you for using the Shell Command Executor!

