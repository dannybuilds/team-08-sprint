// Members :  Nick Stites
//         :  Danny Restrepo
// Course  :  ECE 211 Intro to Design Processes
// School  :  Portland State University
// Date    :  8th November 2023
// Project :  Team 08 Sprint Project
// Title   :  Wifi Weather Display Team 08

#include <Wire.h>
#include <WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include "config.h"
#include <LiquidCrystal.h>

#define SUN_PIN 14    // drives sun pictogram LED
#define RAIN_PIN 15   // drives rain pictogram LED
#define SNOW_PIN 33   // drives snow pictogram LED
#define CLOUD_PIN 32  // drives cloud pictogram LED



AdafruitIO_Feed *hightemp = io.feed("hightemp");            // sets the 'hightemp' feed
AdafruitIO_Feed *precipitation = io.feed("precipitation");  // sets the 'precipitation' feed

LiquidCrystal lcd(27, 12, 21, 17, 16, 19);  // sets interface pins
int todaysHigh = 0;                         // declares and initilizes variable todaysHigh


void setup()
{
    Serial.begin(9600);
    lcd.begin(16, 2);            // (LCD rows, LCD cols)

    pinMode(SUN_PIN, OUTPUT);    // initialize pin as an output
    pinMode(RAIN_PIN, OUTPUT);   // initialize pin as an output
    pinMode(SNOW_PIN, OUTPUT);   // initialize pin as an output
    pinMode(CLOUD_PIN, OUTPUT);  // initialize pin as an output

    lcd.setCursor(0, 0);
    lcd.print("Hello,");
    lcd.setCursor(0, 1);
    lcd.print("From Team 08!");  

    Serial.print("Connecting to Adafruit IO");

    io.connect();                // connectS to io.adafruit.com

    // sets up a message handler for the count feed,
    // the handleMessage function (defined below)
    // will be called whenever a message is
    // received from adafruit io
    hightemp->onMessage(handleTemp);
    precipitation->onMessage(handleCondition);

    // waits for a connection
    while (io.status() < AIO_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    // connection status feedback
    Serial.println();
    Serial.println(io.statusText());
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
    Serial.println(data->value());   // prints the temperature data to the serial monitor
    int todaysHigh = data->toInt();  // stores the incoming temperature data as an integer
}


void handleCondition(AdafruitIO_Data *data)
{
    lcd.clear();  // clears the lcd display

    String forecast = data->toString();  // stores the incoming weather data in a string

    // the following strings store the varous IFTTT weather report words I've discovered so far
    String rain = String("Rain");
    String lightrain = String("Light Rain");
    String rainshower = String("Rain Shower");
    String snow = String("Snow");
    String cloudy = String("Cloudy");
    String mostlycloudy = String("Mostly Cloudy");
    String partlycloudy = String("Partly Cloudy");
    String clearsky = String("Clear");
    String fair = String("Fair");
    String sunny = String("Sunny");
    String rainandsnow = String("Rain and Snow");
    String snowshower = String("Snow Shower");

    // if there is rain in the forcast light up rain LED and print forecast to screen
    if (forecast.equalsIgnoreCase(rain) || forecast.equalsIgnoreCase(lightrain) || forecast.equalsIgnoreCase(rainshower))
    {
        Serial.println("rain in the forecast today");
        lcd.setCursor(0, 0);                           // configured so we get a new line for the high temp print
        lcd.print("rain in the forecast today");
        lcd.setCursor(1, 0);                           // configured so we get a new line for the high temp print
        lcd.print("todays high is " + String(todaysHigh));
        digitalWrite(RAIN_PIN, HIGH);                   // sets rain pin to HIGH
    }

    // if there is snow in the forcast light up snow LED and print forecast to screen
    if (forecast.equalsIgnoreCase(snow) || forecast.equalsIgnoreCase(rainandsnow) || forecast.equalsIgnoreCase(snowshower))
    {
        Serial.println("snow in the forecast today");
        lcd.setCursor(0, 0);                           // configured so we get a new line for the high temp print
        lcd.print("snow in the forecast today");
        lcd.setCursor(1, 0);                           // configured so we get a new line for the high temp print
        lcd.print("todays high is " + String(todaysHigh));
        digitalWrite(SNOW_PIN, HIGH);                   // sets snow pin to HIGH
    }

    // if there is sun in the forcast light up sun LED and print forecast to screen
    if (forecast.equalsIgnoreCase(clearsky) || forecast.equalsIgnoreCase(fair) || forecast.equalsIgnoreCase(sunny))
    {
        Serial.println("sun in the forecast today");
        lcd.setCursor(0, 0);                          // configured so we get a new line for the high temp print
        lcd.print("sun in the forecast today");
        lcd.setCursor(1, 0);                          // configured so we get a new line for the high temp print
        lcd.print("todays high is " + String(todaysHigh));
        digitalWrite(SUN_PIN, HIGH);                   // sets sun pin to HIGH
    }

    // if there is clouds in the forcast light up cloud LED and print forecast to screen
    if (forecast.equalsIgnoreCase(cloudy) || forecast.equalsIgnoreCase(mostlycloudy) || forecast.equalsIgnoreCase(partlycloudy))
    {
        Serial.println("cloudy sky in the forecast today");
        lcd.setCursor(0, 0);                                 // configured so we get a new line for the high temp print
        lcd.print("cloudy sky in the forecast today");
        lcd.setCursor(1, 0);                                 // configured so we get a new line for the high temp print
        lcd.print("todays high is " + String(todaysHigh));
        digitalWrite(CLOUD_PIN, HIGH);                        // sets cloud pin to HIGH
    }
}