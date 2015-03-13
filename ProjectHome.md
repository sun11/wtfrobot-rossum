A robot using kinect and ros to do slam,navigation,and object recognition.

This project uses ROS(Robot Operating System) as the core,it has a Kinect sensor as a replacement
of a laser scanner,using the Arduino board to drive the robot,and a netbook attached inside.

1. Voice Control:Using voice to control the robot through an Android
phone,which can recognize English offline and recognize Chinese online.

2. Following movement(turtlebot\_follower):Keep a distance between the robot and the
human,and make it be perpendicular to the human.When the human turn
around or move,the robot can follow.

3. Simultaneous Localization and Mapping(SLAM):The mobile robot collect data
through its sensors and build model for the environment,estimate its position by
the map at the same time.

4. Autonomous navigation:On the basis of building the static map,make the
robot move from one place to an given place.

5. Object Recognition:Ultilize the tpofinder library to recognize objects which
have textured feature,like the book cover and the coffee box.

You can get the source using:

git clone https://code.google.com/p/wtfrobot-rossum/

Video demo: http://v.youku.com/v_show/id_XNTY0MTUwMTMy.html

Related articles(Chinese):

http://blog.csdn.net/wtfrobot/article/details/9173633/

http://blog.csdn.net/wtfrobot/article/details/9881749/)

http://blog.csdn.net/wtfrobot/article/details/9881771/

http://blog.csdn.net/wtfrobot/article/details/9881815/

http://blog.csdn.net/wtfrobot/article/details/9881859/

http://blog.csdn.net/wtfrobot/article/details/9881889/

http://blog.csdn.net/wtfrobot/article/details/9881965/