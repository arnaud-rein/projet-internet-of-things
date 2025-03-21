#ifndef INCLUDE_MAIN_HPP
#define INCLUDE_MAIN_HPP


#include <Arduino.h>

//LIB 
#include  "SIM7080G_POWER.hpp"
#include  "SIM7080G_GNSS.hpp"
#include  "PARSER_TIMESTAMP.hpp"
#include "SIM7080G_SERIAL.hpp"
#include "SIM7080G_CATM1.hpp"
#include "SIM7080G_TCP.hpp"
#include "machineEtat.hpp"


//SETUP 
#include "setup/gnss/SETUP_GNSS.hpp"


//CONTEXT
#include "context/display/LatLng/DisplayLatLng.hpp"
#include "context/display/TimeStamp/DisplayTimeStamp.hpp"

enum ProcessStep {
    STEP_INIT,
    STEP_WAIT_SIM,
    STEP_CONFIG_CATM1,
    STEP_WAIT_CNACT,
    STEP_DONE
};



#endif
