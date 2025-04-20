# Minishell

A custom implementation of a simple shell, inspired by bash, developed as part of the 42 School curriculum.

## Table of Contents
- [Minishell](#minishell)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Features](#features)
  - [Requirements](#requirements)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Implementation Details](#implementation-details)
    - [Parsing Process](#parsing-process)
    - [Execution Process](#execution-process)
    - [Environment Management](#environment-management)
  - [Project Structure](#project-structure)
  - [Built-in Commands](#built-in-commands)
  - [Signal Handling](#signal-handling)
  - [Contributors](#contributors)

## Overview

Minishell is a simplified shell implementation that mimics the basic functionality of bash. It provides an interactive command-line interface where users can execute commands, manage processes, and navigate the file system. The project focuses on proper parsing, command execution, signal handling, and memory management.

## Features

- Command execution with absolute or relative paths
- Command history navigation
- Environment variable expansion (`$VAR`)
- Redirections (`<`, `>`, `<<`, `>>`)
- Pipes (`|`) for connecting multiple commands
- Signal handling for keyboard interrupts
- Built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
- Error handling and appropriate error messages
- Proper memory management

## Requirements

- GCC compiler
- GNU Make
- readline library
- Linux or macOS environment

## Installation

1. Clone the repository (if applicable)
```bash
git clone <repository-url>
cd minishell
```

2. Compile the program
```bash
make
```

## Usage

Run the minishell program:
```bash
./minishell
```

Once inside the shell, you can use it like a standard command-line interface:

```bash
minishell> ls -la
minishell> echo "Hello, World!"
minishell> cd /path/to/directory
minishell> export VAR=value
minishell> echo $VAR
minishell> cat file.txt | grep pattern > output.txt
minishell> exit
```

## Implementation Details

### Parsing Process
1. Read input using readline library
2. Tokenize the input into commands and operators
3. Parse tokens into a structured representation
4. Handle syntax errors and edge cases
5. Prepare for execution

### Execution Process
1. Set up redirections if present
2. Check for built-in commands
3. Find executable paths for external commands
4. Create child processes using fork() when needed
5. Execute commands using execve()
6. Wait for commands to complete and collect exit status
7. Restore standard input/output if redirected

### Environment Management
- Environment variables stored and managed internally
- Support for variable expansion in commands
- Special handling for PATH to locate executables

## Project Structure

- **main.c**: Entry point and main shell loop
- **env/**: Environment variable management
  - Environment variable initialization
  - Variable lookup and modification
  - Export and unset functionality
- **error_free/**: Error handling and memory management utilities
- **execute/**: Command execution logic
  - Built-in command implementation
  - External command execution
  - Process management
- **lexer_parser/**: Input processing
  - Tokenization
  - Command parsing
  - Syntax validation
- **libft/**: Custom C library with utility functions
- **library/**: Header files and shared components
- **memory/**: Memory allocation and deallocation utilities
- **signal/**: Signal handlers for keyboard interrupts
- **utils/**: General utility functions

## Built-in Commands

- **echo**: Display a line of text (with -n flag support)
- **cd**: Change the current directory
- **pwd**: Print the current working directory
- **export**: Set environment variables
- **unset**: Remove environment variables
- **env**: Display all environment variables
- **exit**: Exit the shell with optional status code

## Signal Handling

Minishell properly handles the following signals:
- **Ctrl+C** (SIGINT): Interrupts the current command
- **Ctrl+D** (EOF): Exits the shell gracefully
- **Ctrl+\\** (SIGQUIT): Ignored in interactive mode

## Contributors

- [bsoykan](https://github.com/bsoykan)
- [mkocaman](https://github.com/mkocaman)

---

*This project is part of the 42 School curriculum.*