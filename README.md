# minishell

A minimal Unix shell implementation built in C as part of the **42 School** curriculum. minishell replicates the core behavior of bash, handling command execution, pipes, redirections, environment variables, and built-in commands.

## Features

- **Command execution** — runs executables found in `PATH` using `execve`
- **Pipes** — supports chaining commands with `|`
- **Redirections** — handles `>`, `>>`, `<`, and `<<` (here_doc)
- **Environment variables** — expansion of `$VAR` and `$?`
- **Quote handling** — single quotes (`'`) and double quotes (`"`) with correct expansion rules
- **Signals** — handles `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` correctly

## Built-in Commands

| Command | Description |
|---------|-------------|
| `echo` | Prints arguments to stdout (with `-n` flag support) |
| `cd` | Changes the current working directory |
| `pwd` | Prints the current working directory |
| `export` | Sets or exports environment variables |
| `unset` | Removes environment variables |
| `env` | Displays the current environment |
| `exit` | Exits the shell with an optional exit code |

## Building & Running

```bash
make
./minishell
```

## Requirements

- `gcc` compiler
- `readline` library

## Part of the 42 School Curriculum

Completed as part of the core curriculum at [42 Madrid](https://www.42madrid.com/), covering process management, inter-process communication, and shell behavior in depth.
