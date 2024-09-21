
# Minishell

## Description
Minishell is a simple, custom shell written in C, designed to emulate the functionality of the bash shell. The project involves handling various processes, file descriptors, and command-line inputs, giving me an opportunity to delve into key concepts related to system programming.

This shell includes support for a command-line interface, pipes, redirections, environment variable handling, and a few built-in commands.

## Features
- Displays a command prompt waiting for user input.
- Handles both relative and absolute paths for commands.
- Command history is maintained for easier navigation.
- Supports pipes (|) for passing the output of one command as input to another.
- Redirections:
  - `<` for input redirection.
  - `>` for output redirection.
  - `<<` reads input until a delimiter is found (here-doc).
  - `>>` appends output to an existing file.
- Handles environment variables (`$`) and expands them accordingly.
- Recognizes and expands `$?` to the exit status of the most recent command.
- Supports signal handling for `ctrl-C`, `ctrl-D`, and `ctrl-\`, behaving similarly to bash.
- Built-in commands:
  - `echo` (with `-n` option)
  - `cd` (with relative or absolute paths)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Bonus Features
- Logical operators `&&` and `||` with support for prioritizing execution using parentheses.
- Wildcard `*` support for pattern matching in the current directory.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/minishell.git
   ```
2. Navigate to the project directory:
   ```bash
   cd minishell
   ```
3. Compile the project using the provided `Makefile`:
   ```bash
   make
   ```

## Usage
To start the shell:
```bash
./minishell
```

Once inside the shell, you can execute commands just like in a regular bash terminal.

### Example commands:
```bash
echo "Hello, World!"
ls -la | grep minishell
cat < input.txt > output.txt
export PATH=/usr/local/bin
```

## Requirements
- C programming language.
- The `readline` library for command history.
  
## External Functions Used
The shell makes use of the following external functions:
- `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`
- Standard system functions like `printf`, `malloc`, `free`, `write`, `fork`, `wait`, `execve`, `dup`, `pipe`, and more.

## Known Limitations
- Memory leaks caused by the `readline()` function are not handled as per project requirements. However, all other memory allocations are managed and freed correctly.

## Future Improvements
- Better error handling and more built-in commands.
- Expand upon wildcard support and improve the robustness of logical operators.

## License
This project is licensed under the MIT License.
