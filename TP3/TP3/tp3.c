#include "tp3.h"

T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite){
    T_Produit* NewProduit;
    (*NewProduit).marque = marque;
    (*NewProduit).prix = prix;
    (*NewProduit).qualite = qualite;
    (*NewProduit).qualite_en_stock = quantite;
    
    return NewProduit;
}

T_Rayon *creerRayon(char *nom)
{
    T_Rayon* NewRayon;
    (*NewRayon).nom_rayon = nom;
    return NewRayon;
}

T_Magasin *creerMagasin(char *nom)
{
    T_Magasin* NewMagasin;
    (*NewMagasin).nom = nom;
    return NewMagasin;
}
