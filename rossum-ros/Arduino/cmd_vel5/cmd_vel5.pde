#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>


// motor A
int dir1PinA = 13;
int dir2PinA = 12;
int speedPinA = 10;

// motor B
int dir1PinB = 11;
int dir2PinB = 8;
int speedPinB = 9;

ros::NodeHandle nh;

void messageCb(const geometry_msgs::Twist& msg)
{

  int speed_value;
  int angle_value;
  int leftwheelspeed;
  int rightwheelspeed;
  
  speed_value = msg.linear.x;
  angle_value = msg.angular.z;
  
  if(speed_value > 10){
    speed_value = 10;
  }
  if(speed_value < -10){
    speed_value = -10;
  }
  if(angle_value > 2){
    angle_value = 2;
  }
  if(angle_value < -2){
    angle_value = -2;
  }
    
  leftwheelspeed = map(abs(speed_value),0,10,0,250);
  rightwheelspeed = map(abs(speed_value),0,10,0,250);

  int as;
  as = map(abs(angle_value),0,2,0,250);

  if(speed_value > 0){  //forward
    if(angle_value > 0){ // left turn
      leftwheelspeed = leftwheelspeed - as*2;
    }
    else{ //right turn
      rightwheelspeed = rightwheelspeed - as*2;
    }
  }

  if(speed_value < 0){  //back
    if(angle_value > 0){ // left turn
      rightwheelspeed = rightwheelspeed - as*2;
      rightwheelspeed = -rightwheelspeed;
      leftwheelspeed = -leftwheelspeed;
      
    }
    else{ //right turn
      leftwheelspeed = leftwheelspeed - as*2;
      leftwheelspeed = -leftwheelspeed;
      rightwheelspeed = -rightwheelspeed;
    }
  }


  if(speed_value == 0){
    leftwheelspeed = 0;
    rightwheelspeed = 0;
  }  
  
  
  if(leftwheelspeed >= 0 && rightwheelspeed >= 0){
    digitalWrite(dir1PinA, HIGH);
    digitalWrite(dir2PinA, LOW);
    digitalWrite(dir1PinB, LOW);
    digitalWrite(dir2PinB, HIGH);
  }
  if(leftwheelspeed < 0 && rightwheelspeed < 0){
    digitalWrite(dir1PinA, LOW);
    digitalWrite(dir2PinA, HIGH);
    digitalWrite(dir1PinB, HIGH);
    digitalWrite(dir2PinB, LOW);
  }
  
  if(leftwheelspeed < 0 && rightwheelspeed >= 0){
    digitalWrite(dir1PinA, HIGH);
    digitalWrite(dir2PinA, LOW);
    digitalWrite(dir1PinB, HIGH);
    digitalWrite(dir2PinB, LOW);
  }
  if(leftwheelspeed >= 0 && rightwheelspeed < 0){
    digitalWrite(dir1PinA, LOW);
    digitalWrite(dir2PinA, HIGH);
    digitalWrite(dir1PinB, LOW);
    digitalWrite(dir2PinB, HIGH);

  }
  
  analogWrite(speedPinA, abs(leftwheelspeed));
  analogWrite(speedPinB, abs(rightwheelspeed)); 
  

//    delay(200);      

}


ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb);

void setup(){
  nh.initNode();
  nh.subscribe(sub);
  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(dir1PinB, OUTPUT);
  pinMode(dir2PinB, OUTPUT);
  pinMode(speedPinB, OUTPUT);
}

void loop(){
  nh.spinOnce();
  delay(10);
}
