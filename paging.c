#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int count = 0;
int memory;
int frameSize;
int frameNum;
int frames[100];
int frameCount = 0;
int files[100];
int size[100];
int internalFrag[100];
int frag = 0;
void insert(){
	int frameReq;
	int tempSize;
	int tempName;
	printf("Enter Process ID and size: ");
	scanf("%d%d",&tempName,&tempSize);
	if (tempSize%frameSize == 0){
		frameReq = tempSize/frameSize;
	}
	else{
		frameReq = (tempSize/frameSize) + 1;
	}
	if (frameReq <= frameNum){
		frag+=frameReq*frameSize -tempSize;
		frameNum-=frameReq;
		for (int i = 0; i<100;i++){
			if (size[i] == 0){
				size[i] = tempSize;
				files[i] = tempName;
				internalFrag[i]=frameReq*frameSize -tempSize;
				break;		
			}
		}
		int check = 0; int i = 0;
		while (check < frameReq){
			if (frames[i]== 0){
			 frames[i] = tempName;
			 check++;
			}
			i++;
	
		}
		
	}
	else{
		printf("\nNot enough frames, delete a process");
	}
	
}

void delete(){
	int id;
	printf("Enter the Process ID to be deleted: ");
	scanf("%d",&id);
	for (int i = 0; i < 100; i++){
		if (files[i] == id){
			files[i] = 0;
			size[i] = 0;
			frag-= internalFrag[i];
		}
		if (frames[i] == id){
			frames[i] = 0;
			frameNum++;
		}
	}
}
void display(){
	for (int i =0; i < 100; i++){
		if(size[i] != 0){
			printf("P%d	%dmb\t",files[i],size[i]);
			for (int j = 0; j < 100; j++){
				if (frames[j] == files[i]){
					printf("%d\t",j);
				}
			}
			printf("\n");
		}
	}
	printf("\nInternal Fragmentation = %dmb",frag);
}
void main(){
	printf("Enter the total memory: ");
	scanf("%d",&memory);
	printf("Enter the frame size: ");
	scanf("%d",&frameSize);
	frameNum = memory/frameSize;
	int op;
	char ch;
	do{
		printf("\n*************************************");
		printf("\n1.Insert Process\n2.Delete Process\n3.Display Process");
		printf("\nEnter Choice: ");
		scanf("%d",&op);
		switch (op){
			case 1:
				insert();
				break;
			case 2:
				delete();
				break;
			case 3:
				display();
				break;
		}
	} while ( op != 0);		
	
}
