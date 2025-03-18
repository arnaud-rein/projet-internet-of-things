#include <Arduino.h>
#include "POWER.hpp"
#include "SIM7080G_SERIAL.hpp"


void setup() {
  pinMode(PIN_PWRKEY, OUTPUT);
  turn_on_SIM7080G();
  Serial.begin(115200); // init port uart // on a aussi un port uart qui pointe vers notre pc 
  Serial.println("Around the World"); // CTRL + ALT + S 
  period1 = millis();
  String reponse = Send_AT("AT+SIMCOMATI");
  Serial.println(reponse);
  
  Serial.println("Niveau de batterie :");
  Serial.println(getBatteryLevel());  
  

}


void loop() {
  // put your main code here, to run repeatedly:
  if(Sim7080G.available()){
    char byte_recv = Sim7080G.read();
    Serial.print(byte_recv);
    // Serial.print(ESP.getHeapSize);
  }
  everyX();
  // Serial.println(millis()); 
}