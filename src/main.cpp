
#include "INCLUDE_MAIN.hpp"
unsigned long period1;


// -----------Utilisation Machine d'état ----------------------->
// SECTION BIENTOT REFACTOR DANS UN DOSSIER CAR IL Y A UN BUG QUANND ON DEPLACE CE CODE 
MachineEtat machine;
ATCommandTask taskSim("AT+SIMCOMATI", "860016044667504", 10, 3000);
ATCommandTask taskCNACT("AT+CNACT=0,1", "PDP", 15, 5000);
boolean test = true;
ProcessStep currentStep = STEP_INIT;
// Création de deux tâches AT indépendantes
ATCommandTask task1("AT+CAOPEN=0,0,\"TCP\",\"rntgi-185-223-151-250.a.free.pinggy.link\",41735", "OK", 15, 15000);
// ATCommandTask task2("AT+COPS?", "+COPS:", 3, 3000);

void switchPipeline(){ //#machineEtat //http://127.0.0.1:5500/documentation/index.html#machineEtat
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





void sendMinimalCBORMessage() { // http://127.0.0.1:5500/documentation/index.html#pinggy
  // 1. Préparer un message simple
  const char* message = "coucou serveur";
  json j = message;

  // 2. Convertir en CBOR
  std::vector<uint8_t> cborData = json::to_cbor(j);

  // 3. Ouvrir la connexion TCP (Pinggy)
  Send_AT("AT+CAOPEN=0,0,\"TCP\",\"rntgi-185-223-151-250.a.free.pinggy.link\",41735");
  delay(3000);  // attendre que la connexion soit établie

  // 4. Informer le module qu’on va envoyer N octets
  String cmd = "AT+CASEND=0," + String(cborData.size());
  Send_AT(cmd);
  delay(500);  // attendre le prompt '>'

  // 5. Envoyer les octets CBOR
  for (uint8_t byte : cborData) {
    Sim7080G.write(byte);
  }

  Serial.println("[ENVOYÉ] CBOR minimal envoyé");

  // 6. Fermer la connexion proprement
  delay(2000);
  Send_AT("AT+CACLOSE=0");
}


// -----------Utilisation Machine d'état ----------------------->


void everyX(){

  if((millis() - period1) > 3000){
    // switchPipeline();
    //  DisplayLatLngInfo(); // afficher les coordonnéees, nécessite d'activer "initGnssCongif();" dans le setup pour que ca fonctionne
    // displayTimeStamp(); // afficher les coordonnéees, nécessite d'activer "initGnssCongif();" dans le setup pour que ca fonctionne
     loop_CATM1();
    sendMinimalCBORMessage();

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
  // Serial.println(getBatteryLevel()); // fonctionne une fois sur 100 

  // initGnssCongif(); // on peut ensuite utiliser la méthode dans src/context/display pour afficher la latLng() 
  
  setup_CATM1(); // connexion4G :  http://127.0.0.1:5500/documentation/index.html#connexion4G

  // TCP_send();



}


void loop() {

  everyX();
}
