/************************************************
增量式PID算法：直接计算出调整量的大小
DOut= KP*dk + KI*ek + KD*(dk-dk-1)
************************************************/

float Set;				//设定值
float KP;				//比例常数
float KI;				//积分常数
float KD;				//微分常数
float LE;				//上次误差
float SE;				//累计误差
float LD;				//上次的微分值

void pid(void)			//需要周期性执行此任务函数
{
	float now,E,DE,Dout;
	while(1)
	{
		now=sampleadc();	//采样得到控制对象的当前值
		E=Set-now;			//计算当前误差   
		DE=E-LE;			//下一刻变化趋势 D
		
		Dout=KP * DE			//P比例项
		   +KI * E			//I积分项
		   +KD * (DE-LE);	//D微分项
		CtrlOut(Dout);		//输出计算结果，执行
		LE=E;				//保存误差值，供下次计算使用
		LD=DE;
		delay_ms(500);		//采样周期500ms
	}
}