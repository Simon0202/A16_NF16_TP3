#include "tp3.h"

T_Produit *creerProduit(char *marque, float prix, quality qualite,unsigned int quantite){
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
