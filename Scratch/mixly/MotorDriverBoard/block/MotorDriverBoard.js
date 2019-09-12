'use strict';

goog.provide('Blockly.Blocks.MotorDriverBoard');

goog.require('Blockly.Blocks');


Blockly.Blocks.MotorDriverBoard.HUE = 120;


var MOTORDRIVERBOARD_DCPORTS=[[Blockly.MOTORDRIVERBOARD_DCPORTS_FIRST,"1"],[Blockly.MOTORDRIVERBOARD_DCPORTS_SECOND,"2"],[Blockly.MOTORDRIVERBOARD_DCPORTS_THIRD,"3"],[Blockly.MOTORDRIVERBOARD_DCPORTS_FOURTH,"4"]];
var MOTORDRIVERBOARD_DCDIRECTION=[[Blockly.MOTORDRIVERBOARD_DCDIRECTION_FORWARD,"1"],[Blockly.MOTORDRIVERBOARD_DCDIRECTION_BACK,"2"]];

var MOTORDRIVERBOARD_ENPORTS=[[Blockly.MOTORDRIVERBOARD_ENPORTS_FIRST,"1"],[Blockly.MOTORDRIVERBOARD_ENPORTS_SECOND,"2"],[Blockly.MOTORDRIVERBOARD_ENPORTS_THIRD,"3"],[Blockly.MOTORDRIVERBOARD_ENPORTS_FOURTH,"4"]];
var MOTORDRIVERBOARD_ENDIRECTION=[[Blockly.MOTORDRIVERBOARD_ENDIRECTION_FORWARD,"1"],[Blockly.MOTORDRIVERBOARD_ENDIRECTION_BACK,"2"]];

var MOTORDRIVERBOARD_STPORTS=[[Blockly.MOTORDRIVERBOARD_STPORTS_FIRST,"1"],[Blockly.MOTORDRIVERBOARD_STPORTS_SECOND,"2"]];
var MOTORDRIVERBOARD_STDIRECTION=[[Blockly.MOTORDRIVERBOARD_STDIRECTION_FORWARD,"1"],[Blockly.MOTORDRIVERBOARD_STDIRECTION_BACK,"2"]];
var MOTORDRIVERBOARD_STSTYLE=[[Blockly.MOTORDRIVERBOARD_STYLE_SINGLE,"1"],[Blockly.MOTORDRIVERBOARD_STYLE_DOUBLE,"2"],[Blockly.MOTORDRIVERBOARD_STYLE_INTERLEAVE,"3"],[Blockly.MOTORDRIVERBOARD_STYLE_MICROSTEP,"4"]];

var MOTORDRIVERBOARD_RGBNUMBER=[[Blockly.MOTORDRIVERBOARD_RGBNUMBER_ALL,"0"],[Blockly.MOTORDRIVERBOARD_RGBNUMBER_LEFT,"1"],[Blockly.MOTORDRIVERBOARD_RGBNUMBER_RIGHT,"2"]];
var MOTORDRIVERBOARD_RGBCOLOR=[[Blockly.MOTORDRIVERBOARD_RGBCOLOR_RED,"0xFF0000"],[Blockly.MOTORDRIVERBOARD_RGBCOLOR_GREEN,"0x00FF00"],[Blockly.MOTORDRIVERBOARD_RGBCOLOR_BLUE,"0x0000FF"],[Blockly.MOTORDRIVERBOARD_RGBCOLOR_YELLOW,"0xFFFF00"],[Blockly.MOTORDRIVERBOARD_RGBCOLOR_PURPLE,"0xFF00FF"],[Blockly.MOTORDRIVERBOARD_RGBCOLOR_WHITE,"0xFFFFFF"],[Blockly.MOTORDRIVERBOARD_RGBCOLOR_OFF,"0x000000"]];

var MOTORDRIVERBOARD_SOUNDS=[[Blockly.MOTORDRIVERBOARD_SOUNDS_CONNECTED,"0"],[Blockly.MOTORDRIVERBOARD_SOUNDS_DISCONNECTED,"1"],[Blockly.MOTORDRIVERBOARD_SOUNDS_BUTTONPUSHED,"2"],[Blockly.MOTORDRIVERBOARD_SOUNDS_MODE1,"3"],[Blockly.MOTORDRIVERBOARD_SOUNDS_MODE2,"4"],[Blockly.MOTORDRIVERBOARD_SOUNDS_MODE3,"5"],[Blockly.MOTORDRIVERBOARD_SOUNDS_SURPRISE,"6"],[Blockly.MOTORDRIVERBOARD_SOUNDS_OHOH,"7"],[Blockly.MOTORDRIVERBOARD_SOUNDS_OHOH2,"8"],[Blockly.MOTORDRIVERBOARD_SOUNDS_CUDDLY,"9"],[Blockly.MOTORDRIVERBOARD_SOUNDS_SLEEPING,"10"],[Blockly.MOTORDRIVERBOARD_SOUNDS_HAPPY,"11"],[Blockly.MOTORDRIVERBOARD_SOUNDS_SUPERHAPPY,"12"],[Blockly.MOTORDRIVERBOARD_SOUNDS_SHORTHAPPY,"13"],[Blockly.MOTORDRIVERBOARD_SOUNDS_SAD,"14"],[Blockly.MOTORDRIVERBOARD_SOUNDS_CONFUSED,"15"],[Blockly.MOTORDRIVERBOARD_SOUNDS_FART1,"16"],[Blockly.MOTORDRIVERBOARD_SOUNDS_FART2,"17"],[Blockly.MOTORDRIVERBOARD_SOUNDS_FART3,"18"]];


var MOTORDRIVERBOARD_IRKEY=[["1","0"],["2","1"],["3","2"],["4","3"],["5","4"],["6","5"],["7","6"],["8","7"],["9","8"],["0","9"],["*","10"],["#","11"],[Blockly.MOTORDRIVERBOARD_IRKEY_UP,"12"],[Blockly.MOTORDRIVERBOARD_IRKEY_DOWN,"13"],["OK","14"],[Blockly.MOTORDRIVERBOARD_IRKEY_LEFT,"15"],[Blockly.MOTORDRIVERBOARD_IRKEY_RIGHT,"16"]];

var MOTORDRIVERBOARD_PS2KEYS=[[Blockly.MOTORDRIVERBOARD_PS2KEYS_UP,"16"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_DOWN,"64"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_LEFT,"128"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_RIGHT,"32"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_TRIANGLE,"4096"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_CIRCLE,"8192"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_CROSS,"16384"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_SQUARE,"32768"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_L1,"1024"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_L2,"256"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_L3,"2"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_R1,"2048"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_R2,"512"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_R3,"4"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_SELECT,"1"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_START,"8"]];

var MOTORDRIVERBOARD_VIBRATE=[[Blockly.MOTORDRIVERBOARD_VIBRATE_LX,"7"],[Blockly.MOTORDRIVERBOARD_VIBRATE_LY,"8"],[Blockly.MOTORDRIVERBOARD_VIBRATE_RX,"5"],[Blockly.MOTORDRIVERBOARD_VIBRATE_RY,"6"]];

var MOTORDRIVERBOARD_SERVOPORTS=[[Blockly.MOTORDRIVERBOARD_SERVOPORTS_FIRST,"1"],[Blockly.MOTORDRIVERBOARD_SERVOPORTS_SECOND,"2"],[Blockly.MOTORDRIVERBOARD_SERVOPORTS_THIRD,"3"],[Blockly.MOTORDRIVERBOARD_SERVOPORTS_FOURTH,"4"],[Blockly.MOTORDRIVERBOARD_SERVOPORTS_FIVETH,"5"],[Blockly.MOTORDRIVERBOARD_SERVOPORTS_SIXTH,"6"]];
//第0个图形块的样式,MotorDriverBoard初始化
Blockly.Blocks.md_setup = {
 init:function(){
	this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_SETUP)
	this.setPreviousStatement(false,null);
    this.setNextStatement(true,null);   
	this.setTooltip('');
 }
};
Blockly.Blocks.md_initdcmotor = {
	init:function(){
	    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
		this.appendDummyInput("")
			.appendField(Blockly.MOTORDRIVERBOARD_INITDCMOTOR)
		   // .appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_DCPORTS),"DCPorts")
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
		}
};
//第一个图形块的样式,直流电机下拉（下拉没有value），正反转（下拉），速度（输入,有value）
Blockly.Blocks.md_dcmotor = {
  init: function() {
	    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
        this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_DCMOTOR)
        .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_DCPORTS), "DCPorts")
		 .appendField(Blockly.MOTORDRIVERBOARD_DCDIRECTIONS)
		 .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_DCDIRECTION), "DCDirections")
         .appendField(Blockly.MOTORDRIVERBOARD_SPEED);
	   this.appendValueInput("Speed", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	    this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
        this.setTooltip('');
  }
};
//第二个图形块的样式,停止直流电机下拉（下拉没有value）
Blockly.Blocks.md_stopDCmotor = {
	init:function(){
	    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
		this.appendDummyInput("")
			.appendField(Blockly.MOTORDRIVERBOARD_STOPDCMOTOR)
		   // .appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_DCPORTS),"DCPorts")
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
		}
};
Blockly.Blocks.md_initENmotor = {
	init:function(){
	    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
		this.appendDummyInput("")
			.appendField(Blockly.MOTORDRIVERBOARD_INITENMOTOR)
		   // .appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_ENPORTS),"ENPorts")
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
		}
};
//第三个图形块的样式,编码电机下拉（下拉没有value），正反转（下拉），速度（输入,有value）
Blockly.Blocks.md_enmotor = {
  init: function() {
    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_ENMOTOR)
        .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_ENPORTS), "ENPorts")
		 .appendField(Blockly.MOTORDRIVERBOARD_ENDIRECTIONS)
		 .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_ENDIRECTION), "ENDirections")
         .appendField(Blockly.MOTORDRIVERBOARD_SPEED);
	   this.appendValueInput("Speed", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	    this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
        this.setTooltip('');
  }
};
//第四个图形块的样式,停止编码电机 下拉（下拉没有value）
Blockly.Blocks.md_stopENmotor = {
	init:function(){
	    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
		this.appendDummyInput("")
			.appendField(Blockly.MOTORDRIVERBOARD_STOPENMOTOR)
		   // .appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_ENPORTS),"ENPorts")
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
		}
};
Blockly.Blocks.md_initstmotor = {
	init:function(){
	    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
		this.appendDummyInput("")
			.appendField(Blockly.MOTORDRIVERBOARD_INITSTMOTOR)
		   // .appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_STPORTS),"STPorts")
			.appendField(Blockly.MOTORDRIVERBOARD_STEPS);
	   this.appendValueInput("Steps", Number)
        .setCheck(Number)
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
		}
};
//第五个图形块的样式,步进电机下拉，步数value，方向下拉，方式下拉
Blockly.Blocks.md_stmotor = {
  init: function() {
    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_STMOTOR)
        .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_STPORTS), "STPorts")
		 .appendField(Blockly.MOTORDRIVERBOARD_STDIRECTIONS)
		 .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_STDIRECTION), "STDirections")
		 .appendField(Blockly.MOTORDRIVERBOARD_STSTYLES)
		 .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_STSTYLE), "STStyles")
         .appendField(Blockly.MOTORDRIVERBOARD_STEPS);
	   this.appendValueInput("Steps", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
		this.appendDummyInput("")
		.appendField(Blockly.MOTORDRIVERBOARD_SPEED)
		this.appendValueInput("Speed", Number)
		  .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	    this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
        this.setTooltip('');
  }
};
Blockly.Blocks.md_initRGB = {
  init: function(){
	 this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
	 this.appendDummyInput("")
         .appendField(Blockly.MOTORDRIVERBOARD_INITRGB)	 
	 	 //.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/hb_ultrasonic.png", 45, 38))	 
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
 	
	}	
};
//第六个图形块的样式,rgb
Blockly.Blocks.md_RGB = {
  init: function(){
	 this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
	 this.appendDummyInput("")
         .appendField(Blockly.MOTORDRIVERBOARD_SETRGB)	 
	 	 //.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/hb_ultrasonic.png", 45, 38))	 
         .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_RGBNUMBER), "RGB")	 
	     .appendField(Blockly.MOTORDRIVERBOARD_RGBCOLOUR)
		 .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_RGBCOLOR), "RGBCOLOR");
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
 	
	}	
};
//通过模拟值参数设置rgb
Blockly.Blocks.md_setColor = {
  init: function(){
	 this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
	 this.appendDummyInput("")
         .appendField(Blockly.MOTORDRIVERBOARD_SETRGB)	 
	 	 //.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/hb_ultrasonic.png", 45, 38))	 
         .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_RGBNUMBER), "RGB")	 
	     .appendField(Blockly.MOTORDRIVERBOARD_RGBCOLOUR)		 
		this.appendValueInput("red", Number)
		.appendField(Blockly.MOTORDRIVERBOARD_RED)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);		
		this.appendValueInput("green", Number)
		.appendField(Blockly.MOTORDRIVERBOARD_GREEN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
		this.appendValueInput("blue", Number)
		.appendField(Blockly.MOTORDRIVERBOARD_BLUE)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
 	
	}	
};
//第七个图形块的样式,播放声音 下拉
Blockly.Blocks.md_initSounds = {
 init:function(){
	 this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
	 this.appendDummyInput("")        
		// .appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
		 .appendField(Blockly.MOTORDRIVERBOARD_INITSOUNDS)
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
 }
};
Blockly.Blocks.md_playSounds = {
 init:function(){
	 this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
	 this.appendDummyInput("")        
		// .appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
		 .appendField(Blockly.MOTORDRIVERBOARD_PLAYSOUNDS)
		 .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_SOUNDS), "Sounds")	 
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
 }
};
//第八个图形块的样式 超声波初始化
Blockly.Blocks.md_initultrasonic = {
  init: function() {
    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_INITULTRASONIC)
		//.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_irreceive.png", 38, 32))
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//第九个图形块的样式 读取超声波距离下拉
Blockly.Blocks.md_readUltrasonicDistance = {
  init: function() {
    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_READULTRASONICDISTANCE)
		//.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_ultrasonic.png", 38, 32))
    this.setOutput(true, Number);
    this.setTooltip('');
  }
};
//第十个图形块的样式 红外接收初始化
Blockly.Blocks.md_initirremote = {
  init: function() {
    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_INITIRREMOTE)
		//.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_ultrasonic.png", 38, 32))
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//第十一个图形块的样式(setOutput) 红外遥控按键（下拉，返回boolean）
Blockly.Blocks.md_irKeyPress = {
  init: function() {
    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_IRKEYPRESS)
		.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_IRKEY), "Irkeys")	
		//.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_ultrasonic.png", 38, 32))
     this.setOutput(true, Number);
    this.setTooltip('');
  }
};
//第十二个图形块的样式 nrf24l01初始化    field的name不确定使NUM待检测
Blockly.Blocks.md_initnrf24l01 = {
  init: function() {
    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01)
		//.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_ultrasonic.png", 38, 32))
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//第十三个图形块的样式 NRF24L01发送数据地址value 数据value
Blockly.Blocks.md_nrf24l01send = {
  init: function() {
    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01SENDDATA);		
		this.appendValueInput("address", Number)
		.appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01ADDRESS)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
		
		this.appendValueInput("data", Number)
		.appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01DATA)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//第十四个图形块的样式 NRF24L01接收数据地址value
Blockly.Blocks.md_nrf24l01receive = {
  init: function() {
    this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01RECEIVEDATA);		
		this.appendValueInput("address", Number)
		.appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01ADDRESS)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//第十五个图形块的样式 NRF24L01数据不为空
Blockly.Blocks.md_NRF24L01isnotnull = {
 init:function(){
	this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01ISNOTNULL)
	   this.setOutput(true, Number);
    this.setTooltip('');
 }
};
//第十六个图形块的样式 获取NRF24L01数据
Blockly.Blocks.md_getNRF24L01 = {
 init:function(){
	this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_GETINITNRF24L01)
	   this.setOutput(true, Number);
    this.setTooltip('');
 }
};
//第十七个图形块的样式 PS2手柄初始化
Blockly.Blocks.md_PS2init = {
 init:function(){
	this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_PS2INIT)
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
 }
};
//第十八个图形块的样式 PS2键被按下（下拉）
Blockly.Blocks.md_WhichPS2KeyPressed = {
  init:function(){
	this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);  
	this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_WHICHPS2KEYPRESSED)
	    //.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_ps2.png", 38, 32))
	   // .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_PS2KEY), "PS2Key")
	this.setOutput(true, Boolean);
	this.setTooltip('');
  }
};

//第二十个图形块的样式 ps2手柄按下（下拉）
Blockly.Blocks.md_ps2keypress = {
  init:function(){
	this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);  
	this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_PS2KEYPRESS)
	    //.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_irtracking.png", 38, 32))
	    .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_PS2KEYS), "PS2keys")
	this.setOutput(true, Boolean);
	this.setTooltip('');
  }
};
//第二十一个图形块的样式 ps2手柄松开
Blockly.Blocks.md_ps2keyunpress = {
  init:function(){
	this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);  
	this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_PS2KEYUNPRESS)
	    //.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_irtracking.png", 38, 32))
	    .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_PS2KEYS), "PS2keys")
	this.setOutput(true, Boolean);
	this.setTooltip('');
  }
};
//第二十二个图形块的样式 获取摇杆值（下拉）
Blockly.Blocks.md_ps2getvibrate = {
  init:function(){
	this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);  
	this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_PS2GETVIBRATE)
	    //.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_irtracking.png", 38, 32))
	    .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_VIBRATE), "Vibrate")
	this.setOutput(true, Number);
	this.setTooltip('');
  }
};
//第二十三个图形块的样式 读取ps2状态
Blockly.Blocks.md_ps2status = {
 init:function(){
	this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_PS2STATUS)
	    //.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_irtracking.png", 38, 32))
	this.setPreviousStatement(true,null);
    this.setNextStatement(true,null);   
	this.setTooltip('');
 }
};
//第二十三个图形块的样式 舵机 接口下拉  角度value
Blockly.Blocks.md_initservo = {
 init:function(){
	this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_INITSERVO)
		.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_SERVOPORTS), "Servoports")
	    //.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_irtracking.png", 38, 32))
	this.setPreviousStatement(true,null);
    this.setNextStatement(true,null);   
	this.setTooltip('');
 }
};
Blockly.Blocks.md_servo = {
 init:function(){
	this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_SERVOPORT)
		.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_SERVOPORTS), "Servoports")
		  .appendField(Blockly.MOTORDRIVERBOARD_ANGLE);
	   this.appendValueInput("angle", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	    //.appendField(new Blockly.FieldImage("../../media/MotorDriverBoard/md_irtracking.png", 38, 32))
	this.setPreviousStatement(true,null);
    this.setNextStatement(true,null);   
	this.setTooltip('');
 }
};
//读取舵机角度
Blockly.Blocks.md_readservo= {
  init:function(){
	this.setColour(Blockly.Blocks.MotorDriverBoard.HUE);  
	this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_SERVOPORT)
		.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_SERVOPORTS), "Servoports")
		.appendField(Blockly.MOTORDRIVERBOARD_READDEGEREES)
	this.setOutput(true, Number);
	this.setTooltip('');
  }
};