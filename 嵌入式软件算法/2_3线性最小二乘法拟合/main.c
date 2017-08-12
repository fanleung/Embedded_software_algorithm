#include <stdio.h>
#define MAX 20				//标定节点个数的最大值
int n;						//实际标定节点个数
float x[MAX];				//记录标定节点的AD转换结果
float y[MAX];				//记录标定节点的温度
float a[2];					//存放线性拟合的两个系数

void lsline()		//线性拟合算法
{
	float ave_x,ave_y,sumx2,sumxy;	//定义变量
	int i;
	ave_x=ave_y=sumx2=sumxy=0;		//初始化
	for(i=0;i<n;i++)
	{
		ave_x+=x[i];		//计算xi的累计值
		ave_y+=y[i];		//计算yi的累计值
	}
	ave_x=ave_x/n;		//计算xi的平均值
	ave_y=ave_y/n;		//计算yi的平均值
	for(i=0;i<n;i++)
	{
		sumx2 += (x[i]-ave_x)*(x[i]-ave_x);		//sumx2为xi的方差累计值
		sumxy += (y[i]-ave_x)*(x[i]-ave_x);		//xy
	}
	a[1] = sumxy/sumx2;		//先计算直线方程的一次项系数a1
	a[0] = ave_y-a[1]*ave_x;	//再计算直线方程的常系数项a0
}

int main()
{
	int i ;
	printf("\n输入标定节点的个数：");
	scanf("%d",&n);
	for(i=0;i<n;i++)	//输入n个标定节点的数据
	{
		printf("输入第%d个标定节点的AD转换值：",i+1);
		scanf("%f",&x[i]);
		printf("输入第%d个标定节点的温度值：",i+1);
		scanf("%f",&y[i]);
	}
	getchar();
	lsline();		//调用线性拟合算法
	printf("\n线性拟合方程式为：y=%fx",a[1]);
	if(a[0]<0) printf("%f",a[0]);
	else printf(" + %f",a[0]);
	getchar();
}