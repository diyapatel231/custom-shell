# custom-shell

A lightweight Unix shell written in C, supporting basic command execution, piping, redirection, and background processes.

## Features
- **Basic Commands**: Execute Linux commands like `ls`, `pwd`, `cat`.
- **Redirection**: Support for input/output redirection (e.g., `ls > output.txt`, `cat < file.txt`).
- **Piping**: Chain commands using pipes (e.g., `ls | grep shell`).
- **Built-in Commands**: Includes `cd` for changing directories and `exit` for exiting the shell.

## How to Build and Run
1. Clone this repository:
   ```bash
   git clone <repo_url>
   cd custom-shell
2. Build the shell:
   ```bash
   make
3. Run the shell:
   ```bash
   ./shell
