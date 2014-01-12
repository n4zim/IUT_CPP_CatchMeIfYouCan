(FR) AJOUTS PAR RAPPORT AU SUJET
========

Changements
--------

Les changements que nous avons apporté au jeu original.


Nous avons ajouté des structures compreneant l'ensemble des paramètres du jeu afin d'aiser le code. Par exemple, nous avons rajouté une structure SGameStatus qui va contenir l'ensemble de l'état la configuration du jeu, comme le numéro de la manche actuelle, la position des players et les code de touches à utiliser pour bouger les playrs. La configuration de gamestatus peut être chargée depuis le fichier .gameconfig. Le jeu va ensuite se charger lui même d'initialiser le jeu correctement en appliquant les paramètres.


Nous avons changé la génération de la carte en ajoutant un générateur d'obstacles aléatoires, générant des formes dont le nombre varia en fonction du niveau de difficulté (choisi aléatoirement par le jeu).


Nous avons ajouté de la musique, avec l'utilisation de la librairie SFML, en particulier sa partie audio pour charger et jouer 
des fichiers sonores. La musique à la particularité d'être dynamique : elle va changer en fonction de l'état du jeu. (chagnement de volume des pistes sonores). 


Nous avons ajouté un système de bonus et de malus, permettant de rajouter un peu de sauce piquante au jeu.


Nous avons ajouté un écran titre et quelques menus afin que le joueur soit plus à l'aise lors du lancement du jeu et commprenne ce qu'il doit faire. 


Nous avons chagné fondamentalement le principe et les règles du jeu :
Un joueur doit chasser l'autre tour à tour et le jeu se joue en temps réel.
Par exemple, au premier round, c'est le joueur 1 qui doit chasser le joueur 2, et inversement pour chque round.
Le terme "temps réel" signifie que les joueurs peuvent jouer en même temps, en appuyant au clavier en même temps pour rendre le jeu plus frénétique. Les joueurs peuvent donc envoyer leur input *en même temps*, à condition qu'ils martèlent leur clavier (ne par resté enfoncé sur un bouton).


Méthode de test et de travail
--------

Afin de tester les nouvelles fonctionalités alors que le jeu n'était pas terminé, nous nous étions basés sur un moteur simple (le code de base), en y rajoutant notre code et testant si il fonctionnait bien.


Nous avons aussi utilisé GIT pour gérere les différentes versions du programme et créer quelques branches quand on voulait implémenter une fonctionnalité qui pouvait causer des problèmes.

Ainsi (et aussi grâce à la séparation en plusieurs fichiers), nous avons pu nous partager plus facilement le travail.
