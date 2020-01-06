'use strict';

goog.provide('Blockly.Arduino.MotorDriverBoard');

goog.require('Blockly.Arduino');

//����0��ͼ�ο�ת��ΪC���� Hummerbot��ʼ��
Blockly.Arduino.md_setup = function() {
 //Blockly.Arduino.definitions_['define_Arduino'] = '#include<Arduino.h>';
 //Blockly.Arduino.definitions_['define_wire'] = '#include<wire.h>';
 //Blockly.Arduino.definitions_['define_SoftwareSerial'] = '#include<SoftwareSerial.h>';
 //Blockly.Arduino.definitions_['define_ProtocolParser'] = '#include<ProtocolParser.h>';
 //Blockly.Arduino.definitions_['define_BluetoothHandle'] = '#include<BluetoothHandle.h>';
 //Blockly.Arduino.definitions_['define_KeyMap'] = '#include<KeyMap.h>';
// Blockly.Arduino.definitions_['define_debug'] = '#include<debug.h>';
var dropdown_version = this.getFieldValue('version');
 Blockly.Arduino.definitions_['define_Emakefun_MotorDriver'] = '#include<Emakefun_MotorDriver.h>\nEmakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver(0x60,'+dropdown_version+');\n';

 Blockly.Arduino.setups_['setup_md_setup1'] ='\t'+'Serial.begin(9600);\n'

 var code = '';
 return code;
};
Blockly.Arduino.md_initdcmotor = function(){
 var dropdown_DCPorts = this.getFieldValue('DCPorts');
  Blockly.Arduino.definitions_['object'+dropdown_DCPorts+''] = '#include<Emakefun_MotorDriver.h>\nEmakefun_DCMotor *DCmotor_'+dropdown_DCPorts+' = mMotorDriver.getMotor('+dropdown_DCPorts+');\n'
 Blockly.Arduino.setups_['setup_md_setup2'] ='\t'+'mMotorDriver.begin(50);\n'
 var code = ''
 return code;
};
//����һ��ͼ�ο�ת��ΪC���� ֱ����������������û��value��������ת�����������ٶȣ�����,��value��
Blockly.Arduino.md_dcmotor = function() {
 var dropdown_DCPorts = this.getFieldValue('DCPorts');
 var dropdown_DCDirections = this.getFieldValue('DCDirections');
   var value_Speed = Blockly.Arduino.valueToCode(this,'Speed',Blockly.Arduino.ORDER_ATOMIC);


 var code = 'DCmotor_'+dropdown_DCPorts+'->setSpeed('+value_Speed+');\n'
 			+'DCmotor_'+dropdown_DCPorts+'->run('+dropdown_DCDirections+');\n';
return code;
};
//���ڶ���ͼ�ο�ת��ΪC���� ֱֹͣ������ ����������û��value��
Blockly.Arduino.md_stopDCmotor = function(){
 var dropdown_DCPorts = this.getFieldValue('DCPorts');
 var code = 'DCmotor_'+dropdown_DCPorts+'->run(BRAKE);\n'
 return code;
};
Blockly.Arduino.md_initENmotor = function(){
 var dropdown_ENPorts = this.getFieldValue('ENPorts');
  Blockly.Arduino.definitions_['object'+dropdown_ENPorts+''] = '#include<Emakefun_MotorDriver.h>\nEmakefun_EncoderMotor *EncodeMotor_'+dropdown_ENPorts+' = mMotorDriver.getEncoderMotor('+dropdown_ENPorts+');\n'
 var code = ''
 return code;
};
//��������ͼ�ο�ת��ΪC���� ������������������û��value��������ת�����������ٶȣ�����,��value��
 Blockly.Arduino.md_enmotor = function() {
 var dropdown_ENPorts = this.getFieldValue('ENPorts');
 var dropdown_ENDirections = this.getFieldValue('ENDirections');
   var value_Speed = Blockly.Arduino.valueToCode(this,'Speed',Blockly.Arduino.ORDER_ATOMIC);

 Blockly.Arduino.setups_['setup_md_setup3'] ='\t'+'mMotorDriver.begin(50);\n'

 var code = 'EncodeMotor_'+dropdown_ENPorts+'->setSpeed('+value_Speed+');\n'
 			+'EncodeMotor_'+dropdown_ENPorts+'->run('+dropdown_ENDirections+');\n';
return code;
};
//�����ĸ�ͼ�ο�ת��ΪC���� ֹͣ�������� ����������û��value��
Blockly.Arduino.md_stopENmotor = function(){
 var dropdown_ENPorts = this.getFieldValue('ENPorts');
 var code = 'EncodeMotor_'+dropdown_ENPorts+'->run(BRAKE);\n'
 return code;
};
Blockly.Arduino.md_initstmotor = function(){
 var value_Steps = Blockly.Arduino.valueToCode(this,'Steps',Blockly.Arduino.ORDER_ATOMIC);
 var dropdown_STPorts = this.getFieldValue('STPorts');
 Blockly.Arduino.definitions_['object'+dropdown_STPorts+''] = '#include<Emakefun_MotorDriver.h>\nEmakefun_StepperMotor *StepperMotor_'+dropdown_STPorts+' = mMotorDriver.getStepper('+value_Steps+','+dropdown_STPorts+');\n'
 var code = ''
 return code;
};
//��������ͼ�ο�ת��ΪC���� ������������������value��������������ʽ����
Blockly.Arduino.md_stmotor = function(){
 var dropdown_STPorts = this.getFieldValue('STPorts');
 var dropdown_STDirections = this.getFieldValue('STDirections');
  //var dropdown_STStyles = this.getFieldValue('STStyles');
 var value_Steps = Blockly.Arduino.valueToCode(this,'Steps',Blockly.Arduino.ORDER_ATOMIC);
 var value_Speed = Blockly.Arduino.valueToCode(this,'Speed',Blockly.Arduino.ORDER_ATOMIC);
  Blockly.Arduino.setups_['setup_md_setup7'] ='\t'+'mMotorDriver.begin();\n'

 var code = ' StepperMotor_'+dropdown_STPorts+'->setSpeed('+value_Speed+');\n'+' StepperMotor_'+dropdown_STPorts+'->step('+value_Steps+','+dropdown_STDirections+');\n'
 return code;
};
//ֹͣ��������
Blockly.Arduino.md_stopstmotor = function(){
 var dropdown_STTPorts = this.getFieldValue('STTPorts');
 var code = 'StepperMotor_'+dropdown_STTPorts+'->release();\n'
 return code;
};
Blockly.Arduino.md_initRGB = function(){
	//var dropdown_RGB = this.getFieldValue('RGB');
	//var dropdown_RGBCOLOR = this.getFieldValue('RGBCOLOR');
	 Blockly.Arduino.definitions_['object55'] = '#include<RGBLed.h>\nRGBLed *rgb = mMotorDriver.getSensor(E_RGB);\n'
 var code = '';
 return code;
};
//��������ͼ�ο�ת��ΪC���� ����RGB����ɫ���������죬�̣������ƣ��ϣ��ף��ڣ�
Blockly.Arduino.md_RGB = function(){
	var value_brightnesss = Blockly.Arduino.valueToCode(this,'brightnesss',Blockly.Arduino.ORDER_ATOMIC);
	var dropdown_RGB = this.getFieldValue('RGB');
	var dropdown_RGBCOLOR = this.getFieldValue('RGBCOLOR');
	 //Blockly.Arduino.definitions_['object5'] = 'Emakefun_Sensor *rgb = mMotorDriver.getSensor(E_RGB);\n'
 var code = 'rgb->setBrightness('+value_brightnesss+');\nrgb->SetRgbColor((E_RGB_INDEX)'+dropdown_RGB+', '+dropdown_RGBCOLOR+');\n';
 return code;
};
//ͨ��ģ��ֵ��������rgb
Blockly.Arduino.md_setColor = function(){
	var dropdown_RGB = this.getFieldValue('RGB');
	var value_red = Blockly.Arduino.valueToCode(this,'red',Blockly.Arduino.ORDER_ATOMIC);
	var value_green = Blockly.Arduino.valueToCode(this,'green',Blockly.Arduino.ORDER_ATOMIC);
	var value_blue = Blockly.Arduino.valueToCode(this,'blue',Blockly.Arduino.ORDER_ATOMIC);
	var value_brightnessss = Blockly.Arduino.valueToCode(this,'brightnessss',Blockly.Arduino.ORDER_ATOMIC);
	 //Blockly.Arduino.definitions_['object55'] = '#include<RGBLed.h>\nRGBLed rgbled_A3(A1, 2);\n'
 var code = 'rgb->setBrightness('+value_brightnessss+');\nrgb->setColor((E_RGB_INDEX)'+dropdown_RGB+', '+value_red+','+value_green+','+value_blue+');\n'+'rgb->show();\n';
 return code;
};
//rgb���� md_
Blockly.Arduino.setrgbbrightness = function(){
	var value_brightness = Blockly.Arduino.valueToCode(this,'brightness',Blockly.Arduino.ORDER_ATOMIC);
	 //Blockly.Arduino.definitions_['object55'] = '#include<RGBLed.h>\nRGBLed rgbled_A3(A1, 2);\n'
 var code = 'rgb->setBrightness('+value_brightness+');\n';
 return code;
};
//�����߸�ͼ�ο�ת��ΪC���� �������� ����
Blockly.Arduino.md_initSounds = function(){
	//var dropdown_Sounds = this.getFieldValue('Sounds');
	Blockly.Arduino.definitions_['object6'] = '#include<Buzzer.h>\n#include<Sounds.h>\nEmakefun_Sensor *buzzer = mMotorDriver.getSensor(E_BUZZER);\n'
 var code = '';
 return code;
};
Blockly.Arduino.md_playSounds = function(){
	var dropdown_Sounds = this.getFieldValue('Sounds');
	//Blockly.Arduino.definitions_['object6'] = 'Emakefun_Sensor *buzzer = mMotorDriver.getSensor(E_BUZZER);\n'
 var code = 'buzzer->Sing('+dropdown_Sounds+');\n';
 return code;
};
//���ڰ˸�ͼ�ο�ת��ΪC���� ��������ʼ��
Blockly.Arduino.md_initultrasonic = function () {
    Blockly.Arduino.setups_['md_initultrasonic'] = '\t' + 'mMotorDriver.getSensor(E_ULTRASONIC);\n'
    Blockly.Arduino.definitions_['object7'] = '#include<Emakefun_MotorDriver.h>\nEmakefun_Sensor *ultrasonic = mMotorDriver.getSensor(E_SENSOR_MAX);\n'
 var code = '';
 return code;
};
//���ھŸ�ͼ�ο�ת��ΪC���� ��ȡ����������
Blockly.Arduino.md_readUltrasonicDistance = function(){

 var code = 'ultrasonic->GetUltrasonicDistance()';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; //��codeΪ����ʽʱ�ô˷��ط�ʽ
};
//����ʮ��ͼ�ο�ת��ΪC���� �������ճ�ʼ��
Blockly.Arduino.md_initirremote = function(){
    Blockly.Arduino.definitions_['define_KeyMap'] = '#include<KeyMap.h>\n#include<IRremote.h>\nIRremote *ir = mMotorDriver.getSensor(E_IR);\n';
	//Blockly.Arduino.definitions_['object8'] = ''
  var code = '';
 return code;
};
//if irremote pressed
Blockly.Arduino.md_isirremote = function(){
	//Blockly.Arduino.definitions_['define_KeyMap'] = '#include<KeyMap.h>\n#include<IRremote.h>\nEmakefun_Sensor *ir = mMotorDriver.getSensor(E_IR);\n';
	//Blockly.Arduino.definitions_['object8'] = ''
  var code = 'irKeyCode = ir->getCode()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};
//����ʮһ��ͼ�ο�ת��ΪC���� ����ң�ذ���������������boolean��
Blockly.Arduino.md_irKeyPress = function(){
	var dropdown_Irkeys = this.getFieldValue('Irkeys');
Blockly.Arduino.definitions_['object9'] = 'byte irKeyCode;\n'
var code = '(E_EM_IR_KEYCODE)ir->getIrKey(irKeyCode,2) == ' + dropdown_Irkeys + '';
 return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.md_irKeyPress2 = function(){
	var dropdown_Irkeys2 = this.getFieldValue('Irkeys2');
Blockly.Arduino.definitions_['object9'] = 'byte irKeyCode;\n'
var code = '(E_NORMAL_IR_KEYCODE)ir->getIrKey(irKeyCode) == ' + dropdown_Irkeys2 + '';
 return [code, Blockly.Arduino.ORDER_ATOMIC];
};

//����ʮ����ͼ�ο�ת��ΪC���� NRF24L01��ʼ��    field��name��ȷ��ʹNUM������
Blockly.Arduino.md_initnrf24l01 = function(){
	Blockly.Arduino.definitions_['md_initnrf24l01'] = '#include<nRF24L01.h>\nNrf24l Mirf = Nrf24l(10, 9);\n'
	//Blockly.Arduino.setups_['md_initnrf24l01'] ='\t'+'Serial.begin(9600);\nMirf.spi = &MirfHardwareSpi;\nMirf.init();\nMirf.channel = 90;\nMirf.config();\n'
  var code = '';
 return code;
};
//����ʮ����ͼ�ο�ת��ΪC���� NRF24L01�������ݵ�ַvalue ����value
Blockly.Arduino.md_nrf24l01send = function(){

 var value_address = Blockly.Arduino.valueToCode(this,'address',Blockly.Arduino.ORDER_ATOMIC);
 var value_channel = Blockly.Arduino.valueToCode(this,'channel',Blockly.Arduino.ORDER_ATOMIC);
 var value_arr = Blockly.Arduino.valueToCode(this,'arr',Blockly.Arduino.ORDER_ATOMIC);
    //Blockly.Arduino.definitions_['md_nrf24l01send123'] = ''
	Blockly.Arduino.definitions_['md_nrf24l01send123'] = '#include<nRF24L01.h>\nNrf24l Mirf = Nrf24l(10, 9);\n'
	Blockly.Arduino.setups_['md_nrf24l01send123'] ='Serial.begin(9600);\n  Mirf.spi = &MirfHardwareSpi;\n  Mirf.init();\n  Mirf.setRADDR('+value_address+');\n  Mirf.payload = sizeof('+value_arr+');\n  Mirf.channel = '+value_channel+';\n  Mirf.config();\n'
 var code = '';
 return code;
};
//��������
Blockly.Arduino.md_nrf24l01rec = function(){

 var value_address2 = Blockly.Arduino.valueToCode(this,'address2',Blockly.Arduino.ORDER_ATOMIC);
 var value_channel2 = Blockly.Arduino.valueToCode(this,'channel2',Blockly.Arduino.ORDER_ATOMIC);
 var value_arr2 = Blockly.Arduino.valueToCode(this,'arr2',Blockly.Arduino.ORDER_ATOMIC);
    //Blockly.Arduino.definitions_['md_nrf24l01send123'] = ''
	Blockly.Arduino.definitions_['md_nrf24l01rec'] = '#include<nRF24L01.h>\nNrf24l Mirf = Nrf24l(10, 9);\n'
	Blockly.Arduino.setups_['md_nrf24l01rec'] ='Serial.begin(9600);\n  Mirf.spi = &MirfHardwareSpi;\n  Mirf.init();\n  Mirf.setRADDR('+value_address2+');\n  Mirf.payload = sizeof('+value_arr2+');\n  Mirf.channel = '+value_channel2+';\n  Mirf.config();\n'
 var code = '';
 return code;
};
//nrfadd��������
Blockly.Arduino.md_nrf24l01senddatass = function(){
	 var value_nrfdatass = Blockly.Arduino.valueToCode(this,'nrfdatass',Blockly.Arduino.ORDER_ATOMIC);
	//Blockly.Arduino.definitions_['md_initnrf24l01'] = '#include<nRF24L01.h>\nNrf24l Mirf = Nrf24l(10, 9);\n'
	//Blockly.Arduino.setups_['md_initnrf24l01'] ='\t'+'Serial.begin(9600);\nMirf.spi = &MirfHardwareSpi;\nMirf.init();\nMirf.channel = 90;\nMirf.config();\n'
  var code = 'Mirf.send('+value_nrfdatass+'); \n';
 return code;
};
//��������
Blockly.Arduino.md_nrfissend = function(){
 var code = 'Mirf.isSending()';
 return [code, Blockly.Arduino.ORDER_ATOMIC];
};
//׼����������
Blockly.Arduino.md_nrfdataradys = function(){
 var code = 'Mirf.dataReady()';
 return [code, Blockly.Arduino.ORDER_ATOMIC];
};
//nrfadd��������
Blockly.Arduino.md_nrfrecdatas = function(){
	 var value_md_nrfdatasss = Blockly.Arduino.valueToCode(this,'nrfdatasss',Blockly.Arduino.ORDER_ATOMIC);
	//Blockly.Arduino.definitions_['md_initnrf24l01'] = '#include<nRF24L01.h>\nNrf24l Mirf = Nrf24l(10, 9);\n'
	//Blockly.Arduino.setups_['md_initnrf24l01'] ='\t'+'Serial.begin(9600);\nMirf.spi = &MirfHardwareSpi;\nMirf.init();\nMirf.channel = 90;\nMirf.config();\n'
  var code = 'Mirf.getData('+value_md_nrfdatasss+'); \n';
 return code;
};
//����ʮ�ĸ�ͼ�ο�ת��ΪC���� NRF24L01�������ݵ�ַvalue
Blockly.Arduino.md_nrf24l01receive = function(){
  var value_address = Blockly.Arduino.valueToCode(this,'address',Blockly.Arduino.ORDER_ATOMIC);
   Blockly.Arduino.definitions_['md_nrf24l01receive'] = 'byte value;\n'
  Blockly.Arduino.setups_['setup_md_setup1'] ='Serial.begin(9600);\n Mirf.spi = &MirfHardwareSpi;\n  Mirf.init();\n  Mirf.setRADDR((byte *)\"'+value_address+'\");\n   Mirf.payload = sizeof(value);\n  Mirf.channel = 90; \n  Mirf.config();\n  Serial.println("Listening...");\n';
 var code = 'while (Mirf.dataReady()) {\n    Mirf.getData(&value);\n    Serial.print("Got MotorDriver data: ");\n   Serial.println(value);\n}\n';
  return code; //��codeΪ����ʽʱ�ô˷��ط�ʽ
};
//����ʮ����ͼ�ο�ת��ΪC���� NRF24L01���ݲ�Ϊ��
Blockly.Arduino.md_NRF24L01isnotnull = function(){
 var code = 'NrfData != NULL';
 return [code, Blockly.Arduino.ORDER_ATOMIC];
};
//����ʮ����ͼ�ο�ת��ΪC���� ��ȡNRF24L01����
Blockly.Arduino.md_getNRF24L01 = function(){
 var code = 'NrfData';
 return [code, Blockly.Arduino.ORDER_ATOMIC];
};
//����ʮ�߸�ͼ�ο�ת��ΪC���� PS2�ֱ���ʼ��
Blockly.Arduino.md_PS2init = function(){
	Blockly.Arduino.definitions_['object10'] = '#include<PS2X_lib.h>\nPS2X *ps2x;\n'
	Blockly.Arduino.setups_['setup_PS2init'] ='\t'+'ps2x = mMotorDriver.getSensor(E_PS2X);\n'
 var code = 'static int vibrate = 0;\nbyte PSS_X = 0,PSS_Y = 0;\nps2x->read_gamepad(false, vibrate);\n';
 return code;
};
//����ʮ�˸�ͼ�ο�ת��ΪC���� PS2�������£�������
Blockly.Arduino.md_WhichPS2KeyPressed = function(){
 var code = 'ps2x->ButtonDataByte()';
 return [code, Blockly.Arduino.ORDER_ATOMIC];
};

//���ڶ�ʮ��ͼ�ο�ת��ΪC���� ps2�ֱ����� ������value
Blockly.Arduino.md_ps2keypress = function(){
 var dropdown_PS2keys = this.getFieldValue('PS2keys');
 var code = 'ps2x->Button('+dropdown_PS2keys+')';
 return [code, Blockly.Arduino.ORDER_ATOMIC];
};
//���ڶ�ʮһ��ͼ�ο�ת��ΪC���� ps2�ֱ��ɿ� ������value
Blockly.Arduino.md_ps2keyunpress = function(){
	 var dropdown_PS2keys = this.getFieldValue('PS2keys');
	  var code = 'ps2x->mPs2x->ButtonReleased('+dropdown_PS2keys+')';
 return [code, Blockly.Arduino.ORDER_ATOMIC];
};
//���ڶ�ʮ����ͼ�ο�ת��ΪC���� ��ȡҡ��ֵ��������
Blockly.Arduino.md_ps2getvibrate = function(){
 var dropdown_Vibrate = this.getFieldValue('Vibrate');
 var code = 'ps2x->Analog('+dropdown_Vibrate+')';
 return [code, Blockly.Arduino.ORDER_ATOMIC];
};
//���ڶ�ʮ����ͼ�ο�ת��ΪC���� ��ȡҡ�˽Ƕȣ�������
Blockly.Arduino.md_ps2getvibrate2 = function(){
 var dropdown_Vibrate2 = this.getFieldValue('Vibrate2');
 var code = 'ps2x->'+dropdown_Vibrate2+''
 return [code, Blockly.Arduino.ORDER_ATOMIC];
};
//���ڶ�ʮ����ͼ�ο�ת��ΪC���� ��ȡps2״̬
Blockly.Arduino.md_ps2status = function(){
 var code = 'ps2x.read_gamepad(false, 0);\n';
 return code;
};
//���ڶ�ʮ�ĸ�ͼ�ο�ת��ΪC���� ���� �ӿ�����  �Ƕ�value
Blockly.Arduino.md_initservo = function(){
	var dropdown_Servoports = this.getFieldValue('Servoports');
	//var value_angle = Blockly.Arduino.valueToCode(this,'angle',Blockly.Arduino.ORDER_ATOMIC);
	//Blockly.Arduino.setups_['setup_md_setup5'] ='\t'+'mMotorDriver.begin(50);\n'
	//Blockly.Arduino.definitions_['object666'+dropdown_Servoports+''] = 'Emakefun_Servo *servo'+dropdown_Servoports+' = mMotorDriver.getServo('+dropdown_Servoports+');\n'
	Blockly.Arduino.setups_['setup_md_setup5'] ='\t'+'mMotorDriver.begin(50);\n'
	Blockly.Arduino.definitions_['object66'+dropdown_Servoports+''] = 'Emakefun_Servo *servo'+dropdown_Servoports+' = mMotorDriver.getServo('+dropdown_Servoports+');\n'
 var code = '';
 return code;
};
Blockly.Arduino.md_servo = function(){
	var dropdown_Servoports = this.getFieldValue('Servoports');
	var value_angle = Blockly.Arduino.valueToCode(this,'angle',Blockly.Arduino.ORDER_ATOMIC);

 var code = ' servo'+dropdown_Servoports+'->writeServo('+value_angle+');\n';
 return code;
};

Blockly.Arduino.md_readservo = function(){
var dropdown_Servoports = this.getFieldValue('Servoports');
 var code = ' servo'+dropdown_Servoports+'->readDegrees()';
 return [code, Blockly.Arduino.ORDER_ATOMIC];
};
//��������ʼ��
Blockly.Arduino.md_m4init = function () {
    var dropdown_M4Ports1 = this.getFieldValue('M4Ports1');
    var dropdown_M4Ports2 = this.getFieldValue('M4Ports2');
    var dropdown_M4Ports3 = this.getFieldValue('M4Ports3');
    var dropdown_M4Ports4 = this.getFieldValue('M4Ports4');
    Blockly.Arduino.definitions_['md_m4init'] = '#include<Emakefun_MotorDriver.h>\n'
    Blockly.Arduino.definitions_['Amd_m4init2'] = '\t' + 'Emakefun_DCMotor *DCmotor_'+dropdown_M4Ports1+' = mMotorDriver.getMotor(' + dropdown_M4Ports1 + ');\n    Emakefun_DCMotor *DCmotor_'+dropdown_M4Ports2+' = mMotorDriver.getMotor(' + dropdown_M4Ports2 + ');\n    Emakefun_DCMotor *DCmotor_'+dropdown_M4Ports3+' = mMotorDriver.getMotor(' + dropdown_M4Ports3 + ');\n    Emakefun_DCMotor *DCmotor_'+dropdown_M4Ports4+' = mMotorDriver.getMotor(' + dropdown_M4Ports4 + ');\n'
    Blockly.Arduino.setups_['md_m4init'] ='\t'+'mMotorDriver.begin(50);\n'
    var code = ''
    return code;
};
//ǰ��
Blockly.Arduino.md_m4goforward = function () {
    var value_m4speed1 = Blockly.Arduino.valueToCode(this, 'm4speed1', Blockly.Arduino.ORDER_ATOMIC);
    var code = '    LeftFoward->setSpeed(' + value_m4speed1 + ');\n    RightFoward->setSpeed(' + value_m4speed1 + ');\n    LeftBackward->setSpeed(' + value_m4speed1 + ');\n    RightBackward->setSpeed(' + value_m4speed1 + ');\n    LeftFoward->run(FORWARD);\n    RightFoward->run(FORWARD);\n    LeftBackward->run(FORWARD);\n    RightBackward->run(FORWARD);\n';
    return code;
};
//����
Blockly.Arduino.md_m4backforward = function () {
    var value_m4speed2 = Blockly.Arduino.valueToCode(this, 'm4speed2', Blockly.Arduino.ORDER_ATOMIC);
    var code = '    LeftFoward->setSpeed(' + value_m4speed2 + ');\n    RightFoward->setSpeed(' + value_m4speed2 + ');\n    LeftBackward->setSpeed(' + value_m4speed2 + ');\n    RightBackward->setSpeed(' + value_m4speed2 + ');\n    LeftFoward->run(BACKWARD);\n    RightFoward->run(BACKWARD);\n    LeftBackward->run(BACKWARD);\n    RightBackward->run(BACKWARD);\n';
    return code;
};
//��ת
Blockly.Arduino.md_m4turnleft = function () {
    var value_m4speed3 = Blockly.Arduino.valueToCode(this, 'm4speed3', Blockly.Arduino.ORDER_ATOMIC);
    var code = '    LeftFoward->setSpeed(' + value_m4speed3 + '/2);\n    RightFoward->setSpeed(' + value_m4speed3 + ');\n    LeftBackward->setSpeed(' + value_m4speed3 + '/2);\n    RightBackward->setSpeed(' + value_m4speed3 + ');\n    LeftFoward->run(FORWARD);\n    RightFoward->run(FORWARD);\n    LeftBackward->run(FORWARD);\n    RightBackward->run(FORWARD);\n';
    return code;
};
//��ת
Blockly.Arduino.md_m4turnright = function () {
    var value_m4speed4 = Blockly.Arduino.valueToCode(this, 'm4speed4', Blockly.Arduino.ORDER_ATOMIC);
    var code = '    LeftFoward->setSpeed(' + value_m4speed4 + ');\n    RightFoward->setSpeed(' + value_m4speed4 + '/2);\n    LeftBackward->setSpeed(' + value_m4speed4 + ');\n    RightBackward->setSpeed(' + value_m4speed4 + '/2);\n    LeftFoward->run(FORWARD);\n    RightFoward->run(FORWARD);\n    LeftBackward->run(FORWARD);\n    RightBackward->run(FORWARD);\n';
    return code;
};
//������
Blockly.Arduino.md_m4turnlefts = function () {
    var value_m4speed33 = Blockly.Arduino.valueToCode(this, 'm4speed33', Blockly.Arduino.ORDER_ATOMIC);
    var code = '    LeftFoward->setSpeed(' + value_m4speed33 + ');\n    RightFoward->setSpeed(' + value_m4speed33 + ');\n    LeftBackward->setSpeed(' + value_m4speed33 + ');\n    RightBackward->setSpeed(' + value_m4speed33 + ');\n    LeftFoward->run(BACKWARD);\n    RightFoward->run(FORWARD);\n    LeftBackward->run(BACKWARD);\n    RightBackward->run(FORWARD);\n';
    return code;
};
//������
Blockly.Arduino.md_m4turnrights = function () {
    var value_m4speed44 = Blockly.Arduino.valueToCode(this, 'm4speed44', Blockly.Arduino.ORDER_ATOMIC);
    var code = '    LeftFoward->setSpeed(' + value_m4speed44 + ');\n    RightFoward->setSpeed(' + value_m4speed44 + ');\n    LeftBackward->setSpeed(' + value_m4speed44 + ');\n    RightBackward->setSpeed(' + value_m4speed44 + ');\n    LeftFoward->run(FORWARD);\n    RightFoward->run(BACKWARD);\n    LeftBackward->run(FORWARD);\n    RightBackward->run(BACKWARD);\n';
    return code;
};
//��ʻ�Ƕ�
Blockly.Arduino.md_m4godegree = function () {
    var value_m4godegree = Blockly.Arduino.valueToCode(this, 'm4godegree', Blockly.Arduino.ORDER_ATOMIC);
    var value_m4gospeed = Blockly.Arduino.valueToCode(this, 'm4gospeed', Blockly.Arduino.ORDER_ATOMIC);
    if (value_m4godegree >= 0 && value_m4godegree <= 90) {
        var code = '    LeftFoward->setSpeed(' + value_m4gospeed + ');\n    RightFoward->setSpeed(' + value_m4gospeed + ' * ((float)(' + value_m4godegree + ') / 90));\n    LeftBackward->setSpeed(' + value_m4gospeed + ');\n    RightBackward->setSpeed(' + value_m4gospeed + ' * ((float)(' + value_m4godegree + ') / 90));\n    LeftFoward->run(FORWARD);\n    RightFoward->run(FORWARD);\n    LeftBackward->run(FORWARD);\n    RightBackward->run(FORWARD);\n';
    } else if (value_m4godegree > 90 && value_m4godegree <= 180) {
        var code = '    LeftFoward->setSpeed(' + value_m4gospeed + ' * (float)(180 - ' + value_m4godegree + ') / 90);\n    RightFoward->setSpeed(' + value_m4gospeed + ');\n    LeftBackward->setSpeed(' + value_m4gospeed + ' * (float)(180 - ' + value_m4godegree + ') / 90);\n    RightBackward->setSpeed(' + value_m4gospeed + ');\n    LeftFoward->run(FORWARD);\n    RightFoward->run(FORWARD);\n    LeftBackward->run(FORWARD);\n    RightBackward->run(FORWARD);\n';
    } else if (value_m4godegree > 180 && value_m4godegree <= 270) {
        var code = '    LeftFoward->setSpeed(' + value_m4gospeed + ' * ((float)(' + value_m4godegree + ' - 180) / 90));\n    RightFoward->setSpeed(' + value_m4gospeed + ');\n    LeftBackward->setSpeed(' + value_m4gospeed + ' * ((float)(' + value_m4godegree + ' - 180) / 90));\n    RightBackward->setSpeed(' + value_m4gospeed + ');\n    LeftFoward->run(BACKWARD);\n    RightFoward->run(BACKWARD);\n    LeftBackward->run(BACKWARD);\n    RightBackward->run(BACKWARD);\n';
    } else if (value_m4godegree > 270 && value_m4godegree <= 360) {
        var code = '    LeftFoward->setSpeed(' + value_m4gospeed + ');\n    RightFoward->setSpeed(' + value_m4gospeed + ' * (float)(360 - ' + value_m4godegree + ') / 90);\n    LeftBackward->setSpeed(' + value_m4gospeed + ');\n    RightBackward->setSpeed(' + value_m4gospeed + ' * (float)(360 - ' + value_m4godegree + ') / 90);\n    LeftFoward->run(BACKWARD);\n    RightFoward->run(BACKWARD);\n    LeftBackward->run(BACKWARD);\n    RightBackward->run(BACKWARD);\n';
    } else {
        var code = '    LeftFoward->run(BRAKE);\n    RightFoward->run(BRAKE);\n    LeftBackward->run(BRAKE);\n    RightBackward->run(BRAKE);\n';
    }

    return code;
};
//ֹͣ
Blockly.Arduino.md_m4stop = function () {
    var code = '    LeftFoward->run(BRAKE);\n    RightFoward->run(BRAKE);\n    LeftBackward->run(BRAKE);\n    RightBackward->run(BRAKE);\n';
    return code;
};
Blockly.Arduino.md_bluetoothinit = function () {
    //var dropdown_DCPorts = this.getFieldValue('DCPorts');
    Blockly.Arduino.definitions_['md_bluetoothinit'] = '#include<ProtocolParser.h>\n#include<BluetoothHandle.h>\nProtocolParser *mProtocol = new ProtocolParser();\n'
    var code = ''
    return code;
};
Blockly.Arduino.md_receivedata = function () {
    var code = 'mProtocol->RecevData();\n';
    return code;
};
Blockly.Arduino.md_receiveddata = function () {
    var code = 'mProtocol->ParserPackage()';
    return [code, Blockly.Arduino.ORDER_ATOMIC]; //��codeΪ����ʽʱ�ô˷��ط�ʽ
};
Blockly.Arduino.md_bluetoothKeyPress = function () {
    var dropdown_BLUETOOTHKEY = this.getFieldValue('BLUETOOTHKEY');
    var code = 'mProtocol->GetBluetoothButton()==' + dropdown_BLUETOOTHKEY + '';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};
Blockly.Arduino.md_bluetoothstyle = function () {
    var dropdown_BLUETOOTHSTYLE = this.getFieldValue('BLUETOOTHSTYLE');
    var code = 'mProtocol->GetRobotControlFun()==' + dropdown_BLUETOOTHSTYLE + '';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};
Blockly.Arduino.md_bluetoothgetdegree = function () {
    var code = 'mProtocol->GetRobotDegree()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};
Blockly.Arduino.md_bluetoothgetspeed = function () {
    var code = 'mProtocol->GetRobotSpeed()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};
Blockly.Arduino.md_nrfinit = function () {
	Blockly.Arduino.definitions_['md_nrfinit'] = '#include<ProtocolParser.h>\n#include<BluetoothHandle.h>\n#include<nRF24L01.h>\nNrf24l  *Nrf24L01 = mMotorDriver.getSensor(E_NRF24L01);\nProtocolParser *mProtocol = new ProtocolParser();\n';
	 var value_nrfadd = Blockly.Arduino.valueToCode(this, 'nrfadd', Blockly.Arduino.ORDER_ATOMIC);
	 Blockly.Arduino.setups_['md_nrfinit'] ='Nrf24L01->setRADDR('+value_nrfadd+');\n'
    var code = 'byte value[12] = {0};\nbool godata = false;\n';
    return code;
};

Blockly.Arduino.md_nrfdataready = function () {
    var code = 'Nrf24L01->dataReady()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.md_nrfvalue = function () {
	 //var value_nrfadd = Blockly.Arduino.valueToCode(this, 'nrfadd', Blockly.Arduino.ORDER_ATOMIC);
    var code = 'byte value[12] = {0};\nbool godata = false;\n';
    return code;
};

Blockly.Arduino.md_nrfgetdata = function () {
	 //var value_nrfadd = Blockly.Arduino.valueToCode(this, 'nrfadd', Blockly.Arduino.ORDER_ATOMIC);
    var code = 'Nrf24L01->getData(value);\nmProtocol->RecevData(value, 12);\n';
    return code;
};

Blockly.Arduino.md_nrfgetpackage = function () {
    var code = 'mProtocol->ParserPackage()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.md_nrfnewob = function () {
	 //var value_nrfadd = Blockly.Arduino.valueToCode(this, 'nrfadd', Blockly.Arduino.ORDER_ATOMIC);
    var code = 'E_CONTOROL_FUNC fun = mProtocol->GetRobotControlFun();\n';
    return code;
};

Blockly.Arduino.md_nrfdatafun = function () {
	 var dropdown_datafun = this.getFieldValue('datafun');
    var code = 'mProtocol->GetRobotControlFun() == '+dropdown_datafun+'';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.md_nrfbuttons = function () {
	 var dropdown_nrfbuttons = this.getFieldValue('nrfbuttons');
    var code = 'mProtocol->GetBluetoothButton() == '+dropdown_nrfbuttons+'';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.md_nrfgetdegree = function () {
	 //var value_nrfadd = Blockly.Arduino.valueToCode(this, 'nrfadd', Blockly.Arduino.ORDER_ATOMIC);
    var code = 'mProtocol->GetRobotDegree()';
     return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.md_nrfgetspeed = function () {
	 //var value_nrfadd = Blockly.Arduino.valueToCode(this, 'nrfadd', Blockly.Arduino.ORDER_ATOMIC);
    var code = 'mProtocol->GetRobotSpeed()';
   return [code, Blockly.Arduino.ORDER_ATOMIC];
};
