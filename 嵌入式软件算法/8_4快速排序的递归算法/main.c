#include <stdio.h>
#define MAX 100
int R[MAX+1];			//R[1]到R[n]存储待排序元素，R[0]用作辅助
int n;

void disp(int S[]);

void QUICKSORT(int low,int high)
{
	int i,j;
	if(low>=high)	return;
	i=low;
	j=high;
	R[0]=R[i];
	while(i<j)
	{
		while(R[j]>=R[0] && i<j) j--;	//右边： 比基数大，j往左走
			if(i<j)	R[i++] = R[j];		//如果跟基数对比小于基数，将此数放到基数位置，i往右边走
		
		while(R[i]<R[0] && i<j) i++;	//左边： 比基数小，i往右走
			if(i<j) R[j--] = R[i];		//如果比基数大，将此书放到基数位置，j往左走
	}
	R[i] = R[0];	//把基数的值还出来
	disp(R);
	if(low<i-1)	QUICKSORT(low,i-1);		//左边如果有两个以上元素，递归调用
	if(i+1<high) QUICKSORT(i+1,high);	//右边如果有两个以上元素，递归调用
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
	QUICKSORT(1,n);
}