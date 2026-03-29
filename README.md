# Minishell

A small Unix shell implementation written in C (42 school project).

## Features

- Interactive prompt using `readline` + command history.
- Command parsing with quote handling and environment variable expansion.
- Pipelines and redirections: `|`, `<`, `>`, `<<`, `>>`.
- Builtins:
- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`
- External command execution with `PATH` lookup.
- Signal and exit-status handling.

## Project Structure

- `main.c`: program entry point and interactive loop.
- `include/`: shared headers.
- `parsing/`: tokenization, parsing, expansion, heredoc, and signal helpers.
- `src/builtins/`: builtin command implementations.
- `src/exec/`: process creation, pipes, execution flow.
- `src/redirect/`: file redirection helpers.
- `src/free/`: memory cleanup helpers.
- `libft/`: custom utility library dependency.

## Build

```bash
make
```

This produces the executable:

```bash
./minishell
```

## Clean

```bash
make clean
make fclean
make re
```

## Notes

- The `Makefile` is configured for Homebrew `readline` paths on macOS.
- On Linux, install `readline` development headers (for example `libreadline-dev`)
  and adjust `CPPFLAGS` / `LDFLAGS` in `Makefile` if needed.
