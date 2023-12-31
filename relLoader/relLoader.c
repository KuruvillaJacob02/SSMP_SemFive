#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char BITMASK[100];

void hexToBin(char token[]){
      int j = 0;
      BITMASK[0] = '\0';
      while (token[j] != '\0'){
          //printf("%c",token[j]);
          switch (token[j]){
              case '0': strcat(BITMASK, "0000"); break;
              case '1': strcat(BITMASK, "0001"); break;
	      case '2': strcat(BITMASK, "0010"); break;
	      case '3': strcat(BITMASK, "0011"); break;
              case '4': strcat(BITMASK, "0100"); break;
              case '5': strcat(BITMASK, "0101"); break;
              case '6': strcat(BITMASK, "0110"); break;
              case '7': strcat(BITMASK, "0111"); break;
              case '8': strcat(BITMASK, "1000"); break;
              case '9': strcat(BITMASK, "1001"); break;
              case 'A': strcat(BITMASK, "1010"); break;
              case 'B': strcat(BITMASK, "1011"); break;
              case 'C': strcat(BITMASK, "1100"); break;
              case 'D': strcat(BITMASK, "1101"); break;
              case 'E': strcat(BITMASK, "1110"); break;
              case 'F': strcat(BITMASK, "1111"); break;	      						
          }
          j++;
      }
      //printf("%s\n",BITMASK);
}
int main(){
    FILE *object = fopen("object.txt","r");
    int start; int code;
    char opcode[25], addr[25];
    char arr[25];
    char line[100];
    printf("Enter starting address : ");
    scanf("%x",&start);
    int first = start;
    while (fscanf(object, "%s", line) != EOF){
        char * token = strtok(line,"^");
        if (strcmp(token, "T") == 0){
            token = strtok(NULL,"^"); //Moves to Address
            token = strtok(NULL,"^"); //Moves to Length
            token = strtok(NULL,"^"); //Moves to Bitmask
            hexToBin(token);
            token = strtok(NULL,"^");
            int bitCount = 0;
            while (token != NULL){
                if (BITMASK[bitCount] == '1'){
                    opcode[0] = '\0';
                    addr[0] = '\0';
                    //code = strtol(token, NULL,16);
                    //sprintf(arr, "%x", code);
                    //printf("%ld\n", strlen(token));
                    for (int i  =0; i < strlen(token); i++){
                        int opLen = strlen(opcode);
                        int addrLen = strlen(addr);
                        if (i == 0 || i == 1){
                          //strcat(opcode, token[i]);
                          opcode[opLen] = token[i];
                          opcode[opLen+1] = '\0';
                          
                        }
                        else {
                            //strcat(addr,token[i]);
                            addr[addrLen] = token[i];
                            addr[addrLen+1] = '\0';
                        } 
                    }
                    code = strtol(addr,NULL,16);
                    code += first;
                    //printf("\n");
                    printf("%x : %s%x\n", start,opcode,code);
                }
                else
                  printf("%x : %s\n", start, token);
                start += strlen(token)/2;
                token = strtok(NULL,"^");
                bitCount++;
            }
            
        }
    }
    
}
