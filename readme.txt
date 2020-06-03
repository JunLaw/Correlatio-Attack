Pour compiler le générateur de geffe:

1) Aller dans le dossier generateur_geffe dans le terminal
2) Dans le terminal/bash lancer la commande make build : les fichiers de compilation/edition de lien/executable seront générés
3) Lancer make pour executer l'exemple dans le makefile

Si vous voulez utilisez d'autre entrée pour le générateur voici la procédure à suivre : 
1) aller dans le makefile
2) Changer la ligne de commande dans run:
3) le premier argument correspond à la fonction de filtrage il vous faudra obligatoirement inserer 8 chiffres soit 0 soit 1 cela correspond à f0,f1...f7 dans l'enoncé
4) le deuxieme argument correspond à l'initialisation des LFSR il vous faudra les rentrer du LFSR1 au LFSR3 avec 16 bits chacun, le deuxieme argument doit être de longueur 48 ne pas rajouter d'espace entre chaque initialisation
exemple : 110101011010101010100101010100101011011010101010
LFSR 1 :  1101010110101010
LFSR 2 :  1010010101010010
LFSR 3 :  1011011010101010
5) le troisième argument sera un nombre entier positif

Il affichera le nombre de bits générés par le geffe

Pour compiler l'attaque par correlation (incomplete car ne marche pas):

1) Aller dans le dossier correlation_attack dans correl/
2) dans le terminal lancer la commande make correl puis make runcorrel
3) Un générateur de suite binaire à 256 bits est fourni dans le dossier pour le lancer taper la commande make rand il affichera la suite binaire et l'ecrira dans le fichier rand.txt 
4) vous pouvez lancer l'executable manuellement avec la commande ./correl suivi d'une suite chiffrante de 256 bits

Il affichera les initialisation des trois LFSR par rapport à la suite chiffrante donnée et la fonction de filtrage cité dans l'exercice

Pour compiler le calculateur de taux de correlation d'une suite chiffrante

1) Aller dans le dossier compute_correlation dans correl/
2) Lancer le Makefile avec make
3) pour executer manuellement le programme lancer ./compute suivi d'une fonction de filtrage à 8 bits

Il affichera la coincidence entre les 1 et 0 ainsi que le taux de correlation totale entre la fonction de filtrage et les trois LFSR

Pour compiler le chiffrement de feistel à 1 tour

1) Aller dans le dossier Feistel/
2) commande pour compiler gcc cryptanalyse_1_tour.c -o feistel
3) sinon make run
3) pour compiler manuellement faites ./feistel suivi de : une suite de 32 bits pour X0r (espace), une suite 32 bits pour X0l,une suite 32 bits pour X1r, une suite pour X1l

Il affichera les clés K0 et K1
