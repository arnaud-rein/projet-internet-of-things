
# 🌐 Projet IoT – ESP32 + SIM7080G

Ce projet utilise une carte **ESP32** connectée à un module **SIM7080G** pour envoyer des données vers un serveur distant via le réseau **4G (CAT-M1 / NB-IoT)**.

## 📦 Matériel utilisé

- ✅ ESP32 (ex : Adafruit QT Py ESP32-C3)
- ✅ Module SIM7080G (communication AT via UART)
- ✅ Carte SIM compatible CAT-M1 ou NB-IoT
- ✅ Antenne LTE
- ✅ Accès Internet mobile (réseau 4G)

---

## 📁 Structure du projet

- `src/` – Code principal de l'ESP32 (PlatformIO)
- `lib/` – Modules (gestion AT, machine d’état, etc.)
- `documentation/` – Documentation HTML (avec index.html)

---

## 📚 Documentation

La documentation du projet est disponible dans le fichier :



### ▶️ Pour l’ouvrir facilement :

1. Installe l’extension **Live Server** dans VS Code  
2. Clic droit sur `index.html`  
3. Sélectionne **"Open with Live Server"**

💡 Cela ouvrira automatiquement la page dans ton navigateur pour une lecture fluide.

---

## 🚀 Fonctionnalités implémentées

- 📡 Connexion réseau via SIM7080G
- 📤 Envoi de données en CBOR (format binaire compact)
- 🧠 Machine d'état pour gérer les échanges AT de manière non bloquante
- 🌐 Envoi des données sur un serveur distant via TCP/Pinggy

---

## 🛠️ Dépendances

- PlatformIO avec framework `arduinoespressif32`
- Bibliothèque JSON [nlohmann/json](https://github.com/nlohmann/json)
- Librairie base64 (optionnelle pour debug)

---

## ✅ À venir

- Lecture de capteurs
- Encapsulation des données dans des structures JSON/CBOR plus complètes
- Réception de commandes depuis le serveur

---

## 🧑‍💻 Auteur

Ce projet a été réalisé dans le cadre d’un projet IoT étudiant – encadré par JUNIA.

---

## 🧩 Structure avancée du projet

Pour garder un code propre, modulaire et évolutif, j’ai séparé certaines responsabilités en plusieurs dossiers spécifiques :

### 📁 `context/`
Ce dossier contient tous les objets globaux et partagés du projet (par exemple : objets `MachineEtat`, `ATCommandTask`, buffers, états, etc.).

> 🔄 Il joue un peu le rôle de **"contexte d’exécution"** que l’on pourrait retrouver dans d'autres langages ou frameworks.

Cela permet d'éviter d’encombrer le fichier `main.cpp` avec des déclarations trop nombreuses ou globales.

---

### 📁 `setup/`
Ce dossier contient les fonctions d’initialisation du projet (setup réseau, setup capteurs, setup AT, etc.).

> 🛠 Il permet d’isoler toute la configuration du matériel et du logiciel au démarrage.

Cela rend le fichier `setup()` plus lisible et facilite l'ajout de nouveaux modules à l’avenir.

---

### 🎯 Pourquoi cette structure ?

✅ **Séparation des responsabilités**  
✅ **Lisibilité améliorée**  
✅ **Facilement maintenable et extensible pour le futur**  
✅ **Évite de "polluer" les fichiers principaux (`main.cpp`, `lib/`, etc.)**

Cette organisation est pensée pour **accompagner le projet sur le long terme**, notamment si on ajoute plus de protocoles, de capteurs, ou une logique serveur plus complexe.


