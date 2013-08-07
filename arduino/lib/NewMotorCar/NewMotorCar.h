#ifndef NewMotorCar_h

#define NewMotorCar_h

#include "Arduino.h"
class NewMotorCar

{

  private:

          int _speedLeftPin;

    //      int _speedRightPin;

          int _dir1LeftPin;

          int _dir2LeftPin;
    //      int _dirRightPin;


  public:

  NewMotorCar(int _slpin,int _d1lpin,int _d2lpin);  //int _srpin,int _drpin);

  void work(int _speed);

};
#endif