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

import geometry_msgs.Twist;
import org.ros.concurrent.CancellableLoop;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
import org.ros.node.topic.Publisher;

public class TalkParam extends AbstractNodeMain {

	  public static String tmpstring="WTF";
	  public static float LX,LY,LZ,AX,AY,AZ;
	  
  @Override
  public GraphName getDefaultNodeName() {
    return GraphName.of("rosjava_tutorial_pubsub/talker");
  }

  @Override
  public void onStart(final ConnectedNode connectedNode) {
	  final Publisher<Twist> publisher =
		       connectedNode.newPublisher("cmd_vel", "geometry_msgs/Twist");
    // This CancellableLoop will be canceled automatically when the node shuts
    // down.
    connectedNode.executeCancellableLoop(new CancellableLoop() {
    	
      @Override
      protected void setup() {
      }

      @Override
      public void loop() throws InterruptedException {
    		Twist cmd = publisher.newMessage();
        if(PocketSphinxROS.send)
        {
        cmd.getLinear().setX(LX);
        cmd.getLinear().setY(LY);
        cmd.getLinear().setZ(LZ);
        cmd.getAngular().setX(AX);
        cmd.getAngular().setY(AY);
        cmd.getAngular().setZ(AZ);
        publisher.publish(cmd);
        }
       Thread.sleep(100);
      }
    });
  }
}