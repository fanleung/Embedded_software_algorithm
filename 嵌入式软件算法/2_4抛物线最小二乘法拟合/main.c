#include <stdio.h>
#define MAX 20				//标定节点个数的最大值
int n;						//实际标定节点个数
float x[MAX];				//记录标定节点的AD转换结果
float y[MAX];				//记录标定节点的温度
float aa[3];				//存放线性拟合的两个系数
float A[3][3];				//三元一次方程组的系数矩阵
float B[3];					//三元一次方程组的常数项

float DETA()		//行列式计算
{
	return (A[0][0]*A[1][1]*A[2][2]+A[1][0]*A[2][1]*A[0][2]+
		A[2][0]*A[0][1]*A[1][2]-A[2][0]*A[1][1]*A[0][2]
		-A[0][0]*A[2][1]*A[1][2]-A[1][0]*A[0][1]*A[2][2]);
}

void swap(int k)	//常数项与k列系数交换
{
	int i;
	float t;
	for(i=0;i<3;i++)
	{
		t=B[i];
		B[i]=A[i][k];
		A[i][k]=t;
	}
}


void lsqins()		//抛物线拟合算法
{
	int i,j;
	float t,d;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			A[i][j]=0;
			B[i]=0;
	}
	for(i=0;i<n;i++)
	{
		t=x[i];
		A[0][1]+=t;		//计算Sy
		t*=x[i];
		A[1][1]+=t;
		t*=x[i];
		A[1][2]+=t;
		t*=x[i];
		A[2][2]+=t;
		t=y[i];
		B[0]+=t;
		t*=x[i];
		B[1]+=t;
		t*=x[i];
		B[2]+=t;
	}
		A[0][0]=n;
		A[1][0]=A[2][1];
		A[2][0]=A[0][2]=A[1][1];
		A[2][1]=A[1][2];
		d=DETA();		//求系数行列式的值
		swap(0);		//将a0的系数与常数项交换
		aa[0]=DETA()/d;	//解出a0
		swap(0);		//恢复原来的系数与常数项
		swap(1);		//将a1的系数与常数项交换
		aa[1]=DETA()/d;	//解出a0
		swap(1);		//恢复原来的系数与常数项
		swap(2);		//将a1的系数与常数项交换
		aa[2]=DETA()/d;	//解出a0
}	

int main()
{
	int i;
	float X,Y;
	printf("\n输入标定节点的个数：");
	scanf("%d",&n);
	for(i=0;i<n;i++)	//输入n个标定节点的数据
	{
		printf("输入第%d个标定节点的AD转换值：",i+1);
		scanf("%f",&x[i]);
		printf("输入第%d个标定节点的温度值：",i+1);
		scanf("%f",&y[i]);
	}
	lsqins();		//求解抛物线拟合函数
	printf("\n二次项a2为 %f ",aa[2]);
	printf("\n一次项a1为 %f ",aa[1]);
	printf("\n常数项a0为 %f ",aa[0]);
	printf("\n可以开始进行验证");
	while(1)
	{
		printf("\n输入AD转换结果：");
		scanf("%f",&X);
		if(X==0)break;		//输入0结束验证
		Y=aa[0]+aa[1]*X+aa[2]*X*X;	//通过抛物线拟合方程式计算对应温度
		printf("\n对应温度为：% 2.2f℃",Y);	//显示对应温度
	}
}