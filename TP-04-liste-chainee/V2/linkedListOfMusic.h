#pragma once

#include "linkedList.h"
#define BUFFER_SIZE 500

typedef struct Music_s {
    char* nom;
    char* artiste;
    char* album;
    char* genre;
    int numeroDisque;
    int numeroPiste;
    int annee;
} Music_s;

typedef Music_s* Music;

Music creerMusic(char* nom, char* artiste, char* album, char* genre, int numeroDisque, int numeroPiste, int annee);

Liste lireMusic(char* fileName);

Liste trierMusicParAnnee(Liste l);
