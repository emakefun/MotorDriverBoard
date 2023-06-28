'use strict';

goog.provide('Blockly.Blocks.MotorDriverBoard');

goog.require('Blockly.Blocks');


Blockly.Msg['MOTORDRIVERBOARD_HUE'] = 120;


var MOTORDRIVERBOARD_DCPORTS=[[Blockly.MOTORDRIVERBOARD_DCPORTS_FIRST,"1"],[Blockly.MOTORDRIVERBOARD_DCPORTS_SECOND,"2"],[Blockly.MOTORDRIVERBOARD_DCPORTS_THIRD,"3"],[Blockly.MOTORDRIVERBOARD_DCPORTS_FOURTH,"4"]];
var MOTORDRIVERBOARD_DCDIRECTION=[[Blockly.MOTORDRIVERBOARD_DCDIRECTION_FORWARD,"FORWARD"],[Blockly.MOTORDRIVERBOARD_DCDIRECTION_BACK,"BACKWARD"],[Blockly.MOTORDRIVERBOARD_DCDIRECTION_BRAKE,"BRAKE"],[Blockly.MOTORDRIVERBOARD_DCDIRECTION_RELEASE,"RELEASE"]];

var MOTORDRIVERBOARD_ENPORTS=[[Blockly.MOTORDRIVERBOARD_ENPORTS_FIRST,"1"],[Blockly.MOTORDRIVERBOARD_ENPORTS_SECOND,"2"],[Blockly.MOTORDRIVERBOARD_ENPORTS_THIRD,"3"],[Blockly.MOTORDRIVERBOARD_ENPORTS_FOURTH,"4"]];
var MOTORDRIVERBOARD_ENDIRECTION=[[Blockly.MOTORDRIVERBOARD_ENDIRECTION_FORWARD,"FORWARD"],[Blockly.MOTORDRIVERBOARD_ENDIRECTION_BACK,"BACKWARD"]];

var MOTORDRIVERBOARD_STPORTS=[[Blockly.MOTORDRIVERBOARD_STPORTS_FIRST,"1"],[Blockly.MOTORDRIVERBOARD_STPORTS_SECOND,"2"]];
var MOTORDRIVERBOARD_STDIRECTION=[[Blockly.MOTORDRIVERBOARD_STDIRECTION_FORWARD, "FORWARD"],[Blockly.MOTORDRIVERBOARD_STDIRECTION_BACK, "BACKWARD"]];
//var MOTORDRIVERBOARD_STSTYLE=[[Blockly.MOTORDRIVERBOARD_STYLE_SINGLE,"1"],[Blockly.MOTORDRIVERBOARD_STYLE_DOUBLE,"2"],[Blockly.MOTORDRIVERBOARD_STYLE_INTERLEAVE,"3"],[Blockly.MOTORDRIVERBOARD_STYLE_MICROSTEP,"4"]];
var MOTORDRIVERBOARD_STDOUBLESINGLE = [[Blockly.MOTORDRIVERBOARD_STDOUBLE,"DOUBLE"],[Blockly.MOTORDRIVERBOARD_STSINGLE,"SINGLE"],[Blockly.MOTORDRIVERBOARD_INTERLEAVE,"INTERLEAVE"]];
var MOTORDRIVERBOARD_RGBNUMBER=[[Blockly.MOTORDRIVERBOARD_RGBNUMBER_ALL,"0"]];
var MOTORDRIVERBOARD_RGBCOLOR=[[Blockly.MOTORDRIVERBOARD_RGBCOLOR_RED,"0xFF0000"],[Blockly.MOTORDRIVERBOARD_RGBCOLOR_GREEN,"0x00FF00"],[Blockly.MOTORDRIVERBOARD_RGBCOLOR_BLUE,"0x0000FF"],[Blockly.MOTORDRIVERBOARD_RGBCOLOR_YELLOW,"0xFFFF00"],[Blockly.MOTORDRIVERBOARD_RGBCOLOR_PURPLE,"0xFF00FF"],[Blockly.MOTORDRIVERBOARD_RGBCOLOR_WHITE,"0xFFFFFF"],[Blockly.MOTORDRIVERBOARD_RGBCOLOR_OFF,"0x000000"]];

var MOTORDRIVERBOARD_SOUNDS=[[Blockly.MOTORDRIVERBOARD_SOUNDS_CONNECTED,"0"],[Blockly.MOTORDRIVERBOARD_SOUNDS_DISCONNECTED,"1"],[Blockly.MOTORDRIVERBOARD_SOUNDS_BUTTONPUSHED,"2"],[Blockly.MOTORDRIVERBOARD_SOUNDS_MODE1,"3"],[Blockly.MOTORDRIVERBOARD_SOUNDS_MODE2,"4"],[Blockly.MOTORDRIVERBOARD_SOUNDS_MODE3,"5"],[Blockly.MOTORDRIVERBOARD_SOUNDS_SURPRISE,"6"],[Blockly.MOTORDRIVERBOARD_SOUNDS_OHOH,"7"],[Blockly.MOTORDRIVERBOARD_SOUNDS_OHOH2,"8"],[Blockly.MOTORDRIVERBOARD_SOUNDS_CUDDLY,"9"],[Blockly.MOTORDRIVERBOARD_SOUNDS_SLEEPING,"10"],[Blockly.MOTORDRIVERBOARD_SOUNDS_HAPPY,"11"],[Blockly.MOTORDRIVERBOARD_SOUNDS_SUPERHAPPY,"12"],[Blockly.MOTORDRIVERBOARD_SOUNDS_SHORTHAPPY,"13"],[Blockly.MOTORDRIVERBOARD_SOUNDS_SAD,"14"],[Blockly.MOTORDRIVERBOARD_SOUNDS_CONFUSED,"15"],[Blockly.MOTORDRIVERBOARD_SOUNDS_FART1,"16"],[Blockly.MOTORDRIVERBOARD_SOUNDS_FART2,"17"],[Blockly.MOTORDRIVERBOARD_SOUNDS_FART3,"18"],[Blockly.MOTORDRIVERBOARD_SOUNDS_DIDI,"19"]];

var MOTORDRIVERBOARD_IRKEY2=[["1","IR_KEYCODE_1"],["2","IR_KEYCODE_2"],["3","IR_KEYCODE_3"],["4","IR_KEYCODE_4"],["5","IR_KEYCODE_5"],["6","IR_KEYCODE_6"],["7","IR_KEYCODE_7"],["8","IR_KEYCODE_8"],["9","IR_KEYCODE_9"],["0","IR_KEYCODE_0"],["*","IR_KEYCODE_STAR"],["#","IR_KEYCODE_POUND"],["↑","IR_KEYCODE_UP"],["↓","IR_KEYCODE_DOWN"],["OK","IR_KEYCODE_OK"],["←","IR_KEYCODE_LEFT"],["→","IR_KEYCODE_RIGHT"]];

var MOTORDRIVERBOARD_IRKEY=[["1","EM_IR_KEYCODE_1"],["2","EM_IR_KEYCODE_2"],["3","EM_IR_KEYCODE_3"],["4","EM_IR_KEYCODE_4"],["5","EM_IR_KEYCODE_5"],["6","EM_IR_KEYCODE_6"],["7","EM_IR_KEYCODE_7"],["8","EM_IR_KEYCODE_8"],["9","EM_IR_KEYCODE_9"],["0","EM_IR_KEYCODE_0"],["A","EM_IR_KEYCODE_A"],["B","EM_IR_KEYCODE_B"],["C","EM_IR_KEYCODE_C"],["D","EM_IR_KEYCODE_D"],["+","EM_IR_KEYCODE_PLUS"],["-","EM_IR_KEYCODE_REDUCE"],["↑","EM_IR_KEYCODE_UP"],["↓","EM_IR_KEYCODE_DOWN"],["OK","EM_IR_KEYCODE_OK"],["←","EM_IR_KEYCODE_LEFT"],["→","EM_IR_KEYCODE_RIGHT"]];

var MOTORDRIVERBOARD_GPIO = [["S1","S1"],["S2","S2"],["S3","S3"],["S4","S4"],["S5","S5"],["S6","S6"],["S7","S7"],["S8","S8"]];

var MOTORDRIVERBOARD_GPIOMODE = [[Blockly.MOTORDRIVERBOARD_GPIOHIGH,"HIGH"],[Blockly.MOTORDRIVERBOARD_GPIOLOW,"LOW"]];

var MOTORDRIVERBOARD_PS2KEYS=[[Blockly.MOTORDRIVERBOARD_PS2KEYS_UP,"16"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_DOWN,"64"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_LEFT,"128"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_RIGHT,"32"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_TRIANGLE,"4096"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_CIRCLE,"8192"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_CROSS,"16384"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_SQUARE,"32768"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_L1,"1024"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_L2,"256"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_L3,"2"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_R1,"2048"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_R2,"512"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_R3,"4"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_SELECT,"1"],[Blockly.MOTORDRIVERBOARD_PS2KEYS_START,"8"]];

var MOTORDRIVERBOARD_VIBRATE=[[Blockly.MOTORDRIVERBOARD_VIBRATE_LX,"7"],[Blockly.MOTORDRIVERBOARD_VIBRATE_LY,"8"],[Blockly.MOTORDRIVERBOARD_VIBRATE_RX,"5"],[Blockly.MOTORDRIVERBOARD_VIBRATE_RY,"6"]];
var MOTORDRIVERBOARD_VIBRATE2=[[Blockly.MOTORDRIVERBOARD_VIBRATE2_L,"LeftHart()"],[Blockly.MOTORDRIVERBOARD_VIBRATE2_R,"RightHart();"]];
var MOTORDRIVERBOARD_SERVOPORTS=[[Blockly.MOTORDRIVERBOARD_SERVOPORTS_FIRST,"1"],[Blockly.MOTORDRIVERBOARD_SERVOPORTS_SECOND,"2"],[Blockly.MOTORDRIVERBOARD_SERVOPORTS_THIRD,"3"],[Blockly.MOTORDRIVERBOARD_SERVOPORTS_FOURTH,"4"],[Blockly.MOTORDRIVERBOARD_SERVOPORTS_FIVETH,"5"],[Blockly.MOTORDRIVERBOARD_SERVOPORTS_SIXTH,"6"],[Blockly.MOTORDRIVERBOARD_SERVOPORTS_SEVENTH,"7"],[Blockly.MOTORDRIVERBOARD_SERVOPORTS_EIGHTH,"8"]];

//二维码
Blockly.Blocks.md_qrcode = {
  init: function() {
    this.setColour("#00CCCC");
    this.appendDummyInput("").appendField(Blockly.MOTORDRIVERBOARD_QRCODE)
	.appendField(new Blockly.FieldTextInput('https://github.com/emakefun/MotorDriverBoard'), 'nulllab_rgbUltrasonic')
    this.setTooltip(Blockly.MIXLY_1617171136759936_2);
    this.setHelpUrl();
  }
};
//第0个图形块的样式,MotorDriverBoard初始化
Blockly.Blocks.md_setup = {
 init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_SETUP)
	this.setPreviousStatement(true,null);
    this.setNextStatement(true,null);
	this.setTooltip('');
 }
};

Blockly.Blocks.md_setFreq = {
    init:function(){
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
        this.appendValueInput("freq", Number)
        .appendField(Blockly.MOTORDRIVERBOARD_GPIOFREQ)
        this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
        this.setInputsInline(true);
		this.setTooltip('');
     }
};

Blockly.Blocks.md_gpio = {
    init:function(){
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_GPIO)
        .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_GPIO), "mdGpio")
        .appendField(Blockly.MOTORDRIVERBOARD_GPIOMODE)
        .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_GPIOMODE), "mdGpioMode")
        this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
     }
};

Blockly.Blocks.md_pwm = {
    init:function(){
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_GPIO)
        .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_GPIO), "mdGpio")
        this.appendValueInput("pwm", Number)
        .appendField(Blockly.MOTORDRIVERBOARD_GPIOPWM)
        this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
        this.setInputsInline(true);
		this.setTooltip('');
     }
};

Blockly.Blocks.md_initdcmotor = {
	init:function(){
	    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
		this.appendDummyInput("")
			.appendField(Blockly.MOTORDRIVERBOARD_INITDCMOTOR)
		   // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_DCPORTS),"DCPorts")
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
		}
};
//第一个图形块的样式,直流电机下拉（下拉没有value），正反转（下拉），速度（输入,有value）
Blockly.Blocks.md_dcmotor = {
  init: function() {
	    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_DCMOTOR)
        .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_DCPORTS), "DCPorts")
		 .appendField(Blockly.MOTORDRIVERBOARD_DCDIRECTIONS)
		 .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_DCDIRECTION), "DCDirections")
         .appendField(Blockly.MOTORDRIVERBOARD_NRFSPEED);
	   this.appendValueInput("Speed", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	    this.setPreviousStatement(true, null);
        this.setInputsInline(true);
		this.setNextStatement(true, null);
        this.setTooltip('');
  }
};
//第二个图形块的样式,停止直流电机下拉（下拉没有value）
Blockly.Blocks.md_stopDCmotor = {
	init:function(){
	    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
		this.appendDummyInput("")
			.appendField(Blockly.MOTORDRIVERBOARD_STOPDCMOTOR)
		   // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_DCPORTS),"DCPorts")
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
		}
};
Blockly.Blocks.md_initENmotor = {
	init:function(){
	    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
		this.appendDummyInput("")
			.appendField(Blockly.MOTORDRIVERBOARD_INITENMOTOR)
		   // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_ENPORTS),"ENPorts")
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
		}
};
//第三个图形块的样式,编码电机下拉（下拉没有value），正反转（下拉），速度（输入,有value）
Blockly.Blocks.md_enmotor = {
  init: function() {
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_ENMOTOR)
        .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_ENPORTS), "ENPorts")
		 .appendField(Blockly.MOTORDRIVERBOARD_ENDIRECTIONS)
		 .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_ENDIRECTION), "ENDirections")
         .appendField(Blockly.MOTORDRIVERBOARD_NRFSPEED);
	   this.appendValueInput("Speed", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	    this.setPreviousStatement(true, null);
        this.setInputsInline(true);
		this.setNextStatement(true, null);
        this.setTooltip('');
  }
};
//第四个图形块的样式,停止编码电机 下拉（下拉没有value）
Blockly.Blocks.md_stopENmotor = {
	init:function(){
	    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
		this.appendDummyInput("")
			.appendField(Blockly.MOTORDRIVERBOARD_STOPENMOTOR)
		   // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_ENPORTS),"ENPorts")
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
		}
};
Blockly.Blocks.md_initstmotor = {
	init:function(){
	    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
		this.appendDummyInput("")
			.appendField(Blockly.MOTORDRIVERBOARD_INITSTMOTOR)
		   // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_STPORTS),"STPorts")
			.appendField(Blockly.MOTORDRIVERBOARD_STEPS);
	   this.appendValueInput("Steps", Number)
        .setCheck(Number)
        this.appendValueInput("freq", Number)
        .setCheck(Number)
        .appendField(Blockly.MOTORDRIVERBOARD_MINFREQ);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
        this.setInputsInline(true);
		this.setTooltip('');
		}
};
//第五个图形块的样式,步进电机下拉，步数value，方向下拉，方式下拉
Blockly.Blocks.md_stmotor = {
  init: function() {
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_STMOTOR)
        .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_STPORTS), "STPorts")
		 .appendField(Blockly.MOTORDRIVERBOARD_STDIRECTIONS)
		 .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_STDIRECTION), "STDirections")
         .appendField(Blockly.MOTORDRIVERBOARD_STDOUBLESINGLE)
		 .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_STDOUBLESINGLE), "doubleSingle")
		 //.appendField(Blockly.MOTORDRIVERBOARD_STSTYLES)
		 //.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_STSTYLE), "STStyles")
         .appendField(Blockly.MOTORDRIVERBOARD_STEPS1);
	   this.appendValueInput("Steps", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	    this.setPreviousStatement(true, null);
        this.setInputsInline(true);
		this.setNextStatement(true, null);
        this.setTooltip('');
  }
};
//停止步进电机
Blockly.Blocks.md_stopstmotor = {
	init:function(){
	    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
		this.appendDummyInput("")
			.appendField(Blockly.MOTORDRIVERBOARD_STOPSTMOTOR)
		   // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_STPORTS),"STTPorts")
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
		}
};


Blockly.Blocks.md_initRGB = {
  init: function(){
	 this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	 this.appendDummyInput("")
         .appendField(Blockly.MOTORDRIVERBOARD_INITRGB)
	 	 //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/hb_ultrasonic.png", 45, 38))
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);

	}
};
//第六个图形块的样式,rgb
Blockly.Blocks.md_RGB = {
  init: function(){
	 this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	 this.appendDummyInput("")
         .appendField(Blockly.MOTORDRIVERBOARD_SETRGB)
	 	 //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/hb_ultrasonic.png", 45, 38))
         .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_RGBNUMBER), "RGB")
	     .appendField(Blockly.MOTORDRIVERBOARD_RGBCOLOUR)
		 .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_RGBCOLOR), "RGBCOLOR");
		  this.appendDummyInput("")
		   .appendField(Blockly.MOTORDRIVERBOARD_RGBBRIGHTNESSS)
		   this.appendValueInput("brightnesss", Number);
		   this.setInputsInline(true);
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);

	}
};
//通过模拟值参数设置rgb
Blockly.Blocks.md_setColor = {
  init: function(){
	 this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	 this.appendDummyInput("")
         .appendField(Blockly.MOTORDRIVERBOARD_SETRGB)
	 	 //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/hb_ultrasonic.png", 45, 38))
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
		 this.appendDummyInput("")
		   .appendField(Blockly.MOTORDRIVERBOARD_RGBBRIGHTNESSS)
		   this.appendValueInput("brightnessss", Number);
		  this.setInputsInline(true);
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);

	}
};
//设置rgb亮度
Blockly.Blocks.md_setrgbbrightness = {
  init: function(){
	 this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	 this.appendDummyInput("")
         .appendField(Blockly.MOTORDRIVERBOARD_SETRGBBRIGHTNESS)
		this.appendValueInput("brightness", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);

	}
};
//第七个图形块的样式,播放声音 下拉
Blockly.Blocks.md_initSounds = {
 init:function(){
	 this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	 this.appendDummyInput("")
		// .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
		 .appendField(Blockly.MOTORDRIVERBOARD_INITSOUNDS)
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
 }
};
Blockly.Blocks.md_playSounds = {
 init:function(){
	 this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	 this.appendDummyInput("")
		// .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_MotorDriverBoard.png", 38, 32))
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
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_INITULTRASONIC)
		//.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irreceive.png", 38, 32))
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//第九个图形块的样式 读取超声波距离下拉
Blockly.Blocks.md_readUltrasonicDistance = {
  init: function() {
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_READULTRASONICDISTANCE)
		//.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_ultrasonic.png", 38, 32))
    this.setOutput(true, Number);
    this.setTooltip('');
  }
};
//第十个图形块的样式 红外接收初始化
Blockly.Blocks.md_initirremote = {
  init: function() {
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_INITIRREMOTE)
		//.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_ultrasonic.png", 38, 32))
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//if irremote pressed
Blockly.Blocks.md_isirremote = {
  init: function() {
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_IFIRREMOTEPRESSED)
		//.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_ultrasonic.png", 38, 32))
    this.setOutput(true, Boolean);
    this.setTooltip('');
  }
};
//第十一个图形块的样式(setOutput) 红外遥控按键（下拉，返回boolean）
Blockly.Blocks.md_irKeyPress = {
  init: function() {
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_IRKEYPRESS)
		.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_IRKEY), "Irkeys")
		//.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_ultrasonic.png", 38, 32))
     this.setOutput(true, Number);
    this.setTooltip('');
  }
};
//第十一个图形块的样式(setOutput) 普通红外遥控按键（下拉，返回boolean）
Blockly.Blocks.md_irKeyPress2 = {
  init: function() {
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_IRKEYPRESS2)
		.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_IRKEY2), "Irkeys2")
		//.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_ultrasonic.png", 38, 32))
     this.setOutput(true, Number);
    this.setTooltip('');
  }
};

//第十二个图形块的样式 nrf24l01初始化    field的name不确定使NUM待检测
Blockly.Blocks.md_initnrf24l01 = {
  init: function() {
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01)
		//.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_ultrasonic.png", 38, 32))
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//第十三个图形块的样式 NRF24L01发送数据地址value 数据value
Blockly.Blocks.md_nrf24l01send = {
  init: function() {
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01SENDDATA);
		this.appendValueInput("address", String)
		.setCheck([String, Number])
	.setAlign(Blockly.ALIGN_RIGHT)
		.appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01ADDRESS)
		this.appendValueInput("channel", Number)
		.appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01CHANNEL)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
		this.appendValueInput("arr", Number)
		.appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01DATA)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
		  this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//初始化接收数组
Blockly.Blocks.md_nrf24l01rec = {
  init: function() {
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01SENDDATA);
		this.appendValueInput("address2", String)
				.setCheck([String, Number])
	   .setAlign(Blockly.ALIGN_RIGHT)
		.appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01ADDRESS)

		this.appendValueInput("channel2", Number)
		.appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01CHANNEL)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
		this.appendValueInput("arr2", Number)
		.appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01DATA2)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
		  this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//nrf发送数据
Blockly.Blocks.md_nrf24l01senddatass = {
  init: function() {
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01SENDDATASS);
		this.appendValueInput("nrfdatass", Number)
		  this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//nrf24l01发送出数据
Blockly.Blocks.md_nrfissend = {
  init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_NRFISSEND)
	    //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_ps2.png", 38, 32))
	   // .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_PS2KEY), "PS2Key")
	this.setOutput(true, Boolean);
	this.setTooltip('');
  }
};
//已准备接收数据
Blockly.Blocks.md_nrfdataradys = {
  init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_NRFREADYDATA)
	    //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_ps2.png", 38, 32))
	   // .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_PS2KEY), "PS2Key")
	this.setOutput(true, Boolean);
	this.setTooltip('');
  }
};
//nrf接收数据
Blockly.Blocks.md_nrfrecdatas = {
  init: function() {
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
        .appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01RECDATASSS);
		this.appendValueInput("nrfdatasss", Number)
		  this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//第十四个图形块的样式 NRF24L01接收数据地址value
Blockly.Blocks.md_nrf24l01receive = {
  init: function() {
    this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
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
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_INITNRF24L01ISNOTNULL)
	   this.setOutput(true, Number);
    this.setTooltip('');
 }
};
//第十六个图形块的样式 获取NRF24L01数据
Blockly.Blocks.md_getNRF24L01 = {
 init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_GETINITNRF24L01)
	   this.setOutput(true, Number);
    this.setTooltip('');
 }
};
//第十七个图形块的样式 PS2手柄初始化
Blockly.Blocks.md_PS2init = {
 init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_PS2INIT)
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
 }
};

Blockly.Blocks.md_ps2getvalue = {
    init:function(){
       this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
       this.appendDummyInput("")
           .appendField(Blockly.MOTORDRIVERBOARD_PS2GETVALUE)
       this.setPreviousStatement(true, null);
       this.setNextStatement(true, null);
       this.setTooltip('');
    }
   };
//第十八个图形块的样式 PS2键被按下（下拉）
Blockly.Blocks.md_WhichPS2KeyPressed = {
  init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_WHICHPS2KEYPRESSED)
	    //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_ps2.png", 38, 32))
	   // .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_PS2KEY), "PS2Key")
	this.setOutput(true, Boolean);
	this.setTooltip('');
  }
};

//第二十个图形块的样式 ps2手柄按下（下拉）
Blockly.Blocks.md_ps2keypress = {
  init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_PS2KEYPRESS)
	    //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
	    .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_PS2KEYS), "PS2keys")
	this.setOutput(true, Boolean);
	this.setTooltip('');
  }
};
//第二十一个图形块的样式 ps2手柄松开
Blockly.Blocks.md_ps2keyunpress = {
  init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_PS2KEYUNPRESS)
	    //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
	    .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_PS2KEYS), "PS2keys")
	this.setOutput(true, Boolean);
	this.setTooltip('');
  }
};
//第二十二个图形块的样式 获取摇杆值（下拉）
Blockly.Blocks.md_ps2getvibrate = {
  init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_PS2GETVIBRATE)
	    //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
	    .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_VIBRATE), "Vibrate")
	this.setOutput(true, Number);
	this.setTooltip('');
  }
};
//第二十二个图形块的样式 获取摇杆角度（下拉）
Blockly.Blocks.md_ps2getvibrate2 = {
  init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_PS2GETVIBRATE2)
	    //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
	    .appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_VIBRATE2), "Vibrate2")
	this.setOutput(true, Number);
	this.setTooltip('');
  }
};
//第二十三个图形块的样式 读取ps2状态
Blockly.Blocks.md_ps2status = {
 init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_PS2STATUS)
	    //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
	this.setPreviousStatement(true,null);
    this.setNextStatement(true,null);
	this.setTooltip('');
 }
};
//第二十三个图形块的样式 舵机 接口下拉  角度value
Blockly.Blocks.md_initservo = {
 init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_INITSERVO)
		.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_SERVOPORTS), "Servoports")
	    //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
	this.setPreviousStatement(true,null);
    this.setNextStatement(true,null);
	this.setTooltip('');
 }
};
Blockly.Blocks.md_servo = {
 init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
    this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_SERVOPORT)
		.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_SERVOPORTS), "Servoports")
	   this.appendValueInput("angle", Number)
       .appendField(Blockly.MOTORDRIVERBOARD_ANGLE)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	   this.appendValueInput("speed", Number)
       .appendField(Blockly.MOTORDRIVERBOARD_SPEED)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
        this.setInputsInline(true);
	    //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
	this.setPreviousStatement(true,null);
    this.setNextStatement(true,null);
	this.setTooltip('');
 }
};
//读取舵机角度
Blockly.Blocks.md_readservo= {
  init:function(){
	this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
	this.appendDummyInput("")
	    .appendField(Blockly.MOTORDRIVERBOARD_SERVOPORT)
		.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_SERVOPORTS), "Servoports")
		.appendField(Blockly.MOTORDRIVERBOARD_READDEGEREES)
	this.setOutput(true, Number);
	this.setTooltip('');
  }
};
//四驱车初始化
Blockly.Blocks.md_m4init = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
			.appendField(Blockly.MOTORDRIVERBOARD_M4INIT)
        this.appendDummyInput("")
       .appendField(Blockly.MOTORDRIVERBOARD_LEFTFORWARD)
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_DCPORTS), "M4Ports1")
         .appendField(Blockly.MOTORDRIVERBOARD_RIGHTFORWARD)
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_DCPORTS), "M4Ports2")
         .appendField(Blockly.MOTORDRIVERBOARD_LEFTBACKWARD)
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_DCPORTS), "M4Ports3")
         .appendField(Blockly.MOTORDRIVERBOARD_RIGHTBACKWARD)
			.appendField(new Blockly.FieldDropdown(MOTORDRIVERBOARD_DCPORTS), "M4Ports4")
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};
//前进
Blockly.Blocks.md_m4goforward = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_M4GOFORWARD)
        this.appendValueInput("m4speed1", Number)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};
//后退
Blockly.Blocks.md_m4backforward = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_M4BACKFORWARD)
        this.appendValueInput("m4speed2", Number)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};
//左转
Blockly.Blocks.md_m4turnleft = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_M4TURNLEFT)
        this.appendValueInput("m4speed3", Number)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};
//右转
Blockly.Blocks.md_m4turnright = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_M4TURNRIGHT)
        this.appendValueInput("m4speed4", Number)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};
//左自旋
Blockly.Blocks.md_m4turnlefts = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_M4TURNLEFTS)
        this.appendValueInput("m4speed33", Number)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};
//右自旋
Blockly.Blocks.md_m4turnrights = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_M4TURNRIGHTS)
        this.appendValueInput("m4speed44", Number)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};
//行驶角度
Blockly.Blocks.md_m4godegree = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_M4GODEGREE)
        this.appendValueInput("m4godegree", Number)
        this.appendDummyInput("")
         .appendField(Blockly.MOTORDRIVERBOARD_M4GOSPEED)
        this.appendValueInput("m4gospeed", Number)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};
//停止
Blockly.Blocks.md_m4stop = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_M4STOP)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};
//蓝牙初始化
Blockly.Blocks.md_bluetoothinit = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_BLUETOOTHINIT)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};
Blockly.Blocks.md_receivedata = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
            .appendField(Blockly.MOTORDRIVERBOARD_RECEIVEDATA)
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};
Blockly.Blocks.md_receiveddata = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_RECEIVEDDDATA)
           //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
        this.setOutput(true, Boolean);
        this.setTooltip('');
    }
};

Blockly.Blocks.md_bluetoothKeyPress = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_BLUETOOTHPRESS)
           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
            .appendField(new Blockly.FieldDropdown(
           [
               ["↑", "0x0008"],
               ["↓", "0x0020"],
               ["←", "0x0010"],
               ["→", "0x0004"],
			   ["green", "0x1000"],
               ["red", "0x2000"],
               ["blue", "0x4000"],
               ["pink", "0x8000"],
           ]), "BLUETOOTHKEY")
        this.setOutput(true, Boolean);
        this.setTooltip('');
    }
};
Blockly.Blocks.md_bluetoothstyle = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_BLUETOOTHSTYLE)
            //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
            .appendField(new Blockly.FieldDropdown([
                [Blockly.MOTORDRIVERBOARD_BLUETOOTHSTYLE_BUTTONS, "13"],
                [Blockly.MOTORDRIVERBOARD_BLUETOOTHSTYLE_DIRECTIONS, "5"],
                [Blockly.MOTORDRIVERBOARD_BLUETOOTHSTYLE_SPEEDS, "6"],
            ]), "BLUETOOTHSTYLE")
        this.setOutput(true, Number);
        this.setTooltip('');
    }
};
Blockly.Blocks.md_bluetoothgetdegree = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_BLUETOOTHGETDEGREE)
           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
        this.setOutput(true, Number);
        this.setTooltip('');
    }
};

Blockly.Blocks.md_bluetoothgetspeed = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_BLUETOOTHGETSPEED)
           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
        this.setOutput(true, Number);
        this.setTooltip('');
    }
};

Blockly.Blocks.md_nrfinit = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_NRFINIT)
           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
        this.appendValueInput("nrfadd", String)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};

Blockly.Blocks.md_nrfdataready = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_NRFDATAREADY)
           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
        this.setOutput(true, Number);
        this.setTooltip('');
    }
};

Blockly.Blocks.md_nrfvalue = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_NRFVALUE)
           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
        //this.appendValueInput("nrfadd", String)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};

Blockly.Blocks.md_nrfgetdata = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_NRFGETDATA)
           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
        //this.appendValueInput("nrfadd", String)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};

Blockly.Blocks.md_nrfgetpackage = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_NRFGETPACKAGE)
           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
        this.setOutput(true, Number);
        this.setTooltip('');
    }
};

Blockly.Blocks.md_nrfnewob = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_NRFNEWOB)
           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
        //this.appendValueInput("nrfadd", String)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};

Blockly.Blocks.md_nrfdatafun = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_NRFDATAFUN)
			 .appendField(new Blockly.FieldDropdown(
           [
               [Blockly.MOTORDRIVERBOARD_NRFDIRECTION, "E_ROBOT_CONTROL_DIRECTION"],
               [Blockly.MOTORDRIVERBOARD_NRFSPEED, "E_ROBOT_CONTROL_SPEED"],
               [Blockly.MOTORDRIVERBOARD_NRFBUTTON, "E_BUTTON"],
           ]), "datafun")
           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
        this.setOutput(true, Number);
        this.setTooltip('');
    }
};

Blockly.Blocks.md_nrfbuttons = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
		.appendField(Blockly.MOTORDRIVERBOARD_NRFBUTTONS)
		 .appendField(new Blockly.FieldDropdown(
           [
               [Blockly.MOTORDRIVERBOARD_NRFBUTTONSL1, "0x0080"],
               [Blockly.MOTORDRIVERBOARD_NRFBUTTONSR1, "0x0040"],
               [Blockly.MOTORDRIVERBOARD_NRFBUTTONSUP, "BT_PAD_UP"],
			   [Blockly.MOTORDRIVERBOARD_NRFBUTTONSDOWN, "BT_PAD_DOWN"],
               [Blockly.MOTORDRIVERBOARD_NRFBUTTONSLEFT, "BT_PAD_LEFT"],
               [Blockly.MOTORDRIVERBOARD_NRFBUTTONSRIGHT, "BT_PAD_RIGHT"],
           ]), "nrfbuttons")


           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
        this.setOutput(true, Number);
        this.setTooltip('');
    }
};

Blockly.Blocks.md_nrfgetdegree = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_NRFGETDEGREE)
           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
        //this.appendValueInput("nrfadd", String)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
       this.setOutput(true, Number);
        this.setTooltip('');
    }
};

Blockly.Blocks.md_nrfgetspeed = {
    init: function () {
        this.setColour(Blockly.Msg['MOTORDRIVERBOARD_HUE']);
        this.appendDummyInput("")
            .appendField(Blockly.MOTORDRIVERBOARD_NRFGETSPEED)
           // .appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/panthertank/pt_bluetooth.png", 45, 38))
        //this.appendValueInput("nrfadd", String)
        //.appendField(new Blockly.FieldImage("./libraries/ThirdParty/MotorDriverBoard/media/MotorDriverBoard/md_irtracking.png", 38, 32))
       this.setOutput(true, Number);
        this.setTooltip('');
    }
};
