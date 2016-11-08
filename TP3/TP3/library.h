//
//  library.h
//  TP3
//
//  Created by suyiqing on 11/8/16.
//  Copyright © 2016 LAURENT SIMON. All rights reserved.
//

#ifndef library_h
#define library_h

typedef struct Produit {
    char* marque;
    double prix;
    char qualite;   //valeur possible : A, B, C
    int qualite_en_stock;
    struct Produit* suivant;
} T_Produit;

typedef struct Rayon {
    char* nom_rayon;
    int nombre_produit;
    T_Produit* premier;
    struct Rayon* suivant;
} T_Rayon;

typedef struct Magasin {
    char* nom;
    T_Rayon* premier;
} T_Magasin;

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



#endif /* library_h */
