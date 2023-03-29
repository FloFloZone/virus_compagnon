# Virus compagnon MediaPlayer

## Présentation

Nous avons eu comme projet de créer un virus compagnon qui est caché dans MediaPlayer.c en même temps qu'on programme classique de visualisation d'image. Le but de ce virus compagnon est de se recopier à l'identique dans tous les autres executable de son répertoire tout en évitant la sur-infection d'un fichier. Pour cela on doit au préalable faire une copie du précédent éxécutable en lui rajoutant .old à la fin et un '.' au début pour le rendre invisible. Pour ensuite copier à l'identique notre virus.

Je tiens à préciser au préalable que les fichiers .sh qui vont être présentés sont uniquement pour faciliter l'utilisation dans le cadre d'un test (monde fermé) et que ça n'aurait pas vraiment de légitimité dans un monde ouvert

## Programme

Notre répertoire avant toute manipulation est composé de :
* 6 images avec différentes exensions
* notre fichier implémentant le virus donc MediaPlayer.c
* 6 petits programmes de test pour démontrer le bon fonctionnement du virus
* 2 fichier .sh pour faciliter la mise en oeuvre d'un test

Dans la composition de nos 6 petits programmes nous avons :
1. Interface graphique :
* MonPG1.C : un calculateur d'imc en version graphique
* MonPG2.C : une calculatrice en version graphique
* MonPG3.C : un juste prix
* MonPG5.C : un morpion

(pour certaines interfaces graphiques on est passé par des builder pour pouvoir utiliser des .glade pour diversifier)

2. Interface textuelle :
* MonPG4.c : le jeu du Mastermind
* MonPG6.C : un calculateur de la suite de Fibonacci

## Installation 

En ce qui concerne l'installation il vous suffit de faire :
- `sudo ./installateur.sh`

si le fichier n'est pas executable faire :

- `sudo chmod +x ./installateur.sh`

Le fichier installateur est constitué de : 

Une mise à jour de votre system
- `yes | sudo apt update`
- `yes | sudo apt upgrade`
- `yes | sudo apt autoremove`

l'installation des librairies nécessaires à GTK (interface graphique):
- `yes | sudo apt-get install libgtk-3-dev`
- `yes | sudo apt-get install libcanberra-gtk-dev`
- `yes | sudo apt install build-essential`

Ils ont tous `yes` pour pouvoir répondre automatiquement à la question de l'installation

et les droits d'éxécution au fichier compiler.sh pour pouvoir compiler tous les fichiers de démonstrations directement avec le flags et les libs inclus

Ensuite vous pouvez lancer compiler.sh avec : 
- `./compiler.sh`

pour compiler tous les programmes et leur donner les droits d'éxécutions
Par la suite vous pouvez lancer MediaPlayer pour lancer les tests
- `./MediaPlayer.exe`

## Auteurs

Ce projet a été conçu par un groupe de deux personnes : 
- [**PARENTE Florian**](https://www.linkedin.com/in/florian-parent%C3%A9-b78644203/)
- **VERGNE Claudia**

## Licence

Ceci est un projet de sécurité en L3 Informatique ce qui signifie qu'il est simplement à but éducatif.