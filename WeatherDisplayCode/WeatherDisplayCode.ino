// Wifi Weather Display Team 08
#include <Wire.h> 
#include <WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include "config.h"
#include <LiquidCrystal.h>

#define RainPin 1 //change based on hardware setup
#define SnowPin 2 //change based on hardware setup
#define SunPin 3 //change based on hardware setup
#define CloudPin 4 //change based on hardware setup

AdafruitIO_Feed *hightemp = io.feed("hightemp"); // set up the 'hightemp' feed
AdafruitIO_Feed *precipitation = io.feed("precipitation"); // set up the 'precipitation' feed

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Set interface pins
int todaysHigh = 0; // Declaring and initilizing variable todaysHigh 

void setup() {
  
  Serial.begin(9600);
  lcd.begin(16, 2); //number of rows then columns of LCD display
  lcd.setCursor(0, 0);
  lcd.print("Hello,");
  lcd.setCursor(0, 1);
  lcd.print("From Team 08!");
  
  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  hightemp->onMessage(handleTemp);
  precipitation->onMessage(handleCondition);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  
  io.run();
}

// this function is called whenever a feed message
// is received from Adafruit IO. it was attached to
// the feed in the setup() function above.
void handleTemp(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());  // print the temperature data to the serial monitor
  int todaysHigh = data->toInt(); // store the incoming temperature data as an integer
}  
  
void handleCondition(AdafruitIO_Data *data) {

  lcd.clear(); // Clear the lcd display
  
  String forecast = data->toString(); // store the incoming weather data in a string
  
  //the following strings store the varous IFTTT weather report words I've discovered so far
  String rain = String("Rain");
  String lightrain = String("Light Rain");
  String rainshower = String ("Rain Shower");
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
  if (forecast.equalsIgnoreCase(rain) || forecast.equalsIgnoreCase(lightrain) || forecast.equalsIgnoreCase(rainshower)){
    Serial.println("rain in the forecast today");
    lcd.setCursor(0, 0); //configure so we get a new line for the high temp print
    lcd.print("rain in the forecast today");
    lcd.setCursor(1, 0); //configure so we get a new line for the high temp print
    lcd.print("todays high is " + String(todaysHigh));
    digitalWrite(RainPin, HIGH); //setting rain pin to HIGH
  }
  
  // if there is snow in the forcast light up snow LED and print forecast to screen
  if (forecast.equalsIgnoreCase(snow) || forecast.equalsIgnoreCase(rainandsnow) || forecast.equalsIgnoreCase(snowshower)){
    Serial.println("snow in the forecast today");
    lcd.setCursor(0, 0); //configure so we get a new line for the high temp print
    lcd.print("snow in the forecast today"); 
    lcd.setCursor(1, 0); //configure so we get a new line for the high temp print
    lcd.print("todays high is " + String(todaysHigh));
    digitalWrite(SnowPin, HIGH); //setting snow pin to HIGH
  }
  
  // if there is sun in the forcast light up sun LED and print forecast to screen
  if (forecast.equalsIgnoreCase(clearsky) || forecast.equalsIgnoreCase(fair) || forecast.equalsIgnoreCase(sunny)){
    Serial.println("sun in the forecast today");
    lcd.setCursor(0, 0); //configure so we get a new line for the high temp print
    lcd.print("sun in the forecast today");
    lcd.setCursor(1, 0); //configure so we get a new line for the high temp print
    lcd.print("todays high is " + String(todaysHigh));
    digitalWrite(SunPin, HIGH); //setting sun pin to HIGH

  }
  // if there is clouds in the forcast light up cloud LED and print forecast to screen
  if (forecast.equalsIgnoreCase(cloudy) || forecast.equalsIgnoreCase(mostlycloudy) || forecast.equalsIgnoreCase(partlycloudy)){
    Serial.println("cloudy sky in the forecast today");
    lcd.setCursor(0, 0); //configure so we get a new line for the high temp print
    lcd.print("cloudy sky in the forecast today");
    lcd.setCursor(1, 0); //configure so we get a new line for the high temp print
    lcd.print("todays high is " + String(todaysHigh));
    digitalWrite(CloudPin, HIGH); //setting cloud pin to HIGH
   }
}
