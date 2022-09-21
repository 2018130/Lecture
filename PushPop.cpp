#include <stdio.h>
#include <cstdlib>
#include <conio.h>

struct Node* head = NULL;

struct Node{
	char data;
	Node* nextNode;
};
	
void push(char data){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->	data = data;
	newNode->nextNode = NULL;
	
	if(head == NULL) {
		head = newNode;
	}else{
		Node* curNode = head;
		while(true){
			if(curNode->nextNode == NULL){
				curNode->nextNode = newNode;
				break;
			}
			curNode = curNode->nextNode;
		}
	}
}

char pop(void){
	if(head == NULL) return '-';
	
	Node* preLastNode;
	Node* lastNode;
	Node* curNode = head;
	
	while(curNode != NULL){
		preLastNode = lastNode;
		lastNode = curNode;
		curNode = curNode->	nextNode;
	}
	int lastData = lastNode->data;
	
	preLastNode->nextNode = NULL;
	if(lastNode == head) head = NULL;
	free(lastNode);
	lastNode = NULL;
	
	return lastData;
}

int main(void){
	int count = 0;
	char key;
	
	do{
		count++;
		printf("%2d 번 문자 입력>", count);
		key = getch();
		push(key);
		printf("%c \n", key);
	}while(key != 27);
	printf("\n\n");
	printf("데이터 pop과정\n\n");
	while(count != 0){
		key = pop();
		count--;
		printf("%c", key);
	}
	printf("\n");
}
