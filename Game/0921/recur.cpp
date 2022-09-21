#include <stdio.h>
#include <string.h>

int main(void){
	char input[40];
	scanf("%s", input);
	for(int i = 0; i < strlen(input) / 2; i++){
		if(input[i] != input[strlen(input) - i - 1]){
			printf("회문이 아닙니다");
			return 0;
		}
	}
	printf("회문입니다");
	return 0;
}
