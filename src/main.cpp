
#include "INCLUDE_MAIN.hpp"
unsigned long period1; 


  void everyX(){
    if((millis() - period1) > 3000){
      // Serial.println("coucou");
      period1 = millis();
      Serial.println(DisplayLatLng());

    }
  }


void setup() {
  pinMode(PIN_PWRKEY, OUTPUT);
  turn_on_SIM7080G();
  // reboot_SIM7080G();
  Serial.begin(115200); // init port uart // on a aussi un port uart qui pointe vers notre pc 
  Serial.println("Around the World"); // CTRL + ALT + S 
  period1 = millis();
  String reponse = Send_AT("AT+SIMCOMATI");
  Serial.println(reponse);
  
  Serial.println("Niveau de batterie :");
  Serial.println(getBatteryLevel());  

  initGnssCongif();
  
  period1 = millis();
}


void loop() {

  everyX();
}
