/*
 * Hardware_Methoden.h
 *
 * Created: 21.01.2023 15:51:44
 *  Author: Thomas Heß
 */ 


#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <stddef.h>  // für size_t
#include <stdint.h> // für uint8_t
#include <stdbool.h> // damit bool als (abgeleiteter) Datentyp existiert

//#include "ClassAutomat.h" // damit Timer auf den Automaten zugreifen kann, für isr


namespace Display
{
    void init();
    void locate(int, int);
    void print(const char*, ...);
    void clear_row(short);
}

namespace Serial
{
    void print(const char*, ...);
}

namespace ExtInterruptPins
{
    void isr_Start(void);
    void isr_Stopp(void);
    void isr_Drinnen(void);
    void isr_Draussen(void);

    void init_extint_Start(void);
    void init_extint_Stopp(void);
    void init_extint_Drinnen(void);
    void init_extint_Draussen(void);

    void extint_Start_enable(void);
    void extint_Start_disable(void);
    
    void extint_Stopp_enable(void);
    void extint_Stopp_disable(void);

    void extint_Drinnen_enable(void);
    void extint_Drinnen_disable(void);

    void extint_Draussen_enable(void);
    void extint_Draussen_disable(void);

    int get_EndtasterDraussen(void);
}

namespace Resets
{
    void init_Resets(void);
    int get_soft_reset(void);
}

namespace Motor 
{
    void init();
    void links();
    void rechts();
    void stopp();
}

namespace Heizungen
{
    void init();
    void Heizung_an();
    void Heizung_aus();
}

namespace LEDs
{
    void init(); // LEDs initialisieren
    void ready(bool OnOff); // LED_READY an- bzw. abschalten
    void anzeige(bool OnOff);// LED_ANZEIGE an- bzw. abschalten
    void fehler(bool OnOff);// LED_ANZEIGE an- bzw. abschalten
}

namespace Timers
{    
    void init_TIM7_interrupt(void);
    void isr_TIM7(void);

    void TIM7_start(void);
    void TIM7_stop(void);
}

namespace Bluetooth
{
    void init_bt(void);
    bool bt_readable(void);
    void bt_read(void*,size_t);
}

#endif /* HARDWARE_H_ */