
#include "INCLUDE_MAIN.hpp"
unsigned long period1;


MachineEtat machine;
ATCommandTask taskSim("AT+SIMCOMATI", "860016044667504", 10, 3000);
ATCommandTask taskCNACT("AT+CNACT=0,1", "PDP", 15, 5000);
boolean test = true;
ProcessStep currentStep = STEP_INIT;
// Création de deux tâches AT indépendantes
ATCommandTask task1("AT+CAOPEN=0,0,\"TCP\",\"rndav-2a01-cb0a-9014-328d-dcb0-4b5d-50df-772d.a.free.pinggy.link\",35427", "OK", 15, 15000);
// ATCommandTask task2("AT+COPS?", "+COPS:", 3, 3000);

void switchPipeline(){
  period1 = millis();

    switch (currentStep) {
        case STEP_INIT:
            Serial.println("[STEP_INIT] Démarrage...");
            currentStep = STEP_WAIT_SIM;
            break;

        case STEP_WAIT_SIM:
            Serial.println("[STEP_WAIT_SIM] Attente de la fin de taskSim...");
            if (!taskSim.isFinished) {
                machine.updateATState(taskSim);
            } else {
                currentStep = STEP_CONFIG_CATM1;
            }
            break;

        case STEP_CONFIG_CATM1:
            Serial.println("[STEP_CONFIG_CATM1] Configuration du CATM1...");
            if (test) {
                // Éteindre le GNSS avant d'activer CATM1
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
            currentStep = STEP_WAIT_CNACT;
            break;

        case STEP_WAIT_CNACT:
            Serial.println("[STEP_WAIT_CNACT] Attente de la fin de taskCNACT...");
            if (!taskCNACT.isFinished) {
                machine.updateATState(taskCNACT);
            } else {
                currentStep = STEP_DONE;
            }
            break;

        case STEP_DONE:
            Serial.println("[STEP_DONE] Processus terminé !");
            // Si tu veux recommencer depuis le début après la fin :
            // currentStep = STEP_INIT;
            break;
    }
}



  void everyX(){

if((millis() - period1) > 3000){
  switchPipeline();

}
  }


void setup() {
  pinMode(PIN_PWRKEY, OUTPUT);
  // turn_on_SIM7080G();
  Serial.begin(115200); // init port uart // on a aussi un port uart qui pointe vers notre pc
  reboot_SIM7080G();
  Serial.println("Around the World"); // CTRL + ALT + S
  period1 = millis();


  // String reponse = Send_AT("AT+SIMCOMATI");
  // Serial.println(reponse);

  // Serial.println("Niveau de batterie :");
  // Serial.println(getBatteryLevel());

  // initGnssCongif();
  // setup_CATM1();

  // TCP_send();





}


void loop() {

  everyX();
}
