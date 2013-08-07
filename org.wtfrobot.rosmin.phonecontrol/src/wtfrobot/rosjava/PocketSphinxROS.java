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

import java.util.Date;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.SeekBar.OnSeekBarChangeListener;

import org.ros.address.InetAddressFactory;
import org.ros.android.MessageCallable;
import org.ros.android.RosActivity;
import org.ros.android.view.RosTextView;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMainExecutor;

import wtfrobot.rosjava.IsrActivity;
import wtfrobot.rosjava.RecognitionListener;
import wtfrobot.rosjava.RecognizerTask;
import wtfrobot.rosjava.TalkChnString;
import wtfrobot.rosjava.TalkEnString;
import wtfrobot.rosjava.TalkParam;

import edu.cmu.pocketsphinx.demo.R;

public class PocketSphinxROS extends RosActivity implements OnTouchListener, RecognitionListener {

  private RosTextView<std_msgs.String> rosTextView;
  private TalkParam talker;
  private TalkEnString talkerenstring;
  private TalkChnString talkerchnstring;
  private TalkServo talkerserver;
  private TalkObject talkerobject;
  public Button forward,back,right,left,stop,btn_isr_demo,revive;
  public static boolean send=false,sendenstring=false,sendchnstring=false,sendservo=true,sendobject=false;
  public Handler handler = new Handler(){};
  //servo
  public TextView Value01,Value02;
  public static SeekBar servo1;
  public static SeekBar servo2;
  
  public PocketSphinxROS() {
    // The RosActivity constructor configures the notification title and ticker
    // messages.
    super("Pubsub Tutorial", "Pubsub Tutorial");
  }
//*pocketsphinx***************************************************************************************

  static {
    System.loadLibrary("pocketsphinx_jni");
  }
  /**
   * Recognizer task, which runs in a worker thread.
   */
  RecognizerTask rec;
  /**
   * Thread in which the recognizer task runs.
   */
  Thread rec_thread;
  /**
   * Time at which current recognition started.
   */
  Date start_date;
  /**
   * Number of seconds of speech.
   */
  float speech_dur;
  /**
   * Are we listening?
   */
  boolean listening;
  /**
   * Progress dialog for final recognition.
   */
  ProgressDialog rec_dialog;
  /**
   * Performance counter view.
   */
  static TextView performance_text;
  /**
   * Editable text view.
   */

  public boolean onTouch(View v, MotionEvent event) {
    switch (event.getAction()) {
    case MotionEvent.ACTION_DOWN:
      start_date = new Date();
      this.listening = true;
      this.rec.start();
      break;
    case MotionEvent.ACTION_UP:
      if (this.listening) {
        Log.d(getClass().getName(), "Showing Dialog");
        this.rec_dialog = ProgressDialog.show(this, "", "Recognizing speech...", true);
        this.rec_dialog.setCancelable(false);
        this.listening = false;
      }
      this.rec.stop();
      break;
    default:
      ;
    }
    /* Let the button handle its own state */
    return false;
  }
//****************************************************************************************
  @SuppressWarnings("unchecked")
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);
    rosTextView = (RosTextView<std_msgs.String>) findViewById(R.id.text);
    rosTextView.setTopicName("recognizer/output");
    rosTextView.setMessageType(std_msgs.String._TYPE);
    rosTextView.setMessageToStringCallable(new MessageCallable<String, std_msgs.String>() {
      @Override
      public String call(std_msgs.String message) {
        return message.getData();
      }
    });
    this.rec = new RecognizerTask();
    this.rec_thread = new Thread(this.rec);
    this.listening = false;
    Button voice = (Button) findViewById(R.id.Voice);
    voice.setOnTouchListener(this);
    performance_text = (TextView) findViewById(R.id.PerformanceText); 
    this.rec.setRecognitionListener(this);
    this.rec_thread.start();
    
    forward = (Button)findViewById(R.id.forward);
    back = (Button)findViewById(R.id.back);
    right = (Button)findViewById(R.id.right);
    left = (Button)findViewById(R.id.left);
    stop = (Button)findViewById(R.id.stop);
    revive = (Button)findViewById(R.id.revive);
    btn_isr_demo=(Button)findViewById(R.id.btn_isr_demo);
    
    Value01 = (TextView)findViewById(R.id.value1);
    Value02 = (TextView)findViewById(R.id.value2);
    final SeekBar servo1 = (SeekBar)findViewById(R.id.servo1); //左右
    final SeekBar servo2 = (SeekBar)findViewById(R.id.servo2); //上下
    servo1.setMax(180);
    servo1.setProgress(73);
    servo2.setMax(150);
    servo2.setProgress(145);
    
    forward.setOnTouchListener(new OnTouchListener(){
        @Override
        public boolean onTouch(View v, MotionEvent event) {
          if (event.getAction() == MotionEvent.ACTION_DOWN)
          {
//          	Talker.tmpstring="FORWARD" ;
        	  dispose.control("forward");
			send=true;
          }
          else if(event.getAction() == MotionEvent.ACTION_UP)
          {
        	  send=false;
        	  sendenstring=true;
        	  sendchnstring=true;
          }
         return false;
         }
          });
    back.setOnTouchListener(new OnTouchListener(){
        @Override
        public boolean onTouch(View v, MotionEvent event) {
          if (event.getAction() == MotionEvent.ACTION_DOWN)
          {
        	  dispose.control("back");
			 send=true;
          }
          else if(event.getAction() == MotionEvent.ACTION_UP)
          {
        	  send=false;
        	  sendenstring=true;
        	  sendchnstring=true;
          }
         return false;
         }
          });
    left.setOnTouchListener(new OnTouchListener(){
        @Override
        public boolean onTouch(View v, MotionEvent event) {
          if (event.getAction() == MotionEvent.ACTION_DOWN)
          {
			dispose.control("left");
			send=true;
          }
          else if(event.getAction() == MotionEvent.ACTION_UP)
          {
        	  send=false;
        	  sendenstring=true;
        	  sendchnstring=true;
          }
         return false;
         }
          });
    right.setOnTouchListener(new OnTouchListener(){
        @Override
        public boolean onTouch(View v, MotionEvent event) {
          if (event.getAction() == MotionEvent.ACTION_DOWN)
          {
        	  dispose.control("right");
			send=true;
          }
          else if(event.getAction() == MotionEvent.ACTION_UP)
          {
        	  send=false;
        	  sendenstring=true;
        	  sendchnstring=true;
          }
         return false;
         }
          });
       stop.setOnTouchListener(new OnTouchListener(){
        @Override
        public boolean onTouch(View v, MotionEvent event) {
          if (event.getAction() == MotionEvent.ACTION_DOWN)
          {
        	  dispose.control("stop");
			send = false;				
          }
          else if(event.getAction() == MotionEvent.ACTION_UP)
          {
        	  sendenstring=true;
        	  sendchnstring=true;
          }
         return false;
         }
          });
       btn_isr_demo.setOnTouchListener(new OnTouchListener(){
           @Override
           public boolean onTouch(View v, MotionEvent event) {
             if (event.getAction() == MotionEvent.ACTION_DOWN)
             {
             }
             else if(event.getAction() == MotionEvent.ACTION_UP)
             {
     			Intent intent = new Intent();
     			intent.setClass(PocketSphinxROS.this,IsrActivity.class);
            	 startActivity(intent);
             }
            return false;
            }
             });
       revive.setOnTouchListener(new OnTouchListener(){
           @Override
           public boolean onTouch(View v, MotionEvent event) {
             if (event.getAction() == MotionEvent.ACTION_DOWN)
             {
            	 dispose.control("revive");
             }
             else if(event.getAction() == MotionEvent.ACTION_UP)
             {
           	  send=false;
         	 servo1.setProgress(73);
         	 servo2.setProgress(145);
             }
            return false;
            }
             });
       
       servo1.setOnSeekBarChangeListener(new OnSeekBarChangeListener(){
    	      @Override
    	      public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser)
    	      {
    	    	  if(progress > 150){
    	    	        Value01.setText("当前角度:" + 0.6 );
    	    	        TalkServo.pos[0]=0.6;
    	    	  }
    	    	  else{
    	    		  Value01.setText("当前角度:" + ((float)(progress-90)/100 ));
    	    		  TalkServo.pos[0]=(float)(progress-90)/100;
    			}
    			sendservo=true;
    	      }
    	      @Override
    	      public void onStartTrackingTouch(SeekBar seekBar)
    	      {
    	      }
    	      @Override
    	      public void onStopTrackingTouch(SeekBar seekBar)
    	      { 
    	      }   	      
    	    });
    	    
    	    servo2.setOnSeekBarChangeListener(new OnSeekBarChangeListener(){
    	      @Override
    	      public void onProgressChanged(SeekBar seekBar, int progress,boolean fromUser)
    	      {
    	        Value02.setText("当前角度:" +((float)(progress-75)/100));      	       
    	        TalkServo.pos[1]=(float)(progress-75)/100;
    			sendservo=true;
    	      }
    	      @Override
    	      public void onStartTrackingTouch(SeekBar seekBar)
    	      {
    	      }
    	      @Override
    	      public void onStopTrackingTouch(SeekBar seekBar)
    	      {
    	      }
    	      });
  }
    //Voice Control 
    /** Called when partial results are generated. */
    public void onPartialResults(Bundle b) {
      final String hyp = b.getString("hyp");
      handler.post(new Runnable() {
          public void run() {
            performance_text.setText(hyp);
//          Talker.tmpstring = hyp;
          }
        });
    }

    /** Called with full results are generated. */
    public void onResults(Bundle b) {
		final String hyp = b.getString("hyp");
		final PocketSphinxROS that = this;
		  handler.post(new Runnable() {
			public void run() {
//				Date end_date = new Date();
				performance_text.setText(hyp);
				dispose.control(hyp);
				sendenstring=true;
				send=true;
				Log.d(getClass().getName(), "Hiding Dialog");
				that.rec_dialog.dismiss();
			}
		});
	}

    public void onError(int err) {   
    }
    
	@Override
	protected void init(NodeMainExecutor nodeMainExecutor) {
		// TODO Auto-generated method stub
	    talker = new TalkParam();
	    talkerenstring = new TalkEnString();
	    talkerchnstring = new TalkChnString();
	    talkerserver = new TalkServo();
	    talkerobject = new TalkObject();
	     NodeConfiguration nodeConfiguration = NodeConfiguration.newPublic(InetAddressFactory.newNonLoopback().getHostAddress(), getMasterUri());
	     // 这里用户已经被提示输入master的URI来开始或启动本地master
	     nodeConfiguration.setMasterUri(getMasterUri());
	     nodeMainExecutor.execute(talker, nodeConfiguration);
	     nodeMainExecutor.execute(talkerenstring, nodeConfiguration);
	     nodeMainExecutor.execute(talkerchnstring, nodeConfiguration);
	     nodeMainExecutor.execute(talkerserver, nodeConfiguration);
	     nodeMainExecutor.execute(talkerobject, nodeConfiguration);
	     //  RosTextView作为显示输入信息是必须存在的
	     nodeMainExecutor.execute(rosTextView, nodeConfiguration);
	   }
	
	/*---------------------------------------------------------------------------------------------------------------------------------*/
	
}
