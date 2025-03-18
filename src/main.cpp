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



String convertTimestampToLocalTime(String utcTimestamp, int timeOffset) {
  // Extraction des valeurs du timestamp (yyyyMMddhhmmss.sss)
  int year = utcTimestamp.substring(0, 4).toInt();    // Année (ex: 2025)
  int month = utcTimestamp.substring(4, 6).toInt();   // Mois (ex: 03)
  int day = utcTimestamp.substring(6, 8).toInt();     // Jour (ex: 18)
  int hour = utcTimestamp.substring(8, 10).toInt();   // Heure UTC (ex: 15)
  int minute = utcTimestamp.substring(10, 12).toInt(); // Minute (ex: 46)
  int second = utcTimestamp.substring(12, 14).toInt(); // Seconde (ex: 53)

  // Ajout du décalage horaire
  hour += timeOffset;

  // Gérer les dépassements de jour si l'heure dépasse 23h59
  if (hour >= 24) {
      hour -= 24;  // On revient à une heure valide
      day += 1;     // On passe au jour suivant
  } else if (hour < 0) {
      hour += 24;  // On revient à une heure valide
      day -= 1;     // On passe au jour précédent
  }

  // Gérer le dépassement du mois
  if (day > 31) { // Ce n'est pas parfait (pas de vérification des mois à 30 jours)
      day = 1;
      month += 1;
  }
  if (month > 12) {
      month = 1;
      year += 1;
  }

  // Formater la date et l'heure locale
  String localTime = String(year) + "/" + (month < 10 ? "0" : "") + String(month) + "/" +
                     (day < 10 ? "0" : "") + String(day) + " " +
                     (hour < 10 ? "0" : "") + String(hour) + ":" +
                     (minute < 10 ? "0" : "") + String(minute) + ":" +
                     (second < 10 ? "0" : "") + String(second);

  return localTime;
}


void getLatLng(String gnssData){
  int index = 0;   // Compteur pour suivre le nombre de valeurs extraites
  int start = 0;   // Position de départ pour extraire une valeur
    int end = 0;     // Position de fin de la valeur extraite

    String values[19]; // Tableau pour stocker les différentes valeurs séparées par des virgules

    // Boucle pour parcourir toute la chaîne et extraire les valeurs une par une
    while ((end = gnssData.indexOf(',', start)) != -1 && index < 19) {
        // Extraire la sous-chaîne entre "start" et la première virgule trouvée
        values[index++] = gnssData.substring(start, end);
        // Déplacer "start" après la virgule pour la prochaine extraction
        start = end + 1;
    }

    Serial.println("latitude : " + values[3]);
    Serial.println("longitude : " + values[4]);
    Serial.println("utc date : " + convertTimestampToLocalTime(values[2], 1));
    
  

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
  // Serial.println(get_GNSS_Info());
  String gnssData = get_GNSS_Info();
  getLatLng(gnssData);
  delay(10000);
}
