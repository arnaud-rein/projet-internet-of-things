
#include "INCLUDE_MAIN.hpp"
unsigned long period1; 


MachineEtat machine;
ATCommandTask taskSim("AT+SIMCOMATI", "860016044667504", 10, 3000);
ATCommandTask taskCNACT("AT+CNACT=0,1", "PDP", 15, 5000);
boolean test = true; 

// Création de deux tâches AT indépendantes
ATCommandTask task1("AT+CAOPEN=0,0,\"TCP\",\"rndav-2a01-cb0a-9014-328d-dcb0-4b5d-50df-772d.a.free.pinggy.link\",35427", "OK", 15, 15000);
// ATCommandTask task2("AT+COPS?", "+COPS:", 3, 3000);
  void everyX(){
    
if((millis() - period1) > 3000){
  period1 = millis();
  // DisplayLatLngInfo();
  // displayTimeStamp();
  // loop_CATM1();
  if(!taskSim.isFinished){
    machine.updateATState(taskSim);
    
  }else{

    if(test){
      //You must turn off GNSS before turning on CATM1
  gnssTurnOff();
  Send_AT("AT+CNMP=38");
  Send_AT("AT+CMNB=1");
  Send_AT("AT+CNACT=0,0");
  Send_AT("AT+CGDCONT=1,\"IP\",\"iot.1nce.net\"");
  Send_AT("AT+CGNAPN");
  Send_AT("AT+CNCFG=0,1,iot.1nce.net");

  Send_AT("AT+CEREG?");
  test = false; 

    }
  if(!taskCNACT.isFinished){
    machine.updateATState(taskCNACT);

  }else{
    Serial.println("+++++++++++++++++++++++FINISH####################################");
  }

  }

  Serial.println("---------------------------------------");
   
}
  }


void setup() {
  pinMode(PIN_PWRKEY, OUTPUT);
  // turn_on_SIM7080G();
  Serial.begin(115200); // init port uart // on a aussi un port uart qui pointe vers notre pc 
  reboot_SIM7080G();
  Serial.println("Around the World"); // CTRL + ALT + S 
  period1 = millis();
  String reponse = Send_AT("AT+SIMCOMATI");
  Serial.println(reponse);
  
  Serial.println("Niveau de batterie :");
  Serial.println(getBatteryLevel());  

  // initGnssCongif();
  // setup_CATM1();
  
  // TCP_send(); 
  period1 = millis();





}


void loop() {

  everyX();
}
