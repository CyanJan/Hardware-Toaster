/* 
* main.cpp
*
* Created: 12.02.2023 22:37:38
* Author: Thomas Heß
*/

/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#undef __ARM_FP

#include "mbed.h"
#include "Automat.h"
#include "Hardware_Methoden.h"  // für Zugriff auf die Hardware (GPIO, UART, ADC, ...) z.B. für Polling
#include "Variable_Global.h"  // Definition der globalen Variablen, die von anderen Funktionen in anderen cpp-files benötigt werden
#include <cstdint>
#include <cstdio>



/************************************************************
 * Angeschlossene Hardware:
 *
 * Tasten:      Start               PB_0    extInt, steigende Flanke
 *              Stopp               PB_3    extInt, steigende Flanke
 *              EndTasterDrinnen    PA_1    extInt, steigende Flanke
 *              EndTasterDraussen   PA_6    extInt, steigende Flanke
 *              SoftReset           PB_4    extInt, steigende Flanke
 *              HardReset           PA_10   extInt, steigende Flanke
 *              
 * Motor:		A PC_0
 * 				B PC_3
 * Heizung:     PC_6
 * Timer:
 *              TIM7            Interrupt jede Sekunde, erhöht timeInState
 *
 ************************************************************/
Automat derAutomat;     // Deklaration der globalen Variable derAutomat, die in Variable_Global.h extern definiert ist
                            // nur in einem cpp-file deklarieren, in den anderen cpp-files nur per 
                            // #include "Globals.h" verfügbar machen
                            // Im Konstruktor von Automat wird init() aufgerufen um die FSM zu initialisieren


int main()
{
       
	

	 // Globale Interruptfreigabe
	 __enable_irq();


    while (true) {
    


        derAutomat.process_StateChange();

    } // of while(true)

    return 1;
}
