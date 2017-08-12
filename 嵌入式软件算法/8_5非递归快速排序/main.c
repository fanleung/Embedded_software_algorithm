#include <stdio.h>
#define MAX 100
int R[MAX+1];			//R[1]到R[n]存储待排序元素，R[0]用作辅助
int n;

typedef struct
{
	int d[MAX];			//用数组作为队列的存储空间
	int front,rear;		//指示队头，队尾
}SEQUEUE;
SEQUEUE sq;

void disp(int S[]);		//声明函数

int ENQUEUE(int x)		//顺序循环队列入队算法
{
	if(sq.front == (sq.rear +1 ) % MAX)		//判断是否队满
		return NULL;
	else
	{
		sq.rear = (sq.rear+1) % MAX;	//队尾加1
		sq.d[sq.rear] = x;			//插入x
		return 1;
	}
}

int DEQUEUE()
{
	if(sq.front == sq.rear)		//判断是否队空
		return NULL;
	else 
	{
		sq.front = (sq.front+1)% MAX;	//队头加1
		return (sq.d[sq.front]);		//出队1个元素
	}
}

void QUICKSORT()
{
	int i,j,l,r;
	sq.front = sq.rear =MAX-1;		//初始化空队
	ENQUEUE(1);						//排序区间起点
	ENQUEUE(n);						//排序区间终点
	while(1)
	{
		l=DEQUEUE();				//排序区间起点
		r=DEQUEUE();				//排序区间终点
		if(l == NULL)	return;		//没有待排序区间，算法结束
		i=l;
		j=r;
		R[0] =R[i];
		while(i<j)
		{
			while(R[j]>=R[0] && i<j) j--;	//右边： 比基数大，j往左走
				if(i<j)	R[i++] = R[j];		//如果跟基数对比小于基数，将此数放到基数位置，i往右边走
			
			while(R[i]<R[0] && i<j) i++;	//左边： 比基数小，i往右走
				if(i<j) R[j--] = R[i];		//如果比基数大，将此书放到基数位置，j往左走
		}
		R[i] = R[0];	//把基数的值还出来
		disp(R);
		if(l<i-1)			//如果小数区存在
		{
			ENQUEUE(l);		//小数区起点序号入队
			ENQUEUE(i-1);	//小数区终点序号入队
		}
		if(i+1<r)			//如果大数区存在
		{
			ENQUEUE(i+1);	//大数区起点序号入队
			ENQUEUE(r);		//大数区终点序号入队
		}
	}
}

void disp(int S[])
{
	int i;
	printf("\n");
	for(i=1;i<=n;i++)	printf("%d ",S[i]);
	printf("\n");
}

void main()
{
	int i;
	while(1)
	{
		printf("\n输入元素个数：");
		scanf("%d",&n);
		if(n<=MAX) break;
		printf("\n个数不能超过%d",MAX);
	}
	for(i=1;i<=n;i++)
	{
		printf("\n输入第%d个元素的值：",i);
		scanf("%d",&R[i]);
	}
	disp(R);
	QUICKSORT();
}