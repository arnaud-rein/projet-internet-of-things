
#include "INCLUDE_MAIN.hpp"
unsigned long period1; 


  void everyX(){
    if((millis() - period1) > 3000){
      period1 = millis();
      // DisplayLatLngInfo();
      // displayTimeStamp();
      // loop_CATM1();

      //sub string 

      String test = "+CSQ: 23,99";

      int indexStartCSQ = test.indexOf("+CSQ:", 0);
      Serial.print("indexStartCSQ : ");
      Serial.println((String) indexStartCSQ);

      int indexAfterCSQ = indexStartCSQ + 6; 

      Serial.print("indexAfterCsq  : ");
      Serial.println((String) indexAfterCSQ);


      int virgule = test.indexOf(",", indexAfterCSQ);

      Serial.print("virgule  : ");
      Serial.println((String) virgule);
      

      String numberEnt = test.substring(indexAfterCSQ, virgule);

      Serial.print("number ent  : ");
      Serial.println(numberEnt);

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

  // initGnssCongif();
  setup_CATM1();
  
  period1 = millis();





}


void loop() {

  everyX();
}
