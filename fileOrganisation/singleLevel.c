#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct lib{
	char name[10];
	char* files[20];
};
struct lib l;

int len = 0;
char temp[20];
void create_directory(){
	printf("Enter Directory Name: ");
	scanf("%s",&l.name);
	printf("Directory Sucessfully created");	
}

void create_file() {
    char temp[20];
    int found = 0;
    printf("\nEnter the file name: ");
    scanf("%s", temp);
    if (len == 0) {
        l.files[len] = (char *)malloc(20);
        strcpy(l.files[len], temp);
        len++;
    } else {
        for (int i = 0; i < len; i++) {
            int val = strcmp(temp, l.files[i]);
            if (val == 0) {
                found = 1;
                break;
            }
        }
        if (found == 1) {
            printf("\nFile already exists");
        } else {
            l.files[len] = (char *)malloc(20);
            strcpy(l.files[len], temp);
            len++;
        }
    }
}

void delete_file() {
    int found = 0;
    int loc;
    printf("Enter file to be deleted: ");
    scanf("%s", temp);
    for (int i = 0; i < len; i++) {
        int val = strcmp(l.files[i], temp);
        if (val == 0) {
            free(l.files[i]);
            found = 1;
            loc = i;
            break;
        }
    }
    if (found == 1) {
        for (int i = loc; i < len - 1; i++) {
            l.files[i] = l.files[i + 1];
        }
        len--;
        printf("File successfully deleted\n");
    } else {
        printf("File not found\n");
    }
}


void search_file(){
	int found = 0;
	printf("\nEnter file to search: ");
	scanf("%s",temp);
	for (int i = 0; i < len; i++){
		int val = strcmp(l.files[i],temp);
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
	for (int i = 0; i < len; i++){
		printf("%s\n",l.files[i]);
	}
}
int main(){
	int op;
	char ch;
	do{
		printf("*************************************");
		printf("\n1.Create Directory\n2.Create File\n3.Delete File\n4.Search File\n5.Display files");
		printf("\nEnter Choice: ");
		scanf("%d",&op);
		switch (op){
			case 1:
				create_directory();
				break;
			case 2:
				create_file();
				break;
			case 3:
				delete_file();
				break;
			case 4:
				search_file();
				break;
			case 5:
				display_files();
				break;
		}
		printf("\nDo you wish to continue (Y/N): ");
		scanf(" %c",&ch);
	} while ( ch == 'Y');
}










