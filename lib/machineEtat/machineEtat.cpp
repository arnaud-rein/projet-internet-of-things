#include "MachineEtat.hpp"

// Constructeur pour initialiser la structure ATCommandTask
ATCommandTask::ATCommandTask(String cmd, String expected, int maxRetries, unsigned long timeout)
    : state(IDLE), command(cmd), expectedResponse(expected), responseBuffer(""), lastSendTime(0),
      retryCount(0), MAX_RETRIES(maxRetries), TIMEOUT(timeout), isFinished(false) {}

// Constructeur de la machine d'état
MachineEtat::MachineEtat() {}

// Implémentation de la machine d’état
void MachineEtat::updateATState(ATCommandTask &task) {
    switch (task.state) {
        case IDLE:
            Serial.println("[IDLE] Prêt à envoyer : " + String(task.command));
            task.retryCount = 0;
            task.responseBuffer = "";
            task.state = SENDING;
            break;

        case SENDING:
            Serial.println("[SENDING] Envoi de : " + String(task.command));
            Sim7080G.println(task.command);
            task.lastSendTime = millis();
            task.state = WAITING_RESPONSE;
            break;

        case WAITING_RESPONSE:
        if (Sim7080G.available()) {
            task.responseBuffer = Sim7080G.readStringUntil('\n');
                task.state = PARSING;
            } else if (millis() - task.lastSendTime > task.TIMEOUT) {
                Serial.println("[TIMEOUT] Pas de réponse pour " + String(task.command));
                task.state = RETRY;
            }
            break;

        case PARSING:
            Serial.println("[PARSING] Réponse reçue : " + task.responseBuffer);
            if (task.responseBuffer.indexOf(task.expectedResponse) >= 0) {
                Serial.println("[SUCCESS] Réponse valide pour " + String(task.command));
                task.isFinished = true;  // ⬅️ Marquer la tâche comme terminée
                task.state = IDLE;
            } else {
                Serial.println("[FAIL] Réponse incorrecte pour " + String(task.command));
                task.state = RETRY;
            }
            break;

        case RETRY:
            if (task.retryCount < task.MAX_RETRIES) {
                task.retryCount++;
                Serial.println("[RETRY] Tentative " + String(task.retryCount) + " pour " + String(task.command));
                task.state = SENDING;
            } else {
                Serial.println("[ERROR] Échec après " + String(task.MAX_RETRIES) + " essais pour " + String(task.command));
                task.state = ERROR;
                task.isFinished = true; // TO DO : remplacer par isBlocked ou function qui reboot 
            }
            break;

        case ERROR:
            Serial.println("[ERROR] Problème avec " + String(task.command));
            task.state = IDLE;
            break;
    }
}
