#include <Arduino.h>
#include "POWER.hpp"
// #include "ARGALI_PINOUT.hpp"



void turn_on_SIM7080G(){
  
    digitalWrite(PIN_PWRKEY, LOW);
    delay(200);
    digitalWrite(PIN_PWRKEY, OUTPUT_OPEN_DRAIN);
    delay(3000);
    Sim7080G.begin(Sim7080G_BAUDRATE, SERIAL_8N1, 20, 21);
    Sim7080G.println("AT+GSN");
    Sim7080G.println("AT+SIMCOMATI");
  }

  void turn_off_SIM7080G(){
    Sim7080G.println("AT+CPOWD=1");
    Serial.println("This the end");

  }

  String getBatteryLevel() {
    return Send_AT("AT+CBC");  // Envoie la commande AT+CBC
}

