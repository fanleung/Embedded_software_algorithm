/************************************************
位置式PID算法：直接计算出输出控制信号的大小
Out= KP*ek + KI*Sk + KD*dk
************************************************/

float Set;				//设定值
float KP;				//比例常数
float KI;				//积分常数
float KD;				//微分常数
float LE;				//上次误差
float SE;				//累计误差

void pid(void)			//需要周期性执行此任务函数
{
	float now,E,DE,out;
	while(1)
	{
		now=sampleadc();	//采样得到控制对象的当前值
		E=Set-now;			//计算当前误差   P
		SE+=E;				//累计误差		 I
		DE=E-LE;			//下一刻变化趋势 D
		
		out=KP * E			//P比例项
		   +KI * SE			//I积分项
		   +KD * DE;		//D微分项
		CtrlOut(out);		//输出计算结果，执行
		LE=E;				//保存误差值，供下次计算使用
		delay_ms(500);		//采样周期500ms
	}
}