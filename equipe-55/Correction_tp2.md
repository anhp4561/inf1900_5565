# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Machines à états finis logicielles
+ Section #  : 3
+ Équipe #   : 55
+ Correcteur : Charles Jiang

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |     -0.5       |
| __Résultat partiel__                         | __(1/1.5)__ |

nom de l'etat ne match pas le nom dans le code (ex: `:STATE2` `:STATE1`)

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (/0.5)     |
| Noms de variables décrivent l'intention      | (0/0.5)     |
| Noms de fonctions décrivent l'intention      | (0/0.5)     |
| __Résultat partiel__                         | __(0.5/1.5)__ |

pb2: reading1 et reading2 non significatif
pb2: isStable, non significatif. utilisez (isButtonPressed, isButtonDebounced, etc..)
pb2: utilisation variable global reading1, reading2 (en tant que non const)


## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme 
 + Procédure peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'Internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(1/1.0)__ |


## Indentation   

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Indentation structurée                       | (0/0.5)     |
| Indentation uniforme dans le programme       | (/0.5)     |
| __Résultat partiel__                         | __(0.5/1.0)__ |

switch case indentation
pb2: enum class State declaration


# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |            |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| etc                                          |      x      |
| __Résultat partiel__                         | __(0.5/1.0)__ |

absence de fonction: utilisez des fonctions pour verifier l'appui d'un bouton


## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation appropriée des registres         |      -0.5      |
| Machine à états codée clairement             |     x       |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisées   |            |
| etc                                          |            |
| __Résultat partiel__                         | __(2.5/4.0)__ |

PORTA = PORTA0; -> meilleure facon de d'eteindre PORTA (ex: 0x00) PORTA0 est mieux utilise pour les bitshift (-0.5)

pb1: premier switch case inutile: tous les cas set pressed = true. utilisez directement le 2e switch case et combinez avec une fonction qui verifie l'appui d'un bouton
pb1: vous utilisez les conditions if/else if/else avec 'reset' au lieu d>une machine a etat. 


# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (/1.5)     |
| Absence de fichiers inutiles                 | (/1.5)     |
| __Résultat partiel__                         | __(3/3.0)__ |


## Compilation    

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de messages d'erreurs de compilation | (/1.5)     |
| Absence de messages d'attention (*warning*)  | (/0.5)     |
| __Résultat partiel__                         | __(2/2.0)__ |
   

## Évaluation boîte noire  

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Cas normal de fonctionnement                 | (/2.5)     |
| Cas limites observables                      | (/2.5)     |
| __Résultat partiel__                         | __(5/5.0)__ |

# Résultat

__Total des points: 16.0/20__

# Commentaires du correcteur:

 if (reset == true) equivalent de --> if (reset)


# Basé sur le commit suivant
```
commit 7d32e0480b1eae59133bcab098702770d77f79fe
Author: Anh Pham <anh-tuan.pham@polymtl.ca>
Date:   Mon Jan 31 18:12:43 2022 -0500

    ajout partie 400 Hz pb2
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp2/pb1`
```
make : on entre dans le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/55/tp/tp2/pb1 »
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324a -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c pb1.cpp
avr-gcc -Wl,-Map,exopb1.elf.map -mmcu=atmega324a -o exopb1.elf  pb1.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex exopb1.elf exopb1.hex
make : on quitte le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/55/tp/tp2/pb1 »

```

## Sortie de `make` dans `tp/tp2/pb2`
```
make : on entre dans le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/55/tp/tp2/pb2 »
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c tp2_p2.cpp
avr-gcc -Wl,-Map,p2.elf.map -mmcu=atmega324pa -o p2.elf  tp2_p2.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex p2.elf p2.hex
make : on quitte le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/55/tp/tp2/pb2 »

```
