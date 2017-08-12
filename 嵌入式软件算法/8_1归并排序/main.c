#include <stdio.h>
#define MAX 100			//元素个数的最大值
int R[MAX],R1[MAX];		//待排序数据存放在数组R[]中，数组R1[]为辅助数组
int n;					//实际元素个数，为全局变量

void disp(int S[]);
//内层算法
//归并两个有序子列
void MERGE(int P[],int Q[],int low,int mid,int high)
{
	int i,j,k;
	i=low;j=mid;k=low;
	while(i<mid && j<high)		//取小者复制
		if(P[i] <= P[j] ) Q[k++] = P[i++];
		else Q[k++] = P[j++];
	while(i<mid) Q[k++] = P[i++];	//复制第一个子列剩余元素
	while(j<high) Q[k++] = P[j++];	//复制第二个子列剩余元素
}

//中层算法
void MERGEPASS(int M[],int N[],int length)
{
	int i,j;
	i=0;		//指向第一对子列的起始端
	while(i+2*length -1 < n)		//归并两个长度为length的子列
	{
		MERGE(M,N,i,i+length,i+2*length);	
		i+=2*length;			//指向下一对子列的起始端、
	}
	if(i+length <n)
		MERGE(M,N,i,i+length,n);	//第2个子列长度小于length
	else for(j=i;j<n;j++)
		N[j]=M[j];				//将最后一个子列复制给数组N
}

//外层算法
void MERGESORT()
{
	int length=1;			//有序子列的长度初始化为1，从单个元素开始进行归并
	while(length <n)			//只要整个数组还可以分成两个以上子列
	{	
		MERGEPASS(R,R1,length);	//进行一轮归并，从R[]到R1[]
		disp(R1);				//显示这一轮归并操作后的结果
		length *=2;				//一轮归并后，有序子列的长度增加一倍
		MERGEPASS(R1,R,length);	//再进行一轮归并，结果返回给R[]
		length *=2;				//一轮归并后，有序子列的长度增加一倍
		disp(R);				//显示这一轮归并操作的结果
	}
}

void disp(int S[])
{
	int i;
	printf("\n");
	for(i=0;i<n;i++)
		printf("%d ",S[i]);
	printf("\n");
}

void main()
{
	int i;
	while(1)
	{
		printf("\n请输入实际元素个数：");
		scanf("%d",&n);
		if(n<=MAX)break;
		printf("\n实际元素个数不能超过%d",MAX);
	}
	for(i=0;i<n;i++)
	{
		printf("\n输入第%d个元素的值：",i+1);
		scanf("%d",&R[i]);
	}
	disp(R);
	MERGESORT();
}