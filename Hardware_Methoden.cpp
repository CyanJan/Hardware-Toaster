/*
 * Hardware_Methoden.cpp
 *
 * Created: 21.01.2023 17:29:12
 *  Author: Thomas Heß
 */ 
#undef __ARM_FP
#include "Hardware_Methoden.h"
#include "Hardware_Definitionen.h"
#include "mbed.h"
#include "TextLCD_I2C.h"
#include "Variable_Global.h" // für globalen Zugriff auf den Automaten derAutomat, speziell für isr

#include <cstdio>
#include <stdarg.h>


// Für Sturm-Board, um das LC-Display per I2C ansteuern zu können obwohl es an PA_11, PA_12
// angeschlossen ist. Es müssen auf dem Morpho-Header folgende Verbindungen gesteckt werden:
// SCL: PA_11 <-> PB_8
// SDA: PA_12 <-> PB_9

DigitalIn scl(PA_11,PullUp);  
DigitalIn sda(PA_12,PullUp);

DigitalOut LED_Ready(LED_READY);
DigitalOut LED_Fehler(LED_FEHLER);
DigitalOut LED_Anzeige(LED_ANZEIGE);

DigitalOut Motor_A(MOTOR_A_OUT);
DigitalOut Motor_B(MOTOR_B_OUT);
DigitalOut Heizung(HEIZUNG);

InterruptIn Start(S_START);
InterruptIn Stopp(S_STOPP);
InterruptIn Drinnen(ENDTASTER_DRINNEN);
InterruptIn Draussen(ENDTASTER_DRAUSSEN);

DigitalIn SoftReset(SOFT_RESET);
DigitalIn HardReset(HARD_RESET);


I2C i2c_lcd(I2C_SDA, I2C_SCL); // PB_9, PB_8 
// I2C i2c_lcd(PB_9, PB_8);
// I2C-Adresse 0x27 - 16 Spalten und 2 Zeilen 
// LCD20x4 → 20 Spalten und 4 Zeilen 
TextLCD_I2C LC_Display(&i2c_lcd, 0x27<<1, TextLCD_I2C::LCD16x2);


// BufferedSerial blue(BT_TX, BT_RX); // TX,RX
// DigitalOut enable(BT_EN, 0); // Enable auf 0, also kein Konfigurationsmodus

#pragma region LCD
//=============================================================================
// LCD
//=============================================================================

void Display::init()
{
    LC_Display.setBackLight(true);
    LC_Display.cls(); 
    LC_Display.locate(0,0); // (column,row) 
    
}

void Display::locate(int column, int row)
{
    LC_Display.locate(column, row);
}

// Wrapper for printf(), according to https://stackoverflow.com/questions/20639632/how-to-wrap-printf-into-a-function-or-macro

void Display::print(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    LC_Display.vprintf(format, args);


    va_end(args);
}

void Display::clear_row(short row)
{
    Display::locate(0, row);
    Display::print("                ");
}
#pragma endregion
#pragma region Serial Monitor
//=============================================================================
// Serial ... Serieller Monitor
//=============================================================================

void Serial::print(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);

}
#pragma endregion
#pragma region ExtInterruptPins
    #pragma region init
    void ExtInterruptPins::init_extint_Start()
    {
        Start.mode(PullDown);
        Start.rise(&isr_Start);
        Start.enable_irq();
    }
    void ExtInterruptPins::init_extint_Stopp()
    {
        Stopp.mode(PullDown);
        Stopp.rise(&isr_Start);
        Stopp.enable_irq();
    }
    void ExtInterruptPins::init_extint_Drinnen()
    {
        Drinnen.mode(PullDown);
        Drinnen.rise(&isr_Drinnen);
        Drinnen.enable_irq();
    }
    void ExtInterruptPins::init_extint_Draussen()
    {
        Draussen.mode(PullDown);
        Draussen.rise(&isr_Draussen);
        Draussen.enable_irq();
    }
    #pragma endregion

    #pragma region isr
    void ExtInterruptPins::isr_Start(void)
    {
        derAutomat.sendEvent(TasterStart);
    }

    void ExtInterruptPins::isr_Stopp(void)
    {
        derAutomat.sendEvent(TasterStopp);
    }

    void ExtInterruptPins::isr_Drinnen()
    {
        derAutomat.sendEvent(EndTasterDrinnen);
    }

    void ExtInterruptPins::isr_Draussen()
    {
        derAutomat.sendEvent(EndTasterDraussen);
    }
    #pragma endregion

    #pragma region En-/Disable
    void ExtInterruptPins::extint_Start_enable(void)
    {
        Start.rise(&isr_Start);
        Start.enable_irq();
    }

    void ExtInterruptPins::extint_Start_disable(void)
    {
        Start.rise(NULL);
    }

    void ExtInterruptPins::extint_Stopp_enable()
    {
        Stopp.rise(&isr_Stopp);
        Stopp.enable_irq();
    }
    void ExtInterruptPins::extint_Stopp_disable()
    {
        Stopp.rise(NULL);
    }

    void ExtInterruptPins::extint_Drinnen_enable()
    {
        Drinnen.rise(&isr_Drinnen);
        Drinnen.enable_irq();
    }

    void ExtInterruptPins::extint_Drinnen_disable()
    {
        Drinnen.rise(NULL);
    }

    void ExtInterruptPins::extint_Draussen_enable()
    {
        Draussen.rise(&isr_Draussen);
        Draussen.enable_irq();
    }
    void ExtInterruptPins::extint_Draussen_disable()
    {
        Draussen.rise(NULL);
    }

    #pragma endregion

    #pragma region get
    int ExtInterruptPins::get_EndtasterDraussen()
    {
        return Draussen.read();
    }
    #pragma endregion
#pragma endregion
#pragma region Resets
void Resets::init_Resets()
{
    SoftReset.mode(PullDown);
}
int Resets::get_soft_reset()
{
    return SoftReset.read();
}
#pragma endregion
#pragma region LEDs
//=============================================================================
// LEDs
//=============================================================================

void LEDs::init()
{
    LED_Ready.write(false);
    LED_Anzeige.write(false);
    LED_Fehler.write(false);
}


void LEDs::ready(bool OnOff)
{
    LED_Ready.write(OnOff);
    /*
    if(OnOff == 1) LED_Ready.write(1); // LED an
	else LED_Ready.write(0); // LED aus
    */
}

void LEDs::anzeige(bool OnOff)
{
    LED_Anzeige.write(OnOff);

    //if(OnOff == 1) LED_Anzeige.write(true); 
    //else LED_Anzeige.write(false);
}

void LEDs::fehler(bool OnOff)
{
    LED_Fehler.write(OnOff);
}
#pragma endregion
#pragma region Motor
//=============================================================================
// Motor
//=============================================================================

void Motor::init()
{
    Motor_A.write(false);
    Motor_B.write(false);
}

void Motor::links()
{
    Motor_A.write(false);
	Motor_B.write(true);
}

void Motor::rechts()
{
    Motor_A.write(true);
    Motor_B.write(false);
}

void Motor::stopp()
{
    Motor_A.write(false);
    Motor_B.write(false);
}
#pragma endregion
#pragma region Heizung
//=============================================================================
// Heizungen
//=============================================================================

void Heizungen::init()
{
    Heizung.write(false);
}

void Heizungen::Heizung_an()
{
    Heizung.write(true);
}

void Heizungen::Heizung_aus()
{
    Heizung.write(false);
}
#pragma endregion
#pragma region Timer
//=============================================================================
// Timer
//=============================================================================

void Timers::init_TIM7_interrupt()
{
        // TIM7 mit Takt versorgen, Bit 5 in RCC_APB1ENR
    RCC->APB1ENR |= (1 << TIM7EN); // RCC_APB1ENR |= 0b 100000: RCC_APB1ENR.TIM7EN=1
    
    // TIM7 stoppen
    TIM7->CR1 &= ~(1 << CEN); // TIM7_CR1.CEN = 0; Bit 0
    
    // Prescaler auf 31999 setzen -A Taktsignal wird durch 32000 geteilt
    // Bei fCLK = 32MHz ergibt dies 1ms fCNT
    TIM7->PSC = 31999; // (1ms * 32MHz)-1 = 31999
    
    // TIM7 UIF löschen, ist Bit 0 im Register TIM6_SR
    TIM7->SR &= ~(1 << UIF); // FS TIM7->SR = 0, geht, da restl. 15 Bit reserved sind, trotzdem ungute Lösung
   
    // TIM7 neu laden
    TIM7->CNT = 0;
    
    // TIM7 Maximalwert auf 1000 setzen, also Interrupt nach 1s
    TIM7->ARR = 1000;
    
    // TIM7 ISR in die Vektortabelle des NVIC eintragen
    NVIC_SetVector(TIM7_IRQn,(uint32_t) &isr_TIM7);

    // TIM7-Interrupt im NVIC freigeben
    HAL_NVIC_EnableIRQ(TIM7_IRQn);

    // TIM7 Interrupt freigeben TIM7_DIER.UIE=1: Bit 0 setzen
    TIM7->DIER |= (1 << UIE);

    // TIM7 starten
    // TIM7->CR1 |= (1 << CEN); // TIM7_CR1.CEN = 1; Bit 0

}

void Timers::isr_TIM7(void)
{
     // TIM7 Interrupt stoppen TIM7_DIER.UIE=1: Bit 0 löschen
    TIM7->DIER &= ~(1 << UIE);

    // TIM7 stoppen
    TIM7->CR1 &= ~(1 << CEN); // TIM7_CR1.CEN = 0; Bit 0

    //  Tick-Ereignis senden
    derAutomat.sendEvent(Tick);

    derAutomat.fsm_set_timeInState(1); // timeInState der fsm um 1 erhöhen

    // TIM7 UIF löschen, ist Bit 0 im Register TIM7_SR
    TIM7->SR &= ~(1 << UIF); // FS TIM7->SR = 0, geht, da restl. 15 Bit reserved sind, trotzdem ungute Lösung
   
    // TIM7 neu laden
    TIM7->CNT = 0;

    // TIM7 Interrupt freigeben TIM7_DIER.UIE=1: Bit 0 setzen
    TIM7->DIER |= (1 << UIE);

    //TIM7 starten
    TIM7->CR1 |= (1 << CEN); // TIM7_CR1.CEN = 1; Bit 0

    
}

void Timers::TIM7_start()
{   
    TIM7->CNT=0;
    TIM7->CR1 |= (1 << CEN); // TIM7_CR1.CEN = 1; Bit 0
}

void Timers::TIM7_stop()
{
    TIM7->CR1 &= ~(1 << CEN); // TIM7_CR1.CEN = 0; Bit 0
}
#pragma endregion
#pragma region Bluetooth
//=============================================================================
// Bluetooth
//=============================================================================
/*
void Bluetooth::init_bt()
{
    // Set desired properties (38400-8-N-1). HC10 kann nur 9600Baud 
    blue.set_baud(9600);
    blue.set_format(8,                    // bits
                  BufferedSerial::None, // parity
                  1                     // stop bits
    );
}

bool Bluetooth::bt_readable()
{
    return(blue.readable());
}

void Bluetooth::bt_read(void *buf, size_t laenge)
{
    blue.read(buf, laenge);
}
*/
#pragma endregion