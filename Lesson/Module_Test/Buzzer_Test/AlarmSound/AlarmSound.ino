#define BUZZER_PIN A0

void setup()  
{  
    pinMode(BUZZER_PIN,OUTPUT);  
}  
   
void loop()  
{  
    for(int i = 200; i <= 800; i++)   // 200HZ ~ 800HZ  
    {  
        tone(BUZZER_PIN,i);
    }  
    delay(1000);                    //Max Frequency hold 1s   
    for(int i= 800; i >= 200; i--)   // 800HZ ~ 200HZ
    {  
        tone(BUZZER_PIN,i);  
        delay(10);  
    }  
}
