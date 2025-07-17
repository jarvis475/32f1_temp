#include "sys.h"
#include "PidContoller.h"
//#include "UserConfiguration.h"

//绝对式PID算法
void PID_AbsoluteMode(PID_AbsoluteType* PID)
{
 if(PID->kp      < 0)    PID->kp      = -PID->kp;
 if(PID->ki      < 0)    PID->ki      = -PID->ki;
 if(PID->kd      < 0)    PID->kd      = -PID->kd;
 if(PID->errILim < 0)    PID->errILim = -PID->errILim;

 PID->errP = PID->errNow;  //读取现在的误差，用于kp控制

 PID->errI += PID->errNow; //误差积分，用于ki控制

 if(PID->errILim != 0)	   //微分上限和下限
 {
  if(     PID->errI >  PID->errILim)    PID->errI =  PID->errILim;
  else if(PID->errI < -PID->errILim)    PID->errI = -PID->errILim;
 }
 
 PID->errD = PID->errNow - PID->errOld;//误差微分，用于kd控制

 PID->errOld = PID->errNow;	//保存现在的误差
 
 PID->ctrOut = PID->kp * PID->errP + PID->ki * PID->errI + PID->kd * PID->errD;//计算绝对式PID输出

}


/*******************************************************************************************************/



//增量式PID算法
void PID_IncrementMode(PID_IncrementType* PID)
{
 float dErrP, dErrI, dErrD;
 
 if(PID->kp < 0)    PID->kp = -PID->kp;
 if(PID->ki < 0)	PID->ki = -PID->ki;
 if(PID->kd < 0)    PID->kd = -PID->kd;

 dErrP = PID->errNow - PID->errOld1;

 dErrI = PID->errNow;

 dErrD = PID->errNow - 2 * PID->errOld1 + PID->errOld2;

 PID->errOld2 = PID->errOld1; //二阶误差微分
 PID->errOld1 = PID->errNow;  //一阶误差微分

 /*增量式PID计算*/
 PID->dCtrOut = PID->kp * dErrP + PID->ki * dErrI + PID->kd * dErrD;
 
 if(PID->kp == 0 && PID->ki == 0 && PID->kd == 0)   PID->ctrOut = 0;

 else PID->ctrOut += PID->dCtrOut;
}

/*****************************************Power Control PID***********************************************/
extern short nowtem;

float temperatureTag, temperatureNow;//定义一个目标温度，采样速度，控制量

PID_AbsoluteType PID_Control;//定义PID算法的结构体
extern u16 PWM_Duty;
void User_PidPWMControl(float Tag)
{
	temperatureNow = nowtem/10.0f; temperatureTag = Tag;

	PID_Control.errNow = temperatureTag - temperatureNow; //计算并写入温度误差

	PID_Control.kp      = 70.0f;             //写入比例系数
	PID_Control.ki      = 1.3f;              //写入积分系数
	PID_Control.kd      = (float)0.01;              //写入微分系数
	PID_Control.errILim = (float)500.0;           //写入误差积分上限为1000 下限为-1000

	PID_AbsoluteMode(&PID_Control);       //执行绝对式PID算法

	if(PID_Control.ctrOut<=0) PID_Control.ctrOut=0;
	if(PID_Control.ctrOut>=999) PID_Control.ctrOut=999;

	PWM_Duty =PID_Control.ctrOut;         //读取控制值

}
