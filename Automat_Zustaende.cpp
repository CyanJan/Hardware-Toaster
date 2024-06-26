/*
 * Automat_Zustaende.cpp
 *
 * Created: 22.01.2023 10:41:44
 *  Author: Thomas Heß
 * Implementierung der Methoden entry(), exit() und do() für die einzelnen Zustandsklassen (die Objekte werden erst in ClassAutomat.cpp erzeugt)
 */ 

#include "Automat_Zustaende.h"
#include "Hardware_Methoden.h"
#include "Variable_Global.h"

#include <cstdint>
#include <stdint.h>

#pragma region StateInitialisierung
//=============================================================================
// Zustandsklasse StateInitialisierung
//=============================================================================
void StateInitialisierung::entryAction()
{

    Display::init();
    LEDs::init();
    Motor::init();
    Heizungen::init();
    Resets::init_Resets();

    ExtInterruptPins::init_extint_Start();
    ExtInterruptPins::init_extint_Stopp();
    ExtInterruptPins::init_extint_Drinnen();
    ExtInterruptPins::init_extint_Draussen();

    ExtInterruptPins::extint_Start_enable();
    ExtInterruptPins::extint_Stopp_enable();
    ExtInterruptPins::extint_Drinnen_enable();
    ExtInterruptPins::extint_Draussen_enable();

    Timers::init_TIM7_interrupt();
    Timers::TIM7_start();

    derAutomat.sendEvent(NoEvent); // Hiermit wird die Transition nach Bereit ausgelöst

}

void StateInitialisierung::exitAction()
{
    Display::locate(0, 0);
    Display::print("Toaster");
    //Display::print("Automat/Toaster");
    //Serial::print("Automat\n");
}

void StateInitialisierung::doAction()
{
    ;
}

// default constructor
StateInitialisierung::StateInitialisierung()
{

}
// default destructor
StateInitialisierung::~StateInitialisierung()
{

}
#pragma endregion
#pragma region StateBereit
//=============================================================================
// Zustandsklasse StateBereit
//=============================================================================
void StateBereit::entryAction() {

    LEDs::ready(true);

    Display::locate(0, 1);
    Display::print("                ");
    //Display::print("Bereit!  ");
    Serial::print("Bereit!\n\n");
}

//-----------------------------------------------------------------------------
void StateBereit::exitAction() 
{    
    LEDs::ready(false);
}

//-----------------------------------------------------------------------------

void StateBereit::doAction() 
{
    
}	

// default constructor
StateBereit::StateBereit()
{

    
}
// default destructor
StateBereit::~StateBereit()
{

}
#pragma endregion
#pragma region StateEinfahren
//=============================================================================
// Zustandsklasse StateEinfahren
//=============================================================================
void StateEinfahren::entryAction() 
{
    
    Motor::links();
    Display::locate(0, 1);
    Serial::print("Einfahren\n");
    //Display::print("Einfahren");
    
}

//-----------------------------------------------------------------------------
void StateEinfahren::exitAction() 
{
    Motor::stopp();
}

//-----------------------------------------------------------------------------

void StateEinfahren::doAction() {
    
}	

// default constructor
StateEinfahren::StateEinfahren()
{
    
}
// default destructor
StateEinfahren::~StateEinfahren()
{

}
#pragma endregion
#pragma region StateHeizen
//=============================================================================
// Zustandsklasse StateHeizen
//=============================================================================
void StateHeizen::entryAction() 
{
    
    Display::locate(0, 1);
    Serial::print("Heizen\n");
    //Display::print("Heizen...     ");
    
    Heizungen::Heizung_an();
}

//-----------------------------------------------------------------------------
void StateHeizen::exitAction() 
{
    Heizungen::Heizung_aus();
    LEDs::anzeige(false);
}

//-----------------------------------------------------------------------------

void StateHeizen::doAction() 
{
    /*
    if ((derAutomat.fsm_get_timeInState() % 2) == 0)
        LEDs::anzeige(true);
    else
        LEDs::anzeige(false);
    */
    LEDs::anzeige((derAutomat.fsm_get_timeInState() % 2));
}	

// default constructor
StateHeizen::StateHeizen()
{
    
}
// default destructor
StateHeizen::~StateHeizen()
{

}
#pragma endregion
#pragma region StateAusfahren
//=============================================================================
// Zustandsklasse StateAusfahren
//=============================================================================
void StateAusfahren::entryAction() 
{
    
    Motor::rechts();
    Display::locate(0, 1);
    Serial::print("Ausfahren\n");
    //Display::print("Ausfahren");
}

//-----------------------------------------------------------------------------
void StateAusfahren::exitAction() 
{
    Motor::stopp();
}

//-----------------------------------------------------------------------------

void StateAusfahren::doAction() {
    
}	

// default constructor
StateAusfahren::StateAusfahren()
{
    
}
// default destructor
StateAusfahren::~StateAusfahren()
{

}
#pragma endregion
#pragma region StateFehler
//=============================================================================
// Zustandsklasse StateAusfahren
//=============================================================================
void StateFehler::entryAction() 
{
    //Felher LED an
    LEDs::fehler(true);
    //Fehlermeldung auf LCD anzeigen
    Display::locate(0, 1);
    Display::print(":-( Kein Toast");
}

//-----------------------------------------------------------------------------
void StateFehler::exitAction() 
{
    //Fehler LED aus
    LEDs::fehler(false);
    //Fehlermeldung auf LCD löschen
    Display::clear_row(1);   
}

//-----------------------------------------------------------------------------

void StateFehler::doAction() {
    
}	

// default constructor
StateFehler::StateFehler()
{
    
}
// default destructor
StateFehler::~StateFehler()
{

}
#pragma endregion