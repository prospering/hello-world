#include <Arduino.h>
#include <M5Stack.h>


void pir_sensor_setup() {
  M5.begin(); //Init M5Stack.  
  M5.Power.begin(); //Init power  
  M5.lcd.setTextSize(2);  //Set the text size to 2.  
  M5.Lcd.println("PIR example");
  M5.Lcd.setCursor(0, 25);  //Position the cursor at (0,25). 
  M5.Lcd.println("Status: \nValue: ");
  pinMode(36, INPUT); //Set pin 22 to input mode.  
}

void pir_sensor_print_data() {
  // Pas besoin de mettre un fond d'écran noir lorsque l'on combine les capteurs (le co2 initialise déjà un fond)
  // M5.Lcd.fillRect(90,25,180,50,BLACK);  //Draw a black rectangle 180 by 50 at (90,25). 
  M5.Lcd.fillRect(0,130,140,18,BLACK);
  if(digitalRead(36)==1){ //If pin 22 reads a value of 1.
    M5.Lcd.setCursor(0, 130);M5.Lcd.print("Sensing");
  }
  else{
    M5.Lcd.setCursor(0, 130);M5.Lcd.print("Not Sensed");
  }
}