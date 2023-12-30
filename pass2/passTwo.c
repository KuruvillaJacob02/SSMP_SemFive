#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int count = 0, rsize = 0, start = 0, first;
char OP[3][25], ADDR[3][25];

int searchSym(char operand[]){
    char label[25], code[25];
    FILE *symtab = fopen("symtab.txt","r");
    while (fscanf(symtab,"%s\t%s",label,code) != EOF){
        //printf("%s %s\n",label,code);
        if (strcmp(operand,label) == 0){
            strcpy(ADDR[count],code);  //Stores OPCODE
            return 1;
        }
    }
    fclose(symtab);
    return -1;
}
int searchOp(int locctr, char opcode[]){
    char label[25], code[25];
    FILE *optab = fopen("optab.txt","r");
    while (fscanf(optab,"%s %s",label,code) != EOF){
        //printf("%s %s\n",label,code);
        if (strcmp(opcode,label) == 0){
            strcpy(OP[count],code);  //Stores OPCODE
            return 1;
        }
    }
    fclose(optab);
    return -1;
}

int main(){
    FILE *intermediate = fopen("intermediate.txt","r");
    FILE *length = fopen("length.txt","r");
    FILE *object = fopen("object.txt","w");
    char address[25], size[25], label[25], opcode[25], operand[25], flength[25];
  
    fscanf(intermediate, "%s\t%s\t%s\t%s", address,label,opcode,operand);
    fscanf(length,"%s",flength);
    first = strtol(address, NULL, 16);
    if (strcmp("START",opcode) == 0){
        fprintf(object,"H^%s^%s^%s\n",label,operand,flength);
    }
    while (feof(intermediate) != 1){
        fscanf(intermediate, "%s\t%s\t%s\t%s", address,label,opcode,operand);
        //printf("%s\t%s\t%s\t%s\n",address,label,opcode,operand);
        int locctr = strtol(address, NULL, 16);
        
        if (count == 0){            //Initializing text record
            start = locctr;
            rsize = 0;
        }
        
        int opStatus = searchOp(locctr,opcode);
        int symStatus = searchSym(operand);
        
        if (strcmp("WORD", opcode) == 0){
            rsize += 3;
            strcpy(OP[count],operand);
        }   
        else if (strcmp("BYTE", opcode) == 0){
            char *constant = operand + 2;
            int codeCount = 0;
            char ascii[25];
            for (int i = 0; constant[i] != '\''; ++i) {
                //printf("%02X ", constant[i]); 
                codeCount += sprintf(ascii + codeCount, "%02X", constant[i]);
            }
            strcpy(OP[count],ascii);
            rsize += strlen(operand) - 3;
        }
        else if (strcmp("RESW", opcode) == 0)   rsize += 0;           	
        else if (strcmp("RESB", opcode) == 0)   rsize += 0;
        else if (strcmp("END",opcode) == 0){
            strcpy(OP[count],"");
	    strcpy(ADDR[count],"");
	    fprintf(object, "T^%x^%x^%s%s^%s%s^%s%s\n", start, rsize, OP[0],ADDR[0],OP[1],ADDR[1],OP[2],ADDR[2]);	
	    break;
        }
        else if (opStatus == -1){
            printf("INVALID OPCODE\n");
            break;
        }   
        else if (symStatus == -1){
            printf("INVALID SYMB0L\n");
            break;
        }
        
        if(count == 2) {
			fprintf(object, "T^%x^%x^%s%s^%s%s^%s%s\n", start, rsize, OP[0],ADDR[0],OP[1],ADDR[1],OP[2],ADDR[2]);	
			locctr += rsize;
			strcpy(OP[0],"");
			strcpy(ADDR[0],"");
			strcpy(OP[1],"");
			strcpy(ADDR[1],"");
			strcpy(OP[2],"");
			strcpy(ADDR[2],"");
		}
        count = (count + 1)%3;
        
    }
    fprintf(object,"E^%x",first);
    fclose(intermediate);
    fclose(length);
    fclose(object);
}
