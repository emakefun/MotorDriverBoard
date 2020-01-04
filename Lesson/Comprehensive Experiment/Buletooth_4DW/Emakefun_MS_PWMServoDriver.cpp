#include "Emakefun_MS_PWMServoDriver.h"
#include <Wire.h>
#if defined(ARDUINO_SAM_DUE)
 #define WIRE Wire1
#else
 #define WIRE Wire
#endif

Emakefun_MS_PWMServoDriver::Emakefun_MS_PWMServoDriver(uint8_t addr) {
  _i2caddr = addr;
}

void Emakefun_MS_PWMServoDriver::begin(void) {
 WIRE.begin();
 reset();
}


void Emakefun_MS_PWMServoDriver::reset(void) {
 write8(PCA9685_MODE1, 0x0);
}

void Emakefun_MS_PWMServoDriver::setPWMFreq(float freq) {
  //Serial.print("Attempting to set freq ");
  //Serial.println(freq);
  
  freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).

  float prescaleval = 25000000;
  prescaleval /= 4096;
  prescaleval /= freq;
  prescaleval -= 1;
  //Serial.print("Estimated pre-scale: "); Serial.println(prescaleval);
  uint8_t prescale = floor(prescaleval + 0.5);
  //Serial.print("Final pre-scale: "); Serial.println(prescale);  
  
  uint8_t oldmode = read8(PCA9685_MODE1);
  uint8_t newmode = (oldmode&0x7F) | 0x10; // sleep
  write8(PCA9685_MODE1, newmode); // go to sleep
  write8(PCA9685_PRESCALE, prescale); // set the prescaler
  write8(PCA9685_MODE1, oldmode);
  delay(5);
  write8(PCA9685_MODE1, oldmode | 0xa1);  //  This sets the MODE1 register to turn on auto increment.
                                          // This is why the beginTransmission below was not working.
  //  Serial.print("Mode now 0x"); Serial.println(read8(PCA9685_MODE1), HEX);
}

void Emakefun_MS_PWMServoDriver::setPWM(uint8_t num, uint16_t on, uint16_t off) {
  //Serial.print("Setting PWM "); Serial.print(num); Serial.print(": "); Serial.print(on); Serial.print("->"); Serial.println(off);

  WIRE.beginTransmission(_i2caddr);
#if ARDUINO >= 100
  WIRE.write(LED0_ON_L+4*num);
  WIRE.write(on);
  WIRE.write(on>>8);
  WIRE.write(off);
  WIRE.write(off>>8);
#else
  WIRE.send(LED0_ON_L+4*num);
  WIRE.send((uint8_t)on);
  WIRE.send((uint8_t)(on>>8));
  WIRE.send((uint8_t)off);
  WIRE.send((uint8_t)(off>>8));
#endif
  WIRE.endTransmission();
}

uint8_t Emakefun_MS_PWMServoDriver::read8(uint8_t addr) {
  WIRE.beginTransmission(_i2caddr);
#if ARDUINO >= 100
  WIRE.write(addr);
#else
  WIRE.send(addr);
#endif
  WIRE.endTransmission();

  WIRE.requestFrom((uint8_t)_i2caddr, (uint8_t)1);
#if ARDUINO >= 100
  return WIRE.read();
#else
  return WIRE.receive();
#endif
}

void Emakefun_MS_PWMServoDriver::write8(uint8_t addr, uint8_t d) {
  WIRE.beginTransmission(_i2caddr);
#if ARDUINO >= 100
  WIRE.write(addr);
  WIRE.write(d);
#else
  WIRE.send(addr);
  WIRE.send(d);
#endif
  WIRE.endTransmission();
}
