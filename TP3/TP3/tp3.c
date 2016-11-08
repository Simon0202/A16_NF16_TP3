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
    return NewRayon;
}

T_Magasin *creerMagasin(char *nom)
{
    T_Magasin *NewMagasin = malloc(sizeof(struct Magasin));
    NewMagasin->nom = nom;
    return NewMagasin;
}

//Q3
int ajouterProduit(T_Rayon *rayon, T_Produit *produit){
    T_Produit *p;
    if(rayon->premier == NULL){
        rayon->premier = produit;
        rayon->nombre_produit++;
    }
    return 1;
    if (rayon->premier->prix > produit->prix) {
        produit->suivant = rayon->premier->suivant;
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
