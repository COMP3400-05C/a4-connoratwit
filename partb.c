#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, const char* argv[]) {
    // Check if there are any arguments
    if (argc < 2) {
        printf("ERROR: no arguments\n");
        return 1;
    }
    
    // Calculate number of actual arguments
    int num_args = argc - 1;
    
    // Determine middle argument(s)
    int start_idx, end_idx;
    
    if (num_args % 2 == 1) {
        // Odd number of arguments: take the middle one
        start_idx = (num_args / 2) + 1;
        end_idx = start_idx;
    } else {
        // Even number of arguments: take the middle two
        start_idx = (num_args / 2);
        end_idx = start_idx + 1;
    }
    
    // Build the arguments array for echo
    int num_echo_args = (end_idx - start_idx + 1);
    char* eargs[num_echo_args + 2];  // +1 for "echo", +1 for NULL
    
    eargs[0] = "echo";
    for (int i = start_idx, j = 1; i <= end_idx; i++, j++) {
        eargs[j] = (char*)argv[i];
    }
    eargs[num_echo_args + 1] = NULL;
    
    // Execute echo command
    int eret = execv("/bin/echo", eargs);
    
    // If exec returns, there was an error
    if (eret == -1) {
        perror("exec");
        return 1;
    }
    
    return 0;
}