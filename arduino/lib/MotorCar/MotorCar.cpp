#include "Arduino.h"
#include "MotorCar.h"
/*
MotorCar类函数
功能:定义引脚
参数:
       _slpin,左速引脚
       _dlpin,左方引脚
       _srpin,右速引脚
       _drpin,右方引脚
*/
MotorCar::MotorCar(int _slpin,int _dlpin,int _srpin,int _drpin)
{
  _speedLeftPin=_slpin;
  _speedRightPin=_srpin;
  _dirLeftPin=_dlpin;
  _dirRightPin=_drpin;
  pinMode(_speedLeftPin,OUTPUT);
  pinMode(_speedRightPin,OUTPUT);
  pinMode(_dirLeftPin,OUTPUT);
  pinMode(_dirRightPin,OUTPUT);
}
/*
forward了函数---前进
功能:前进
   参数 :_speed--前进速度,范围0~255
*/
void MotorCar::forward(int _speed)
{
  digitalWrite(_dirRightPin,HIGH);//
  digitalWrite(_dirLeftPin,HIGH);//
  analogWrite(_speedRightPin,_speed);//
  analogWrite(_speedLeftPin,_speed);//
}
 /*
back了函数---后退
功能:后退
   参数 :_speed--后退速度,范围0~255
*/
void MotorCar::back(int _speed)
{
  digitalWrite(_dirRightPin,LOW);//
  digitalWrite(_dirLeftPin,LOW);//
  analogWrite(_speedRightPin,_speed);//
  analogWrite(_speedLeftPin,_speed);//
}
  /*
turnLeft了函数--左前转
功能:左转
   参数 :_speed--左转速度,范围0~255
*/
void MotorCar::turnLeft(int _speed)
{
  digitalWrite(_dirRightPin,HIGH);//
  analogWrite(_speedRightPin,_speed);//
  
  analogWrite(_speedLeftPin,0);//
}
  /*
turnLeft2了函数--左后转
功能:左转
   参数 :_speed--左转速度,范围0~255
*/
void MotorCar::turnLeft2(int _speed)
{
  digitalWrite(_dirRightPin,LOW);//
  analogWrite(_speedRightPin,_speed);//
  
  analogWrite(_speedLeftPin,0);//
}
   /*
turnRight了函数--右前转
功能:右转
    参数 :_speed--右转速度,范围0~255
*/
void MotorCar::turnRight(int _speed)
{
  digitalWrite(_dirLeftPin,HIGH);//
  analogWrite(_speedLeftPin,_speed);//
  
  analogWrite(_speedRightPin,0);//
}
   /*
turnRight2了函数--右后转
功能:右转
    参数 :_speed--右转速度,范围0~255
*/
void MotorCar::turnRight2(int _speed)
{
  digitalWrite(_dirLeftPin,LOW);//
  analogWrite(_speedLeftPin,_speed);//
  
  analogWrite(_speedRightPin,0);//
}
   /*
turnLeftOrigin了函数---原地左转
功能:原地左转
    参数 :_speed--原地左转速度,范围0~255
*/
void MotorCar::turnLeftOrigin(int _speed)
{
  digitalWrite(_dirRightPin,HIGH);//
  digitalWrite(_dirLeftPin,LOW);//
  analogWrite(_speedLeftPin,_speed);//
  analogWrite(_speedRightPin,_speed);//
}
   /*
turnRightOrigin了函数---原地右转
功能:原地右转
   参数 :_speed--原地右转速度,范围0~255
*/
void MotorCar::turnRightOrigin(int _speed)
{
  digitalWrite(_dirRightPin,LOW);//
  digitalWrite(_dirLeftPin,HIGH);//
  analogWrite(_speedLeftPin,_speed);//
  analogWrite(_speedRightPin,_speed);//
}
   /*
stop了函数---停止
功能:停止
    参数 :无
*/
void MotorCar::stop()
{
  analogWrite(_speedLeftPin,0);//
  analogWrite(_speedRightPin,0);//
} 