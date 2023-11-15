// Author  :  Danny Restrepo
// School  :  Portland State University
// Course  :  ECE 211 Intro to Design Processes
// Project :  Team 08 Sprint Project
// Title   :  Big Font Module for WWD Device
// Date    :  13th November 2023

#include "font.h"



/************************** Region Definitions for Big Font *********************************/

byte leftSide[8] = 
{
    B00111,
    B01111,
    B01111,
    B01111,
    B01111,
    B01111,
    B01111,
    B00111
};

byte upperBar[8] =
{
    B11111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000
};

byte rightSide[8] =
{
    B11100,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11100
};

byte leftEnd[8] =
{
    B01111,
    B00111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00011,
    B00111
};

byte lowerBar[8] =
{
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111
};

byte rightEnd[8] =
{
    B11110,
    B11100,
    B00000,
    B00000,
    B00000,
    B00000,
    B11000,
    B11100
};

byte middleBar[8] =
{
    B11111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111
};

byte lowerEnd[8] = 
{
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00111,
    B01111
};



/************************************ Constructor *******************************************/

// creates BigFont object
// LiquidCrystal* lcd: LiquidCrystal object to use
BigFont::BigFont(LiquidCrystal* lcd)
{
  _lcd = lcd;
}



/*************************************** Init ***********************************************/

void BigFont::begin()
{
    // creates custom characters, hardware limited to 8 custom characters
    _lcd->createChar(0, leftSide);
    _lcd->createChar(1, upperBar);
    _lcd->createChar(2, rightSide);
    _lcd->createChar(3, leftEnd);
    _lcd->createChar(4, lowerBar);
    _lcd->createChar(5, rightEnd);
    _lcd->createChar(6, middleBar);
    _lcd->createChar(7, lowerEnd);
}



/************************************** Methods *********************************************/

// prints an integer to the display using large characters
// parameters: 
//      n - the integer to display
//      x - column of upper left corner of first large character
//      digits - number of digits of the integer (constant)
//      leading - sets if leading zeros are printed or not (false = no, true = yes)
void BigFont::displayBigInt(int n, byte x, byte digits, bool leading)
{
    boolean isNegative = false;
    if(n < 0)
    {
        isNegative = true;
        n = abs(n);
    }
    
    byte numString[digits];
    byte index = digits - 1;

    while(index)
    {
        numString[index] = n % 10;
        n /= 10;
        index--;
    }

    numString[0] = n % 10;
  
    for (int i = 0; i < digits; i++)
    {
        if(numString[i] == 0 && !leading && i < digits - 1)
        {
            clearBigFont((i * 3) + x);
        }
        else
        {
            displayBigNumber(numString[i], (i * 3) + x);
            leading = true;
        }
    }
}



// x is column of upper left corner for large character
void BigFont::clearBigFont(byte x)
{
    _lcd->setCursor(x,0);
    _lcd->print("   ");
    _lcd->setCursor(x,1); 
    _lcd->print("   ");
}



// n is number to display, x is column of upper left corner for large character
void BigFont::displayBigNumber(byte n, byte x)
{
  switch(n)
  {
    case 0:
    {
        _lcd->setCursor(x,0);
        _lcd->write(byte(0));
        _lcd->write(1);
        _lcd->write(2);
        _lcd->setCursor(x, 1);
        _lcd->write(byte(0));
        _lcd->write(4);
        _lcd->write(2);
        break;
    }

    case 1:
    {
        _lcd->setCursor(x,0);
        _lcd->write(char(254));
        _lcd->write(char(254));
        _lcd->write(2);
        _lcd->setCursor(x,1);
        _lcd->write(char(254));
        _lcd->write(char(254));
        _lcd->write(2);
        break;
    }
    
    case 2:
    {
        _lcd->setCursor(x,0);
        _lcd->write(3);
        _lcd->write(6);
        _lcd->write(2);
        _lcd->setCursor(x, 1);
        _lcd->write(byte(0));
        _lcd->write(4);
        _lcd->write(4);
        break;
    }

    case 3:
    {
        _lcd->setCursor(x,0);
        _lcd->write(3);
        _lcd->write(6);
        _lcd->write(2);
        _lcd->setCursor(x, 1);
        _lcd->write(7);
        _lcd->write(4);
        _lcd->write(2);
        break;
    }

    case 4:
    {
        _lcd->setCursor(x,0);
        _lcd->write(byte(0));
        _lcd->write(4);
        _lcd->write(2);
        _lcd->setCursor(x, 1);
        _lcd->write(char(254));
        _lcd->write(char(254));
        _lcd->write(2);
        break;
    }

    case 5:
    {
        _lcd->setCursor(x,0);
        _lcd->write(byte(0));
        _lcd->write(6);
        _lcd->write(5);
        _lcd->setCursor(x, 1);
        _lcd->write(7);
        _lcd->write(4);
        _lcd->write(2);
        break;
    }

    case 6:
    {
        _lcd->setCursor(x,0);
        _lcd->write(byte(0));
        _lcd->write(6);
        _lcd->write(5);
        _lcd->setCursor(x, 1);
        _lcd->write(byte(0));
        _lcd->write(4);
        _lcd->write(2);
        break;
    }

    case 7:
    {
        _lcd->setCursor(x,0);
        _lcd->write(1);
        _lcd->write(1);
        _lcd->write(2);
        _lcd->setCursor(x, 1);
        _lcd->write(char(254));
        _lcd->write(char(254));
        _lcd->write(2);
        break;
    }

    case 8:
    {
        _lcd->setCursor(x,0);
        _lcd->write(byte(0));
        _lcd->write(6);
        _lcd->write(2);
        _lcd->setCursor(x, 1);
        _lcd->write(byte(0));
        _lcd->write(4);
        _lcd->write(2);
        break;
    }

    case 9:
    {
        _lcd->setCursor(x,0);
        _lcd->write(byte(0));
        _lcd->write(6);
        _lcd->write(2);
        _lcd->setCursor(x, 1);
        _lcd->write(7);
        _lcd->write(4);
        _lcd->write(2);
        break;
    }
  }
}