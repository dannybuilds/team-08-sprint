// Author  :  Danny Restrepo
// School  :  Portland State University
// Course  :  ECE 211 Intro to Design Processes
// Project :  Team 08 Sprint Project
// Title   :  Big Font Header for WWD Device
// Date    :  13th November 2023

#ifndef font_h
#define font_h



#include "Arduino.h"
#include "LiquidCrystal.h"

class BigFont
{
    public:
        BigFont(LiquidCrystal*);

	    void begin();
        void clearBigFont(byte);
        void displayBigNumber(byte, byte);
	    void displayBigInt(int, byte, byte, bool);

    private:
        LiquidCrystal* _lcd;
};



#endif