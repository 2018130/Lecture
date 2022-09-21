#include <stdio.h>

int main(void){
	char string[20];
	char c;
	
	while(true){
		char ch = getchar();
		if(ch == '\n'){
			printf("Good Bye\n");
			break;
		}
		printf("input : %c\n", ch);
	}
	
	return 0;
}
