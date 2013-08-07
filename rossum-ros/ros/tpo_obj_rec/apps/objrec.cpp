//Includes all the headers necessary to use the most common public pieces of the ROS system.
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

//Use image_transport for publishing and subscribing to images in ROS
#include <image_transport/image_transport.h>
//Use cv_bridge to convert between ROS and OpenCV Image formats
#include <cv_bridge/cv_bridge.h>
//Include some useful constants for image encoding. Refer to: http://www.ros.org/doc/api/sensor_msgs/html/namespacesensor__msgs_1_1image__encodings.html for more info.
#include <sensor_msgs/image_encodings.h>

#include <opencv2/imgproc/imgproc.hpp>
//Include headers for OpenCV GUI handling
#include <opencv2/highgui/highgui.hpp>

#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "tpofinder/configure.h"
#include "tpofinder/detect.h"
#include "tpofinder/visualize.h"

#include <sensor_msgs/image_encodings.h>

using namespace cv;
using namespace tpofinder;
using namespace std;
VideoCapture *capture = NULL;
bool verbose = true;

Mat image;
Detector detector;

cv_bridge::CvImage out_msg;
sensor_msgs::JointState joint_msg;

unsigned int iCount = 0;
unsigned int iServoCount = 0;
unsigned int iUndetectCount = 0;
bool foundFlag = false;
Point2f centerPoint;

void openCamera() {
    capture = new VideoCapture(1);
    if (!capture->isOpened()) {
        cerr << "Could not open default camera." << endl;
        exit(-1);
    }
}

void loadModel(Modelbase& modelbase, const string& path) {
    if (verbose) {
        cout << boost::format("Loading object %-20s ... ") % path;
    }
    modelbase.add(path);
    if (verbose) {
        cout << "[DONE]" << endl;
    }
}

void processImage(Detector& detector) {
    if (!image.empty()) {
        cout << "Detecting objects on image          ... ";
        Scene scene = detector.describe(image);
        vector<Detection> detections = detector.detect(scene);
        cout << "[DONE]" << endl;

        // if (detections.size() == 0)
        //     iUndetectCount++;
        // else foundFlag = true;
        // if (iUndetectCount >= 3)
        //     foundFlag = false;
        if (detections.size() >= 1)
            foundFlag = true;
        else foundFlag = false;

        centerPoint = objPosition();

        cout << centerPoint.x << "," << centerPoint.y << endl; 

        BOOST_FOREACH(Detection d, detections) {
        cout << "Drawing                             ..."; 
            drawDetection(image, d);
        cout << "[Done]" << endl;
        }
    }
}

void nextImage() 
{
    if (verbose) {
        cout << "Reading from webcam                 ... ";
    }
    *capture >> image;
    if (verbose) {
        cout << "[DONE]" << endl;
    }
}


/**
* This tutorial demonstrates simple image conversion between ROS image message and OpenCV formats and image processing
*/
int main(int argc, char **argv)
{

    // TODO: adapt to OpenCV 2.4.
    // TODO: remove duplication
    // TODO: support SIFT
    Ptr<FeatureDetector> fd = new OrbFeatureDetector(1000, 1.2, 8);
    Ptr<FeatureDetector> trainFd = new OrbFeatureDetector(250, 1.2, 8);
    Ptr<DescriptorExtractor> de = new OrbDescriptorExtractor(1000, 1.2, 8);
    Ptr<flann::IndexParams> indexParams = new flann::LshIndexParams(15, 12, 2);
    Ptr<DescriptorMatcher> dm = new FlannBasedMatcher(indexParams);

    Feature trainFeature(trainFd, de, dm);

    Modelbase modelbase(trainFeature);

    loadModel(modelbase, PROJECT_BINARY_DIR + "/data/coffee");
    loadModel(modelbase, PROJECT_BINARY_DIR + "/data/irbook");
    loadModel(modelbase, PROJECT_BINARY_DIR + "/data/game");
    loadModel(modelbase, PROJECT_BINARY_DIR + "/data/laserbook");


    Feature feature(fd, de, dm);

    Ptr<DetectionFilter> filter = new AndFilter(
            Ptr<DetectionFilter> (new EigenvalueFilter(-1, 4.0)),
            Ptr<DetectionFilter> (new InliersRatioFilter(0.30)));

    Detector detector(modelbase, feature, filter);

    joint_msg.name.resize(2);
    joint_msg.position.resize(2);
    joint_msg.velocity.resize(2);

    /**
    * The ros::init() function needs to see argc and argv so that it can perform
    * any ROS arguments and name remapping that were provided at the command line. For programmatic
    * remappings you can use a different version of init() which takes remappings
    * directly, but for most command-line programs, passing argc and argv is the easiest
    * way to do it.  The third argument to init() is the name of the node. Node names must be unique in a running system.
    * The name used here must be a base name, ie. it cannot have a / in it.
    * You must call one of the versions of ros::init() before using any other
    * part of the ROS system.
    */
    ros::init(argc, argv, "objrec");
    /**
    * NodeHandle is the main access point to communications with the ROS system.
    * The first NodeHandle constructed will fully initialize this node, and the last
    * NodeHandle destructed will close down the node.
    */ 
    ros::NodeHandle nh;

    ros::Publisher servo_pub = nh.advertise<sensor_msgs::JointState>("joint_states",1000);

    ros::Rate loop_rate(10);

    openCamera();

    float ServoArea = 0;

    while (ros::ok()) {
        nextImage();
        if (iCount >= 15){
            processImage(detector);
            iCount = 0;
        }

        if(!foundFlag){
            if (iServoCount == 40){
                joint_msg.header.stamp = ros::Time::now();
                joint_msg.name[0] = "pan";
                joint_msg.name[1] = "tilz";
                joint_msg.velocity[0] = 0.7;
                joint_msg.velocity[1] = 0.7;
                joint_msg.position[0] = 0.055;
                joint_msg.position[1] = 0.7;
                ServoArea = 0.055;
                servo_pub.publish(joint_msg);
            } else if (iServoCount == 80){
                joint_msg.header.stamp = ros::Time::now();
                joint_msg.name[0] = "pan";
                joint_msg.name[1] = "tilz";
                joint_msg.velocity[0] = 0.7;
                joint_msg.velocity[1] = 0.7;
                joint_msg.position[0] = -0.320;
                joint_msg.position[1] = 0.7;
                ServoArea = -0.320;
                servo_pub.publish(joint_msg);
            } else if (iServoCount == 120){
                joint_msg.header.stamp = ros::Time::now();
                joint_msg.name[0] = "pan";
                joint_msg.name[1] = "tilz";
                joint_msg.velocity[0] = 0.7;
                joint_msg.velocity[1] = 0.7;
                joint_msg.position[0] = -0.695;
                joint_msg.position[1] = 0.7;
                ServoArea = -0.695;
                servo_pub.publish(joint_msg);
                iServoCount = 0;
            } 
        } 

        if(foundFlag) {
            joint_msg.header.stamp = ros::Time::now();
            joint_msg.name[0] = "pan";
            joint_msg.name[1] = "tilz";
            joint_msg.velocity[0] = 0.5;
            joint_msg.velocity[1] = 0.5;
            joint_msg.position[1] = 0.7;

            if (centerPoint.x < 213){
                joint_msg.position[0] = ServoArea+(-0.375)*0.25;
            } else if (centerPoint.x >= 213 && centerPoint.x <= 426){
                joint_msg.position[0] = ServoArea+(-0.375)*0.5;
            } else if (centerPoint.x > 426)
                joint_msg.position[0] = ServoArea+(-0.375)*0.75;

            if ( iServoCount >= 0 ){
                servo_pub.publish(joint_msg); 
                iServoCount = 0;
            }
        }

    //Display the image using OpenCV
     cv::imshow("image processed", image);
    //Add some delay in miliseconds. The function only works if there is at least one HighGUI window created and the window is active. If there are several HighGUI windows, any of them can be active.
     cv::waitKey(3);
     ros::spinOnce();
     iCount++;

     iServoCount++;
    }


    //OpenCV HighGUI call to destroy a display window on shut-down.
    cv::destroyWindow("image processed");

    // pub = it.advertise("camera/image_processed", 1);
    /**
    * In this application all user callbacks will be called from within the ros::spin() call. 
    * ros::spin() will not return until the node has been shutdown, either through a call 
    * to ros::shutdown() or a Ctrl-C.
    */
    
    //ROS_INFO is the replacement for printf/cout.
    ROS_INFO("objrec.cpp::No error.");

}
