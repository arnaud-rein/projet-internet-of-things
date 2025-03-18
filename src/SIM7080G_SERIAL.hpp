
#ifndef SIM7080G_SERIAL_HPP
#define SIM7080G_SERIAL_HPP

#include <Arduino.h>  // Inclusion de la bibliothèque Arduino
#include "ARGALI_PINOUT.hpp"
#include "POWER.hpp"

// Déclaration des variables externes (si utilisées dans plusieurs fichiers)


// Déclaration des fonctions
String Send_AT(String message);

#endif // SIM7080G_SERIAL_HPP
