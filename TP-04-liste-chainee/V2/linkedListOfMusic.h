//gcc -W -Wall -std=c99 linkedList.c linkedListOfMusic.c -o linkedListOfMusic
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
    printf("%s ",(char *) e);
}

void detruireElement(Element e) {
    //free(e);
}

bool equalsElement(Element e1, Element e2){
    return strcmp (e1,e2) == 0 ;
}

int main(void){
    Liste l;

    l = NULL;
    printf("estVide(l) = %s\n",estVide(l)?"TRUE":"FALSE");
    
    l = ajoutTete("Monsieur",l);
    afficheListe_i(l);
    
    l = ajoutTete("Josua",l);
    afficheListe_i(l);
    
    return 0;
}
