// IFTTT/Adafruit IO/NeoPixel strio/7-segment display weather shadowbox by Becky Stern
// This program contains bits and pieces of various library sample codes:
/*************************************************** 
  Adafruit LED 7-Segment backpacks 
  ----> http://www.adafruit.com/products/881
  ----> http://www.adafruit.com/products/880
  ----> http://www.adafruit.com/products/879
  ----> http://www.adafruit.com/products/878

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  I2C LED Backpack Example written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
  
// Adafruit IO Multiple Feed Example written by Todd Treece for Adafruit Industries
// Smart Toilet Light with ESP8266 written by Tony DiCola for Adafruit Industries
// Licenses: MIT (https://opensource.org/licenses/MIT)
 ****************************************************/

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_NeoPixel.h"

#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>

// Adafruit IO Subscription Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

// Configuration you can optionally change (but probably want to keep the same):
#define PIXEL_PIN       2                      // Pin connected to the NeoPixel data input.
#define PIXEL_COUNT     12                      // Number of NeoPixels.
#define PIXEL_TYPE      NEO_GRBW + NEO_KHZ800   // Type of the NeoPixels (see strandtest example).

// before running this code, create feeds on Adafruit IO that match these names:
AdafruitIO_Feed *hightemp = io.feed("hightemp"); // set up the 'hightemp' feed
AdafruitIO_Feed *precipitation = io.feed("precipitation"); // set up the 'precipitation' feed

Adafruit_7segment matrix = Adafruit_7segment();  // create segment display object

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE); // create NeoPixels object

void setup() {
  
  matrix.begin(0x70); // initialize matrix display
  
  // start the serial connection
  Serial.begin(115200);
  
  // Initialize NeoPixels and turn them off.
  pixels.begin();
  lightPixels(pixels.Color(0, 0, 0, 0));

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
  
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
}

// this function is called whenever a feed message
// is received from Adafruit IO. it was attached to
// the feed in the setup() function above.
void handleTemp(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());  // print the temperature data to the serial monitor
  
  int todaysHigh = data->toInt(); // store the incoming temperature data as an integer
  matrix.print(todaysHigh, DEC);  // send the temperature value to the display
  matrix.writeDisplay();          // light up display
  delay(500);                     // wait half a second
}  
  
void handleCondition(AdafruitIO_Data *data) {

  lightPixels(pixels.Color(0, 0, 0, 0)); // reset all pixels to off
  
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
  
  // These if statements compare the incoming weather variable to the stored conditions, and control the NeoPixels accordingly.
  
  // if there's rain in the forecast, tell the the first four pixels to be blue and the middle four pixels to be white (but don't draw them yet)
  if (forecast.equalsIgnoreCase(rain) || forecast.equalsIgnoreCase(lightrain) || forecast.equalsIgnoreCase(rainshower)){
    Serial.println("precipitation in the forecast today");
    pixels.setPixelColor(0, pixels.Color(0, 30, 200, 20));
    pixels.setPixelColor(1, pixels.Color(0, 30, 200, 20));
    pixels.setPixelColor(2, pixels.Color(0, 30, 200, 20));
    pixels.setPixelColor(3, pixels.Color(0, 30, 200, 20));
    pixels.setPixelColor(4, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(5, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(6, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(7, pixels.Color(0, 0, 0, 255));
  }
  
  // if there's snow in the forecast, tell the the first four pixels to be whiteish blue and the middle four pixels to be white (but don't draw them yet)
  if (forecast.equalsIgnoreCase(snow) || forecast.equalsIgnoreCase(rainandsnow) || forecast.equalsIgnoreCase(snowshower)){
    Serial.println("precipitation in the forecast today");
    pixels.setPixelColor(0, pixels.Color(0, 30, 200, 20));
    pixels.setPixelColor(1, pixels.Color(0, 30, 200, 20));
    pixels.setPixelColor(2, pixels.Color(0, 30, 150, 150));
    pixels.setPixelColor(3, pixels.Color(0, 30, 150, 150));
    pixels.setPixelColor(4, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(5, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(6, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(7, pixels.Color(0, 0, 0, 255));
  }
  
  // if there's sun in the forecast, tell the last four pixels to be yellow (but don't draw them yet)
  if (forecast.equalsIgnoreCase(clearsky) || forecast.equalsIgnoreCase(fair) || forecast.equalsIgnoreCase(sunny)){
    Serial.println("some kind of sun in the forecast today");
    pixels.setPixelColor(8, pixels.Color(255, 150, 0, 0));
    pixels.setPixelColor(9, pixels.Color(255, 150, 0, 0));
    pixels.setPixelColor(10, pixels.Color(255, 150, 0, 0));
    pixels.setPixelColor(11, pixels.Color(255, 150, 0, 0));
  }
  // if there're clouds in the forecast, tell the the middle four pixels to white and the last four pixels to be yellow (but don't draw them yet)
  if (forecast.equalsIgnoreCase(cloudy) || forecast.equalsIgnoreCase(mostlycloudy) || forecast.equalsIgnoreCase(partlycloudy)){
    Serial.println("cloudy sky in the forecast today");
    pixels.setPixelColor(4, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(5, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(6, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(7, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(8, pixels.Color(255, 150, 0, 0));
    pixels.setPixelColor(9, pixels.Color(255, 150, 0, 0));
    pixels.setPixelColor(10, pixels.Color(255, 150, 0, 0));
    pixels.setPixelColor(11, pixels.Color(255, 150, 0, 0));
   }
   pixels.show(); // light up the pixels
}

// Function to set all the NeoPixels to the specified color.
void lightPixels(uint32_t color) {
  for (int i=0; i<PIXEL_COUNT; ++i) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}