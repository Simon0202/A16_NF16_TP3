#include "tp3.h"

T_Produit *creerProduit(char *marque, float prix, enum quality qualite,unsigned int quantite){
    T_Produit *NewProduit = malloc(sizeof(struct Produit));
    NewProduit->marque = marque;
    NewProduit->prix=prix;
    NewProduit->qualite = qualite;
    NewProduit->quantite_en_stock = quantite;
    
    return NewProduit;
}

T_Rayon *creerRayon(char *nom)
{
    T_Rayon *NewRayon = malloc(sizeof(struct Rayon));
    NewRayon->nom_rayon = nom;
    NewRayon->nombre_produit = 0;
    NewRayon->premier = NULL;
    NewRayon->suivant = NULL;
    return NewRayon;
}

T_Magasin *creerMagasin(char *nom)
{
    T_Magasin *NewMagasin = malloc(sizeof(struct Magasin));
    NewMagasin->nom = nom;
    NewMagasin->premier = NULL;
    return NewMagasin;
}


//Q3
int ajouterProduit(T_Rayon *rayon, T_Produit *produit){
    T_Rayon *currentRayon=rayon;
    if(currentRayon->premier == NULL){
        currentRayon->premier = produit;
        currentRayon->nombre_produit++;
    }
    return 1;
    if (currentRayon->premier->prix > produit->prix) {
        produit->suivant = currentRayon->premier->suivant;
        rayon->premier = produit;
        rayon->nombre_produit++;
        return 1;
    }
    if(rayon->premier->prix == produit->prix)
        return 0;
    else{
        p = rayon->premier;
        while( p->suivant != NULL && p->suivant->prix < produit->prix)
            p = p->suivant;
        if(p->suivant == NULL){
            p->suivant = produit;
            rayon->nombre_produit++;
            return 1;
        }
        else{
            if(p->suivant->prix == produit->prix)
                return 0;
            else{
                produit->suivant = p->suivant;
                p->suivant = produit;
                rayon->nombre_produit++;
                return 1;
            }
        }
    }
    return 0;
}
    
int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon){
    //Recuperation du magasin afin de ne pas perdre l'adresse du magasin
    //Il comprend la liste simplement chainée des rayons
    T_Magasin *currentMagasin = magasin;
    
    //On verifie qu'un magasin existe
    if(currentMagasin==NULL){
        printf("Il n'y a pas de magasin, on ne peut ajouter le rayon");
        return 0;
    }
    //On verifie si le magasin contient dejà des rayons
    if(currentMagasin->premier == NULL){
        currentMagasin->premier = rayon;
        return 1;
    }
    else{
        //Sinon on va parcourir la liste simplement chainées
        while(strcmp(currentMagasin->premier->suivant->nom_rayon,rayon->nom_rayon)&&currentMagasin->premier->suivant!=NULL){
            currentMagasin->premier = currentMagasin->premier->suivant;
        }
        currentMagasin->premier->suivant= rayon;
        return 1;
    }
}

/*
int totalProduitDansUnRayon(T_Rayon *rayon){
    T_Rayon *currentRayon = rayon;
    unsigned int total = 0;
    if(currentRayon==NULL){
        exit(EXIT_FAILURE);
    }
    else if (currentRayon->premier==NULL){
        return total;
    }
    else{
        while(currentRayon->premier!=NULL){
            total+=currentRayon->premier->quantite_en_stock;
            currentRayon->premier = currentRayon->premier->suivant;
        }
        return total;
    }
}
*/

void afficherMagasin(T_Magasin *magasin){
    //Recuperation du magasin afin de ne pas perdre l'adresse du magasin
    //Il comprend la liste simplement chainée des rayons
    T_Magasin *currentMagasin = magasin;
    
    if(currentMagasin==NULL){
        printf("Aucun magasin existant");
        exit(EXIT_FAILURE);
    }
    else if (currentMagasin->premier==NULL) {
        printf("Il n'existe aucun produit pour ce magasion");
    }
    else{
        printf("||NOM    ||Nombre de produits||\n");
        while (currentMagasin->premier!=NULL) {
            printf("||%s||%d||\n",currentMagasin->premier->nom_rayon,currentMagasin->premier->nombre_produit);
            currentMagasin->premier = currentMagasin->premier->suivant;
        }
        
    }
}
