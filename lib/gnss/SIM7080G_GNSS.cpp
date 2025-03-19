#include "SIM7080G_GNSS.hpp"


String gnssTurnOn(){
    return Send_AT("AT+CGNSPWR=1");  // Envoie la commande AT+CBC
}

String gnssTurnOff(){
    return Send_AT("AT+CGNSPWR=0");  // Envoie la commande AT+CBC
    
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
    //   Serial.println("utc date : " + convertTimestampToLocalTime(values[2], 1));
  
}

String getValueOfGnssData(String gnssData, int16_t choiceValue){
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

    return values[choiceValue];

}


String getTimeStamp(String gnssData){
    String timeStamp = getValueOfGnssData(gnssData, 2);
    return timeStamp;
}
