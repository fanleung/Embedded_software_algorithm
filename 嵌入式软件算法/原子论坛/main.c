#include <stdio.h>

void change(unsigned char *p,unsigned char count);

int main()
{
	int *a;
	int *b;
	*a=10;
	*b=10;
	change(*a,*b);
	printf("%d,%d",a,b);
}


void change(unsigned char *p,unsigned char count)
{
	while(count>0)
	{
		*(p+count)=*(p+count-1);
		count--;
	}
}