
#ifndef SIM7080G_SERIAL_HPP
#define SIM7080G_SERIAL_HPP

#include <Arduino.h>  // Inclusion de la bibliothèque Arduino
#include "ARGALI_PINOUT.hpp"

// Déclaration des variables externes (si utilisées dans plusieurs fichiers)
extern unsigned long period1;

// Déclaration des fonctions
void everyX();
String Send_AT(String message);

#endif // SIM7080G_SERIAL_HPP
