//
//  main.c
//  OpenCProject
//
//  Created by Josua  on 11/10/2022.
//

/**
 Compilation
 clang --std=c99 -W -Wall -o prixTuring main.c

 Exécution
 ./prixTuring < turingWinners.txt > out.txt

 Tests
 diff out.txt turingWinners.txt

 Détection de fuites mémoires
 valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --show-reachable=no ./prixTuring < turingWinners.txt > out.txt
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

typedef struct {
    int annee;
    char* nom;
    char* domaine;}
    gagnant;

/* This function scans a line of text (until \n) and returns a char* that contains all characters on the line (up to 255) excluding \n.
It also ensures the \0 termination.
**WARNING**: The result of this function has been allocated (calloc) by the function */

char* scanLine()
{
    int maxLineSize = 255;
    char c, *line = calloc(maxLineSize+1,sizeof(char));

    scanf("%250[^\n]", line);

    if ( (c = getchar()) != '\n') {
        /* we did not get all the line */
        line[250] = '[';
        line[251] = line[252] = line[253] = '.';
        line[254] = ']';
        // line[255] = '\0'; // useless because already initialized by calloc

        // let's skip all chars untli the end of line
        while (( (c = getchar()) != '\n') && c != EOF) ;
    }

    return line;
}

/* This function scans a line of text (until \n), converts it as an integer and returns this integer */
int scanLineAsInt() {
    int buf;
    scanf("%i\n",&buf);
    return buf;
}

void freeWinners(gagnant* tab,int nbGagnants){
    for(int i=0;i<nbGagnants;i++){
        free(tab[i].nom);
        free(tab[i].domaine);
    }
    free(tab);
}

gagnant* readWinners(int nbGagnant) {
    gagnant* tab;
    tab = malloc(nbGagnant*sizeof(gagnant));
    for(int i=0;i<nbGagnant;i++){
        tab[i].annee=scanLineAsInt();
        tab[i].nom=scanLine();
        tab[i].domaine=scanLine();
    }
    return tab;
}
    
void printWinner(gagnant* tab, int nbGagnants) {
    for(int i=0;i<nbGagnants;i++){
        printf("%i\n%s\n%s\n", tab[i].annee, tab[i].nom, tab[i].domaine);
    }
        
}

gagnant getGagnant(gagnant* tab, int nbGagnants, int annee){
    gagnant test;
    test.annee = 404;
    test.nom = "not found";
    test.domaine = "not found";
    for (int i=0;i<nbGagnants;i++){
        if (tab[i].annee==annee) {
            return tab[i];
        }
    } return test;
}

void afficheGagnant(gagnant G){
    printf("L'année %i Les gagnants ont été : %s \n",G.annee, G.nom);
    printf("Nature des travaux : %s\n",G.domaine);
}

void infosAnnee(int annee){
    int nbGagnants = scanLineAsInt();
    gagnant* tab = readWinners(nbGagnants);
    afficheGagnant(getGagnant(tab, nbGagnants, annee));
}

int prixTuring(void)
{

    int nbGagnants = scanLineAsInt();
    printf("%i\n",nbGagnants);
    
    infosAnnee(2004);
    
    return EXIT_SUCCESS;
}
