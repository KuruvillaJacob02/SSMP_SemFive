#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include <stdlib.h>

void main(){
	int start;
	FILE *f1 = fopen("object.txt", "r");
	FILE *f2 = fopen("output.txt", "w");
	char line[100];char label[20];char symbol[20];char address[20];int count = 0;
    	while (fgets(line, sizeof(line), f1)) {
    		char *token = strtok(line, "^");
    		if (strcmp(token,"T") == 0){
    			int len;
    			token = strtok(NULL, "^");
    			start = strtol(token,NULL,16);
    			token = strtok(NULL, "^"); token = strtok(NULL, "^");
    			while (token != NULL){
    				fprintf(f2,"%x %s\n",start,token);
    				printf("%x\t%s\n",start,token);
    				len = strlen(token);
    				start += len/2;
    				token = strtok(NULL, "^");
    			}
    		}
    		
    	}
    	fclose(f1);
    	fclose(f2);
}
