#ifndef SIM7080G_CATM1
#define SIM7080G_CATM1



#include <Arduino.h> 
#include "ARGALI_PINOUT.hpp"
#include "SIM7080G_SERIAL.hpp"
#include "SIM7080G_GNSS.hpp"

void setup_CATM1();

void loop_CATM1();


int csqNumber(String dataLTE);


#endif

