/*
 * Automat_Transitionen.cpp
 *
 * Created: 12.02.2023 23:15:36
 *  Author: Thomas Heß
 */ 

#include <stdint.h>

#include "Automat_Transitionen.h"
#include "Hardware_Methoden.h" // Für die Transitionsaktionen
#include "Variable_Global.h" // Für Zugriff auf Methoden des Automaten

#pragma region Initialieierung --> Breit
//=============================================================================
// Zustandsübergangsklasse Trans_Initialisierung_Bereit
//=============================================================================

// default constructor
Trans_Initialisierung_Bereit::Trans_Initialisierung_Bereit()
{
    ereignis = NoEvent; // unbedingter Übergang, also muss am ENde der entry() für Initialieierung
                        // sendEvent(NoEvent) kommen um diesen Übergang auszulösen.
}

bool Trans_Initialisierung_Bereit::guard()
{
    return true;
}
bool Trans_Initialisierung_Bereit::action()
{
    return true;
}
Events Trans_Initialisierung_Bereit::getEvent()
{
    return ereignis;
}
bool Trans_Initialisierung_Bereit::decision()
{
    return true;
}

// default destructor
Trans_Initialisierung_Bereit::~Trans_Initialisierung_Bereit()
{

}
#pragma endregion

#pragma region Breit --> Einfahren
//=============================================================================
// Zustandsübergangsklasse Trans_Bereit_Einfahren
//=============================================================================

// default constructor
Trans_Bereit_Einfahren::Trans_Bereit_Einfahren()
{
    ereignis = TasterStart;
}
bool Trans_Bereit_Einfahren::guard()
{
    if (derAutomat.fsm_get_timeInState() >= 10)
        return true;
    
    return false;
}
bool Trans_Bereit_Einfahren::action()
{
    
    return true;
}
Events Trans_Bereit_Einfahren::getEvent()
{
    return ereignis;
}
bool Trans_Bereit_Einfahren::decision()
{
    return true;
}

// default destructor
Trans_Bereit_Einfahren::~Trans_Bereit_Einfahren()
{

}
#pragma endregion

#pragma region Einfahren --> Heizen
//=============================================================================
// Zustandsübergangsklasse Trans_Einfahren_Heizen
//=============================================================================

// default constructor
Trans_Einfahren_Heizen::Trans_Einfahren_Heizen()
{
    ereignis = EndTasterDrinnen;
}
bool Trans_Einfahren_Heizen::guard()
{
    return true;
}
bool Trans_Einfahren_Heizen::action()
{
    return true;
}
Events Trans_Einfahren_Heizen::getEvent()
{
    return ereignis;
}
bool Trans_Einfahren_Heizen::decision()
{
    if(ExtInterruptPins::get_EndtasterDraussen() == 0)
        return true;

    return false;
}

// default destructor
Trans_Einfahren_Heizen::~Trans_Einfahren_Heizen()
{

}
#pragma endregion 

#pragma region Einfahren --> Fehler

// default constructor
Trans_Einfahren_Fehler::Trans_Einfahren_Fehler()
{
    ereignis = Tick;
}
bool Trans_Einfahren_Fehler::guard()
{
    if (derAutomat.fsm_get_timeInState() >= 20)
        return true;

    return false;
}
bool Trans_Einfahren_Fehler::action()
{
    
    return true;
}
Events Trans_Einfahren_Fehler::getEvent()
{
    return ereignis;
}
bool Trans_Einfahren_Fehler::decision()
{
    return true;
}

// default destructor
Trans_Einfahren_Fehler::~Trans_Einfahren_Fehler()
{

}
#pragma endregion 

#pragma region Heizen --> Ausfahern
//=============================================================================
// Zustandsübergangsklasse Trans_Heizen_Ausfahren
//=============================================================================

// default constructor
Trans_Heizen_Ausfahren::Trans_Heizen_Ausfahren()
{
    ereignis = TasterStopp;
}
bool Trans_Heizen_Ausfahren::guard()
{
    return true;
}
bool Trans_Heizen_Ausfahren::action()
{
    Display::locate(0, 1);
    Display::print("Guten Appetit!");
    return true;
}
Events Trans_Heizen_Ausfahren::getEvent()
{
    return ereignis;
}
bool Trans_Heizen_Ausfahren::decision()
{
    return true;
}

// default destructor
Trans_Heizen_Ausfahren::~Trans_Heizen_Ausfahren()
{

}
#pragma endregion

#pragma region Heizen --> Ausfahern
//=============================================================================
// Zustandsübergangsklasse Trans_Heizen_Ausfahren
//=============================================================================

// default constructor
Trans_Heizen_Ausfahren_Auto::Trans_Heizen_Ausfahren_Auto()
{
    ereignis = Tick;
}
bool Trans_Heizen_Ausfahren_Auto::guard()
{
    if (derAutomat.fsm_get_timeInState() >= 15) 
        return true;
    else
        return false;;
}
bool Trans_Heizen_Ausfahren_Auto::action()
{
    Display::locate(0, 1);
    Display::print("Fast schwarz!");
    return true;
}
Events Trans_Heizen_Ausfahren_Auto::getEvent()
{
    return ereignis;
}
bool Trans_Heizen_Ausfahren_Auto::decision()
{
    return true;
}

// default destructor
Trans_Heizen_Ausfahren_Auto::~Trans_Heizen_Ausfahren_Auto()
{

}
#pragma endregion

#pragma region Ausfahren --> Breit
//=============================================================================
// Zustandsübergangsklasse Trans_Ausfahren_Bereit
//=============================================================================

// default constructor
Trans_Ausfahren_Bereit::Trans_Ausfahren_Bereit()
{
    ereignis = EndTasterDraussen;
}
bool Trans_Ausfahren_Bereit::guard()
{
    return true;
}
bool Trans_Ausfahren_Bereit::action()
{
    return true;
}
Events Trans_Ausfahren_Bereit::getEvent()
{
    return ereignis;
}
bool Trans_Ausfahren_Bereit::decision()
{
    return true;
}

// default destructor
Trans_Ausfahren_Bereit::~Trans_Ausfahren_Bereit()
{

}
#pragma endregion

#pragma region Ausfahern --> Fehler

// default constructor
Trans_Ausfahren_Fehler::Trans_Ausfahren_Fehler()
{
    ereignis = Tick;
}
bool Trans_Ausfahren_Fehler::guard()
{
    if (derAutomat.fsm_get_timeInState() >= 10)
        return true;

    return false;
}
bool Trans_Ausfahren_Fehler::action()
{
    
    return true;
}
Events Trans_Ausfahren_Fehler::getEvent()
{
    return ereignis;
}
bool Trans_Ausfahren_Fehler::decision()
{
    return true;
}

// default destructor
Trans_Ausfahren_Fehler::~Trans_Ausfahren_Fehler()
{

}
#pragma endregion 

#pragma region Fehler --> Breit

// default constructor
Trans_Fehler_Bereit::Trans_Fehler_Bereit()
{
    ereignis = Tick;
}
bool Trans_Fehler_Bereit::guard()
{
    if (Resets::get_soft_reset() != 0)
        return true;

    return false;
}
bool Trans_Fehler_Bereit::action()
{
    
    return true;
}
Events Trans_Fehler_Bereit::getEvent()
{
    return ereignis;
}
bool Trans_Fehler_Bereit::decision()
{
    return true;
}

// default destructor
Trans_Fehler_Bereit::~Trans_Fehler_Bereit()
{

}
#pragma endregion 
