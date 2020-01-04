

#ifndef MeConfig_H
#define MeConfig_H



#define ME_PORT_DEFINED

#if defined(__AVR__)
#define MePIN_TO_BASEREG(pin)               ( portInputRegister (digitalPinToPort (pin) ) )
#define MePIN_TO_BITMASK(pin)               ( digitalPinToBitMask (pin) )
#define MeIO_REG_TYPE                       uint8_t
#define MeIO_REG_ASM                        asm ("r30")
#define MeDIRECT_READ(base, mask)           ( ( (*(base) ) & (mask) ) ? 1 : 0)
#define MeDIRECT_MODE_INPUT(base, mask)     ( (*( (base) + 1) ) &= ~(mask) ), ( (*( (base) + 2) ) |= (mask) ) // INPUT_PULLUP
#define MeDIRECT_MODE_OUTPUT(base, mask)    ( (*( (base) + 1) ) |= (mask) )
#define MeDIRECT_WRITE_LOW(base, mask)      ( (*( (base) + 2) ) &= ~(mask) )
#define MeDIRECT_WRITE_HIGH(base, mask)     ( (*( (base) + 2) ) |= (mask) )
#endif // __AVR__

#endif // MeConfig_H

