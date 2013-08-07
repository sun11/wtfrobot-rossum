/*
Copyright (c) 2013 WTFRobot

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * The name of the copyright holders may not be used to endorse or promote products
    derived from this software without specific prior written permission.

This software is provided by the copyright holders and contributors "as is" and
any express or implied warranties, including, but not limited to, the implied
warranties of merchantability and fitness for a particular purpose are disclaimed.
In no event shall the Intel Corporation or contributors be liable for any direct,
indirect, incidental, special, exemplary, or consequential damages
(including, but not limited to, procurement of substitute goods or services;
loss of use, data, or profits; or business interruption) however caused
and on any theory of liability, whether in contract, strict liability,
or tort (including negligence or otherwise) arising in any way out of
the use of this software, even if advised of the possibility of such damage.
*/
#include "Arduino.h"
#include <RobotParams.h>
#include <TimeInfo.h>
#include <OdometricLocalizer.h>
#include <SpeedController.h>
#include <BatteryMonitor.h>
#include <NewMotorCar.h> 
#include <Messenger.h>

#include <digitalWriteFast.h>  // library for high performance reads 
//  and writes by jrraines
// see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1267553811/0
// and http://code.google.com/p/digitalwritefast/

// It turns out that the regular digitalRead() calls are too slow and bring the arduino down when
// used in the interrupt routines while the motor is running at full speed creating more than
// 40000 encoder ticks per second per motor.




#define c_UpdateInterval 20      // update interval in milli seconds                         系统时间更新阈值  20ms
//#define c_MaxMotorCV   30      // range is 0 ... 89 (half servo range)                   最大舵机转动角度  30°

#define MotorWorkingTime   20

// container for robot params wheel diameter [m], trackwidth [m], ticks per revolution     参数：轮子直径，轮距，每圈脉冲计数
RobotParams _RobotParams = RobotParams();   //create robot params

TimeInfo _TimeInfo = TimeInfo();

NewMotorCar LMotor(13,12,11);
NewMotorCar RMotor(8,10,9);
//5,LPWM
//4,D
//6,RPWM
//7,D

//Servo _RightServo;  // create servo object to control right motor
//Servo _LeftServo;   // create servo object to control left motor

/////////////////////###############使用中断0，1进入编码器数据读取脉冲函数，用pin13,12,3,2读取两对AB脉冲值


// Quadrature encoders
// Left encoder
#define c_LeftEncoderInterrupt 0         //中断号
#define c_LeftEncoderPinA 2              //检测脚
#define c_LeftEncoderPinB 5
//#define LeftEncoderIsReversed            //判断是否反向工作
volatile bool _LeftEncoderBSet;          //PinA上升沿，进入中断后，检测PinB电平，大小要么为0，要么为1
volatile long _LeftEncoderTicks = 0;     //计数归零

// Right encoder
#define c_RightEncoderInterrupt 1
#define c_RightEncoderPinA 3
#define c_RightEncoderPinB 6
#define RightEncoderIsReversed            //判断是否反向工作
volatile bool _RightEncoderBSet;
volatile long _RightEncoderTicks = 0;    

////////////////////////////////////////////////###############机器人方位和速度

OdometricLocalizer _OdometricLocalizer(&_RobotParams, &_TimeInfo);                   //方位计算

SpeedController _SpeedController(&_OdometricLocalizer, &_RobotParams, &_TimeInfo);                  //速度调节   需要方位，参数，时间


#define c_ScaledBatteryVInPin A0// analog input pin for the battery voltage divider  //PIN A0  采集电池电压


#define c_VInToVBatteryRatio 2.921/////////////////////////A6上测的电压与真实电源电压的比值

BatteryMonitor _BatteryMonitor(c_ScaledBatteryVInPin, c_VInToVBatteryRatio);

// Instantiate Messenger object with the message function and the default separator (the space character)
Messenger _Messenger = Messenger();


/////////////////////////////////////###################################设置编码器
void SetupEncoders()
{
  // Quadrature encoders
  // Left encoder
  pinMode(c_LeftEncoderPinA, INPUT);      // sets pin A as input
  digitalWrite(c_LeftEncoderPinA, LOW);   // turn on pullup resistors
  pinMode(c_LeftEncoderPinB, INPUT);      // sets pin B as input
  digitalWrite(c_LeftEncoderPinB, LOW);   // turn on pullup resistors
  attachInterrupt(c_LeftEncoderInterrupt, HandleLeftMotorInterruptA, RISING);

  // Right encoder
  pinMode(c_RightEncoderPinA, INPUT);      // sets pin A as input
  digitalWrite(c_RightEncoderPinA, LOW);   // turn on pullup resistors
  pinMode(c_RightEncoderPinB, INPUT);      // sets pin B as input
  digitalWrite(c_RightEncoderPinB, LOW);   // turn on pullup resistors
  attachInterrupt(c_RightEncoderInterrupt, HandleRightMotorInterruptA, RISING); 
}



bool _IsInitialized = false;                  ///############初始化归0

void setup()
{

  Serial.begin(115200);                       //建立串口通信

  SetupEncoders();                            //建立编码器计数

  _Messenger.attach(OnMssageCompleted);       //建立信息读取  机制
  ///############
  // S代表  线速度与转向速度控制命令

  ///############参数初始化命令

  ///DriveGeometry
  ///SpeedControllerParams
  ///BatteryMonitorParams

  //_RightServo.attach(10);                     // attaches the servo on specified pin to the servo object   Servo 指定引脚PWM输出 
  //_LeftServo.attach(11);                      // attaches the servo on specified pin to the servo object   Servo 指定引脚PWM输出 

  /*
/////////////////////##########################先让轮子转动90°
   _RightServo.write(90);                      //即转动到90度。
   _LeftServo.write(90);
   */
  delay(100);                                 ////////延时100ms         
  _TimeInfo.Update();                       //系统初次更新时间
}

void loop()
{

  ReadSerial();                                       ////处理了下串口信息

  unsigned long milliSecsSinceLastUpdate = millis() - _TimeInfo.LastUpdateMillisecs;////此刻时间减去系统上次时间更新（毫秒级）
  if(milliSecsSinceLastUpdate >= c_UpdateInterval)    /////判断时间是否达到更新阈值
  {
    //Serial.println(milliSecsSinceLastUpdate);     

    // time for another update
    _TimeInfo.Update();                              ///////再次更新时间  

    if (_IsInitialized)                              ///////判断系统是否初始化 初始化工作，否则向PC请求初始化
    {                                                ///////第一次系统未初始化
      DoWork();                                      ///////更新 实时数据 ，执行运动命令，再次返回实时数据 
    }
    else
    {
      RequestInitialization();                       //////若系统未初始化成功，再次请求
    }
  }
}
///////////////////////////////////###################中心任务############################//////////////////////////////////////////////




/////////////###########################1111更新方位，电池电量，速度数据

/////////////###########################2222得到命令  控制小车运动（即控制信号）

/////////////###########################3333传回数据：电池电量，当前位置（x，y）（全局坐标），方向Heading（角度），前进速度Forword V，转度角度Omega

void DoWork()                       
{
  ///////////////####################更新数据
  _OdometricLocalizer.Update(_LeftEncoderTicks, _RightEncoderTicks);////Ticks由两个外部中断单独不获断取

  _BatteryMonitor.Update();

  _SpeedController.Update(false);

  //_SpeedController.Update(_BatteryMonitor.VoltageIsTooLow);     ////速度更新
  ////电池电量够则更新速度调节，否则stop



  ///////////////####################执行控制命令
  IssueCommands();



  ///////////////####################开始返回数据   
  Serial.print("o"); // o indicates odometry message    ####    通信协议：o代表里程计得来数据

  Serial.print("\t");                                           //// 数据之间空格

  ////小数点后保留3位有效数字
  Serial.print(_OdometricLocalizer.X, 3);                       ////（x，y）坐标 
  Serial.print("\t");
  Serial.print(_OdometricLocalizer.Y, 3);
  Serial.print("\t");
  Serial.print(_OdometricLocalizer.Heading, 3);                 ////方向
  Serial.print("\t");
  Serial.print(_OdometricLocalizer.V, 3);                       ////平移速度 
  Serial.print("\t");
  Serial.print(_OdometricLocalizer.Omega, 3);                   ////转向角速度

  Serial.print("\n");

  Serial.print("b\t"); // b indicates battery info message ## 通信协议：b 代表电池电量数据
  Serial.print(_BatteryMonitor.BatteryVoltage, 3);            ////小数点后保留3位有效数字
  //Serial.print("\t");
  //Serial.print(_BatteryMonitor.VoltageIsTooLow);
  Serial.print("\n");
  /*
  Serial.print(_LeftEncoderTicks);
   Serial.print("\t");
   Serial.print(_RightEncoderTicks);
   Serial.print("\n");
   */
}


//////////////////////////////#######################请求初始化系统
//////////////////////////////里程参数初始化
//////////////////////////////速度参数初始化
//////////////////////////////电池参数初始化
//////////////////////////////PC端根据print过来的字符完成相应初始化


void RequestInitialization()
{
  _IsInitialized = true;

  if (!_RobotParams.IsInitialized)
  {
    _IsInitialized = false;

    Serial.print("InitializeDriveGeometry"); // ##requesting initialization of the parameters of the differential drive needed for odometry calculations
    Serial.print("\n");
  }

  if (!_SpeedController.IsInitialized)
  {
    _IsInitialized = false;

    Serial.print("InitializeSpeedController"); //## requesting initialization of the speed controller
    Serial.print("\n");
  }

  if (!_BatteryMonitor.IsInitialized)
  {
    _IsInitialized = false;

    Serial.print("InitializeBatteryMonitor"); // ##requesting initialization of the battery monitor
    Serial.print("\n");
  }
}

///////////////////////////////#############################执行命令    控制两个电机转动
///////////////////////////////#############################将PI处理得到的电机运动参数执行
void IssueCommands()                 
{
  float normalizedRightMotorCV, normalizedLeftMotorCV;

  normalizedRightMotorCV = _SpeedController.NormalizedLeftCV;          ///PI调节后得到期望控制数据--转速
  normalizedLeftMotorCV  = _SpeedController.NormalizedRightCV;



  // Serial.print(_SpeedController.CommandedVelocity - 0.2 * _SpeedController.CommandedAngularVelocity);
  // Serial.print("\t");
  // Serial.print(_SpeedController.CommandedVelocity + 0.2 * _SpeedController.CommandedAngularVelocity);
  //  Serial.print("\t");

  /*
  Serial.print(_SpeedController.LeftError);
   Serial.print("\t");
   Serial.print(_SpeedController.RightError);
   Serial.print("\t");
   Serial.print(_SpeedController.TurnError);
   Serial.print("\t");
   Serial.print(_LeftEncoderTicks);
   Serial.print("\t");
   Serial.print(_RightEncoderTicks);
   Serial.print("\t");
   Serial.print(_OdometricLocalizer._PreviousLeftEncoderCounts);
   Serial.print("\t");
   Serial.print(_RobotParams.DistancePerCount);
   Serial.print("\t");
   Serial.print(_TimeInfo.SecondsSinceLastUpdate);
   
   Serial.print("\n");
   */

  /////////#####################映射        控制数据映射到电机转动指令值    60°到120°
  float leftMotorValue = mapFloat(normalizedLeftMotorCV, -1.0, 1.0, -200.0, 200.0); 
  float rightMotorValue = mapFloat(normalizedRightMotorCV, -1.0, 1.0, -160.0, 160.0); 
  if(leftMotorValue>250||leftMotorValue<-250)
  leftMotorValue=0;
  if(rightMotorValue>250||rightMotorValue<-250)
  rightMotorValue=0;
  Serial.print("Speed: ");
  Serial.print(_SpeedController.CommandedVelocity);
  Serial.print("\t");
  Serial.print(_SpeedController.CommandedAngularVelocity);
  Serial.print("\t");
  Serial.print(_SpeedController.angularVelocityOffset);
  Serial.print("\t");
  Serial.print(_SpeedController.LeftError);
  Serial.print("\t");
  Serial.print(_SpeedController.RightError);
  Serial.print("\t");
  Serial.print(_SpeedController.TurnError);
  Serial.print("\t");
  Serial.print(normalizedLeftMotorCV);
  Serial.print("\t");
  Serial.print(normalizedRightMotorCV);
  Serial.print("\t");
  Serial.print(leftMotorValue);
  Serial.print("\t");
  Serial.print(rightMotorValue);
  Serial.print("\t");
  Serial.print(_LeftEncoderTicks);
  Serial.print("\t");
  Serial.print(_RightEncoderTicks);
  Serial.print("\t");
  Serial.print(_OdometricLocalizer.VLeft,3);
  Serial.print("\t");
  Serial.print(_OdometricLocalizer.VRight,3);
  Serial.print("\t");
  Serial.print(abs(_OdometricLocalizer.VLeft)-abs(_OdometricLocalizer.VRight),3);
  Serial.print("\n");

   
  LMotor.work(leftMotorValue);
  RMotor.work(rightMotorValue);


  // _RightServo.write(rightServoValue);     // sets the servo position according to the scaled value (0 ... 179)    执行控制  电机转动
  // _LeftServo.write(leftServoValue);       // sets the servo position according to the scaled value (0 ... 179)
}


// Interrupt service routines for the left motor's quadrature encoder      ####PinA上升沿，进入中断，读编码器数字输出口 PinB
void HandleLeftMotorInterruptA()
{
  // Test transition; since the interrupt will only fire on 'rising' we don't need to read pin A
  _LeftEncoderBSet = digitalReadFast(c_LeftEncoderPinB);   // read the input pin

  // and adjust counter + if A leads B
#ifdef LeftEncoderIsReversed
  _LeftEncoderTicks -= _LeftEncoderBSet ? -1 : +1;
#else
  _LeftEncoderTicks += _LeftEncoderBSet ? -1 : +1;
#endif
}


// Interrupt service routines for the right motor's quadrature encoder    ####PinA上升沿，进入中断，读编码器数字输出口 PinB
void HandleRightMotorInterruptA()
{
  // Test transition; since the interrupt will only fire on 'rising' we don't need to read pin A
  _RightEncoderBSet = digitalReadFast(c_RightEncoderPinB);   // read the input pin             

  // and adjust counter + if A leads B
#ifdef RightEncoderIsReversed
  _RightEncoderTicks -= _RightEncoderBSet ? -1 : +1;
#else
  _RightEncoderTicks += _RightEncoderBSet ? -1 : +1;
#endif
}


////////////////////////####################读串口获取运动指令  
void ReadSerial()
{
  while (Serial.available())
  {
    _Messenger.process(Serial.read());
  }
}


// Define messenger function     #############       定义通信函数      读取初始化命令 初始化个数据 
void OnMssageCompleted()       /////////////////#####检测 处理PC端过来的信息
{                                            ///////////////先检查关键字
  if (_Messenger.checkString("s"))
  {
    SetSpeed();
    ClearOutMessenger();    
    return;
  }

  if (_Messenger.checkString("DriveGeometry"))
  {
    InitializeDriveGeometry();
    ClearOutMessenger();    
    return;
  }

  if (_Messenger.checkString("SpeedControllerParams"))
  {
    InitializeSpeedControllerParams();
    ClearOutMessenger();
    return;
  }

  if (_Messenger.checkString("BatteryMonitorParams"))
  {
    InitializeBatteryMonitor();
  }

  // clear out unrecognized content               
  ClearOutMessenger();
}

void ClearOutMessenger()
{
  while (_Messenger.available())
  {
    _Messenger.readChar();
  }
}


////////////////###################速度设定    大小，方向，转向速度
void SetSpeed()
{
  float commandedVelocity         = GetFloatFromBaseAndExponent(_Messenger.readInt(), _Messenger.readInt());  ////从PC端 获取速度命令参数 平移速度，转向角速度
  float commandedAngularVelocity  = GetFloatFromBaseAndExponent(_Messenger.readInt(), _Messenger.readInt());

  ///_OdometricLocalizer.CommandVelocity(commandedVelocity, commandedAngularVelocity);
  //////////////////////////PID调节控制数据
  _SpeedController.CommandVelocity(commandedVelocity, commandedAngularVelocity); 
}
//////////////######################  从PC端获取命令参数：车轮直径0.0762m   轮距0.37m  每圈的计数   19.5*500*2=19500 
/////////////set robot params wheel diameter [m], trackwidth [m], ticks per revolution
void InitializeDriveGeometry()
{
  float wheelDiameter       = GetFloatFromBaseAndExponent(_Messenger.readInt(), _Messenger.readInt());
  float trackWidth          = GetFloatFromBaseAndExponent(_Messenger.readInt(), _Messenger.readInt());
  int   countsPerRevolution = _Messenger.readInt();

  _RobotParams.Initialize(wheelDiameter, trackWidth, countsPerRevolution);     //初始化
  

   
}

////#######################################初始化速度控制系统参数        从PC端通过串口，用Messenger读取，计算得到PID调试需要的参数
void InitializeSpeedControllerParams()
{
  float velocityPParam = GetFloatFromBaseAndExponent(_Messenger.readInt(), _Messenger.readInt());
  float velocityIParam = GetFloatFromBaseAndExponent(_Messenger.readInt(), _Messenger.readInt());
  float turnPParam     = GetFloatFromBaseAndExponent(_Messenger.readInt(), _Messenger.readInt());
  float turnIParam     = GetFloatFromBaseAndExponent(_Messenger.readInt(), _Messenger.readInt());
  float commandTimeout = GetFloatFromBaseAndExponent(_Messenger.readInt(), _Messenger.readInt());

  _SpeedController.Initialize(velocityPParam, velocityIParam, turnPParam, turnIParam, commandTimeout);////  利用参数  初始化速度控制系统


}

////#######################################初始化电池监视   得到限制电池电压
void InitializeBatteryMonitor()
{
  float voltageTooLowlimit = GetFloatFromBaseAndExponent(_Messenger.readInt(), _Messenger.readInt());
  _BatteryMonitor.InitializeLowVoltageLimit(voltageTooLowlimit);

  /*
  Serial.print("battery monitor Params: ");
   Serial.print(voltageTooLowlimit);
   Serial.print("\n");
   */
}

//////#############################
float GetFloatFromBaseAndExponent(int base, int exponent)
{
  return base * pow(10, exponent);         /////////////#############计数公式得到10为底，exponent为幂，再乘base的float
}
/////////////////////////##################映射函数

long mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; /////////////#############计数公式
}





