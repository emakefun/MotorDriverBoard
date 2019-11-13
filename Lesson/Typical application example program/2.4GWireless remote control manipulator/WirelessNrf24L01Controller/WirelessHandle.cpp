#include "WirelessHandle.h"
#include "Wire.h"

#include "debug.h"

#undef abs

//#undef round

WirelessHandle::WirelessHandle(E_CONTROL_MODE mode)
{
    Cbutton_reg = portInputRegister(3);
    Cmode_reg = portModeRegister(3);
    Dbutton_reg = portInputRegister(4);
    Dmode_reg = portModeRegister(4);
    Bbutton_reg = portInputRegister(2);
    Bmode_reg = portModeRegister(2);
    *Bmode_reg &= ~BUTTON_BIT_BMASK;  //set all gpio input
    *Bbutton_reg |= BUTTON_BIT_BMASK;
    *Cmode_reg &= ~BUTTON_BIT_CMASK;  //set all gpio input
    *Cbutton_reg |= BUTTON_BIT_CMASK;
    *Dmode_reg &= ~BUTTON_BIT_DMASK;  //set all gpio input
    *Dbutton_reg |= BUTTON_BIT_DMASK;
    buttons = 0;
    buttonsB = buttonsC = buttonsD = 0;
    last_buttons = 0;
    pinMode(MODE_GREEN_LED, OUTPUT);
    pinMode(SELEC_BLUE_LED, OUTPUT);
    SetControlMode(mode);
}

void WirelessHandle::SetControlMode(E_CONTROL_MODE mode)
{
    control_mode = mode;
    if (mode == E_NRF24L01_MODE) {
         digitalWrite(MODE_GREEN_LED, LOW);  
    } else {
         digitalWrite(MODE_GREEN_LED, HIGH);
    }
}

E_CONTROL_MODE WirelessHandle::GetControlMode(void)
{
    return control_mode;
}

void WirelessHandle::SetControlSelect(E_CONTROL_SELECT mode)
{
    control_select = mode;
    if (mode == E_WIRELESS_CONTROL_MODE) {
         digitalWrite(SELEC_BLUE_LED, HIGH);  
    } else {
         digitalWrite(SELEC_BLUE_LED, LOW);
    }
}

E_CONTROL_SELECT WirelessHandle::GetControlSelect(void)
{
    return control_select;
}

void WirelessHandle::InitNrf24l01(byte CE, byte CSN)
{
    mNrf24L01 = new Nrf24l(CE, CSN);
    mNrf24L01->spi = &MirfHardwareSpi;
    mNrf24L01->init();
    // Set your own address (sender address) using 5 characters
    //mNrf24L01->setRADDR((byte *)"WirelessHandle");
    mNrf24L01->channel = 90;   //Set the channel used
    mNrf24L01->config();
}

void WirelessHandle::InitMpu6050(void)
{
    struct RAW_type accel_self_enable , accel_self_diable;
    int32_t ax_zero = 0, ay_zero = 0, az_zero = 0, gx_zero = 0, gy_zero = 0, gz_zero = 0;

    Wire.begin();
    accelgyro.initialize();
    delay(300) ;
    accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
    // enable Accel Self Test
    accelgyro.setAccelXSelfTest(1); // enable accel self test
    accelgyro.setAccelYSelfTest(1);
    accelgyro.setAccelZSelfTest(1);
    delay(100);
    accel_self_enable.x = accelgyro.getAccelXSelfTestDate();
    accel_self_enable.y = accelgyro.getAccelYSelfTestDate();
    accel_self_enable.z = accelgyro.getAccelZSelfTestDate();

    accelgyro.setAccelXSelfTest(0); // disable accel self test
    accelgyro.setAccelYSelfTest(0);
    accelgyro.setAccelZSelfTest(0);
    accel_self_diable.x = accelgyro.getAccelXSelfTestDate();
    accel_self_diable.y = accelgyro.getAccelYSelfTestDate();
    accel_self_diable.z = accelgyro.getAccelZSelfTestDate();

    accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
    /* get zero accel/gyro value */
    for (byte i = 0; i < 200; i++) {
       accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); //get raw accel/gyro measurements 
       ax_zero += az;
       ay_zero += ay;
       az_zero += az;
       gx_zero += gx;
       gy_zero += gy;
       gz_zero += gz;
    }
    accel_zero_offsent.x = ax_zero/200;
    accel_zero_offsent.y = ay_zero/200;
    accel_zero_offsent.z = az_zero/200;
    gyro_zero_offsent.x = gx_zero/200;
    gyro_zero_offsent.y = gy_zero/200;
    gyro_zero_offsent.z = gz_zero/200;
}

float WirelessHandle::squared(float x)
{
    return x * x;
}

void WirelessHandle::readSensors(void)
{
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    RwAcc[0] = (ax - accel_zero_offsent.x);
    RwAcc[1] = (ay - accel_zero_offsent.y);
    RwAcc[2] = (az - accel_zero_offsent.z);
    Gyro[0] = (gx - gyro_zero_offsent.x);
    Gyro[1] = (gy - gyro_zero_offsent.y);
    Gyro[2] = (gz - gyro_zero_offsent.z);
}

void WirelessHandle::normalize3DVec(float vector[3])
{
    float R;
    R = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
    vector[0] /= R;
    vector[1] /= R;
    vector[2] /= R;
}

void WirelessHandle::getInclination(void)
{
    static boolean firstSample = true;
    int w = 0;
    readSensors();
    normalize3DVec(RwAcc);
    
    currentTime = millis();
    interval = currentTime - lastTime;
    lastTime = currentTime;
    
    if (firstSample) {
        for (w=0;w<=2;w++) {
            RwEst[w] = RwAcc[w];
        }
    } else {
        if (abs(RwEst[2]) < 0.1) {
            for (w=0;w<=2;w++) {
                RwGyro[w] = RwEst[w];
            }
        } else {
            for (w=0;w<=1;w++) {
                tmpf = Gyro[w];
                tmpf *= interval / 1000.0f;
                Awz[w] = atan2(RwEst[w], RwEst[2]) * 180 / PI;
                Awz[w] += tmpf;
            }
            signRzGyro = ( cos(Awz[0] * PI / 180) >=0 ) ? 1 : -1;

            // http://starlino.com/imu_guide.html
            for (w=0;w<=1;w++) {
                RwGyro[0] = sin(Awz[0] * PI / 180);
                RwGyro[0] /= sqrt( 1 + squared(cos(Awz[0] * PI / 180)) * squared(tan(Awz[1] * PI / 180)) );
                RwGyro[1] = sin(Awz[1] * PI / 180);
                RwGyro[1] /= sqrt( 1 + squared(cos(Awz[1] * PI / 180)) * squared(tan(Awz[0] * PI / 180)) );
            }
                RwGyro[2] = signRzGyro * sqrt(1 - squared(RwGyro[0]) - squared(RwGyro[1]));
        }
        for (w=0;w<=2;w++) RwEst[w] = (RwAcc[w] + wGyro * RwGyro[w]) / (1 + wGyro);
        normalize3DVec(RwEst);
    }
    firstSample = false;
    
}

float WirelessHandle::GetGravity(byte direction)
{
    if (direction == BT_X) {
        return -RwEst[1];
    } else if (direction == BT_Y) {
        return RwEst[0];
    } else if (direction == BT_Z) {
        return RwEst[2];
    }
}

float WirelessHandle::GetRoll(void) {
    roll = 90 - acos(-RwEst[1]) * Rad;
    return roll;
}

float WirelessHandle::GetPitch(void) {
    pitch = 90 - acos(RwEst[0]) * Rad;
    return pitch;
}

int WirelessHandle::GetDegree(void) {
    int degree = 0XFFFF;
    if (control_select == E_GRAVITY_CONTROL_MODE) {
        if ((RwEst[1] < 0.3) && (RwEst[1] > -0.3) && (RwEst[0] < 0.3) && (RwEst[0] > -0.3))
            return 0XFFFF;
        degree = 180 - atan2(RwEst[0], RwEst[1]) * Rad;
    } else {
        float y = -1 * float((Analog(BT_Y) - 127) / 127);
        float x = float((Analog(BT_X) - 127) / 127);
        //Serial.print("x:");
        //Serial.print(x);
        //Serial.print(" y:");
        //Serial.print(y);
        //Serial.print(" ");
        if ((-0.2 <= x) && (x <= 0.2) && (-0.2 <= y) && (y <= 0.2))
        {
            degree = 0xFFFF;
        } else {
            degree = atan2(y, x) * 57.3;
            if (degree < 0) {
                degree = 360 + degree;
             }
        }
    }
    return degree;
}

uint16_t WirelessHandle::ScanKeyPad(void)
{
    buttonsB = 0;
    buttonsC = 0;
    buttonsD = 0;
    last_buttons = buttons;
    buttonsD = ((*Dbutton_reg) & BUTTON_BIT_DMASK)^BUTTON_BIT_DMASK;
    buttonsB=  ((*Bbutton_reg) & BUTTON_BIT_BMASK)^BUTTON_BIT_BMASK;
    buttonsC = ((*Cbutton_reg) & BUTTON_BIT_CMASK)^BUTTON_BIT_CMASK;
    buttons = buttonsD | (buttonsC & 0x01) | (buttonsC >> 2) | (buttonsB << 8);
    //Serial.println(buttons, HEX);
    return buttons;
}

/****************************************************************************************/
boolean WirelessHandle::NewButtonState() {
    return ((last_buttons ^ buttons) > 0);
}

/****************************************************************************************/
boolean WirelessHandle::NewButtonState(uint16_t button) {
    return (((last_buttons ^ buttons) & button) > 0);
}

/****************************************************************************************/
boolean WirelessHandle::ButtonPressed(uint16_t button) {
    return (NewButtonState(button) & Button(button));
}

/****************************************************************************************/
boolean WirelessHandle::ButtonReleased(uint16_t button) {
    return ((NewButtonState(button)) & ((last_buttons & button) > 0));
}

/****************************************************************************************/
boolean WirelessHandle::Button(uint16_t button) {
    return ((buttons & button) > 0);
}

/****************************************************************************************/
unsigned int WirelessHandle::ButtonDataByte(void) {
    return buttons;
}

/****************************************************************************************/
int WirelessHandle::Analog(byte direction) {
    if (direction == BT_X) {
        return analogRead(PIN_ANALOG_X)/4;
    } else if (direction == BT_Y)  {
        return analogRead(PIN_ANALOG_Y)/4;
    }
}
