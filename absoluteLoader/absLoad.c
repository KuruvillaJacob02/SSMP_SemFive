#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *object = fopen("object.txt","r");
    char line[100];
    int start;
    while (fscanf(object, "%s", line) != EOF){
        //printf("%s\n", line);
        char * token = strtok(line,"^");
        if (strcmp(token,"T") == 0){
            token = strtok(NULL, "^");   //Moves to next Token
            start = strtol(token, NULL, 16);  //Currently at Address
            token = strtok(NULL,"^");  //Now at Length
            token = strtok(NULL,"^");  
            while (token != NULL){
                printf("%x : %s\n", start, token);
                start += strlen(token)/2;
                token = strtok(NULL,"^");
            }
            
        }
        
    }
    
    fclose(object);
    return 0;
}
