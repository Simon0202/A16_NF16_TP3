#ifndef tp3_h
#define tp3_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxTaileForMagasinName 50
#define MaxTailleForRayonName 40
#define MaxTailleForBrandName 30

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

//Menu Principal
T_Magasin *initialisationBase();
void menu(T_Magasin *magasin);


//Creation
T_Produit *creerProduit(char *marque, float prix,enum quality qualite,unsigned int quantite);
T_Rayon *creerRayon(char *nom);
T_Magasin *creerMagasin(char *nom);

//Ajout
int ajouterProduit(T_Rayon *rayon, T_Produit *produit);
int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon);

//Supression
void supprimerRayon(T_Magasin *magasin, char *nom_rayon);

//Affichage
void afficherNomMagasin(T_Magasin *magasin);
T_Rayon *retourneRayon(T_Magasin *magasin, char *nomRayon);
void afficherRayon(T_Rayon *rayon);
void afficherMagasin(T_Magasin *magasin);

//Useless
//int totalProduitDansUnRayon(T_Rayon *rayon);


#endif /* tp3_h */
