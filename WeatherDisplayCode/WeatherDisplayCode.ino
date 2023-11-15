// Members :  Nick Stites
//         :  Danny Restrepo
//         :  Caleb Monti
//         :  Jake Milroy
// School  :  Portland State University
// Course  :  ECE 211 Intro to Design Processes
// Project :  Team 08 Sprint Project
// Title   :  Wifi Weather Display
// Date    :  11th November 2023

#include <Wire.h>
#include <WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <LiquidCrystal.h>
#include "config.h"

#define SUN_PIN 14    // drives sun pictogram LED
#define RAIN_PIN 15   // drives rain pictogram LED
#define CLOUD_PIN 32  // drives cloud pictogram LED



AdafruitIO_Feed *hightemp = io.feed("hightemp");            // sets the 'hightemp' feed
AdafruitIO_Feed *precipitation = io.feed("precipitation");  // sets the 'precipitation' feed

LiquidCrystal lcd(27, 12, 19, 16, 17, 21);  // sets interface pins
int todaysHigh = 0;                         // declares and initilizes variable todaysHigh


void setup()
{
    Serial.begin(115200);
    lcd.begin(16, 2);            // (LCD rows, LCD cols)

    pinMode(SUN_PIN, OUTPUT);    // initialize pin as an output
    pinMode(RAIN_PIN, OUTPUT);   // initialize pin as an output
    pinMode(CLOUD_PIN, OUTPUT);  // initialize pin as an output
   
    Serial.print("Connecting to Adafruit IO");
    io.connect();                // connectS to io.adafruit.com

    // sets up a message handler for the count feed,
    // the handleMessage function (defined below)
    // will be called whenever a message is
    // received from adafruit io
    hightemp->onMessage(handleTemp);
    precipitation->onMessage(handleCondition);

    while (io.status() < AIO_CONNECTED)  // waits for a connection
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println();
    Serial.println(io.statusText());     // connection status feedback
    hightemp->get();
    precipitation->get();
}


void loop()
{
    io.run();
}


// this function is called whenever a feed message
// is received from Adafruit IO. it was attached to
// the feed in the setup() function above
void handleTemp(AdafruitIO_Data *data)
{
    Serial.print("received <- ");
    Serial.println(data->value());  // prints the temperature data to the serial monitor
    todaysHigh = data->toInt();     // stores the incoming temperature data as an integer
}


void handleCondition(AdafruitIO_Data *data)
{
    lcd.clear();  // clears the lcd display

    String forecast = data->toString();  // stores the incoming weather data in a string

    // the following strings store the varous IFTTT weather report words I've discovered so far
    String rain = String("Rain");
    String snow = String("Snow");
    String fair = String("Fair");
    String sunny = String("Sunny");
    String cloudy = String("Cloudy");
    String clearsky = String("Clear");
    String lightrain = String("Light Rain");
    String rainshower = String("Rain Shower");
    String snowshower = String("Snow Shower");
    String rainandsnow = String("Rain and Snow");
    String mostlycloudy = String("Mostly Cloudy");
    String partlycloudy = String("Partly Cloudy");

    // if there is rain in the forcast light up rain LED and print forecast to screen
    if (forecast.equalsIgnoreCase(rain) || forecast.equalsIgnoreCase(lightrain) || forecast.equalsIgnoreCase(rainshower))
    {
        Serial.println("rain in the forecast today");
        Serial.print("todays high is " + String(todaysHigh));
        lcd.setCursor(0, 0);                                   
        lcd.print("Rainy out today");
        lcd.setCursor(0, 1);                                   
        lcd.print("The high is " + String(todaysHigh));
        digitalWrite(RAIN_PIN, HIGH);                          // sets rain pin to HIGH
    }

    // if there is sun in the forcast light up sun LED and print forecast to screen
    if (forecast.equalsIgnoreCase(clearsky) || forecast.equalsIgnoreCase(fair) || forecast.equalsIgnoreCase(sunny))
    {
        Serial.println("sun in the forecast today");
        Serial.print("todays high is " + String(todaysHigh));
        lcd.setCursor(0, 0);                                   
        lcd.print("Sunny out today");
        lcd.setCursor(0, 1);                                   
        lcd.print("The high is " + String(todaysHigh));
        digitalWrite(SUN_PIN, HIGH);                           // sets sun pin to HIGH
    }

    // if there is clouds in the forcast light up cloud LED and print forecast to screen
    if (forecast.equalsIgnoreCase(cloudy) || forecast.equalsIgnoreCase(mostlycloudy) || forecast.equalsIgnoreCase(partlycloudy))
    {
        Serial.println("cloudy sky in the forecast today");
        Serial.print("todays high is " + String(todaysHigh));
        lcd.setCursor(0, 0);                                   
        lcd.print("Cloudy out today");  
        lcd.setCursor(0, 1);
        lcd.print("The high is: " + String(todaysHigh));  
        digitalWrite(CLOUD_PIN, HIGH);                         // sets cloud pin to HIGH
    }
}