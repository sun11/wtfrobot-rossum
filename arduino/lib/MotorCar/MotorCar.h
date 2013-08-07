#ifndef MotorCar_h

#define MotorCar_h

#include "WProgram.h"
class MotorCar

{

  private:

          int _speedLeftPin;

          int _speedRightPin;

          int _dirLeftPin;

          int _dirRightPin;


  public:

  MotorCar(int _slpin,int _dlpin,int _srpin,int _drpin);

  void forward(int _speed);

  void back(int _speed);

  void turnLeft(int _speed);
   void turnLeft2(int _speed);
  void turnRight(int _speed);
  void turnRight2(int _speed);

  void turnLeftOrigin(int _speed);

  void turnRightOrigin(int _speed);
 
  void stop();

};
#endif