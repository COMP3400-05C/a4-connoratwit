#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, const char* argv[]) {
    // Check if we have exactly 3 arguments: program_name, word, filename
    if (argc < 3) {
        printf("ERROR: no arguments\n");
        return 1;
    }
    
    const char* search_word = argv[1];
    const char* filename = argv[2];
    
    // Fork a child process
    pid_t pid = fork();
    
    if (pid == -1) {
        // Fork failed
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
        // Child process: run grep
        char* grep_args[] = {
            "grep",
            "-s",           // Suppress error messages
            "-q",           // Quiet mode (no output)
            (char*)search_word,
            (char*)filename,
            NULL
        };
        
        execv("/usr/bin/grep", grep_args);
        
        // If exec returns, there was an error
        perror("exec");
        return 1;
    } else {
        // Parent process: wait for child
        int status;
        waitpid(pid, &status, 0);
        
        // Check if child exited normally
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            
            if (exit_status == 0) {
                // Word found
                printf("FOUND: %s\n", search_word);
                return 0;
            } else if (exit_status == 1) {
                // Word not found (no match)
                printf("NOT FOUND: %s\n", search_word);
                return 0;
            } else if (exit_status == 2) {
                // File doesn't exist or can't be read
                printf("ERROR: %s doesn't exist\n", filename);
                return 2;
            } else {
                // Other error
                printf("ERROR: grep exited with status %d\n", exit_status);
                return 2;
            }
        } else {
            printf("ERROR: child process did not exit normally\n");
            return 1;
        }
    }
    
    return 0;
}