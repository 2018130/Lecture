#include <stdio.h>
#include <string.h>

int main(void){
	char input[40];
	scanf("%s", input);
	for(int i = 0; i < strlen(input) / 2; i++){
		if(input[i] != input[strlen(input) - i - 1]){
			printf("ȸ���� �ƴմϴ�");
			return 0;
		}
	}
	printf("ȸ���Դϴ�");
	return 0;
}
