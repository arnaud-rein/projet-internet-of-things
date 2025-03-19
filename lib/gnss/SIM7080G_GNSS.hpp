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
void getLatLng(String gnssData);
  