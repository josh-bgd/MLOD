//gcc -W -Wall linkedList.c linkedListOfMusic.c -o linkedListOfMusic
//  linkedListOfString.c
//  TP_liste-chainee
//
//  Created by Josua  on 08/11/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"


void afficheElement(Element e){
    printf("%s ",e.nom);
    printf("%s ",e.artiste);
    printf("%s ",e.album);
    printf("%s ",e.genre);
    printf("%d ",e.numeroDisque);
    printf("%d ",e.numeroPiste);
    printf("%d\n",e.annee);
}

void detruireElement(Element e) {
    //free(e);
}

bool equalsElement(Element e1, Element e2){
    bool* cmp = malloc(7*sizeof(bool));
    cmp[0]=(strcmp(e1.nom,e2.nom));
    cmp[1]=(strcmp(e1.artiste,e2.artiste));
    cmp[2]=(strcmp(e1.album,e2.album));
    cmp[3]=(strcmp(e1.genre,e2.genre));
    cmp[4]=(e1.numeroDisque==e2.numeroDisque);
    cmp[5]=(e1.numeroPiste==e2.numeroPiste);
    cmp[6]=(e1.annee==e2.annee);
    for (int i=0;i<7;i++){
        if (cmp[i]==false) {
            return false;
        }
    }
    free(cmp);
    return true ;
}

int main(void){
    Liste l;

    l = NULL;
    printf("estVide(l) = %s\n",estVide(l)?"TRUE":"FALSE");
    
    
    Element Alice;
    Alice.nom = "Them Bones";
    Alice.artiste = "Alice In Chains";
    Alice.album = "Dirt";
    Alice.genre = "Alternative";
    Alice.numeroDisque = 1;
    Alice.numeroPiste = 1;
    Alice.annee = 1992;
    
    l=ajoutTete(Alice, l);
    afficheListe_i(l);
    
    return 0;
}
