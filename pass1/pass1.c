#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include <stdlib.h>
int main() {
    int start;
    int locctr = 0;
    char * ptr;
    FILE *f1 = fopen("input.txt", "r");
    FILE *f2 = fopen("intermediate.txt","w");
    FILE *f3 = fopen("symtab.txt","w");
    char line[100];char label[20];char symbol[20];char address[20];int count = 0;
    while (fgets(line, sizeof(line), f1)) {
    	count++;
    	char *token = strtok(line, "\t");
        // Check if the line starts with whitespace
        if (isspace(line[0])) {
		strcpy(symbol,token); //SYMBOL STORED        	
		token = strtok(NULL, "\t");
        	strcpy(address,token); // ADDRESS STORED
        	fprintf(f2,"%x\t\t%s\t%s\n", locctr,symbol, address);
        	locctr += 3;
        }
        else{
        	strcpy(label,token); //LABEL STORED
        	token = strtok(NULL, "\t");
        	strcpy(symbol,token); //SYMBOL STORED
        	token = strtok(NULL, "\t");
        	strcpy(address,token); // ADDRESS STORED
        	if (strcmp("START",symbol) == 0 && count ==1){
        		start = strtol(address,NULL,16);
        		locctr = start;
        	}
        	else if (count == 1){
        		locctr = 0;
        		fprintf(f2, "%x\t%s\t%s\t%s\n", locctr, label, symbol, address);
        	}
        	fprintf(f3, "%x\t%s\n",locctr,label);
        	fprintf(f2, "%x\t%s\t%s\t%s\n", locctr, label, symbol, address);
        	
        	if (strcmp("WORD", symbol) == 0)
        	 locctr += 3;
            	else if (strcmp("RESB", symbol) == 0)
                	locctr += strtol(address,NULL,16);
            	else if (strcmp("RESW", symbol) == 0) 
               	locctr += 3 * strtol(address,NULL,16);             	
            	else if (strcmp("BYTE", symbol) == 0) 
                	locctr += strlen(address)-4;
            	else if (strcmp("START",symbol) == 0)
            		locctr+=0;
            	else if (strcmp("END",symbol) == 0)
            		break;
            	else
			locctr+=3;   	
        }
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}

