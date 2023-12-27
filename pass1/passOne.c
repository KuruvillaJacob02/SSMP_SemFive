#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include <stdlib.h>


int checkOp(char symbol[]) {
    int flag = 0;
    char label[25], operand[25];
    FILE *optab = fopen("optab.txt", "r");
    while (fscanf(optab, "%s %s", label,operand) != EOF) {
    	//printf("%s %s\n",label,operand);	
        if (strcmp(symbol, label) == 0) {
            flag = 1;
            break;  // No need to continue once a match is found
        }
    }
    fclose(optab);
    return flag;
}

int checkSym(char symbol[], int locctr) {
    int flag = 0;
    char label[25], operand[25];
    FILE *symtab = fopen("symtab.txt", "a+");
    while (fscanf(symtab, "%s\t%s", label, operand) != EOF) {
        if (strcmp(symbol, label) == 0) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        fprintf(symtab, "%s\t%x\n", symbol, locctr);
    }
    fclose(symtab);
    return flag;
}

int main(){
  FILE *symtab = fopen("symtab.txt","w");
  fclose(symtab);
  FILE *input = fopen("input.txt","r");
  FILE *intermediate = fopen("intermediate.txt","w");
  int  flag = 0; int start; int locctr = 0;
  char label[25], opcode[25], operand[25];
  while(feof(input)!=1){
  
	fscanf(input, "%s\t\t%s\t\t%s", label, opcode, operand);  //Reads every line
	//printf("\n%s\t%s\t%s", label,opcode,operand);
	
	if (strcmp(opcode,"START") == 0){
            start = strtol(operand,NULL,16);
            locctr = start;
            fprintf(intermediate, "%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        }
        
        else{
            fprintf(intermediate, "%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);
            if (strcmp(label,"$") != 0 ){
                flag = checkSym(label,locctr);
                if (flag == 1){
                    printf("DUPLICATE SYMBOL");
                    break;
                }
            }
            
            if (strcmp("WORD", opcode) == 0)    locctr += 3;
            else if (strcmp("RESB", opcode) == 0)   locctr += strtol(operand,NULL,16);
            else if (strcmp("RESW", opcode) == 0)   locctr += 3 * strtol(operand,NULL,16);             	
            else if (strcmp("BYTE", opcode) == 0)   locctr += strlen(operand)-3;
            else if (strcmp("END",opcode) == 0)   break;
            else if (checkOp(opcode) == 1)    locctr+=3;
	    else{
		    printf("\nInvalid OPCODE");
		    break;
	    }
        }
  }
  locctr = locctr- start;
  FILE *length = fopen("length.txt","w");
  fprintf(length, "%x", locctr);
  fclose(length);
  fclose(input);
  fclose(intermediate);
  return 0;
}
