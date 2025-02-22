/*
  Name: Krish Patel

  Date: December 11, 2023
  Date Due: January 23, 2024

  Project: Automated Plant Irrigation System

  Description: This project involves automating the process
  of watering a plant. By utilizing a soil moisture sensor,
  a DC water pump, a relay module, and an Arduino Uno, this
  is possible. The purpose of the LCD module is to display
  information regarding the moisture of the soil in real time.

  Functionality: A soil moisture sensor constantly monitors
  the moisture level in the soil. Once it hits a certain
  threshold, it will send a signal to the DC water pump to
  activate, causing water to be pumped into the plant. Once the
  moisture sensor detects that moisture levels are stable, the
  DC water pump deactivates. During this entire process, information
  is constantly updated on the LCD screen.
*/


#include<LiquidCrystal.h>

//initialize LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//pin to relay digital signal to DC water pump
int relayPin = 8;
//store soilmoisture in percent
int moisturePercent = 0;
//Green LED to indicate if DC pump is on
int greenLED = 7;
//Red LED to indicate if DC pump is off
int redLED = 13;
//store value to print to LCD
String status = "";

void setup()
{
  //initialize power to LCD
  lcd.begin(16, 2);

  //set relay pin & LED pins as outuput
  pinMode(relayPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop()
{
  //read analog data from soil moisture sensor
  int moisture = analogRead(0);
  //map analog data to a percent
  moisturePercent = map(moisture, 1023, 250, 0, 100);

  //delay for stability
  delay(500);

  //print out data to LCD
  lcd.setCursor(0, 0);
  status = checkMoisture(moisturePercent);
  lcd.print("Moisture: " + String(moisturePercent) + "% ");
  lcd.setCursor(0, 1);
  lcd.print("Status: " + String(status) + " ");

  //check if plant needs watering
  needWatering(moisturePercent);
}

//function to correspond moisture levels to a condition (e.g. 43% is "Moist")
String checkMoisture(int x) {
  if (x >= 60) {
    status = "Watery";
  } else if (x >= 30) {
    status = "Moist";
  } else {
    status = "Dry";
  }
  return status;
}

//function to determine if plant needs watering; if condition is not met,
//digital signal will be relayed to DC water pump
void needWatering(int x) {
  if (x < 30) {
    //Control DC Water Pump
    digitalWrite(relayPin, HIGH);
    //Control LED Lights
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    delay(1000);
  } else {
    //Control DC Water Pump
    digitalWrite(relayPin, LOW);
    //Control LED Lights
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    delay(1000);
  }
}
