# TrinovaRobot

Bibliothèque C++ modulaire pour ESP32-S3, développée dans le cadre du programme **TrinovaTech – AI Robotics Core V1 (2026)**. Le projet fournit une API pour piloter des moteurs DC ou des servomoteurs via un PCA9685, ainsi qu’un mode Mock pour tester sans matériel.

> **État du projet :** la configuration PlatformIO cible `esp32-s3-devkitc-1` avec le framework Arduino. Les exemples sont fournis dans `examples/`, mais PlatformIO compile par défaut les fichiers placés dans `src/`. Voir [Compiler et téléverser](#compiler-et-téléverser) pour utiliser un exemple.

## Fonctionnalités

- Deux moteurs DC pilotés par un driver de puissance (H-bridge).
- Jusqu’à 16 servomoteurs contrôlés par un PCA9685 sur I2C.
- Mode Mock sans matériel.
- API de mouvement, arrêt d’urgence logiciel et gestion de timeout.
- Déplacements progressifs des servos avec une durée spécifiée.

## Architecture

```text
Application
    ↓
TrinovaRobot (API et sécurité)
    ↓
IRobotDriver
    ├── MockRobotDriver
    ├── DcMotorDriver
    └── ServoDriver
            ↓
        Pca9685Driver
```

Les interfaces publiques se trouvent dans `include/`, l’implémentation dans `src/`, et les démonstrations dans `examples/`.

## Matériel et prérequis

- ESP32-S3 compatible avec la carte PlatformIO `esp32-s3-devkitc-1`.
- PlatformIO Core ou l’extension PlatformIO IDE pour VS Code.
- Framework Arduino-ESP32, installé automatiquement par PlatformIO selon `platformio.ini`.
- Pour `DcMotors` : deux moteurs DC et un driver de puissance adapté aux moteurs.
- Pour `ServoRobot` : un module PCA9685 et les servomoteurs utilisés.

Aucune dépendance externe PlatformIO (`lib_deps`) n’est déclarée dans la configuration actuelle. Le driver PCA9685 utilise directement `Wire`.

## Installation

Clonez le dépôt et ouvrez son dossier dans PlatformIO :

```bash
git clone https://github.com/youssefismail-hub/TrinovaRobot-.git
cd TrinovaRobot-
```

La configuration existante est dans `platformio.ini` :

```ini
[env:esp32-s3-devkitc-1]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino
monitor_speed = 115200
```

## Utilisation de l’API

Exemple minimal en mode simulation :

```cpp
#include <Arduino.h>
#include <TrinovaRobot.h>

TrinovaRobot robot;

void setup() {
    Serial.begin(115200);

    if (!robot.begin(RobotMode::Mock)) {
        Serial.println("Échec de l'initialisation");
        return;
    }

    robot.forward(40);  // Vitesse comprise entre 0 et 100
}

void loop() {
    robot.update();
}
```

Modes disponibles :

| Mode | Usage |
| --- | --- |
| `RobotMode::Mock` | Simulation des commandes sans matériel |
| `RobotMode::DcMotors` | Deux moteurs DC via le driver de puissance |
| `RobotMode::ServoRobot` | Servomoteurs via PCA9685 |

API principale : `begin(mode)`, `update()`, `forward(speed)`, `backward(speed)`, `turnLeft(speed)`, `turnRight(speed)`, `stop()`, `moveServo(channel, angle, durationMs)`, `emergencyStop()` et `clearEmergencyStop()`.

`moveServo` prend un canal PCA9685 (0–15), un angle (0–180) et une durée facultative en millisecondes. Une durée de `0` demande un déplacement immédiat. Appelez `update()` régulièrement dans `loop()` pour faire progresser les mouvements temporisés et vérifier les timeouts.

## Compiler et téléverser

Les trois fichiers de démonstration sont `examples/01_MockControl/01_MockControl.cpp`, `examples/02_DcMotors/02_DcMotors.cpp` et `examples/03_ServoControl/03_ServoControl.cpp`. PlatformIO ne les sélectionne pas automatiquement : le projet compile `src/main.cpp` par défaut. Pour essayer une démonstration, copiez le contenu du fichier `.cpp` choisi dans `src/main.cpp` (en conservant une seule fonction `setup()` et une seule fonction `loop()`), puis lancez :

```bash
pio run                       # Compiler
pio run -t upload             # Téléverser
pio device monitor            # Ouvrir le moniteur série à 115200 bauds
```

Vous pouvez également compiler, téléverser et ouvrir le moniteur depuis l’interface PlatformIO de VS Code. Le port série peut être précisé si nécessaire, par exemple `pio device monitor -p /dev/ttyUSB0` ; adaptez le port à votre système.

`src/main.cpp` contient actuellement le squelette Arduino créé par PlatformIO, pas une application de démonstration complète. Le fichier `test/test_validation.cpp` contient des vérifications sous forme de sketch Arduino ; il n’est pas configuré comme suite de tests automatisée PlatformIO dans la configuration actuelle.

## Exemples

- **01_MockControl** : commandes de mouvement, servos en simulation et arrêt d’urgence sans matériel.
- **02_DcMotors** : séquence avant, rotations, arrière et arrêt ; nécessite les moteurs et leur driver.
- **03_ServoControl** : déplacement du canal servo 0 entre plusieurs angles ; nécessite le PCA9685 et un servo.

## Câblage moteurs DC

Le driver utilise les broches par défaut suivantes sur l’ESP32-S3 :

| Signal | GPIO | Fonction |
| --- | ---: | --- |
| `DIR1_L` | 5 | Direction moteur gauche |
| `DIR2_L` | 6 | Direction moteur gauche |
| `PWM_L` | 9 | Vitesse moteur gauche |
| `DIR1_R` | 7 | Direction moteur droit |
| `DIR2_R` | 8 | Direction moteur droit |
| `PWM_R` | 10 | Vitesse moteur droit |

Le code définit `DIR1=HIGH`, `DIR2=LOW` comme un sens de rotation et l’état inverse comme l’autre sens. Le sens physique « avant » dépend du câblage du moteur. La fréquence PWM configurée dans `RobotConfig` est de 20 kHz par défaut.

Vérifiez que le driver de puissance accepte la logique 3,3 V de l’ESP32-S3, que le câblage correspond aux broches configurées et que les masses sont communes.

## Câblage PCA9685 et servos

Le driver PCA9685 utilise l’adresse I2C `0x40` et règle sa fréquence à 50 Hz pour les servos. Le câblage documenté pour l’ESP32-S3 est :

| PCA9685 | ESP32-S3 |
| --- | --- |
| `VCC` (logique) | 3,3 V |
| `GND` | GND |
| `SDA` | GPIO 21* |
| `SCL` | GPIO 22* |
| `V+` (alimentation servos) | Alimentation externe adaptée aux servos |

Chaque servo se branche sur un canal du PCA9685, de 0 à 15. *Vérifiez que GPIO 21 et GPIO 22 correspondent bien aux broches I2C de votre carte ; la configuration actuelle appelle `Wire.begin()` sans préciser les broches.*

## Sécurité

- **Ne faites jamais fonctionner les moteurs ou les servos depuis la sortie 3,3 V de l’ESP32.** Utilisez des alimentations dimensionnées pour les charges.
- Utilisez une alimentation adaptée au courant de blocage des moteurs et au courant des servos ; vérifiez les spécifications de chaque composant.
- Reliez les masses des alimentations et de la logique lorsque le montage l’exige, en respectant les recommandations des fabricants.
- Pour les premiers essais, surélevez les roues ou déconnectez les mécanismes et limitez le courant de l’alimentation.
- Vérifiez le brochage, la tension logique du driver et la polarité avant mise sous tension.
- `emergencyStop()` est un arrêt d’urgence **logiciel** ; il ne remplace pas un dispositif matériel de coupure et ne constitue pas une fonction de sécurité certifiée.

Le code contient une limitation logicielle de vitesse, un timeout de commande, une initialisation avec arrêt du driver et des limites d’angle servo. Ces protections ne remplacent pas une conception électrique et mécanique sûre.

## Vérification

Le fichier `test/test_validation.cpp` contient des vérifications manuelles du clamp de vitesse, de l’arrêt d’urgence et du timeout. Il utilise `Serial` et les API Arduino ; consultez les messages sur le moniteur série si vous le compilez comme sketch. Il n’existe pas actuellement de configuration PlatformIO dédiée pour lancer ce fichier comme test automatisé.

## Dépannage

- **Échec de compilation :** vérifiez que le projet est ouvert à la racine et que l’environnement PlatformIO `esp32-s3-devkitc-1` est installé.
- **L’exemple n’est pas compilé :** copiez son contenu dans `src/main.cpp`, comme décrit ci-dessus.
- **Erreur d’initialisation PCA9685 :** vérifiez l’alimentation logique, les connexions SDA/SCL, la masse commune et l’adresse I2C `0x40`.
- **Servo immobile ou instable :** vérifiez l’alimentation externe du servo, la masse commune et le canal choisi. Ne tirez pas le courant du servo depuis l’ESP32.
- **Moteur dans le mauvais sens :** vérifiez les fils du moteur et les entrées de direction du driver ; le sens dépend du câblage.
- **Le moniteur série n’affiche rien :** sélectionnez le bon port et utilisez 115200 bauds.

## Structure du dépôt

```text
include/       En-têtes de l’API et des drivers
src/           Implémentation de la bibliothèque et squelette du programme principal
examples/      Démonstrations Mock, moteurs DC et servos
test/          Vérifications sous forme de sketch Arduino
platformio.ini Configuration PlatformIO
```

## Version et licence

La version indiquée dans la documentation du projet est **v1.0.0**. Vérifiez l’historique des versions pour connaître la version effectivement publiée.

Aucun fichier de licence n’a été identifié à la racine du dépôt. Ajoutez une licence explicite si vous souhaitez autoriser et préciser les conditions de réutilisation du code.

Projet réalisé dans le cadre de **TrinovaTech – AI Robotics Core V1 (2026)**.
