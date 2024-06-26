/*
 * Automat_Zustaende.h
 *
 * Created: 22.01.2023 10:32:23
 *  Author: Thomas Heß
 *  Implements all the states of the finite state machine
 *  ApplicationState States of FSM
 */ 


#ifndef CLASSAPPLICATIONSTATES_H_
#define CLASSAPPLICATIONSTATES_H_

#include "Zustand_Oberklasse.h"

#include <stdint.h> 

/*
 *  Initialisierungszustand
*/
class StateInitialisierung : public State
{
  public:
    void entryAction();
    void exitAction();
    void doAction();

    
    StateInitialisierung();
    ~StateInitialisierung();
};

/*
 *  Zustand Bereit
*/
class StateBereit : public State
{
 private:

  public:
    void entryAction();
    void exitAction();
    void doAction();
    

    StateBereit();
    ~StateBereit();
};


/*
 *  Zustand Einfahren
*/
class StateEinfahren : public State
{
  private:

  public:
    void entryAction();
    void exitAction();
    void doAction();


    StateEinfahren();
    ~StateEinfahren();
};

/*
 *  Zustand Heizen
*/
class StateHeizen : public State
{
  private:

  public:
    void entryAction();
    void exitAction();
    void doAction();


    StateHeizen();
    ~StateHeizen();
};

/*
 *  Zustand Ausfahren
*/
class StateAusfahren : public State
{
  private:

  public:
    void entryAction();
    void exitAction();
    void doAction();


    StateAusfahren();
    ~StateAusfahren();
};
#pragma region Fehler
class StateFehler : public State
{
  private:

  public:
    void entryAction();
    void exitAction();
    void doAction();


    StateFehler();
    ~StateFehler();
};
#pragma endregion
#endif /* CLASSAPPLICATIONSTATES_H_ */