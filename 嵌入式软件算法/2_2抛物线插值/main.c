/**********************************************************
				用于AD温度抛物线插值算法
**********************************************************/
#include <stdio.h>

#define N 10	//折线由10个线段组成，即有11个点
float w=10.0;	//插值节点间隔为10℃
float w0=0.0;	//起始温度
float wn=100.0;	//终点温度

float x0,y0;			//第一个插值节点的坐标
float x1,y1;			//第二个插值节点的坐标
float L01,L02,L012;		//中间变量
//11个节点A/D转换结果
int adc[N+1] = {86,376,687,1021,1379,1760,2164,2592,3043,3515,4008};

float line(float x)
{
	return (y0+(y1-y0)*(x-x0)/(x1-x0));
}
	
float qins(int x)				//以线性插值算法为基础的抛物线插值算法
{
	int i;
	if(x<adc[0]) return (w0);	//如果AD转换结果过低，返回起始温度
	if(x>=adc[N]) return (wn);	//如果AD转换结果过高，返回终点温度
	for(i=1;i<N;i++)	
		if(x<adc[i+1])	break;	//判断x的所在区间，得到i的坐标
	x0=adc[i-1];	y0=w*(i-1);
	x1=adc[i];		y1=w*i;
	L01 = line(x);				//过点i-1和i作直线L01
	x1=adc[i+1];	y1=w*(i+1);
	L02=line(x);				//过点i-1和i+1作直线L02
	x0=adc[i];		y0=L01;
	x1=adc[i+1];	y1=L02;
	L012=line(x);				//过(adc[i],L01)和(adc[i+1],L02)作直线L012完成抛物线插值
	return (L012);			//返回抛物线插值计算结果
}

int main()		//折线插值法验算程序
{
	int x;
	float y;
	while(1)
	{
		printf("\nAD转化结果：");
		scanf("%d",&x);
		if(x==0)break;
		y=qins(x);	//执行折线插值法算法
		printf("\n对应温度为： %2.2f℃",y);
	}
}