#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
 
#define Data 820
#define In 2 
#define Out 1
#define Neuron 45
#define Train 20000

#define A 0.2
#define B 0.4
#define a 0.2
#define b 0.3

/*定义权重矩阵*/
double w[Neuron][In];
double v[Neuron][In];
/*定义修正值矩阵*/
double dw[Neuron][In];
double dv[Neuron][In]; 
/*存放输入的最大值最小值*/
double MaxIn[In];
double MinIn[In];
/*存放输出的最大值最小值*/
double MaxOut[Out];
double MinOut[Out]; 
/*存放数据输入*/
double d_in[Data+1][In]; 
/*存放数据输出*/
double d_out[Data][Out]; 
/*存放通过BPNN求出的h*/
double OutputData[Out]; 
/*存放隐含层的输入*/
double temp[Neuron];



void readData(){
	FILE *fin = fopen("in.txt", "r");
	int i, j=0;
	if (fin == NULL)
		return;
	while (j < Data){
		for (i = 0; i < In; i++){
			fscanf(fin, "%lf", &d_in[j][i]);
		}
		j++;
	} 
	fclose(fin);
	
	FILE *fout = fopen("out.txt", "r");
	if (fout == NULL)
		return;
	j = 0;
	while (j < Data){
		for (i = 0; i < Out; i++){
			fscanf(fin, "%lf", &d_out[j][i]);
		}
		j++;
	} 
	fclose(fout);
}

double result(double var1,double var2)
{
	int i,j;
	double sum,y;

	var1=(var1-MinIn[0]+1)/(MaxIn[0]-MinIn[0]+1);
	var2=(var2-MinIn[1]+1)/(MaxIn[1]-MinIn[1]+1);

	for (i = 0; i < Neuron; ++i){
		sum=0;
		sum=w[i][0]*var1+w[i][1]*var2;
		temp[i]=1/(1+exp(-1*sum));
	}
	sum=0;
	for (j = 0; j < Neuron; ++j)
		sum+=v[j][0]*temp[j];

	return sum*(MaxOut[0]-MinOut[0]+1)+MinOut[0]-1;
}
