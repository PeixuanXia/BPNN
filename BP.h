#include "utility.h"

/*��ʼ��BPNN*/
void initBPNN(){
	int i, j; 
	
	/*�ҵ����������ֵ*/
	for (i = 0; i < In; i ++){
		MaxIn[i] = MinIn[i] = d_in[0][i];
		for (j = 0; j < Data; j++){
			MaxIn[i] = MaxIn[i] > d_in[j][i] ? MaxIn[i] : d_in[j][i];
			MinIn[i] = MinIn[i] < d_in[j][i] ? MinIn[i] : d_in[j][i];
		}
	} 
	for (i = 0; i < Out; i ++){
		MaxOut[i] = MinOut[i] = d_out[0][i];
		for (j = 0; j < Data; j++){
			MaxOut[i] = MaxOut[i] > d_out[j][i] ? MaxOut[i] : d_out[j][i];
			MinOut[i] = MinOut[i] < d_out[j][i] ? MinOut[i] : d_out[j][i];
		}
	}
	/*��ԭʼ���ݹ�һ���������ָ�ľ��ǽ�����ת����0~1֮�䡣
	��BP�������������棬��û�ж��������Ҫ��
	����ʵ��ʵ�������У���һ�������ǲ��ɻ�ȱ�ġ�
	��Ϊ����ģ��û���ǵ���BP�������������������⣬
	һ����˵��Ԫ���������0~1֮������ݷǳ����У�
	��һ���ܹ��������ѵ��Ч�ʡ�
	���мӸ�������Ϊ�˷�ֹ���� 0 �������0����Ϊ��ĸ��*/ 
	for (i = 0; i < In; i++)
		for (j = 0; j < Data; j++)
			d_in[j][i] = (d_in[j][i] - MinIn[i] + 1)/ (MaxIn[i] - MinIn[i] + 1);
	for (i = 0; i < Out; i++)
		for (j = 0; j < Data; j++)
			d_out[j][i] = (d_out[j][i] - MinOut[i] + 1)/ (MaxOut[i] - MinOut[i] + 1);
	 
	/*�����ʼ��Ȩ��Ϊ-1.0~1.0����ʼȨ������ֵΪ0*/
	for (i = 0; i < Neuron; i++)
		for (j = 0; j < In; j++){
			//����-1.0~1.0֮�������� 
			w[i][j] = (rand()*2.0/RAND_MAX-1);
			dw[i][j] = 0;
		}
		
	for (i = 0; i < Neuron; i++)
		for (j = 0; j < Out; j++){
			v[i][j] = (rand()*2.0/RAND_MAX-1);
			dv[i][j] = 0;
		}
} 

/*ʹ��BP�㷨ѵ��������*/
void trainNN(){
	int i, j, c = 0;
	double e;
	do{
		e = 0;
		for (i = 0; i < Out; i++)
			for (j = 0; j < Data; j++){
				computOut(j);
				e += fabs((OutputData[i] - d_out[j][i]) / d_out[j][i]);
				backUpdate(j); 
			}
		c++;
	}while (c < Train && (e / Data > 0.01));
}

/*����NN�����*/
void computOut(int var){
	int i,j;
    double sum,y;
    
    for (i = 0; i < Neuron; i++){
    	sum = 0;
		for (j = 0; j < In; j++){
			sum += d_in[var][j]*w[i][j];
		}
		temp[i] = 1/(1 + exp(-1*sum));
	}
	
	for (i = 0; i < Out; i++){
		sum = 0;
		for (j = 0; j < Neuron; j++){
			sum += temp[j]*v[j][i];
		}
		OutputData[i] = sum;
	}
} 

/*���򴫲�����w��v*/
void backUpdate(int var){
	int i, j;
	double t;
	for (i = 0; i < Neuron; i++){
		t = 0;
		for (j = 0; j < Out; j ++){
			t += (OutputData[j]-d_out[var][j])*v[i][j];
			
			dv[i][j] = A*dv[i][j] + B*(OutputData[j]-d_out[var][j])*temp[i];
			v[i][j] -= dv[i][j];
			 
		}
		
		for (j = 0; j < In; j++){
			dw[i][j] = a*dw[i][j] + b*temp[i]*(1-temp[i])*t*d_in[var][j];
			w[i][j] -= dw[i][j];
		}
	}	
}


