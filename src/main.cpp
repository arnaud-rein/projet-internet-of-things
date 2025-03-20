
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
      int lengthEnd = test.length(); 
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
      int numberEndAfterVirgule = test.indexOf(" ", virgule + 1);
      String numberDec = test.substring(virgule + 1, numberEndAfterVirgule);
      Serial.print("number ent  : ");
      Serial.println(numberEnt);
      Serial.print("number dec  : ");
      Serial.println(numberDec);

      Float_gnss flt; 
      flt.ent = numberEnt.toInt();
      flt.dec = numberDec.toInt();
      Serial.println((String) flt.ent + "," + flt.dec);



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
