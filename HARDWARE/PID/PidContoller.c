#include "sys.h"
#include "PidContoller.h"
//#include "UserConfiguration.h"

//����ʽPID�㷨
void PID_AbsoluteMode(PID_AbsoluteType* PID)
{
 if(PID->kp      < 0)    PID->kp      = -PID->kp;
 if(PID->ki      < 0)    PID->ki      = -PID->ki;
 if(PID->kd      < 0)    PID->kd      = -PID->kd;
 if(PID->errILim < 0)    PID->errILim = -PID->errILim;

 PID->errP = PID->errNow;  //��ȡ���ڵ�������kp����

 PID->errI += PID->errNow; //�����֣�����ki����

 if(PID->errILim != 0)	   //΢�����޺�����
 {
  if(     PID->errI >  PID->errILim)    PID->errI =  PID->errILim;
  else if(PID->errI < -PID->errILim)    PID->errI = -PID->errILim;
 }
 
 PID->errD = PID->errNow - PID->errOld;//���΢�֣�����kd����

 PID->errOld = PID->errNow;	//�������ڵ����
 
 PID->ctrOut = PID->kp * PID->errP + PID->ki * PID->errI + PID->kd * PID->errD;//�������ʽPID���

}


/*******************************************************************************************************/



//����ʽPID�㷨
void PID_IncrementMode(PID_IncrementType* PID)
{
 float dErrP, dErrI, dErrD;
 
 if(PID->kp < 0)    PID->kp = -PID->kp;
 if(PID->ki < 0)	PID->ki = -PID->ki;
 if(PID->kd < 0)    PID->kd = -PID->kd;

 dErrP = PID->errNow - PID->errOld1;

 dErrI = PID->errNow;

 dErrD = PID->errNow - 2 * PID->errOld1 + PID->errOld2;

 PID->errOld2 = PID->errOld1; //�������΢��
 PID->errOld1 = PID->errNow;  //һ�����΢��

 /*����ʽPID����*/
 PID->dCtrOut = PID->kp * dErrP + PID->ki * dErrI + PID->kd * dErrD;
 
 if(PID->kp == 0 && PID->ki == 0 && PID->kd == 0)   PID->ctrOut = 0;

 else PID->ctrOut += PID->dCtrOut;
}

/*****************************************Power Control PID***********************************************/
extern short nowtem;

float temperatureTag, temperatureNow;//����һ��Ŀ���¶ȣ������ٶȣ�������

PID_AbsoluteType PID_Control;//����PID�㷨�Ľṹ��
extern u16 PWM_Duty;
void User_PidPWMControl(float Tag)
{
	temperatureNow = nowtem/10.0f; temperatureTag = Tag;

	PID_Control.errNow = temperatureTag - temperatureNow; //���㲢д���¶����

	PID_Control.kp      = 70.0f;             //д�����ϵ��
	PID_Control.ki      = 1.3f;              //д�����ϵ��
	PID_Control.kd      = (float)0.01;              //д��΢��ϵ��
	PID_Control.errILim = (float)500.0;           //д������������Ϊ1000 ����Ϊ-1000

	PID_AbsoluteMode(&PID_Control);       //ִ�о���ʽPID�㷨

	if(PID_Control.ctrOut<=0) PID_Control.ctrOut=0;
	if(PID_Control.ctrOut>=999) PID_Control.ctrOut=999;

	PWM_Duty =PID_Control.ctrOut;         //��ȡ����ֵ

}
