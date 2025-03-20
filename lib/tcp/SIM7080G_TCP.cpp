#include "SIM7080G_TCP.hpp"

// // void TCP_send()
// // {
    
// //     Send_AT("AT+CAOPEN=0,0,\"TCP\",\"rnkuy-2a04-cec0-115b-37ed-392d-81be-5e94-59f4.a.free.pinggy.link\",36585");
    
// //     //cf datasheet
// //     Send_AT("AT+CASEND=0,6");
// //     //attendre le charactère '>' avant d'envoyer la data    
// //     Send_AT("coucou");

// //     //send_TCP_packet_data(&j);

// //     Send_AT("AT+CACLOSE=0");
// //     //Send_AT(AT+CARECV,1460);

// // }


// #include "SIM7080G_TCP.hpp"

// // Fonction pour envoyer une commande AT et attendre une réponse spécifique
// String Send_AT_WaitResponse(String command, String expectedResponse, long timeout) {
//     unsigned long start_time = millis();
//     String response = "";
//     Serial.println("📡 Envoi : " + command);
//     Send_AT(command);  // Envoi de la commande AT

//     // Lecture de la réponse avec timeout
//     while (millis() - start_time < timeout) {
//         if (Serial.available()) {
//             char c = Serial.read();
//             response += c;
//             Serial.print(c); // Affiche la réponse en temps réel

//             // Vérifier si la réponse contient la réponse attendue
//             if (response.indexOf(expectedResponse) != -1) {
//                 Serial.println("✅ Réponse reçue : " + response);
//                 return response;
//             }
//         }
//     }

//     Serial.println("⛔ Timeout ou réponse incorrecte : " + response);
//     return "";  // Retourne une réponse vide en cas d'échec
// }

// void TCP_send() {
//     Serial.println("🚀 Démarrage de TCP_send()...");

//     // 1️⃣ **Ouvrir une connexion TCP**
//     String openResponse = Send_AT_WaitResponse("AT+CAOPEN=0,0,\"TCP\",\"rnsgp-2a04-cec0-115b-37ed-392d-81be-5e94-59f4.a.free.pinggy.link\",33777", "OK", 10000);
//     if (openResponse.indexOf("OK") == -1) {
//         Serial.println("❌ Échec de connexion au serveur !"  + openResponse);
//         return;
//     }

//     // 2️⃣ **Préparer l'envoi de données**
//     String sendResponse = Send_AT_WaitResponse("AT+CASEND=0,6", ">", 5000);
//     if (sendResponse.indexOf(">") == -1) {
//         Serial.println("❌ Le module n'attend pas les données !");
//         return;
//     }

//     // 3️⃣ **Envoyer les données**
//     Send_AT("WESH!");
//     Serial.println("📨 Données envoyées : WESH!");

//     // 4️⃣ **Vérifier si le serveur a bien reçu les données**
//     String recvResponse = Send_AT_WaitResponse("AT+CARECV=0,100", "OK", 5000);
//     Serial.println("📩 Réponse du serveur : " + recvResponse);

//     // 5️⃣ **Fermeture de la connexion TCP**
//     String closeResponse = Send_AT_WaitResponse("AT+CACLOSE=0", "OK", 5000);
//     if (closeResponse.indexOf("OK") != -1) {
//         Serial.println("🔒 Connexion fermée avec succès !");
//     } else {
//         Serial.println("⚠️ Erreur lors de la fermeture de la connexion.");
//     }
// }


void TCP_send()
{
    
    Send_AT("AT+CAOPEN=0,0,\"TCP\",\"rnsgp-2a04-cec0-115b-37ed-392d-81be-5e94-59f4.a.free.pinggy.link\",33777");
    
    //cf datasheet
    Send_AT("AT+CASEND=0,6");
    //attendre le charactère '>' avant d'envoyer la data    
    Send_AT("cou");

    //send_TCP_packet_data(&j);

    Send_AT("AT+CACLOSE=0");
    //send_AT(AT+CARECV,1460);

}