#include <stdio.h>

int main() {
    char *operand = "C'SYSTEM'";
    
    if (operand[0] == 'C') {
        char *constant = operand + 2;  // Skip the 'C' and the opening single quote
        char ascii[25];
        printf("Object Code: ");
        // Convert each character to ASCII and include in object code
        for (int i = 0; constant[i] != '\''; ++i) {
            char *constant = operand + 2;
            int codeCount = 0;
            for (int i = 0; constant[i] != '\''; ++i) {
                //printf("%02X ", constant[i]);  // Print ASCII code (in hexadecimal) for each character
                codeCount += sprintf(ascii + codeCount, "%02X", constant[i]);
            }
        }
        printf("%s Hi",ascii);
        printf("\n");
    }

    return 0;
}

