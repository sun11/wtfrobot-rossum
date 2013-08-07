#!/usr/bin/env python
'''
Created January, 2011

@author: Dr. Rainer Hessmer

  arduino.py - gateway to Arduino based differential drive base
  Copyright (c) 2011 Dr. Rainer Hessmer.  All right reserved.
  Borrowed heavily from Mike Feguson's ArbotiX base_controller.py code.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
      * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
      * Neither the name of the Vanadium Labs LLC nor the names of its 
        contributors may be used to endorse or promote products derived 
        from this software without specific prior written permission.
  
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL VANADIUM LABS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
'''

import roslib; roslib.load_manifest('playground')
import rospy
import tf
import math
from math import sin, cos, pi
import sys
import time

from sensor_msgs.msg import JointState
from std_msgs.msg import Float64
from std_msgs.msg import String
from playground.srv import *

from SerialDataGateway import SerialDataGateway

class JointController(object):
	'''
	Helper class for communicating with an Arduino board over serial port
	'''

	def _HandleReceivedLine(self,  line):
		self._Counter = self._Counter + 1
		#rospy.logdebug(str(self._Counter) + " " + line)
		#if (self._Counter % 50 == 0):
		self._Publisher.publish(String(str(self._Counter) + " " + line))
		
		if (len(line) > 0):
			lineParts = line.split('\t')
			if (lineParts[0] == 'o'):
				return
			if (lineParts[0] == "InitializeSpeedController"):
				# controller requesting initialization
				return
			if (lineParts[0] == "InitializeBatteryMonitor"):
				# controller requesting initialization
				return


	def __init__(self, port="/dev/ttyACM0", baudrate=115200):
		'''
		Initializes the receiver class. 
		port: The serial port to listen to.
		baudrate: Baud rate for the serial communication
		'''

		self._Counter = 0

		rospy.init_node('jointcontroller')

		port = rospy.get_param("~port", "/dev/ttyUSB0")
		baudRate = int(rospy.get_param("~baudRate", 115200))

		rospy.loginfo("Starting with serial port: " + port + ", baud rate: " + str(baudRate))

		# subscriptions
		rospy.Subscriber("joint_states", JointState, self._HandleJointsCommand)
		# self._Publisher = rospy.Publisher('serial', String)
		self._SerialDataGateway = SerialDataGateway(port, baudRate,  self._HandleReceivedLine)


	def Start(self):
		rospy.logdebug("Starting")
		self._SerialDataGateway.Start()

	def Stop(self):
		rospy.logdebug("Stopping")
		self._SerialDataGateway.Stop()
		
	def _HandleJointsCommand(self, msg):
		message = '#1P%dT1000\\r\\n' % (msg.position[msg.name.index("body-1--r_shoulder_link-11")] * 1000,)
		rospy.logdebug("Sending message: " + message)
		self._SerialDataGateway.Write(message)


if __name__ == '__main__':
	jc = JointController()
	try:
		jc.Start()
		rospy.spin()

	except rospy.ROSInterruptException:
		jc.Stop()

