# MotorDriverBoard
[English](README.md) 中文版

MotorDriverBoard是由 [深圳市易创空间科技有限公司](www.emakefun.com)，专门针对Arduino Uno(兼容Mega2560)机器人，电机驱动，多路舵机控制而研发的一款多功能电机驱动扩展板。本驱动板采用I2C方式控制[PCA9685](./doc/pca9685.pdf)(16路PWM输出芯片)。所以本驱动板电机或者舵机不存在和arduino口的对应关系，是通过I2C扩展PWM控制，详情请见[驱动板原理图]()。
![image]()

## 特点
- 支持4路直流电机，最大驱动电流3A
- 支持驱动8路舵机，带自恢复保险丝，防止舵机堵转
- 支持驱动2路4线步进电机
- 支持4路编码电机
- 板载无源蜂鸣器
- 板载1个RGB全彩灯
- 板载红外接收头
- 1个 i2c接口 、1个PS2X接口、1个Uart(蓝牙/wiif模块)接口 、1个NRF24L01模块接口
- 1个超声波模块接口
- 舵机电源可切换到外部供电
- 软件支持Arduino IDE，Mixly，MagicBlock(Scratch3.0)

## 硬件功能介绍
### 正面
![image]()

### 供电说明
- DC头供电

  

- 接线柱供电

  

- 舵机采用驱动板载DC-DC电源供电

  

- 舵机采用外部供电

## 驱动库使用



## 基础示例程序
[gpiotest](examples/gpiotest/gpiotest.ino) 控制PCA9685输出口当作普通IO口输出高低电平

- gpio.begin(1000);  初始化io口的输出频率为1KHz

- gpio.setPin(1, HIGH);  引脚1输出高电平
- gpio.setPin(1, LOW);  引脚1输出低电平

[pwmtest](examples/pwmtest/pwmtest.ino) 这个示例程序为控制PCA9685输出口输出PWM波形



[dc](examples/dc/dc.ino)4路直流电机测试程序

### 连接方法

[servo](examples/servo/servo.ino)
- 八路舵机测试程序

[stepper](examples/stepper/stepper.ino) 步进电机测试程序

- Emakefun_StepperMotor *StepperMotor_1 = mMotorDriver.getStepper(1, 200);  //初始化步进电机1，42步进电机走一步是1.8度，所以一圈的步数为200

- StepperMotor_1->setSpeed(100);  //设置步进电机没分钟转的圈数为100圈

- StepperMotor_1->step(200, FORWARD, DOUBLE); //驱动步进电机按 DOUBLE(全步)的方式，FORWARD（前进）200步。

  步进电机的驱动方式 全步DOUBLE、单步SINGLE、1/2步进INTERLEAVE、1/16步进MICROSTEP这四种驱动方式（步进电机的驱动原理请查阅相关资料）。建议用1/16步进的模式。

  

## 综合应用

[PS2控制四驱小车]()

[PS2控制四驱麦克纳姆轮小车]()

[PS2控制四驱小车加机械臂]()

[蓝牙（WIFI）控制四驱小车]()

## 图像化编程块说明

### MotorDriverBoard 编程图形块
#### [mBlock5]()
![image]()
#### 米思齐
![image]()
#### MagicBlock
![image]()

