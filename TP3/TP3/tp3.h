#ifndef tp3_h
#define tp3_h

#include <stdio.h>
#include <stdlib.h>

//**********
//Structures
//**********
enum quality{A,B,C};

typedef struct Produit {
    char *marque;
    double prix;
    enum quality qualite;   //valeur possible : A, B, C
    unsigned int quantite_en_stock;
    struct Produit* suivant;
} T_Produit;

typedef struct Rayon {
    char *nom_rayon;
    unsigned int nombre_produit;
    T_Produit *premier;
    struct Rayon *suivant;
} T_Rayon;

typedef struct Magasin {
    char *nom;
    T_Rayon *premier;
} T_Magasin;

//**********************
//Functions declarations
//**********************
T_Produit *creerProduit(char *marque, float prix,enum quality qualite,unsigned int quantite);
T_Rayon *creerRayon(char *nom);
T_Magasin *creerMagasin(char *nom);
int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon);



#endif /* tp3_h */
