#include "BP.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main(int argc, char *argv[]) {
	int i;
	double sum,y, var1, var2;

	readData();
	initBPNN();
	trainNN();
	
	printf("���������ֵ��\n");
	for (i = 0; i < In; i++){
		scanf("%lf", &d_in[Data][i]);
	}
	
	printf("������Ϊ��");
	for (i = 0; i < Out; i++){
		printf("%lf", result(d_in[Data][0], d_in[Data][1]));
	}
}	


