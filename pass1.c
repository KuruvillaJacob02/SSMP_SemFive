#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include <stdlib.h>

char convert(int number){
	
}
int main() {
    int start;
    printf("i am lonely ass eater boy :((")
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
        	fprintf(f2,"%d\t\t%s\t%s\n", locctr,symbol, address);
        	locctr += 3;
        }
        else{
        	strcpy(label,token); //LABEL STORED
        	token = strtok(NULL, "\t");
        	strcpy(symbol,token); //SYMBOL STORED
        	token = strtok(NULL, "\t");
        	strcpy(address,token); // ADDRESS STORED
        	if (strcmp("START",symbol) == 0 && count ==1){
        		start = atoi(address);
        		locctr = start;
        		//fprintf(f2, "%d\t%s\t%s\t%s\n", locctr, label, symbol, address);
        		printf("%d\n",start); 
        	}
        	else if (count == 1){
        		locctr = 0;
        		fprintf(f2, "\n%d\t%s\t%s\t%s\n", locctr, label, symbol, address);
        	}
        	fprintf(f3, "%d\t%s\n",locctr,label);
        	fprintf(f2, "%d\t%s\t%s\t%s\n", locctr, label, symbol, address);
        	if (strcmp("WORD", symbol) == 0) {
                locctr += 3; 
            	}	 
            	else if (strcmp("RESB", symbol) == 0) {
                locctr += atoi(address);
            	} 
            	else if (strcmp("RESW", symbol) == 0) {
                locctr += 3 * atoi(address); 
            	}
            	else if (strcmp("BYTE", symbol) == 0) {
            	 printf("%s\n",address);
            	 printf("%d\n",strlen(address)-4);
                locctr += strlen(address)-4;
            	}
            	else if (strcmp("START",symbol) == 0){
            		locctr+=0;
            	}
            	else
			locctr+=3;    	
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}
