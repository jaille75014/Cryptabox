# **CryptaBox** - Sécurisation et Transfert de Fichiers

**CryptaBox** est une application en C permettant de sécuriser, stocker et transférer des fichiers de manière sécurisée grâce à un chiffrement robuste. Ce projet vise à offrir une solution simple pour protéger les fichiers sensibles à l'aide de mots de passe, tout en permettant leur transfert sécurisé entre utilisateurs sur un réseau.

## Fonctionnalités

- **Sécurisation des fichiers** : Vous pouvez sécuriser des fichiers et répertoires en les chiffrant à l'aide d'un mot de passe, garantissant ainsi la confidentialité des données.
  
- **Envoi sécurisé de fichiers** : Les utilisateurs peuvent envoyer des fichiers de manière sécurisée à d'autres utilisateurs via un réseau, avec un chiffrement de la communication.
  
- **Gestion des utilisateurs et historisation** : Le terminal conserve un historique des actions effectuées et permet une gestion basique des utilisateurs pour contrôler l'accès aux fichiers et aux fonctionnalités.

## Prérequis

Avant d'exécuter ce projet, vous devez avoir les outils suivants installés sur votre machine :
- Un compilateur C (ex : GCC)
- La bibliothèque OpenSSL pour les fonctions de chiffrement

### Installation d'OpenSSL 

Sur Debian/Ubuntu :
```bash
sudo apt-get install libssl-dev
```
### Installation de la librairie mysql : 
sur Debian/Ubuntu :
```bash
sudo apt install libmysqlclient-dev
```
## 1; Installation du projet : 
Téléchargez le fichier `cryptabox_1.0-1_amd64.deb` depuis la section "Releases" et installez-le avec :
```bash
sudo dpkg -i cryptabox_1.0-1_amd64.deb
sudo apt-get -f install
```
## 2. Compilation manuelle

Pour compiler le projet depuis le code source, suivez les étapes ci-dessous :
Clonez le dépot : 
```
git clone https://github.com/jaile75014/cryptabox.git
```
cd cryptabox

Compilez le projet :
```
make
```
Lancez l'exécutable :
```
    ./bin/cryptabox
```
3. Installation locale

Pour installer manuellement l'exécutable dans /usr/bin/ :
```
sudo make install
```


 **Arborescence du projet**

Voici la structure du projet pour vous repérer facilement :
```Plaintext
cryptabox/
├── debian/                   # Fichiers pour le packaging Debian
├── src/                      # Code source principal
│   ├── main.c                # Point d'entrée principal du programme
│   ├── cli/
│   │   ├── commands.c        # affichage des commandes utilisateur via le terminal
│   │   ├── commands.h        # Header correspondant à commands.c
│   ├── network/
│   │   ├── client.c          # Fonctionnalités pour le client réseau
│   │   ├── client.h          # Header correspondant à client.c
│   │   ├── server.c          # Fonctionnalités pour le serveur réseau
│   │   ├── server.h          # Header correspondant à server.c
│   ├── security/
│   │   ├── crypto.c          # Fonctions de chiffrement
│   │   ├── crypto.h          # Header correspondant à crypto.c
│   ├── user_management/
│   │   ├── auth.c            # Gestion de l'authentification des utilisateurs
│   │   ├── auth.h            # Header correspondant à auth.c
│   │   ├── history.c         # Historisation des actions des utilisateurs
│   │   ├── history.h         # Header correspondant à history.c
│   │   ├── users.c           # creation et gestion des comptes utilisateurs
│   │   ├── users.h           # Header correspondant à users.c
├── include/                  # Headers globaux
│   ├── global.h              # Déclarations globales pour tout le projet
├── bin/                      # Fichiers binaires après compilation
│   ├── cryptabox             # Exécutable final
├── obj/                      # Fichiers objets intermédiaires
├── Makefile                  # Script de compilation et installation
├── README.md                 # Documentation
```
## Auteurs :  
```Plaintext
  - Jules
  - Alban
  - Rafael
```
<les3mousquetaireesgi@gmail.com>

