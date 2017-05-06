#include "BP.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main(int argc, char *argv[]) {
	int i;
	double sum,y, var1, var2;

	readData();
	initBPNN();
	trainNN();
	
	printf("请输入测试值：\n");
	for (i = 0; i < In; i++){
		scanf("%lf", &d_in[Data][i]);
	}
	
	printf("输出结果为：");
	for (i = 0; i < Out; i++){
		printf("%lf", result(d_in[Data][0], d_in[Data][1]));
	}
}	


