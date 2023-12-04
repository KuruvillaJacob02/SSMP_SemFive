#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include <stdlib.h>

void hexToBinary(const char* hexString, char* binaryResult) {
    int len = strlen(hexString);
    unsigned long decimalValue = strtoul(hexString, NULL, 16);

    for (int i = (len * 4) - 1; i >= 0; --i) {
        binaryResult[i] = (decimalValue & 1) + '0';
        decimalValue >>= 1;
    }
    binaryResult[len * 4] = '\0'; // Null-terminate the string
}
void main(){
	char start[10];
	printf("Enter Starting address: ");
	scanf(" %s", &start);
	int locctr = strtol(start,NULL,16);
	FILE *f1 = fopen("object.txt", "r");
	FILE *f2 = fopen("output.txt", "w");
	char line[100];char label[20];char symbol[20];char address[20];
    	while (fgets(line, sizeof(line), f1)) {
    		char *token = strtok(line, "^");
    		int count = 0;
    		if (strcmp(token,"T") == 0){
    			int len;
    			token = strtok(NULL, "^");
    			//start = strtol(token,NULL,16);
    			token = strtok(NULL, "^"); token = strtok(NULL, "^");
    			char binaryRepresentation[(strlen(token) * 4) + 1];
    			hexToBinary(token, binaryRepresentation);
    			printf("%s",binaryRepresentation);
    			while (token != NULL){
    				//fprintf(f2,"%x %s\n",start,token);
    				//printf("%x\t%s\n",locctr,token);
    				/*if (strcmp(binaryRepresentation[count],"1") == 0){
    					printf("Hi");
    					printf("%x %s",locctr,token);
    				}*/
    				printf(binaryRepresentation);
    				//len = strlen(token);
    				//start += len/2;
    				token = strtok(NULL, "^");
    				count++;
    			}
    		}
    		
    	}
    	fclose(f1);
    	fclose(f2);
}
/*
int main() {
    const char* hexString = "fc0";
    char binaryRepresentation[(strlen(hexString) * 4) + 1];

    hexToBinary(hexString, binaryRepresentation);

    printf("Hex: %s\nBinary: %s\n", hexString, binaryRepresentation);

    return 0;
}*/

