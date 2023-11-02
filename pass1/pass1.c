#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include <stdlib.h>
int checkOp(char symbol[]) {
    int flag = 0;
    char comp[30];
    FILE *f5 = fopen("optab.txt", "r");
    while (fscanf(f5, "%s", comp) != EOF) {
    	//printf("%s\n",comp);
        fscanf(f5, "%*s");	
        if (strcmp(symbol, comp) == 0) {
            flag = 1;
            break;  // No need to continue once a match is found
        }
    }
    fclose(f5);
    return flag;
}
int checkSym(char symbol[]) {
    int flag = 0;
    char comp[30];
    FILE *f3 = fopen("symtab.txt", "r");
    while (fscanf(f3, "%s", comp) != EOF) {
    	//printf("%s\n",comp);
        fscanf(f3, "%*s");	
        if (strcmp(symbol, comp) == 0) {
            flag = 1;
            break;  // No need to continue once a match is found
        }
    }
    fclose(f3);
    return flag;
}
int main() {
    FILE *f7 = fopen("symtab.txt","w");
    fclose(f7);
    int check;
    int start;
    int locctr = 0;
    FILE *f1 = fopen("input.txt", "r");
    FILE *f2 = fopen("intermediate.txt","w");
    FILE *f5 = fopen("length.txt","w");
    char line[100];char label[20];char symbol[20];char address[20];
    fgets(line, sizeof(line), f1);  //READ FIRST LINE
    char *token = strtok(line, "\t");
    strcpy(label,token); //LABEL STORED
    token = strtok(NULL, "\t");
    strcpy(symbol,token); //SYMBOL STORED
    token = strtok(NULL, "\t");
    strcpy(address,token); // ADDRESS STORED
    if (strcmp(symbol,"START") == 0){
    	start = strtol(address,NULL,16);
        locctr = start;
        fprintf(f2, "%x\t%s\t%s\t%s", locctr, label, symbol, address);
    }
    else 
    	locctr = 0;
    // READ REMAINING LINES
    while (fgets(line, sizeof(line), f1)) {
    	char *token = strtok(line, "\t");
        if (isspace(line[0])){
		strcpy(label,"\0");
        	strcpy(symbol,token); // SYMBOL STORED
        	token = strtok(NULL, "\t");
        	strcpy(address,token); // ADDRESS STORED
        }
	else{	
		strcpy(label,token);
		token = strtok(NULL, "\t");
        	strcpy(symbol,token); // SYMBOL STORED
        	token = strtok(NULL, "\t");
        	strcpy(address,token); // ADDRESS STORED
	}
	fprintf(f2, "%x\t%s\t%s\t%s", locctr, label, symbol, address);
	if (strlen(label) != 0){      //CHECK SYMBOL
		if (checkSym(label) == 0){
			FILE *f4 = fopen("symtab.txt", "a");
			fprintf(f4, "%s\t%x\n",label,locctr);
			fclose(f4);
		}
		else{
			printf("\nDUPLICATE SYMBOL");
			FILE *f7 = fopen("symtab.txt","w");
			fclose(f7);
			//remove("intermediate.txt");
			//remove("length.txt");
			break;
		}
	}
	if (strcmp("WORD", symbol) == 0)	//CHECK OPCODE
         	locctr += 3;
        else if (strcmp("RESB", symbol) == 0)
               locctr += strtol(address,NULL,16);
        else if (strcmp("RESW", symbol) == 0) 
               locctr += 3 * strtol(address,NULL,16);             	
        else if (strcmp("BYTE", symbol) == 0) 
                locctr += strlen(address)-4;
        else if (strcmp("END",symbol) == 0)
            	break;
        else if (checkOp(symbol) == 1)
		locctr+=3;
	else{
		printf("\nInvalid OPCODE");
		FILE *f7 = fopen("symtab.txt","w");
		fclose(f7);
		//remove("intermediate.txt");
		//remove("length.txt");
	}
		   	
    }
    locctr = locctr- start;
    fprintf(f5,"%x",locctr);
    fclose(f1);
    fclose(f2);
    return 0;
}
