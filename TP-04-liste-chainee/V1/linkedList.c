#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>

#define TODO NULL;

// retourne vrai si l est vide et faux sinon
bool estVide(Liste l) {
    return l == NULL;
}

// créer une liste d'un seul élément contenant la valeur v
Liste creer(Element v){
    Liste l = malloc(sizeof(Cellule));
    if (l==NULL) {

        fprintf(stderr, "Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    l->val = v;
    l->suiv = NULL;
    return l;
}

// ajoute l'élément v en tete de la liste l
Liste ajoutTete(Element v, Liste l) {
    Liste new = creer(v);
    new -> suiv = l;
    return new;
}


/*void afficheElement(Element e) {
    printf("%i ",e);
}*/

// affiche tous les éléments de la liste l
// Attention, cette fonction doit être indépendante du type des éléments de la liste
// utiliser une fonction annexe affiche_element
// Attention la liste peut être vide !
// version itérative

void afficheListe_i(Liste l) {
    Liste p= l;

    while (!estVide(p)){
        afficheElement(p->val);
        p = p->suiv;
    }
    printf("\n");
}

// version recursive
void afficheListe_r(Liste l) {
    if (estVide(l)){
        printf("\n");
    } else{
        afficheElement(l->val);
        afficheListe_r(l->suiv);
    }
}

/*void detruireElement(Element e) {
    // rien faire
}*/

// Détruit tous les éléments de la liste l
// version itérative
void detruire_i(Liste l) {
    Liste suivant, courant = l;

    while (!estVide(courant))
    {
        suivant = courant->suiv;
        detruireElement(courant->val);
        free(courant);
        courant=suivant;
    }
}

// version récursive
void detruire_r(Liste l) {
    if (!estVide(l)){
        detruire_r(l->suiv);
        detruireElement(l->val);
        free(l);
    }
}

// retourne la liste dans laquelle l'élément v a été ajouté en fin
// version itérative
Liste ajoutFin_i(Element v, Liste l) {
    Liste elem = creer(v);
    Liste p = l;

    if (estVide(p)){
        return elem;
    }
    while (!estVide(p->suiv)){
        p = p->suiv;
        p->suiv = elem;
    }
    return l;
}

// version recursive
Liste ajoutFin_r(Element v, Liste l) {
    if (estVide(l))
    {
        return creer(v);
    }
    else {

        l->suiv = ajoutFin_r(v,l->suiv);
        return l;
    }
}

// compare deux elements
/*bool equalsElement(Element e1, Element e2){
    return e1 == e2;
}*/

// Retourne un pointeur sur l'élément de la liste l contenant la valeur v ou NULL
// version itérative
Liste cherche_i(Element v,Liste l) {
    Liste p=l;
    while (!estVide(p) && !equalsElement(v,p->val))
    {
        p=p->suiv;
    }
    return p;
}

// version récursive
Liste cherche_r(Element v,Liste l) {
    if (estVide(l) || equalsElement(v,l->val)){
        return l;
    }
    else
    {
        return cherche_r(v,l->suiv);
    }
}

// Retourne la liste modifiée dans la laquelle le premier élément ayant la valeur v a été supprimé
// ne fait rien si aucun élément possède cette valeur
// version itérative
/* Liste retirePremier_i(Element v, Liste l)
{
    Liste cherche = cherche_i(v, l);
    if (equalsElement(l, cherche))
    {
        l = l->suiv;
        cherche->suiv = NULL;
        detruire_i(cherche);
    }
    else if (!estVide(cherche))
    {
        Liste tmp = l;
        while (!equalsElement(tmp->suiv, cherche))
        {
            tmp = tmp->suiv;
        }
        tmp->suiv = cherche->suiv;
        cherche->suiv = NULL;
        detruire_i(cherche);
    }
    return l;
} */

Liste retirePremier_i(Element v, Liste l)
{
    Liste precedent, p = NULL;
    
    if (estVide(p)){
        return l;
    }
    if(equalsElement(l->val, v)){
        p=l->suiv;
        l->suiv=NULL;
        detruire_r(l);
        return p;
    }
    
    precedent =l;
    p=l->suiv;
    while (!estVide(p) && !equalsElement(p->val, v)) {
        precedent = p;
        p = p->suiv;
    }
    
    if (!estVide(p)){
        // on a trouvé v
        precedent ->suiv = p->suiv;
        p->suiv = NULL;
        detruire_r(p);
    }
    return l;
}


// version recursive
Liste retirePremier_r(Element v, Liste l) {
    if (!estVide(cherche_i(v,l))) {
        return l;
    }

    if (equalsElement(v, l->val))
    {
        Liste tmp = l->suiv;
        l->suiv = NULL;
        detruire_r(l);
        return tmp;

    }
    else {
        l->suiv = retirePremier_r(v, l->suiv);
        return l;
    }
}




void afficheEnvers_r(Liste l) {
    if (!estVide(l))
    {
        afficheEnvers_r(l->suiv);
        afficheElement(l->val);
    }
}


