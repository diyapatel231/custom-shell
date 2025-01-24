#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMD_LEN 1024  // Maximum command length
#define MAX_ARGS 128      // Maximum number of arguments

// Function to display the shell prompt
void prompt() {
    printf("my-shell> ");
}

// Function to handle redirection (>, <) if present in the command
int handle_redirection(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0) {  // Output redirection
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("Failed to open file for redirection");
                return -1;
            }
            dup2(fd, STDOUT_FILENO);  // Redirect stdout
            close(fd);
            args[i] = NULL;
            break;
        } else if (strcmp(args[i], "<") == 0) {  // Input redirection
            int fd = open(args[i + 1], O_RDONLY);
            if (fd < 0) {
                perror("Failed to open file for input redirection");
                return -1;
            }
            dup2(fd, STDIN_FILENO);  // Redirect stdin
            close(fd);
            args[i] = NULL;
            break;
        }
    }
    return 0;
}

// Function to execute a single command
void execute_command(char *cmd) {
    char *args[MAX_ARGS];
    int i = 0;

    // Tokenize the command into arguments
    char *token = strtok(cmd, " \t\n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;

    // Handle empty commands
    if (args[0] == NULL) return;

    // Built-in command: exit
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }

    // Built-in command: cd
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL || chdir(args[1]) != 0) {
            perror("cd failed");
        }
        return;
    }

    // Fork and execute the command
    pid_t pid = fork();
    if (pid == 0) {  // Child process
        if (handle_redirection(args) != 0) exit(EXIT_FAILURE);

        if (execvp(args[0], args) == -1) {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {  // Parent process
        wait(NULL);  // Wait for the child to finish
    } else {
        perror("Fork failed");
    }
}

int main() {
    char command[MAX_CMD_LEN];

    while (1) {
        prompt();  // Display the shell prompt
        if (fgets(command, MAX_CMD_LEN, stdin) == NULL) {
            break;  // Exit on EOF (Ctrl+D)
        }
        execute_command(command);  // Execute the user input
    }

    return 0;
}
