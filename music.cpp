#include <stdio.h>
#include <math.h>
#include <windows.h>

int calc_frequency(int octave, int inx){
	double do_scale = 32.7032;
	double ratio = pow(2.0, 1.0/12), temp;
	int i;
	temp = do_scale*pow(2, octave - 1);
	for(i = 0; i < inx; i++){
		temp = (int)(temp + 0.5);
		temp *= ratio;
	}
	return (int)temp;
}
int main(void){
	int index[] = {0, 2, 4, 5, 7, 9, 11, 12};
	int freq[8];
	for(int i = 0; i < 8; i++){
		freq[i] = calc_frequency(4, index[i]);
	}
	printf("切背辆捞 动动动 楷林 \n");
	int music[] = {4, 4, 5, 5, 4, 4, 2, 
					4,4,2,2,1,
					4,4,5,5,4,4,2,
					4,2,1,2,0};
	for(int i = 0; i < 24; i++){
		//printf("%d", music[i]);
		Beep(freq[music[i]], 300);
	}
	 
}
