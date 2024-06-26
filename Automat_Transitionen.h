/*
 * Automat_Transitionen.h
 *
 * Created: 04.11.2023 22:54:01
 *  Author: Thomas Heß
 */ 


#ifndef APPLICATIONTRANSITIONS_H_
#define APPLICATIONTRANSITIONS_H_

#include "Ereignisse_Transition_Oberklasse.h"

#include <stdint.h>


class Trans_Initialisierung_Bereit : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Initialisierung_Bereit();
            ~Trans_Initialisierung_Bereit();

};

class Trans_Bereit_Einfahren : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Bereit_Einfahren();
            ~Trans_Bereit_Einfahren();

};

class Trans_Einfahren_Heizen : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Einfahren_Heizen();
            ~Trans_Einfahren_Heizen();

};

class Trans_Einfahren_Fehler : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Einfahren_Fehler();
            ~Trans_Einfahren_Fehler();

};

class Trans_Heizen_Ausfahren : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Heizen_Ausfahren();
            ~Trans_Heizen_Ausfahren();

};

class Trans_Heizen_Ausfahren_Auto : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Heizen_Ausfahren_Auto();
            ~Trans_Heizen_Ausfahren_Auto();

};

class Trans_Ausfahren_Bereit : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Ausfahren_Bereit();
            ~Trans_Ausfahren_Bereit();
};

class Trans_Ausfahren_Fehler : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Ausfahren_Fehler();
            ~Trans_Ausfahren_Fehler();
};

class Trans_Fehler_Bereit : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Fehler_Bereit();
            ~Trans_Fehler_Bereit();
};

#endif /* APPLICATIONTRANSITIONS_H_ */