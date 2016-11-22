#ifndef tp3_h
#define tp3_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxTaileForMagasinName 200
#define MaxTailleForRayonName 200
#define MaxTailleForBrandName 200

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


typedef struct Ord{
    enum quality qualite;
    char *marque;
    char *nomRayon;
    double prix;
    unsigned int quantite;
    struct Ord *suivant;
}T_Ord;



//**********************
//Functions declarations
//**********************

//Menu Principal
void initialisationBase();
void menu(T_Magasin *magasin);


//Creation
T_Produit *creerProduit(char *marque, double prix,enum quality qualite,unsigned int quantite);
T_Rayon *creerRayon(char *nom);
T_Magasin *creerMagasin(char *nom);
T_Ord *creerOrd(char *marque, char *nomRayon, double prix, enum quality qualite, unsigned int quantite);

//Ajout
int ajouterProduit(T_Rayon *rayon, T_Produit *produit);
int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon);

//Supression
int supprimerRayon(T_Magasin *magasin, char *nom_rayon);
int supprimerProduit(T_Rayon *rayon, char* marque_produit);

//Affichage
void afficherRayon(T_Rayon *rayon);
void afficherMagasin(T_Magasin *magasin);

//Recherche
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max);


//added
void afficherNomMagasin(T_Magasin *magasin);
T_Rayon *retourneRayon(T_Magasin *magasin, char *nomRayon);
int convertCharToInt(char c);
char convertIntToChar(int val);

#endif /* tp3_h */
