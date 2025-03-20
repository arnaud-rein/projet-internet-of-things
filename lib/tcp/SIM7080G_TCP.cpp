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


// void TCP_send()
// {
    
//     Send_AT("AT+CAOPEN=0,0,\"TCP\",\"rnsgp-2a04-cec0-115b-37ed-392d-81be-5e94-59f4.a.free.pinggy.link\",33777");
    
//     //cf datasheet
//     Send_AT("AT+CASEND=0,6");
//     //attendre le charactère '>' avant d'envoyer la data    
//     Send_AT("cou");

//     //send_TCP_packet_data(&j);

//     Send_AT("AT+CACLOSE=0");
//     //send_AT(AT+CARECV,1460);

// }


void TCP_send()
{
    // Ouvrir une connexion TCP vers Pinggy
    Send_AT("AT+CAOPEN=0,0,\"TCP\",\"rnshw-2a01-cb0a-9014-328d-dcb0-4b5d-50df-772d.a.free.pinggy.link\",43487");
    delay(2000); // Attendre que la connexion soit établie

    // Vérifier que la connexion est bien OK (à gérer avec une fonction qui lit la réponse AT)
    
    // Indiquer au module qu'on va envoyer 10 octets
    Send_AT("AT+CASEND=0,10");
    
    // Attendre le prompt `>` avant d'envoyer les données
    delay(1000); // Petite attente pour que le module soit prêt

    // Envoyer des données (exemple : une requête HTTP GET basique)
    Send_AT("GET /test\n");

    // Attendre la réponse du serveur
    delay(2000);

    // Lire la réponse du serveur (tu dois implémenter une fonction qui affiche la réponse)
    // read_AT_response();

    // Fermer proprement la connexion TCP
    Send_AT("AT+CACLOSE=0");
}


// void TCP_send()
// {
//     // 1️⃣ Ouvrir la connexion TCP avec Pinggy
//     Send_AT("AT+CAOPEN=0,0,\"TCP\",\"rnshw-xxxxx.a.free.pinggy.link\",43487");
//     delay(5000); // Attendre la réponse du module

//     // 2️⃣ Vérifier si la connexion est bien ouverte
//     // (Ajoute une fonction pour lire la réponse si nécessaire)
    
//     // 3️⃣ Indiquer qu'on va envoyer 83 octets (calcul exact)
//     Send_AT("AT+CASEND=0,83"); 
//     delay(15000); // Attendre le prompt '>'

//     // 4️⃣ Envoyer les données en respectant le format HTTP
//     Send_AT("POST /data HTTP/1.1\r\n");
//     Send_AT("Host: rnshw-xxxxx.a.free.pinggy.link\r\n");
//     Send_AT("Content-Type: application/json\r\n");
//     Send_AT("Content-Length: 18\r\n");
//     Send_AT("\r\n");  // Ligne vide essentielle !
//     Send_AT("{\"temperature\":25.5}\r\n");

//     delay(10000); // Attendre pour éviter la coupure

//     // 5️⃣ Lire la réponse (optionnel)
//     // read_AT_response();

//     // 6️⃣ Fermer proprement la connexion TCP
//     Send_AT("AT+CACLOSE=0");
// }
