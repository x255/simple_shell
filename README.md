# Simple Shell Project

This is a simple shell project developed as part of a programming assignment. The goal of this project is to create a basic shell program that emulates the functionality of the `/bin/sh` shell.

## Project Overview

The shell program, named `hsh`, allows users to execute commands and provides a similar output and error handling as the standard shell. It supports various features, including command execution, built-in commands, piping, and redirection.

## Compilation

To compile the shell program, use the following command:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

To run the shell in interactive mode, execute the following command:

```
$ ./hsh
```

The shell will prompt with `($)` to accept commands. Enter commands and press Enter to execute them. To exit the shell, use the `exit` command.

### Non-Interactive Mode

To run the shell in non-interactive mode, you can use input/output redirection. For example:

```
$ echo "/bin/ls" | ./hsh
```

This will execute the command `/bin/ls` using the shell.

## Functionality

The shell program provides the following functionality:

- Execution of external commands using `execve`
- Support for built-in commands such as `cd` and `exit`
- Handling of command arguments, piping, and redirection
- Error handling and displaying appropriate error messages
- Signal handling for graceful termination or suspension

## Testing

The shell should be tested thoroughly to ensure its correctness and functionality. Sample test cases have been provided to test the shell in both interactive and non-interactive modes. These test cases cover various scenarios, including edge cases.

## Dependencies

The shell program relies on standard C library functions and system calls such as `access`, `chdir`, `execve`, `fork`, etc. Refer to the list of allowed functions and system calls for more details.

## Contributors

This project was developed by Tichaona Christopher Munyau as part of the Simple Shell Month 2 project at ALX Software Enginneering program

## License

This project is licensed under the Tichaona Christopher Munyau

## Contact Information

For any inquiries or feedback, please contact munyau.chris@yahoo.com.