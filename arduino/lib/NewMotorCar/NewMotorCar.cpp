#include "Arduino.h"
#include "NewMotorCar.h"

NewMotorCar::NewMotorCar(int _slpin,int _d1lpin,int _d2lpin)//int _srpin,int _drpin)
{
  _speedLeftPin=_slpin;
  _dir1LeftPin=_d1lpin;
  _dir2LeftPin=_d2lpin;
  //_speedRightPin=_srpin;
  //_dirRightPin=_drpin;
  pinMode(_speedLeftPin,OUTPUT);
  pinMode(_dir1LeftPin,OUTPUT);
  pinMode(_dir2LeftPin,OUTPUT);
 // pinMode(_speedRightPin,OUTPUT);
 // pinMode(_dirRightPin,OUTPUT);
}

void NewMotorCar::work(int _speed)
{
  if(_speed>0)
  {
  digitalWrite(_dir1LeftPin,LOW);//
  digitalWrite(_dir2LeftPin,HIGH);//
  analogWrite(_speedLeftPin,_speed);//
  }
  else if(_speed<0)
  {
  digitalWrite(_dir1LeftPin,HIGH);// 
  digitalWrite(_dir2LeftPin,LOW);//   analogWrite(_speedLeftPin,_speed);//s
  analogWrite(_speedLeftPin,abs(_speed));//
  }
  else 
  {
  digitalWrite(_dir1LeftPin,LOW);//
  digitalWrite(_dir2LeftPin,LOW);//
  analogWrite(_speedLeftPin,_speed);//
  }
  
}
