#include <stdio.h>

#define a 0.03125	//滤波系数
float samp;			//滤波算法的有效输出

void tasksampctrl(void)
{
	float _new;
	samp=sample_adc();		//初始化
	delay_ms(500);			//延时500ms
	while(1)
	{
		_new=sample_adc();	//新的采样数据
		samp= A*_new+(1-A)*samp;
		delay_ms(500);
	}
}
