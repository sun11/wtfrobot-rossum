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

public class dispose {
	public static void control(String s)
	{
		if(s.equalsIgnoreCase("forward") || s.equalsIgnoreCase("come forward")|| s.equalsIgnoreCase("move")|| s.equalsIgnoreCase("前进"))
		{
			TalkParam.tmpstring="COME FORWARD";
			IsrActivity.tmpchnstring="ekho -s40 前进";		
			TalkParam.AX=0;
			TalkParam.AY=0;
			TalkParam.AZ=0;
			TalkParam.LX=0.4f;
			TalkParam.LY=0;
			TalkParam.LZ=0;
			PocketSphinxROS.send=true;
		}
		if(s.equalsIgnoreCase("stop")|| s.equalsIgnoreCase("停止"))
		{
			TalkParam.tmpstring="STOP";
			IsrActivity.tmpchnstring="ekho -s40 停止";
			TalkParam.AX=0;
			TalkParam.AY=0;
			TalkParam.AZ=0;
			TalkParam.LX=0;
			TalkParam.LY=0;
			TalkParam.LZ=0;
			PocketSphinxROS.send=false;
		}
		if(s.equalsIgnoreCase("right") || s.equalsIgnoreCase("rotate right")|| s.equalsIgnoreCase("右转"))
		{
			TalkParam.tmpstring="ROTATE RIGHT";
			IsrActivity.tmpchnstring="ekho -s40 右转";	
			TalkParam.AX=0;
			TalkParam.AY=0;
			TalkParam.AZ= -0.6f;
			TalkParam.LX=0;
			TalkParam.LY=0;
			TalkParam.LZ=0;
			PocketSphinxROS.send=true;
		}
		if(s.equalsIgnoreCase("left")|| s.equalsIgnoreCase("rotate left")|| s.equalsIgnoreCase("左转"))
		{
			TalkParam.tmpstring="ROTATE LEFT";
			IsrActivity.tmpchnstring="ekho -s40 左转";
			TalkParam.AX=0;
			TalkParam.AY=0;
			TalkParam.AZ= 0.6f;
			TalkParam.LX=0;
			TalkParam.LY=0;
			TalkParam.LZ=0;
			PocketSphinxROS.send=true;
		}
		if(s.equalsIgnoreCase("back")|| s.equalsIgnoreCase("come back") || s.equalsIgnoreCase("后退"))
		{
			TalkParam.tmpstring="COME BACK";
			IsrActivity.tmpchnstring="ekho -s50 后退";
			TalkParam.AX=0;
			TalkParam.AY=0;
			TalkParam.AZ=0;
			TalkParam.LX= -0.2f;
			TalkParam.LY=0;
			TalkParam.LZ=0;
			PocketSphinxROS.send=true;
		}
		if(s.equalsIgnoreCase("speed up")|| s.equalsIgnoreCase("加速"))
		{
			TalkParam.tmpstring="ok";
			IsrActivity.tmpchnstring="ekho  加毛速";
			PocketSphinxROS.send=true;
		}
		///////////////////////////////////////////////////////////////////////////////////////
		if(s.equalsIgnoreCase("上看") || s.equalsIgnoreCase("向上看")|| s.equalsIgnoreCase("抬头"))
		{
			IsrActivity.tmpchnstring="ekho  抬头";		
			TalkServo.pos[0]=-0.1;
			TalkServo.pos[1]=0.2;
			PocketSphinxROS.send=true;
			PocketSphinxROS.sendservo=true;
		}
		if(s.equalsIgnoreCase("向左看") || s.equalsIgnoreCase("左看"))
		{
			IsrActivity.tmpchnstring="ekho  往左看";		
			TalkServo.pos[0]=0.6;
			TalkServo.pos[1]=0.7;
			PocketSphinxROS.sendservo=true;
		}
		if(s.equalsIgnoreCase("向右看") || s.equalsIgnoreCase("右看"))
		{
			IsrActivity.tmpchnstring="ekho  往右看";		
			TalkServo.pos[0]=-0.9;
			TalkServo.pos[1]=0.7;
			PocketSphinxROS.sendservo=true;
		}
		if(s.equalsIgnoreCase("下看") || s.equalsIgnoreCase("向下看")|| s.equalsIgnoreCase("低头"))
		{
			IsrActivity.tmpchnstring="ekho  低头";		
			TalkServo.pos[0]=-0.1;
			TalkServo.pos[1]=0.7;
			PocketSphinxROS.sendservo=true;
		}
		if(s.equalsIgnoreCase("revive") || s.equalsIgnoreCase("复位"))
		{
			IsrActivity.tmpchnstring="ekho -s20 舵机恢复初始位置";		
			TalkServo.pos[0]= -0.17;
			TalkServo.pos[1]= 0.75;
			TalkParam.AX=0;
			TalkParam.AY=0;
			TalkParam.AZ=0;
			TalkParam.LX=0;
			TalkParam.LY=0;
			TalkParam.LZ=0;
			PocketSphinxROS.sendservo=true;
		}
		////////////////////////////////////////////////////////////////////
		if(s.equalsIgnoreCase("傅世忱") )
		{
			IsrActivity.tmpchnstring="ekho -s10  傅世忱是大傻逼";		
		}
		if(s.equalsIgnoreCase("田乔") )
		{
			IsrActivity.tmpchnstring="ekho  -s10 你说啥？是那个大帅哥麽？";		
		}
		if(s.equalsIgnoreCase("王孙平") )
		{
			IsrActivity.tmpchnstring="ekho  -s10 他又去睡觉了";		
		}
		if(s.equalsIgnoreCase("主人") )
		{
			IsrActivity.tmpchnstring="ekho -s10 三个主人都是大傻逼";		
		}
		if(s.equalsIgnoreCase("你好") )
		{
			IsrActivity.tmpchnstring="ekho  你好";		
		}
		if(s.equalsIgnoreCase("你是谁") )
		{
			IsrActivity.tmpchnstring="ekho  -s15 我是呆子机器人";		
		}
		//////////////////////////////////////////////////////////////////////////
		if(s.contains("去一区取咖啡"))
		{
			IsrActivity.tmpchnstring="ekho  -s15 去一区取咖啡";		
			IsrActivity.tmpobjstring="1";
			PocketSphinxROS.sendobject=true;
		}
		if(s.contains("去一区取字典"))
		{
			IsrActivity.tmpchnstring="ekho  -s15 去一区取字典";	
			IsrActivity.tmpobjstring="2";
			PocketSphinxROS.sendobject=true;
		}
		if(s.contains("去二区取咖啡"))
		{
			IsrActivity.tmpchnstring="ekho  -s15 去二区取咖啡";	
			IsrActivity.tmpobjstring="3";
			PocketSphinxROS.sendobject=true;
		}
		if(s.contains("去二区取字典"))
		{
			IsrActivity.tmpchnstring="ekho  -s15 去二区取字典";		
		}
		if(s.contains("去三区取咖啡"))
		{
			IsrActivity.tmpchnstring="ekho  -s15 去三区取咖啡";		
		}
		if(s.contains("去三区取字典"))
		{
			IsrActivity.tmpchnstring="ekho  -s15 去三区取字典";		
		}
	}
}
