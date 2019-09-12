#include "Servo.h"
#define EM_MOTOR_SHIELD_BOARD_VERSION 3

#if (EM_MOTOR_SHIELD_BOARD_VERSION > 2)
    #define SERVO_PIN 7
#else
    #define SERVO_PIN 5
#endif
Servo myservo;  // Create a servo motor object

char inByte = 0; //Serial port to receive data
int angle = 0;  //Angle value 
String temp = "";//Temporary character variables, or use it for the cache

void setup()   
{  
    myservo.attach(SERVO_PIN);    //Define the steering gear pin to 13
    Serial.begin(9600);  //Set the baud rate
}

void loop()   
{  
    while (Serial.available() > 0) //Determine whether the serial data
    {  
        inByte = Serial.read();//Read data, the serial port can only read 1 character
        temp += inByte;//The characters read into temporary variables inside the cache, 
        //Continue to determine the serial port there is no data, know all the data read out  
    }
    //Determine whether the temporary variable is empty
    if(temp != "") {  
        angle = temp.toInt();    //Convert variable string type to integer  
        Serial.println(angle);  //Output data to the serial port for observation
        myservo.write(angle);  //Control the servo to rotate the corresponding angle.  
     }  
     temp = "";//Please see temporary variables
     delay(100);//Delayed 100 milliseconds 
}  
