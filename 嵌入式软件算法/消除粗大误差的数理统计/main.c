#include <stdio.h>
#include <math.h>
#define MAX 200			//样本最大值200

float d[MAX];		//存放样本数据
int n;				//当前样本个数
float ave;			//平均数
float s;			//方差

float averg()
{
	int i;
	float sum;
	for(i=0,sum=0;i<n;i++)
		sum+=d[i];
	return sum/n;
}

float jfc()
{
	int i;
	float sum,c;
	for(i=0,sum=0;i<n;i++)
	{
		c=d[i]-ave;
		sum+=c*c;
	}
	return sqrt(sum/(n-1));
}

int del()
{
	int i,k;
	float low,high;
	low=ave-3*s;
	high=ave+3*s;
	k=0;								//初始化剔除标志
	for(i=0;i<n;i++)					
		if(d[i]<low || d[i]>high)		//发现坏样本
		{
			if(i<n-1)					//如果该样本不是最后一个样本
			{
				d[i]=d[n-1];		//用最后一个样本来覆盖这个样本
				i--;				//退回前一个位置以便处理了刚刚覆盖的样本
			}
			n--;		//当前有效样本个	数
			k=1;		//设置剔除操作标志
		}
		return k;	//返回剔除标志
}

void main()
{
	int i;
	printf("\n\n亲输入数据样本的个数：");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("亲输入第%d个数据样本的值：",i+1);
		scanf("%f",&d[i]);
	}
	getchar();
	while(1)
	{
		ave=averg();
		s=jfc();
		if(!del()) break;
	}
	printf("\n剔除坏数样本后的平均值=%f\n",ave);
	printf("\n剔除坏数样本后的均方差=%f\n",s);
	getchar();
}