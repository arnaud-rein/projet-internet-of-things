#include "SIM7080G_SERIAL.hpp"
// #include "ARGALI_PINOUT.hpp"


String Send_AT(String message){
  unsigned long start_time = millis();
  Sim7080G.println(message);
  String uart_buffer = "";
  char tmp_char = 'A'; 
  while ((millis() - start_time < 1000) && (uart_buffer.endsWith("OK") == false))
  {
    /* code */
    if(Sim7080G.available()){
      tmp_char = Sim7080G.read();
      uart_buffer += tmp_char; 
      Serial.print(tmp_char);
      
    }

  }
  return uart_buffer; 
}