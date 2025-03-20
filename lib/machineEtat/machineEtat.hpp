#ifndef MACHINE_ETAT_HPP
#define MACHINE_ETAT_HPP

#include <Arduino.h>

// Définition des états de la machine d'état
enum ATState {
    IDLE,
    SENDING,
    WAITING_RESPONSE,
    PARSING,
    RETRY,
    ERROR
};

// Structure pour gérer une tâche AT
struct ATCommandTask {
    ATState state;
    const char* command;
    const char* expectedResponse;
    String responseBuffer;
    unsigned long lastSendTime;
    int retryCount;
    const int MAX_RETRIES;
    const unsigned long TIMEOUT;
    bool isFinished;  // ⬅️ Ajout pour bloquer la réexécution

    ATCommandTask(const char* cmd, const char* expected, int maxRetries, unsigned long timeout);
};

// Classe de la machine d'état
class MachineEtat {
public:
    MachineEtat();
    void updateATState(ATCommandTask &task);
};

#endif
