
#include "Buzzer.h"
#include <avr/wdt.h>

uint8_t buzzer_pin;

#ifdef ME_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * Buzzer pins are used and initialized here.
 * \param[in]
 *   None
 */
Buzzer::Buzzer()
{
  buzzer_pin = 9;
}

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
Buzzer::Buzzer(uint8_t port):MePort(port)
{
  buzzer_pin = port;
}

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * you can set any slot for the buzzer device.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \param[in]
 *   slot - SLOT1 or SLOT2
 */
Buzzer::Buzzer(uint8_t port, uint8_t slot):MePort(port)
{
  buzzer_pin = s2;
  if(slot == SLOT2)
  {
    buzzer_pin = s2;
  }
  else
  {
    buzzer_pin = s1;
  }
}
#else // ME_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * \param[in]
 *   switchPin - arduino port for buzzer detect pin.
 */
Buzzer::Buzzer(int pin)
{
  buzzer_pin = pin;
}
#endif // ME_PORT_DEFINED

/**
 * \par Function
 *    setpin
 * \par Description
 *    Reset the buzzer available pin by its arduino port.
 * \param[in]
 *    pin - arduino port for buzzer detect pin.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void Buzzer::setpin(int pin)
{
  buzzer_pin = pin;
}

/**
 * \par Function
 *    tone
 * \par Description
 *    Playing the tones.
 * \param[in]
 *    pin - Which pin on board that buzzer is connecting to.
 * \param[in]
 *    frequency - The speed of buzzer's tone play.
 * \param[in]
 *    duration - Time of a tone play.
 * \par Output
 *    None
 * \Return
 *    None.
 * \par Others
 *    Frequency (in hertz) and duration (in milliseconds).
 */
void Buzzer::tone(int pin, uint16_t frequency, uint32_t duration)
{
  buzzer_pin = pin;
  int period = 1000000L / frequency;
  int pulse = period / 2;
  pinMode(buzzer_pin, OUTPUT);
  for (long i = 0; i < duration * 1000L; i += period)
  {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(pulse);
    wdt_reset();
  }
}

/**
 * \par Function
 *    tone
 * \par Description
 *    Playing the tones.
 * \param[in]
 *    frequency - The speed of buzzer's tone play.
 * \param[in]
 *    duration - Time of a tone play.
 * \par Output
 *    None
 * \Return
 *    None.
 * \par Others
 *    Frequency (in hertz) and duration (in milliseconds).
 */
void Buzzer::tone(uint16_t frequency, uint32_t duration)
{
    int period = 1000000L / frequency;
    int pulse = period / 2;
    pinMode(buzzer_pin, OUTPUT);
    for (long i = 0; i < duration * 1000L; i += period)
    {
        digitalWrite(buzzer_pin, HIGH);
        delayMicroseconds(pulse);
        digitalWrite(buzzer_pin, LOW);
        delayMicroseconds(pulse);
        wdt_reset();
    }
}

void Buzzer::_tone (float noteFrequency, long noteDuration, int silentDuration)
{

    // tone(10,261,500);
    // delay(500);

      if(silentDuration==0){silentDuration=1;}

      tone(buzzer_pin, noteFrequency, noteDuration);
      delay(noteDuration);       //milliseconds to microseconds
      //noTone(PIN_Buzzer);
      delay(silentDuration);
}


void Buzzer::bendTones(float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration){

  //Examples:
  //  bendTones (880, 2093, 1.02, 18, 1);
  //  bendTones (note_A5, note_C7, 1.02, 18, 0);

  if(silentDuration==0){silentDuration=1;}

  if(initFrequency < finalFrequency)
  {
      for (int i=initFrequency; i<finalFrequency; i=i*prop) {
          _tone(i, noteDuration, silentDuration);
      }

  } else{

      for (int i=initFrequency; i>finalFrequency; i=i/prop) {
          _tone(i, noteDuration, silentDuration);
      }
  }
}

/**
 * \par Function
 *    noTone
 * \par Description
 *    Do not playing the tones.
 * \param[in]
 *    pin - Which pin on board that buzzer is connecting to.
 * \par Output
 *    None
 * \Return
 *    None.
 * \par Others
 *    None
 */
void Buzzer::noTone(int pin)
{
  buzzer_pin = pin;
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, LOW);
}

/**
 * \par Function
 *    noTone
 * \par Description
 *    Do not playing the tones.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \Return
 *    None.
 * \par Others
 *    None
 */
void Buzzer::noTone()
{
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, LOW);
}
