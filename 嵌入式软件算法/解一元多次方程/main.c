#include <stdio.h> 
#define N 10+1 
#define LEN sizeof(RC) 
typedef struct 
{
	float value; 
	struct RC *next; 
}RC; 


float power(float x,int y) /*此函数为求幂函数*/ 
{	
	float out;int i;
	float sum;
	for(i=1,out=1;i<=y;i++) 
	{
		sum*=x;
	} 
	return sum;
} 

float root(float x1,float x2,float dgname[N]) /*形参中的数组头指针对应实参二维数组的每一行的头指针*/ 
{
	int i;float y1,y2,set,value,x3,y3=1; /*该函数root用弦截法求出某一元指定次方程的根*/ 
	x3=x1; 
	while(y3<1E-6&&y3>-(1E-6)) 
	{
		if(y3<0) x1=x3; 
		else x2=x3; 
		for(i=0,value=0;i<=N;i++) /*三个for函数用于求出一元多次方程的值(y1,y2,y3)*/ 
		{
			set=power(x1,i)*dgname[i];value+=set;} 
			y1=value; 
			for(i=0,value=0;i<=N;i++) 
			{
				set=power(x2,i)*dgname[i];value+=set;} 
				y2=value; 
				x3=(y2*x1-y1*x2)/(y2-y1); 
				for(i=0,value=0;i<=N;i++) 
				{
					set=power(x3,i)*dgname[i];value+=set;} 
					y3=value; 
				} 
	return(y3); 
} 

main() 
{
	int h_p,i,j,count;
	float btm,top;
	float cfc[N-1][N];RC *head,*p1,*p2,*p3; /*cfc数组用于储存原方程以及历次求导的各项系数*/ 
	printf("\nEnter the highest times power(at largest times power:%d)",N-1); 
	scanf("%d",&h_p); 
	printf("\nEnter the coefficient from high times power to low times power in sequence"); 
	for(i=h_p-1;i>=0;i--) 
	{
		scanf("%f",cfc[0][i]);} 
		if(h_p<N) 
		{
			for(i=h_p;i<=N-1;i++)
			{
				cfc[0][i]=0;
			}
		} 
		printf("\nEnter the area of roots exist in"); 
		printf("\tlarger than:"); 
		scanf("%f",&btm); 
		printf("\tsmaller than:"); 
		scanf("%f",&top); 
		for(i=0;i<=N-2;i++) 
		{
			for(j=0;j<=h_p-1-i;j++)
			{
				cfc[i+1][j]=cfc[i][j+1]*(j+1);
			}
		} /*添加cfc数组内容*/ 
		head=p1=malloc(LEN);
		*head->value=btm; /*top,btm分别为方程域的上下限*/ 
		for(i=N-1;i>=0;i--) /*建立链表(指针head,p1,p2,p3有关)储存解各次不同方程的根,不断更新*/ 
		{
			*p1=*head;p2=*p1->next; 
			if(*p1->value**p2->value<0) 
			{
				p3=malloc(LEN);
				*p3->value=*p2->value;
				*p2->next=p3;
				*p2->value=root(*p1->value,*p2->value,cfc[i]);
				p1=p3;p2=*p1->next;
			} 
			if((*p1->value)*(*p2->value)<0 && *p2->value!=top) p2=*p2->next; 
			for(;*p2->value=top;) 
			{
				if(*p1->value**p2->value<0) 
				{
					*p1->value=root(*p1->value,*p2->value,cfc[i]);
					p1=*p1->next;p2=*p2->next;
				} 
			if((*p1->value)*(*p2->value)>0) p1=*p1->next; 
			} 
			} 
			printf("\nSo the roots are:\n"); 
			if(*head->next->value!=top) 
			{
				for(p1=*head->next;;p1=*p1->next) 
				{
					if(*p1->value=top) break;
					printf("%f",*p1->value);
				} 
			} 
			else printf("The function has no roots"); 
}