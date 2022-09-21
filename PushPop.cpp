#include <stdio.h>
#include <cstdlib>
#include <conio.h>

struct Node* head = NULL;

struct Node {
	char data;
	Node* nextNode;
};

void push(char data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->nextNode = NULL;

	if (head == NULL) {
		head = newNode;
	}
	else {
		Node* curNode = head;
		while (true) {
			if (curNode->nextNode == NULL) {
				curNode->nextNode = newNode;
				break;
			}
			curNode = curNode->nextNode;
		}
	}
}

char pop(void) {
	if (head == NULL) return '-';

	Node* preLastNode = NULL;
	Node* lastNode = NULL;
	Node* curNode = head;

	while (curNode != NULL) {
		preLastNode = lastNode;
		lastNode = curNode;
		curNode = curNode->nextNode;
	}
	int lastData = lastNode->data;

	if(preLastNode != NULL)
		preLastNode->nextNode = NULL;
	if (lastNode == head) 
		head = NULL;
	free(lastNode);
	lastNode = NULL;

	return lastData;
}

int main(void) {
	int count = 0;
	char key;

	do {
		count++;
		printf("%2d => ", count);
		key = _getch();
		push(key);
		printf("%c \n", key);
	} while (key != '!');
	printf("\n\n");
	while (count != 0) {
		key = pop();
		count--;
		printf("%c", key);
	}
	printf("\n");
}
