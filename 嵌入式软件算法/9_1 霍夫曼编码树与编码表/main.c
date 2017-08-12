/*****
霍夫曼编码
*******/

#include <stdio.h>
#include <conio.h>
#include <string.h>

#define MAX_NUM 10000		//定义一个很大的数，用于查找最小值算法
#define MAX 20				//编码对象个数的最大值
int n;						//编码对象的实际个数

typedef struct						//定义哈夫曼树节点的数据类型
{
	char c;							//用一个字符代表一个编码对象
	float weight;					//该编码对象对应的权值
	int parent,lchild,rchild;		//父节点，左孩子，右孩子指针
}HTNode;

HTNode HT[2*MAX-1];
char CODE[MAX][MAX];
char CH[20];				//待编码的字符串
char B[60];					//存放编码后的二进制字符串

void createHFMTree();
void Encoding();
void Decoding();

int main()
{
	int i,j,root;
	printf("\n\n输入编码对象的个数：");
	scanf("%d",&n);
	for(i=0;i<n;i++)		//输入n个编码对象的原始数据，初始化节点指针
	{
		printf("输入代表编码对象字符:");
		scanf("%s",&HT[i].c);
		printf("输入对应的权值：");
		scanf("%f",&HT[i].weight);
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	root = 2*n-2;		//将最后一个中间节点作为霍夫曼树的根节点
	for(i=n;i<=root;i++)
	{
		HT[i].c = '\0';
		HT[i].weight=0;
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	createHFMTree();		//生成霍夫曼编码树和编码表
	for(i=0;i<n;i++)		//显示霍夫曼编码表
	{
		printf("\n");
		printf("字符：%c\t",HT[i].c);
		printf("\t权值：%3.2f\t",HT[i].weight);
		printf("\t对应的哈夫曼编码：");
		puts(CODE[i]);
	}
	printf("\n输入代表消息串的字符串：");
	scanf("%s",CH);
	Encoding();		//进行编码
	printf("\n输入二进制代码串：");
	scanf("%s",B);
	Decoding();		//进行译码
	getchar();
	return 0;
}

void Encoding()				//编码函数
{
	int i=0,j;
	B[0]='\0';				//初始化编码结果为空字符串
	printf("\n对应的二进制代码串是：");		//显示编码结果
	while(CH[i])							//扫描待编码字符串，直到字符串结束标志为止
	{
		for(j=0;j<n;j++)					//将待编码字符与代表编码对象的字符进行比较
		
			if(CH[i] == HT[j].c)			//找到相同的字符
			{
				printf("%s",CODE[j]);		//从编码表中取出对应的编码进行显示
				strcpy(B,CODE[j]);			//拷贝到编码结果
				break;						//完成了一个字符的编码
			}
	i++;					//继续扫描下一个字符
	}
	printf("\n");
}

void Decoding()
{
	int i=0;									//扫描二进制码串的指针
	int j=0;									//存放译码结果的指针
	int p;										//指向霍夫曼编码树每个节点的动态指针
	int root=2*n-2;								//霍夫曼编码树根节点的编码
	printf("\n对应消息串是：");					//准备输出二进制码串
	while(B[i])
	{
		p=root;		//从霍夫曼编码树根节点开始
		while(HT[p].lchild || HT[p].rchild)		//如果当前节点有子节点
		{
			if(B[i]=='0')					//当前二进制码是0就移动到左子节点
				p = HT[p].lchild;	
			else p=HT[p].rchild;			//是1就移动到右子结点
			i++;					//取下一个二进制码
		}
		printf("%c",HT[p].c);	//显示该叶节点代表消息的字符
		CH[j] = HT[p].c;		//并将该字符保存到译码结果的数组中
		j++;					//调整存放译码结果的指针
	}
	CH[j]='\0';
	printf("\n");
}


void createHFMTree()		//生成霍夫曼编码树和编码表的算法
{
	int i,j,k,min,p,q,root;
	char c[MAX];		//存放临时编码
	root = 2*n-2;		//最后一个中间节点为霍夫曼编码树的根节点
	for(i=n;i<=root;i++)
	{
		min = MAX_NUM;		//初始化最小值
		for(j=0;j<i;j++)
		if(HT[j].parent == 0 && HT[j].weight < min)
		{	
			p=j;					//保存权值最小节点的编号
			min = HT[j].weight;		//更新最小值
		}
		min = MAX_NUM;		//再次初始化最小值，准备寻找第2个
		for(j=0;j<i;j++)
		if(HT[j].parent == 0 && j!=p && min > HT[j].weight)	//
		{
			q=j;
			min=HT[j].weight;
		}
	HT[p].parent = i;	//当前中间节点HT[i]做子节点HT[p]的父节点
	HT[q].parent = i;	//当前中间节点HT[i]做子节点HT[q]的父节点
	HT[i].lchild = p;	//子节点HT[p]做中间节点HT[i]的左子节点
	HT[i].rchild = q;	//子节点HT[p]做中间节点HT[i]的右子节点
	HT[i].weight = HT[p].weight + HT[q].weight;		//中间节点的权值
		}
	for(i=0;i<n;i++)
	{
		p=i;				//从当前叶节点出发
		q=HT[i].parent;		//找到父节点
		k=n-1;				//初始化记录编码的指针，指向临时字符数组的末端
		c[k]='\0';
		while(q)
		{
			if(p==HT[q].lchild)
				c[--k]='\0';
			else c[--k]='1';
			p=q;			//向上移动一层，原来的父节点成为当前节点
			q=HT[p].parent;	//新的父节点
		}					//到达根节点后，父节点不存在，路径结束
	for(j=0;k<n;j++,k++)
		CODE[i][j]=c[k];
	}
}

