#include "Panther_Tank.h"
#include "ProtocolParser.h"
#include "Sounds.h"
#include "KeyMap.h"
#include "debug.h"

//MotorShieldBoard V3.0
Tank::Tank(ProtocolParser *Package): SmartCar("PantherTank", 0x01, E_BLUETOOTH_CONTROL)
{
  mMotorDriver = new Emakefun_MotorDriver();
  SetStatus(E_STOP);
  mProtocolPackage = Package;
}

Tank::~Tank()
{
  delete mMotorDriver;
  delete DCMotor_1;
  delete DCMotor_2;
  delete IR;
  delete Buzzer;
  delete Rgb;
  delete UT;
  delete  Ps2x;
  delete Nrf;
  delete mServo1;
  delete mServo2;
  delete mServo3;
  delete mServo4;
  delete mServo5;
  delete mServo6;
}

void Tank::init(void)
{
  DCMotor_1 = mMotorDriver->getMotor(1);
  DCMotor_2 = mMotorDriver->getMotor(2);
  DCMotor_3 = mMotorDriver->getMotor(3);
  DCMotor_4 = mMotorDriver->getMotor(4);
  delay(100);
  mMotorDriver->begin(50);
}
#if ARDUINO > 10609
void Tank::Move(int directions = 1)
#else
void Tank::Move(int directions)
#endif
{
  if (directions == 1) {
    Serial.println(1);
    GoForward();
  } else if (directions == 2) {
    Serial.println(2);
    GoBack();
  } else if (directions == 3) {
    Serial.println(3);
    TurnLeft();
  } else if (directions == 4) {
    Serial.println(4);
    TurnRight();
  } else {
    KeepStop();
  }
}

void Tank::SetSpeed(int s)
{
  if (s > 100) {
    Speed = 100;
    return;
  } else if (s < 0) {
    Speed = 0;
    return;
  }
  Speed = s;
  DCMotor_1->setSpeed((Speed / 10) * 25.5);
  DCMotor_2->setSpeed((Speed / 10) * 25.5);
  DCMotor_3->setSpeed((Speed / 10) * 25.5);
  DCMotor_4->setSpeed((Speed / 10) * 25.5);
  if (GetStatus() == E_STOP) 
    KeepStop();
}

void Tank::GoForward(void)
{
  SetStatus(E_FORWARD);
  SetSpeed(Speed);
  DCMotor_1->run(FORWARD);
  DCMotor_2->run(FORWARD);
  DCMotor_3->run(FORWARD);
  DCMotor_4->run(FORWARD);
}

void Tank::GoBack(void)
{
  SetStatus(E_BACK);
  SetSpeed(Speed);
  DCMotor_1->run(BACKWARD);
  DCMotor_2->run(BACKWARD);
  DCMotor_3->run(BACKWARD);
  DCMotor_4->run(BACKWARD);
}
void Tank::KeepStop(void)
{
  SetStatus(E_STOP);
  DCMotor_1->setSpeed(0);
  DCMotor_2->setSpeed(0);
  DCMotor_3->setSpeed(0);
  DCMotor_4->setSpeed(0);
  DCMotor_1->run(BRAKE);
  DCMotor_2->run(BRAKE);
  DCMotor_1->run(BRAKE);
  DCMotor_2->run(BRAKE);
}

void Tank::TurnLeft(void)
{
  SetStatus(E_LEFT);
  SetSpeed(Speed);
  DCMotor_1->run(BACKWARD);
  DCMotor_2->run(FORWARD);
  DCMotor_3->run(BACKWARD);
  DCMotor_4->run(FORWARD);
}

void Tank::TurnRight(void)
{
  SetStatus(E_RIGHT);
  SetSpeed(Speed);
  DCMotor_1->run(FORWARD);
  DCMotor_2->run(BACKWARD);
  DCMotor_3->run(FORWARD);
  DCMotor_4->run(BACKWARD);
}
void Tank::LeftLateral(void)
{
  SetStatus(E_LEFT_LATERALA);
  SetSpeed(Speed);
  DCMotor_1->run(BACKWARD);
  DCMotor_2->run(FORWARD);
  DCMotor_3->run(FORWARD);
  DCMotor_4->run(BACKWARD);
}

void Tank::RightLateral(void)
{
  SetStatus(E_RIGHT_LATERALA);
  SetSpeed(Speed);
  DCMotor_1->run(FORWARD);
  DCMotor_2->run(BACKWARD);
  DCMotor_3->run(BACKWARD);
  DCMotor_4->run(FORWARD);
}

void Tank::Drive(void)
{
  Drive(Degree);
}

void Tank::Drive(int degree)
{
  DEBUG_LOG(DEBUG_LEVEL_INFO, "degree = %d speed = %d\n", degree, Speed);
  byte value = (Speed / 10) * 25.5;	 //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
  float f;
  if (degree >= 0 && degree <= 90) {
    f = (float)(degree) / 90;
    if (degree <= 5) {
      SetStatus(E_RIGHT);
    } else  if (degree >= 85) {
      SetStatus(E_FORWARD);
    }
    DCMotor_1->setSpeed(value);
    DCMotor_2->setSpeed((float)(value * f));
    DCMotor_3->setSpeed(value);
    DCMotor_4->setSpeed((float)(value * f));
    DCMotor_1->run(FORWARD);
    DCMotor_2->run(FORWARD);
    DCMotor_3->run(FORWARD);
    DCMotor_4->run(FORWARD);
  } else if (degree > 90 && degree <= 180) {
    f = (float)(180 - degree) / 90;
    if (degree <= 95) {
      SetStatus(E_FORWARD);
    } else  if (degree >= 175) {
      SetStatus(E_LEFT);
    }
    DCMotor_1->setSpeed((float)(value * f));
    DCMotor_2->setSpeed(value);
    DCMotor_3->setSpeed((float)(value * f));
    DCMotor_4->setSpeed(value);
    DCMotor_1->run(FORWARD);
    DCMotor_2->run(FORWARD);
    DCMotor_3->run(FORWARD);
    DCMotor_4->run(FORWARD);
  } else if (degree > 180 && degree <= 270) {
    f = (float)(degree - 180) / 90;
    if (degree <= 185) {
      SetStatus(E_LEFT);
    } else  if (degree >= 265) {
      SetStatus(E_BACK);
    }
    DCMotor_1->setSpeed((float)(value * f));
    DCMotor_2->setSpeed(value);
    DCMotor_3->setSpeed((float)(value * f));
    DCMotor_4->setSpeed(value);
    DCMotor_1->run(BACKWARD);
    DCMotor_2->run(BACKWARD);
    DCMotor_3->run(BACKWARD);
    DCMotor_4->run(BACKWARD);
  } else if (degree > 270 && degree <= 360) {
    f = (float)(360 - degree) / 90;
    if (degree <= 275) {
      SetStatus(E_BACK);
    } else  if (degree >= 355) {
      SetStatus(E_RIGHT);
    }
    DCMotor_1->setSpeed(value);
    DCMotor_2->setSpeed((float)(value * f));
    DCMotor_3->setSpeed(value);
    DCMotor_4->setSpeed((float)(value * f));
    DCMotor_1->run(BACKWARD);
    DCMotor_2->run(BACKWARD);
    DCMotor_3->run(BACKWARD);
    DCMotor_4->run(BACKWARD);
  }
  else {
    KeepStop();
    return;
  }
}

void Tank::InitIrPin(void)
{
  IR = mMotorDriver->getSensor(E_IR);
}

int Tank::GetIrKey(void)
{
  byte irKeyCode;
  if (irKeyCode = IR->mIrRecv->getCode()) {
    return ((E_IR_KEYCODE)IR->mIrRecv->getIrKey(irKeyCode));
  } return (NULL);
}

void Tank::InitBuzzerPin(void)
{
  Buzzer = mMotorDriver->getSensor(E_BUZZER);
}

void Tank::sing(byte songName)
{
  Buzzer->Sing(songName);
}

void Tank::PianoSing(ST_MUSIC_TYPE music)
{
  Buzzer->mBuzzer->_tone(music.note, music.beat, 2);
}

void Tank::InitRgbPin(void)
{
  Rgb = mMotorDriver->getSensor(E_RGB);
}

void Tank::SetRgbColor(E_RGB_INDEX index , long Color)
{
  Rgb->SetRgbColor(index, Color);
}

void Tank::LightOff(void)
{
  Rgb->SetRgbColor(E_RGB_ALL, RGB_BLACK);
}

void Tank::SetRgbEffect(E_RGB_INDEX index, long Color, uint8_t effect)
{
  if (Rgb != NULL) {
    switch ((E_RGB_EFFECT)effect) {
      case E_EFFECT_BREATHING:
        for (long i = 0; i < 256; i++) {
          SetRgbColor(index, (i << 16) | (i << 8) | i);
          delay((i < 18) ? 18 : (256 / i));
        }
        for (long i = 255; i >= 0; i--) {
          SetRgbColor(index, (i << 16) | (i << 8) | i);
          delay((i < 18) ? 18 : (256 / i));
        }
        break;
      case E_EFFECT_FLASH:
        for (byte i = 0; i < 6; i++) {
          SetRgbColor(index, Color);
          delay(100);
          SetRgbColor(index, 0);
          delay(100);
        }
        break;
    }
  }
}

void Tank::InitUltrasonicPin(void)
{
  UT = mMotorDriver->getSensor(E_ULTRASONIC);
}

byte Tank::GetUltrasonicValue(byte direction)
{
  byte distance;
  if (direction == 0) {
    SetServoDegree(1, 90);
    distance = UT->GetUltrasonicDistance();
  } else if (direction == 1) {
    SetServoDegree(1, 180);
    distance = UT->GetUltrasonicDistance();
    delay(400);
    SetServoDegree(1, 90);
  } else if (direction == 2) {
    SetServoDegree(1, 15);
    distance = UT->GetUltrasonicDistance();
    delay(400);
    SetServoDegree(1, 90);
  }
  return distance;
}

void Tank::InitServoPin(void)
{
  mServo1 = mMotorDriver->getServo(1);
  mServo2 = mMotorDriver->getServo(2);
  mServo3 = mMotorDriver->getServo(3);
  mServo4 = mMotorDriver->getServo(4);
  mServo5 = mMotorDriver->getServo(5);
  mServo6 = mMotorDriver->getServo(6);
}


void Tank::SetServoBaseDegree(uint8_t base)
{
  ServoBaseDegree = base;
}

void Tank::SetServoDegree(byte pin , byte Angle)
{
  int Degree = Angle;
  int servo_degree;
  ServoPin = pin;
  if (Degree > 360) {
    return;
  }
  if (Degree == 90 || Degree == 270) {
    servo_degree = ServoBaseDegree;
  } else if (Degree >= 0 && Degree <= 180) {
    servo_degree = ServoBaseDegree - 90 + Degree;   // 180-degree-diff
  }
  if (ServoPin == 1)
    mServo1->writeServo(servo_degree);
  else if (ServoPin == 2)
    mServo2->writeServo(Angle);
  else if (ServoPin == 3)
    mServo3->writeServo(Angle);
  else if (ServoPin == 4)
    mServo4->writeServo(Angle);
  else if (ServoPin == 5)
    mServo5->writeServo(Angle);
  else if (ServoPin == 6)
    mServo6->writeServo(Angle);
}

void Tank::InitPs2xPin(void)
{
  Ps2x = mMotorDriver->getSensor(E_PS2X);
}

int Tank::GetPs2xKeyValue(void)
{
  static int vibrate = 0;
  Ps2x->mPs2x->read_gamepad(false, vibrate);
  if (Ps2x->mPs2x->ButtonDataByte()) {
    if (Ps2x->mPs2x->Button(PSB_PAD_UP)) {     //will be TRUE as long as button is pressed
      return PSB_PAD_UP;
    }
    else if (Ps2x->mPs2x->Button(PSB_PAD_RIGHT)) {
      return PSB_PAD_RIGHT;
    }
    else if (Ps2x->mPs2x->Button(PSB_PAD_LEFT)) {
      return PSB_PAD_LEFT;
    }
    else if (Ps2x->mPs2x->Button(PSB_PAD_DOWN)) {
      return PSB_PAD_DOWN;
    }
    else if (Ps2x->mPs2x->Button(PSB_CROSS)) {
      return PSB_CROSS;
    }
    else if (Ps2x->mPs2x->Button(PSB_TRIANGLE)) {
      return PSB_TRIANGLE;
    }
    else if (Ps2x->mPs2x->Button(PSB_CIRCLE)) {
      return PSB_CIRCLE;
    }
    else if (Ps2x->mPs2x->Button(PSB_SQUARE)) {
      return PSB_SQUARE;
    }
    else if (Ps2x->mPs2x->Button(PSB_L1)) {
      return PSB_L1;
    }
    else if (Ps2x->mPs2x->Button(PSB_L2)) {
      return PSB_L2;
    }
    else if (Ps2x->mPs2x->Button(PSB_R1)) {
      return PSB_R1;
    }
    else if (Ps2x->mPs2x->Button(PSB_R2)) {
      return PSB_R2;
    }
  } else
    return NULL;
}

uint16_t Tank::GetPs2xRockerAngle(byte direction)
{
  static int vibrate = 0;
  Ps2x->mPs2x->read_gamepad(false, vibrate);
  if (direction == 1)
    return (Ps2x->mPs2x->LeftHart());
  else if (direction == 2)
    return (Ps2x->mPs2x->RightHart());
}





void Tank::SendUltrasonicData(void)
{
  union
  {
    float d;
    byte data[4];
  } value;
  value.d = GetUltrasonicValue(FRONT);
  SendData.start_code = 0xAA;
  SendData.type = E_PANTHER_TANK;
  SendData.addr = 0x01;
  SendData.function = E_ULTRASONIC;
  SendData.data = value.data;
  SendData.len = 10;
  SendData.end_code = 0x55;
  mProtocolPackage->SendPackage(&SendData, 4);
}
