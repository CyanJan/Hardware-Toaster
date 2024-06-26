/*
 * Hardware_Definitionen.h
 *
 * Created: 21.01.2023 15:44:07
 *  Author: Thomas Heß
 */ 


#ifndef HARDWARE_HWDEFS_H_
#define HARDWARE_HWDEFS_H_



namespace ExtInterruptPins
{
    #define S_START                 PB_0

    #define S_STOPP                 PB_3

    #define ENDTASTER_DRINNEN       PA_1

    #define ENDTASTER_DRAUSSEN      PA_6


}

namespace Resets
{
    #define SOFT_RESET              PB_4

    #define HARD_RESET				PA_10
}

namespace LEDs
{
    #define LED_FEHLER              PC_4
    #define LED_READY               PC_5
    #define LED_ANZEIGE             PC_6
}

namespace Motor 
{
    #define MOTOR_A_OUT		        PC_0
    #define MOTOR_B_OUT		        PC_3
}
namespace Heizungen
{
    #define HEIZUNG                 PC_7
}

namespace Timers 
{
    // #define für einzelne Konfigurationsbits

    // RCC_APB1ENR
    #define TIM6EN 4
    #define TIM7EN 5

    // TIMx_CR1, CEN... counter enable
    #define CEN 0

    // TIMx_DIER, UIE ... Update Interrupt Enable
    #define UIE 0

    // TIMx_SR, UIF ... Update Interrupt Flag
    #define UIF 0
}

namespace Bluetooth
{
    // BT TX-Pin
    #define BT_TX PB_10

    // BT RX-Pin
    #define BT_RX PB_11

    // BT enable pin
    #define BT_EN PB_12
}

#endif /* HARDWARE_HWDEFS_H_ */