#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, const char* argv[]) {
    // Check if there are any arguments
    if (argc < 2) {
        printf("ERROR: No arguments\n");
        return 1;
    }
    
    // Loop through all arguments starting from index 1 
    for (int i = 1; i < argc; i++) {
        // Print each character of the argument in uppercase
        for (int j = 0; argv[i][j] != '\0'; j++) {
            putchar(toupper(argv[i][j]));
        }
        
        // Print comma separator between arguments 
        if (i < argc - 1) {
            putchar(',');
        }
    }
    
    // Print newline at the end
    putchar('\n');
    
    return 0;
}