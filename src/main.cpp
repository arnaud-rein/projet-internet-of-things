
#include "INCLUDE_MAIN.hpp"
unsigned long period1; 


MachineEtat machine;

// Création de deux tâches AT indépendantes
ATCommandTask task1("AT+CAOPEN=0,0,\"TCP\",\"rndav-2a01-cb0a-9014-328d-dcb0-4b5d-50df-772d.a.free.pinggy.link\",35427", "OK", 15, 15000);
// ATCommandTask task2("AT+COPS?", "+COPS:", 3, 3000);
  void everyX(){
    if((millis() - period1) > 3000){
      period1 = millis();
      // DisplayLatLngInfo();
      // displayTimeStamp();
      // loop_CATM1();
      if(!task1.isFinished){
        machine.updateATState(task1);

      }else{
        delay(2000); // Attendre que la connexion soit établie

        // Vérifier que la connexion est bien OK (à gérer avec une fonction qui lit la réponse AT)
        
        // Indiquer au module qu'on va envoyer 10 octets
        Send_AT("AT+CASEND=0,10");
        
        // Attendre le prompt `>` avant d'envoyer les données
        delay(1000); // Petite attente pour que le module soit prêt
    
        // Envoyer des données (exemple : une requête HTTP GET basique)
        Send_AT("GET /test\n");
    
        // Attendre la réponse du serveur
        delay(2000);
    
        // Lire la réponse du serveur (tu dois implémenter une fonction qui affiche la réponse)
        // read_AT_response();
    
        // Fermer proprement la connexion TCP
        Send_AT("AT+CACLOSE=0");
      }
      // machine.updateATState(task2);
      // delay(100); // Éviter de saturer le CPU
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
  setup_CATM1();
  
  // TCP_send(); 
  period1 = millis();





}


void loop() {

  everyX();
}
