//
//  tp3.h
//  TP3
//
//  Created by LAURENT SIMON on 08/11/2016.
//  Copyright © 2016 LAURENT SIMON. All rights reserved.
//

#ifndef tp3_h
#define tp3_h

#include <stdio.h>

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






#endif /* tp3_h */
