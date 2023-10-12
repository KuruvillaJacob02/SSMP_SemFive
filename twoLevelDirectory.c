#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct lib{
	int len;
	char name[10];
	char* files[20];
	struct lib *next;
};
struct lib *head,*tail,*p;
char temp[20];

void choose_directory(){
    int found = 0;
    char temp[20];
    printf("Enter directory name: ");
    scanf("%s", temp);
    p = head;
    while ( p != NULL){
    	int val = strcmp(temp,p->name);
    	if (val == 0){
    		found = 1;
    		printf("Directory found");
    		break;
    	}
    	p=p->next;
    }
    if (found == 0){
    	printf("\nDirectory does not exist");
    }
}
void create_directory(){
	p = (struct lib*)malloc(sizeof(struct lib));
	p->next = NULL;
	printf("Enter Directory Name: ");
	scanf("%s",p->name);
	printf("Directory Sucessfully created\n");
	if (head == NULL){
		head = p;
			
	}
	else{
		tail->next = p;
	}
		tail = p;	
}

void create_file() {
    	char temp[20];
    	int found = 0;
    	printf("\nEnter the file name: ");
    	scanf("%s", temp);
    	if (p->len == 0) {
        	p->files[p->len] = (char *)malloc(20);
        	strcpy(p->files[p->len], temp);
        	p->len++;
    	} else {
        	for (int i = 0; i < p->len; i++) {
            		int val = strcmp(temp, p->files[i]);
            		if (val == 0) {
                		found = 1;
                		break;
            		}
        	}
        	if (found == 1) {
            	printf("\nFile already exists");
        	} 
        	else {
            	p->files[p->len] = (char *)malloc(20);
            	strcpy(p->files[p->len], temp);
            	p->len++;
        	}
    	}
}     

void delete_file() {
    int found = 0;
    int loc;
    printf("Enter file to be deleted: ");
    scanf("%s", temp);
    for (int i = 0; i < p->len; i++) {
        int val = strcmp(p->files[i], temp);
        if (val == 0) {
            free(p->files[i]);
            found = 1;
            loc = i;
            break;
        }
    }
    if (found == 1) {
        for (int i = loc; i < p->len - 1; i++) {
            p->files[i] = p->files[i + 1];
        }
        p->len--;
        printf("File successfully deleted\n");
    } else {
        printf("File not found\n");
    }
}


void search_file(){
	int found = 0;
	printf("\nEnter file to search: ");
	scanf("%s",temp);
	for (int i = 0; i < p->len; i++){
		int val = strcmp(p->files[i],temp);
		if (val == 0){
			found = 1;
			printf("File has been found");
			break;
		}
	}
	if (found == 0){
		printf("File not found");
	}
}

void display_files(){
	for (int i = 0; i < p->len; i++){
		printf("%s\n",p->files[i]);
	}
}
int main(){
	int op;
	char ch;
	do{
		printf("\n*************************************");
		printf("\n1.Create Directory\n2.Choose Directory\n3.Create File\n4.Delete File\n5.Search File\n6.Display files");
		printf("\nEnter Choice: ");
		scanf("%d",&op);
		switch (op){
			case 1:
				create_directory();
				break;
			case 2:
				choose_directory();
				break;
			case 3:
				create_file();
				break;
			case 4:
				delete_file();
				break;
			case 5:
				search_file();
				break;
			case 6:
				display_files();
				break;
		}
	} while ( op != 0);
}
