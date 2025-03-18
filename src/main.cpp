#include <Arduino.h>
#include "POWER.hpp"
#include "SIM7080G_SERIAL.hpp"


void reboot_SIM7080G(){
  turn_off_SIM7080G();
  turn_on_SIM7080G(); 
}

String getGnssTest(){
  return Send_AT("AT+CGNSPWR=1");  // Envoie la commande AT+CBC
}

String check_GNSS_Status() {
  return Send_AT("AT+CGNSPWR?");
}

String get_GNSS_Info() {
  return Send_AT("AT+CGNSINF");
}
String get_GNSS_Mode() {
  return Send_AT("AT+CGNSMOD=1,0,0,1,0");
}


void setup() {
  pinMode(PIN_PWRKEY, OUTPUT);
  // turn_on_SIM7080G();
  reboot_SIM7080G();
  Serial.begin(115200); // init port uart // on a aussi un port uart qui pointe vers notre pc 
  Serial.println("Around the World"); // CTRL + ALT + S 
  period1 = millis();
  String reponse = Send_AT("AT+SIMCOMATI");
  Serial.println(reponse);
  
  Serial.println("Niveau de batterie :");
  Serial.println(getBatteryLevel());  

  Serial.println("GNSS"); 
  Serial.println(getGnssTest());
  
  Serial.println(check_GNSS_Status());
  Serial.println(get_GNSS_Mode());
  

}


void loop() {
  // put your main code here, to run repeatedly:
  if(Sim7080G.available()){
    char byte_recv = Sim7080G.read();
    Serial.print(byte_recv);
    // Serial.print(ESP.getHeapSize);
  }
  // everyX();
  // Serial.println(millis()); 
  Serial.println(get_GNSS_Info());
  delay(10000);
}
