#include "PARSER_TIMESTAMP.hpp"


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



tm convertTimestampToLocalTimeTm(String utcTimestamp, int timeOffset) {

    tm time; 
    // Extraction des valeurs du timestamp (yyyyMMddhhmmss.sss)
    time.annee = utcTimestamp.substring(0, 4).toInt();    // Année (ex: 2025)
    time.mois = utcTimestamp.substring(4, 6).toInt();   // Mois (ex: 03)
    time.jour = utcTimestamp.substring(6, 8).toInt();     // Jour (ex: 18)
   time.heure = utcTimestamp.substring(8, 10).toInt();   // Heure UTC (ex: 15)
    time.minute = utcTimestamp.substring(10, 12).toInt(); // Minute (ex: 46)
    time.seconde = utcTimestamp.substring(12, 14).toInt(); // Seconde (ex: 53)
  
    
    return time;
  }