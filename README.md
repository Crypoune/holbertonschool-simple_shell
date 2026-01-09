# C - Simple Shell

## Description

Simple Shell is a minimal shell implementation that reads user input commands and executes them. It supports basic command execution, built-in commands, and executable lookup in the PATH environment variable.

## Features

✅ **Interactive and Non-Interactive Modes**

- Detects if the application is running in a terminal (TTY) and displays the prompt accordingly.
- Supports both piped input and interactive shell usage.

✅ **Command Execution**

- Parses user input and executes external commands.
- Searches for executable files in the PATH environment variable.
- Handles absolute and relative paths.

✅ **Built-in Commands**

- `exit` – Exit the shell.
- `env` – Display current environment variables.

✅ **Error Handling**

- Exit code 127: Command not found.
- Exit code 126: Permission denied / Is a directory.
- Proper error messages directed to stderr.

✅ **Signal Handling**

- Properly handles Ctrl+C (SIGINT).
- Displays a new prompt after interruption.

✅ **Memory Management**

- Correct cleanup of all allocated memory.
- No memory leaks in user code.

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Manual

```
man ./man_1_simple_shell
```

## File Structure

```
.
├── shell.h       # Header file containing function prototypes
├── main.c        # Main loop and signal handling
├── parser.c      # Command line parsing and tokenization
├── exec.c        # Command execution with fork/execve
├── builtins.c    # Built-in commands (exit, env)
├── getenv.c      # Environment variable retrieval
├── path.c        # PATH lookup and command search
├── cleanup.c     # Memory management and cleanup
├── AUTHORS       # Project authors
└── README.md     # This file
```

## Function Descriptions

### `main.c`

- Implements the shell's main loop.
- Handles user input with getline().
- Manages signal processing (Ctrl+C).
- Detects interactive vs. non-interactive mode.

### `parser.c`

- Parses command line input.
- Splits input into arguments using strtok().
- Returns a dynamically allocated argument vector.

### `exec.c`

- Executes external commands.
- Creates child processes with fork().
- Uses execve() to execute commands.
- Handles error codes and exit statuses.

### `builtins.c`

- Implements the built-in exit command.
- Implements the built-in env command.
- Returns appropriate status codes.

### `getenv.c`

- Custom implementation of getenv().
- Retrieves environment variable values.

### `path.c`

- Searches for executable files in PATH.
- Concatenates directory and command name.
- Checks execution permissions.

### `cleanup.c`

- Frees allocated memory.
- Prevents memory leaks.

## Constraints and Limitations

❌ **Not Supported:**

- Special characters: `"`, `'`, `` ` ``, `\`, `*`, `&`, `#`
- Pipes and redirections.
- Command separators (`;`)
- Built-in `cd` command
- Variable expansion or globbing

✅ **Compatible With:**

- Command arguments
- Path lookup
- Absolute and relative paths
- Error handling and appropriate exit codes

## Allowed Functions

All functions from `string.h` and the following system calls:

- `access`, `chdir`, `close`, `execve`, `exit`, `fork`
- `getcwd`, ​​`getline`, `getpid`, `isatty`, `kill`
- `malloc`, `free`, `open`, `perror`, `printf`, `fprintf`
- `read`, `signal`, `stat`, `strtok`, `wait`, `waitpid`, `write`

## Testing

```bash
# Test exit command
echo "exit" | ./hsh

# Test environment command
echo "env" | ./hsh | head

# Test command execution
echo "ls" | ./hsh

# Test with arguments
echo "echo hello world" | ./hsh
```

## Authors

- [@Arnaud MESSENET](https://github.com/Crypoune)
- [@David DUFONT](https://github.com/dufontdd)

_This project was part of the Holberton School program._
