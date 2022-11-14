# MiniProjet

OLD git : https://github.com/josh-bgd/MiniProjet

# Description du projet
- Ajout de certaines règles au jeu du Snake, un jeu que j'apprécie énormément.
# Quelles modifications ?
- Le score augmente de 15 fois la taille du snake en mangeant un fruit bleu.
- Ajout d'un "BadFruit" de couleur rouge qui retrécit la taille du serpent de "1" si celle-ci est supérieure à 1 sinon Game Over : le Bad fruit peut s'avérer utile mais peut s'avérer être vicieux mais permet de gagner un nombre de point supérieur à celui du fruit (score augmente de 30 fois la taille du snake). 
- Ajout d'un "shrinkFruit" de couleur jaune permettant au joueur d'augmenter considérablement son score en contrepartie d'un retrait de case tous les "4 pas" (score augmente de 800 fois la taille du snake à chaque pas). Tant que le joueur n'a pas fait manger à son serpent un nouveau fruit bleu, le retraicissement continue jusqu'à ce qu'il ne reste plus de case au serpent. 
- Possibilité de rentrer un pseudo (max 5 char) avant de jouer et de le changer a la find e la partie si on change de joueur.

- Changement primaires comme certaines couleurs, pour moderniser le jeu
- possiblement une musique de fond
# Comment compiler
je compile sur NotePad++ de WINDOWS (j'ai installé BOOTCAMP sur mon mac afin de passer en Windows du à des soucis d'installation de raylib dessus)
# Comment exécuter
j'ouvre le dossier raylib, dans le raylib.h j'ouvre mon fichier ".c" puis une fois le code écris : F6, une fenêtre de Bash apparait puis "Ok" et le jeu se lance 
# Comment utiliser le projet
screenshot(s) du jeu
Les règles sont celle du jeu snake, être le plus long serpent sans toucher les bords du plateau ou encore toucher son propre corps
# URL vidéo de démo
https://youtu.be/P_FfwQ9Kxrw
# Quelques détails sur votre implémentation
 - Un snake est une structure composée d'une position, d'une vitesse de mouvement, d'une couleur et d'une taille.
 - Un fruit est une structure composée d'une couleur, d'une taille, d'une position, et d'un bouléen de présence ou non sur la carte.
 - Les deux structures permettent de créer des objets sur la carte (grille) et de faire déplacer le snake à l'aide des touches flèches du clavier.
# Extensions / améliorations possibles
— Faire une vidéo (un teaser) entre 3 min et 5 mi
