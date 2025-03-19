#include <Arduino.h> 
#include "ARGALI_PINOUT.hpp"
#include "SIM7080G_SERIAL.hpp"

String gnssTurnOn();
String gnssTurnOff();
String check_GNSS_Status() ;

String get_GNSS_Info(); 
String get_GNSS_Mode();
String getValueOfGnssData(String gnssData, int16_t choiceValue);
String getTimeStamp(String gnssData);
String getRunStatus(String gnssData);
String getAltitude(String gnssData);
String getLng(String gnssData);
String getLat(String gnssData);
String getTimeStamp(String gnssData);
String getFixStatus(String gnssData);
String getLatLng(String gnssData);



struct Gnss{
    String runStatus;
    String fixStatus;
    String timeStamp; 
    String latitude; 
    String longitude; 
    String altitude;
};

Gnss getGnssResponse();