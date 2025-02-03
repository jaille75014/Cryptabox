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

### Installation d'OpenSSL (si nécessaire)

Sur Debian/Ubuntu :
```bash
sudo apt-get install libssl-dev
```
### Installation de la librairie mysql : 
sur Debian/Ubuntu :
```bash
sudo apt install libmysqlclient-dev
```
