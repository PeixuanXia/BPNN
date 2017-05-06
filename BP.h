#include "utility.h"

/*初始化BPNN*/
void initBPNN(){
	int i, j; 
	
	/*找到输入输出最值*/
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
	/*将原始数据归一化处理就是指的就是将数据转换成0~1之间。
	在BP神经网络理论里面，并没有对这个进行要求，
	不过实际实践过程中，归一化处理是不可或缺的。
	因为理论模型没考虑到，BP神经网络收敛的速率问题，
	一般来说神经元的输出对于0~1之间的数据非常敏感，
	归一化能够显著提高训练效率。
	其中加个常数是为了防止出现 0 的情况（0不能为分母）*/ 
	for (i = 0; i < In; i++)
		for (j = 0; j < Data; j++)
			d_in[j][i] = (d_in[j][i] - MinIn[i] + 1)/ (MaxIn[i] - MinIn[i] + 1);
	for (i = 0; i < Out; i++)
		for (j = 0; j < Data; j++)
			d_out[j][i] = (d_out[j][i] - MinOut[i] + 1)/ (MaxOut[i] - MinOut[i] + 1);
	 
	/*随机初始化权重为-1.0~1.0，初始权重修正值为0*/
	for (i = 0; i < Neuron; i++)
		for (j = 0; j < In; j++){
			//生成-1.0~1.0之间的随机数 
			w[i][j] = (rand()*2.0/RAND_MAX-1);
			dw[i][j] = 0;
		}
		
	for (i = 0; i < Neuron; i++)
		for (j = 0; j < Out; j++){
			v[i][j] = (rand()*2.0/RAND_MAX-1);
			dv[i][j] = 0;
		}
} 

/*使用BP算法训练神经网络*/
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

/*根据NN求输出*/
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

/*反向传播更新w、v*/
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


