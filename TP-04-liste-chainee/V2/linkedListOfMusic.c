//gcc -W -Wall linkedList.c linkedListOfMusic.c -o linkedListOfMusic
//  linkedListOfString.c
//  TP_liste-chainee
//
//  Created by Josua  on 08/11/2022.
//

#include "linkedListOfMusic.h"


void afficheElement(Element e){
    Music music = (Music) e;
    printf("--------------\n");
    printf("%s ",music->nom);
    printf("%s ",music->artiste);
    printf("%s ",music->album);
    printf("%s ",music->genre);
    printf("%d ",music->numeroDisque);
    printf("%d ",music->numeroPiste);
    printf("%d\n",music->annee);
}

void detruireElement(Element e) {
    Music music = (Music) e;
    
    free(music->nom);
    free(music->artiste);
    free(music->album);
    free(music->genre);
    free(music);
}

bool equalsElement(Element e1, Element e2){
    Music music1 = (Music) e1;
    Music music2 = (Music) e2;
    
    bool* cmp = malloc(7*sizeof(bool));
    cmp[0]=(strcmp(music1->nom,music2->nom));
    cmp[1]=(strcmp(music1->artiste,music2->artiste));
    cmp[2]=(strcmp(music1->album,music2->album));
    cmp[3]=(strcmp(music1->genre,music2->genre));
    cmp[4]=(music1->numeroDisque==music2->numeroDisque);
    cmp[5]=(music1->numeroPiste==music2->numeroPiste);
    cmp[6]=(music1->annee==music2->annee);
    for (int i=0;i<7;i++){
        if (cmp[i]==false) {
            return false;
        }
    }
    free(cmp);
    return true ;
}

Liste lireMusic(char* fileName){
    
    char buffer[BUFFER_SIZE];
    size_t len;
    FILE* fichier;
    Liste l=NULL;
    fichier=fopen(fileName,"r");
    
    if(fichier==NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s", fileName);
        return EXIT_FAILURE;
    }
    int nombreDeMusique =0;
    
    while(fgets(buffer, BUFFER_SIZE, fichier)!= NULL)
    {
        nombreDeMusique++;
    }
        rewind(fileName);
        
    for (int i = 0; i < nombreDeMusique; i++)
      {
        fgets(buffer, BUFFER_SIZE, fileName);
        buffer[(len = strcspn(buffer, "\n"))] = 0;

        if (i == 0)
          continue;
           
        
        char* buffer_p = buffer;
        char* nom = strsep(&buffer_p, ",");
        char* artiste = strsep(&buffer_p, ",");
        char* album= strsep(&buffer_p, ",");
        char* genre= strsep(&buffer_p, ",");
        int numeroDisque= atoi(strsep(&buffer_p, ","));
        int numeroPiste= atoi(strsep(&buffer_p, ","));
        int annee= atoi(strsep(&buffer_p, ","));
      
        Music music = creerMusic(nom, artiste, album, genre, numeroDisque, numeroPiste, annee);
        l = ajoutFin_r(music, l);
      }
    
        fclose(fichier);
    return l;
    }

Music creerMusic(char* nom, char* artiste, char* album, char* genre, int numeroDisque, int numeroPiste, int annee){
    
    Music music = malloc(sizeof(Music_s));
    music -> nom  = malloc(strlen(nom)*sizeof(char));
    strcpy(music -> nom, nom);
    music -> artiste  = malloc(strlen(artiste)*sizeof(char));
    strcpy(music -> artiste, artiste);
    music -> album  = malloc(strlen(album)*sizeof(char));
    strcpy(music -> album, album);
    music -> genre  = malloc(strlen(genre)*sizeof(char));
    strcpy(music -> genre, genre);
    music -> numeroDisque = numeroDisque;
    music -> numeroPiste = numeroPiste;
    music -> annee = annee;
    return music;
}

Liste trierMusicParAnnee(Liste l){
    
    if (l == NULL)
       return NULL;
    
    bool EncoreDesMusicATrier;
    Liste l_A;
    Liste l_B = NULL;
    
    do
    {
        
        l_A = l;
        bool EncoreDesMusicATrier = false; /*tant que l'on échange deux musiques on recommencera la boucle, si la boucle sst parcourue entièrement sans rien échanger alors out est trié et il ne reste plus rien à faire*/
    
    
        while (l_A->suiv != l_B) /* à chaque itération on déplace la musique la plus récente à la fin*/
        {
            if (((Music)l_A->val)->annee > ((Music)l_A->suiv->val)->annee) /* si true, on fait passer la musique la plus ancienne avant la plus récente dans la liste*/
            {
                Music tmp = l_A->val;
                l_A->val = l_A->suiv->val;
                l_A->suiv->val = tmp;
                detruireElement(tmp);
                EncoreDesMusicATrier = true;
            }
            l_A = l_A->suiv;
        }
        l_B = l_A;
    } while (EncoreDesMusicATrier);

    return l;

}

