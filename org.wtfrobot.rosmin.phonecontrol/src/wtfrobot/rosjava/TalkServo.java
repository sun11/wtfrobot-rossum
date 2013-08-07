/*
 * Copyright 2013 WTFrobot. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
package wtfrobot.rosjava;

import java.util.ArrayList;
import java.util.Arrays;
import org.ros.concurrent.CancellableLoop;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
import org.ros.node.topic.Publisher;

import sensor_msgs.JointState;

public class TalkServo extends AbstractNodeMain {
	
	public static double[] vel= {0.5,0.5};
	public static double[] pos= {-0.17,0.75};

    String[] s = {"pan","tilz"}; 
    ArrayList<String> list = new ArrayList<String>(Arrays.asList(s));
    
  @Override
  public GraphName getDefaultNodeName() {
    return GraphName.of("rosjava_tutorial_pubsub/talkerserver");
  }

  @Override
  public void onStart(final ConnectedNode connectedNode) {
	  final Publisher<JointState> publisher =
		       connectedNode.newPublisher("joint_states", "sensor_msgs/JointState");
    // This CancellableLoop will be canceled automatically when the node shuts
    // down.
    connectedNode.executeCancellableLoop(new CancellableLoop() {
    	
      @Override
      protected void setup() {
      }

      @Override
      public void loop() throws InterruptedException {
    		JointState joint = (JointState) publisher.newMessage();
/*        if(PocketSphinxROS.sendservo)
        {*/
        	joint.setName(list);
        	joint.setVelocity(vel);
        	joint.setPosition(pos);
        	publisher.publish(joint);
/*        }*/
       Thread.sleep(100);
      }
    });
  }
}