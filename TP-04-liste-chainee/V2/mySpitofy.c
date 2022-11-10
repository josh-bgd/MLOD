//gcc -W -Wall linkedListOfMusic.c mySpitofy.c -o mySpitofy
//  mySpitofy.c
//  
//
//  Created by Josua  on 09/11/2022.
//

#include "linkedListOfMusic.h"

int main(){
    Liste ListeDeMusic = lireMusic("music.csv");
    afficheListe_r(trierMusicParAnnee(ListeDeMusic));
    return 0;
}
