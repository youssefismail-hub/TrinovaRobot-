# TrinovaRobot

Bibliothèque C++ modulaire pour ESP32-S3 permettant le contrôle sécurisé de :

-  Deux moteurs DC
-  Servomoteurs via PCA9685 (I2C)
-  Gestion avancée de sécurité (timeout, emergency stop, limites mécaniques)
-  Mode simulation (Mock)

Projet réalisé dans le cadre du programme **TrinovaTech – AI Robotics Core V1 (2026)**.

---

#  Architecture

L'architecture respecte strictement la séparation imposée par le cahier des charges :

```
Utilisateur
    ↓
TrinovaRobot (API + Sécurité)
    ↓
IRobotDriver
    ↓
    ├── MockRobotDriver
    ├── DcMotorDriver
    └── ServoDriver
        ↓
    Pca9685Driver
```

- L'API publique est isolée.
- Les drivers matériels sont indépendants.
- La sécurité est centralisée.
- Le système compile même sans matériel (mode Mock).

---

#  Modes disponibles

| Mode | Description | Usage recommandé |
|------|------------|-----------------|
| `RobotMode::Mock` | Simulation complète sans matériel | Tests unitaires et validation logicielle |
| `RobotMode::DcMotors` | Contrôle de deux moteurs DC | Robot mobile à roues |
| `RobotMode::ServoRobot` | Contrôle servomoteurs via PCA9685 | Robot articulé / bras robotique |

---

#  Câblage moteurs DC

Le système suppose l'utilisation d'un **driver de puissance (type L298N, TB6612, H-Bridge)**.

Chaque moteur possède :

| Signal | Rôle | Description |
|--------|------|------------|
| DIR1_L | Direction moteur gauche 1 | Définit le sens de rotation |
| DIR2_L | Direction moteur gauche 2 | Inversion logique du sens |
| PWM_L  | Vitesse moteur gauche | Signal PWM 0–255 |
| DIR1_R | Direction moteur droit 1 | Définit le sens de rotation |
| DIR2_R | Direction moteur droit 2 | Inversion logique du sens |
| PWM_R  | Vitesse moteur droit | Signal PWM 0–255 |

###  Fonctionnement

- `DIR1 = HIGH` et `DIR2 = LOW` → rotation avant
- `DIR1 = LOW` et `DIR2 = HIGH` → rotation arrière
- PWM = 0 → arrêt
- Mode freinage : DIR1 et DIR2 à HIGH

###  Affectation des pins ESP32-S3

| Signal | ESP32-S3 Pin |
|--------|-----------|
| DIR1_L | 5 |
| DIR2_L | 6 |
| PWM_L  | 9 |
| DIR1_R | 7 |
| DIR2_R | 8 |
| PWM_R  | 10 |



---

# Câblage PCA9685 (Servomoteurs)

Le module PCA9685 est un contrôleur PWM 16 canaux utilisant le protocole **I2C**.

###  Connexions I2C :

| PCA9685 | ESP32-S3 |
|----------|-----------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 (I2C Data) |
| SCL | GPIO 22 (I2C Clock) |

###  Description des ports

- **SDA (Serial Data)** : ligne de données I2C
- **SCL (Serial Clock)** : ligne d'horloge I2C
- **VCC** : alimentation logique
- **GND** : masse commune

Chaque servo se connecte sur un canal :

```
Channel 0 → Servo 0
Channel 1 → Servo 1
...
Channel 15 → Servo 15
```

---

#  Sécurité importante

La sécurité matérielle est une exigence non négociable du projet.

##  Règles obligatoires :

-  L'alimentation moteurs DOIT être séparée de l'ESP32.
-  L'alimentation servos DOIT être séparée de l'ESP32.
-  Ne jamais alimenter moteurs/servos via le 3.3V logique.
-  Vérifier le courant de blocage des moteurs.
-  Toujours tester avec une alimentation limitée en courant.

##  Sécurités logicielles intégrées :

- Clamp automatique vitesse 0–100
- Timeout automatique moteur
- EmergencyStop prioritaire
- Limites mécaniques servo
- Initialisation sûre au démarrage

---

#  Exemples fournis

Le projet contient trois exemples compilables :

## 1️ 01_MockControl

- Test complet sans matériel
- Validation API
- Démonstration emergency stop

## 2️ 02_DcMotors

- Test avant / arrière
- Test rotation gauche / droite
- Test stop et freinage


## 3️ 03_ServoControl

- Contrôle servo réel
- Mouvement progressif
- Validation limites mécaniques
- Démonstration interpolation non bloquante

---

#  Tests réalisés

Voir le fichier :

```
test/test_validation.cpp 
```


---

#  Compilation

Environnement cible :

- ESP32-S3
- PlatformIO
- Framework Arduino-ESP32