#include <stdio.h>
#define MAX 100			//元素个数的最大值
#define MAXS (MAX+2)
int SR[MAX],TR[MAX];		//待排序数据存放在数组R[]中，数组R1[]为辅助数组
int n;					//实际元素个数，为全局变量

void disp(int S[]);

typedef struct
{
	int d[MAXS];				//用数组作为队列的存储空间
	int front,rear;				//指示队头和队尾的标志
}SEQUEUE;						//顺序队列类型定义
SEQUEUE sq;						//定义顺序队列

int ENQUEUE(int x)				//顺序循环队列的入队算法
{
	if(sq.front == (sq.rear+1) % MAXS)	//满队，入队失败(头=尾)
		return NULL;
	else 
	{
		sq.rear = (sq.rear+1)%MAXS;		//队尾入列了，队尾加1
		sq.d[sq.rear] = x;				//数据入队
		return 1;						//入队成功
	}
}

int DEQUEUE()					//顺序循环队列的出队算法
{
	if(sq.front == sq.rear)		//空队，出队失败
		return NULL;
	else 
	{
		sq.front = (sq.front + 1)% MAXS;	//对首出列了，队首加1
		return (sq.d[sq.front]);
	}
	
}

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
int MERGEPASS(int S[],int T[])
{
	int low,mid,high,i;
	int w=0;		
	low=DEQUEUE();
	while(1)
	{
		mid = DEQUEUE();
		if(mid == -1)
		{
			for(i=low; i<n;i++)
				T[i]=S[i];
				w++;
				ENQUEUE(low);
				ENQUEUE(-1);
				return w;
		}
		high=DEQUEUE();
		if(high==-1)
		{
			high=n;
			MERGE(S,T,low,mid,high);
			w++;
			ENQUEUE(low);
			ENQUEUE(-1);
			return w;
		}
		MERGE(S,T,low,mid,high);
		w++;
		ENQUEUE(low);
		low=high;
	}
}

//外层算法
void MERGESORT()
{
	int i;							//
	sq.front = sq.rear = MAX-1;		//初始化空队
	ENQUEUE(0);
	for(i=1;i<n;i++)
		if(SR[i]<SR[i-1])
			ENQUEUE(i);
		ENQUEUE(-1);				//结束标志入队
		while(1)
		{
			MERGEPASS(SR,TR);		//在两个数组之间反复进行归并操作
			disp(SR);				//进行一轮归并，结果在TR[]
			if(MERGEPASS(TR,SR)==1)	//显示这一轮归并操作后的结果
				return ;			//再进行一轮归并，结果返回到SR[]
			disp(SR);				//如果本轮归并只进行一次，则结束排序，否则显示此轮结果并进行下一轮归并
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
		scanf("%d",&SR[i]);
	}
	disp(SR);			//显示尚未进行排序的数组
	MERGESORT();		//调用改进的归并排序函数
	disp(SR);			//显示排序后的数组各个元素数据
}