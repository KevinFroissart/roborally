# Projet Roborally

## Description

Ce projet vise à créer un joueur automatique pour le jeu [Roborally](https://fr.wikipedia.org/wiki/RoboRally).
Le sujet est disponible en pdf [sur la page du cours](https://liris.cnrs.fr/vincent.nivoliers/lifap6/Supports/Projet/roborally.pdf).

## Utilisation

### Comment éxecuter le programme

```
$ git clone https://github.com/KevinFroissart/roborally.git
$ cd roborally/Src
$ make
$ ./bin/test_board
```

##### Requirements :

```
GCC : sudo apt install build-essential
```

## Structure du projet

    roborally/
    ├─ Src/             code
    │  ├─ appdata/      js app
    │  ├─ bin/          binaries
    |  ├─ headers/      headers
    |  ├─ obj/          objects
    |  ├─ src/          source code
    |  ├─ board.txt     board
    │  └─ Makefile      makefile
    └─ sujet/           project subject

## Meta

Auteurs : https://github.com/KevinFroissart/roborally/graphs/contributors
