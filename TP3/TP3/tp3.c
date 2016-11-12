/*
 *************************************************
 Liste des erreurs notifiées lors de l'utilisation
 *************************************************
 
 
 */

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

void menu(){
    //*********************************
    //Table d'initialisation d'une base
    //*********************************
    
    //Magasin
    T_Magasin *firstMagasin = creerMagasin("Carrefour");
    
    //Premier Rayon
    T_Rayon *milk = creerRayon("milk");
    ajouterRayon(firstMagasin, milk);
    ajouterProduit(milk, creerProduit("danone", 1.25, A, 200));
    ajouterProduit(milk, creerProduit("actimel", 2, A, 1200));
    ajouterProduit(milk, creerProduit("fromage", 1.25, C, 20));
    ajouterProduit(milk, creerProduit("lait", 1.02, B, 78));
    
    //Deuxieme Rayon
    T_Rayon *meat = creerRayon("meat");
    ajouterRayon(firstMagasin, meat);
    ajouterProduit(meat, creerProduit("boeuf", 4, A, 100));
    ajouterProduit(meat, creerProduit("poulet", 2, B, 120));
    ajouterProduit(meat, creerProduit("dinde", 3.12, C, 57));
    ajouterProduit(meat, creerProduit("mouton", 8, A, 90));
    
    
    //Troisieme Rayon
    T_Rayon *drink = creerRayon("drink");
    ajouterRayon(firstMagasin, drink);
    ajouterProduit(drink, creerProduit("coca", 1.2, A, 1000));
    ajouterProduit(drink, creerProduit("fanta", 3.4, A, 1200));
    ajouterProduit(drink, creerProduit("orangina", 3.12, A, 5700));
    ajouterProduit(drink, creerProduit("ice tea", 5, A, 900));
    
    
    
    
    
    
    //Fonctionnement de l'application jusqu'à ce que l'utilisateur quitte le programme
    int enFonctionnement = 0;
    //Menu - 1
    char nomMagasin[MaxTaileForMagasinName];
    T_Magasin *magasin = firstMagasin;
    //Menu - 2
    char nomRayon[MaxTailleForRayonName];
    //Menu - 3
    T_Rayon *rayon;
    char marqueProduit[MaxTailleForBrandName];
    int prixProduit;
    enum quality qualiteProduit;
    int quantiteProduit;
    
    
    
    while(enFonctionnement==0){
        int choix = 0;
        printf("\nMenu des actions possibles\n");
        if(magasin!=NULL){
            afficherNomMagasin(magasin);
        }
        printf("Tapez 1 - Créer un magasin\n");
        printf("Tapez 2 - Ajouter un rayon au magasin\n");
        printf("Tapez 3 - Ajouter un produit dans un rayon\n");
        printf("Tapez 4 - Afficher les rayons du magasin\n");
        printf("Tapez 5 - Afficher les produits d'un rayon\n");
        printf("Tapez 6 - Supprimer un produit\n");
        printf("Tapez 7 - Supprimer un rayon\n");
        printf("Tapez 8 - Rechercher un produit par prix\n");
        printf("Tapez 9 - Quitter\n");
        scanf("%d",&choix);
        
        switch(choix){
            case 1:
                if(magasin==NULL){
                    printf("Veuillez entrer le nom du magasin\n");
                    scanf("%s",nomMagasin);
                    magasin = creerMagasin(nomMagasin);
                }
                else{
                    printf("le magasin est déjà créé et se nomme:%s \n",magasin->nom);
                }
                break;
                
            case 2:
                printf("Veuillez entrer le nom du rayon\n");
                scanf("%s",nomRayon);
                if (ajouterRayon(magasin, creerRayon(nomRayon))!=1){
                    printf("erreur lors de l'ajout du rayon\n");
                };
                break;
            
            case 3:
                printf("Veuillez entrer la marque du produit\n");
                scanf("%s",marqueProduit);
                printf("Veuillez entrer le prix du produit\n");
                scanf("%d",&prixProduit);
                printf("Veuillez entrer la qualite du produit\n");
                scanf("%d",&qualiteProduit);
                printf("Veuillez entrer la quantite du produit\n");
                scanf("%d", &quantiteProduit);
                creerProduit(marqueProduit, prixProduit, qualiteProduit, quantiteProduit);
                break;
                
            case 4:
                afficherMagasin(magasin);
                break;
                
            case 5:
                printf("Veuillez entrer le nom du rayon\n");
                scanf("%s",nomRayon);
                afficherRayon(retourneRayon(magasin, nomRayon));
                break;
                
            case 6:
                break;
                
            case 7:
                break;
                
            case 8:
                break;
                
            case 9:
                printf("La mémoire a été désallouée correctement\n");
                printf("Aurevoir\n");
                enFonctionnement++;
                break;
                
            default:
                exit(EXIT_FAILURE);
                break;
        }
        
    }
}



//Q2
//Les rayons sont triés par ordre croissant sur le nom des rayons
int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon){
    //Recuperation du magasin afin de ne pas perdre l'adresse du magasin
    //Il comprend la liste simplement chainée des rayons
    T_Magasin *currentMagasin = magasin;
    
    //On verifie qu'un magasin existe
    if(currentMagasin==NULL||rayon==NULL){
        printf("Il n'y a pas de magasin ou de rayon, on ne peut ajouter le rayon\n");
        return 0;
    }
    //On verifie si le magasin contient dejà des rayons
    else if(currentMagasin->premier == NULL){
        currentMagasin->premier = rayon;
        return 1;
    }
    //On verifie que le premier rayon ne porte pas le meme nom
    else if(strcmp(currentMagasin->premier->nom_rayon,rayon->nom_rayon)==0){
        printf("Il existe déjà un rayon se nommant: %s",rayon->nom_rayon);
        return 0;
    }
    else{
        //Sinon on va parcourir la liste simplement chainées
        while(currentMagasin->premier->suivant!=NULL && strcmp(currentMagasin->premier->suivant->nom_rayon,rayon->nom_rayon)<=0 && strcmp(currentMagasin->premier->nom_rayon, rayon->nom_rayon)>0){
            currentMagasin->premier = currentMagasin->premier->suivant;
        }
        if(currentMagasin->premier->suivant==NULL){
            if(strcmp(currentMagasin->premier->nom_rayon,rayon->nom_rayon)>0){
                rayon->suivant = currentMagasin->premier;
                magasin->premier = rayon;
                return 1;
            }
            else{
                currentMagasin->premier->suivant=rayon;
                return 1;
            }
        }
        else{
        currentMagasin->premier->suivant = rayon;
        return 1;
        }
    }
}


//Q3
//Les produits sont triés par ordre croissant du prix du produit
int ajouterProduit(T_Rayon *rayon, T_Produit *produit){
    
    T_Rayon *currentRayon = rayon;  //on récupère l'adresse du rayon sur lequel on fait l'ajout
    
    if(currentRayon == NULL||produit == NULL){
        printf("Aucun rayon ou produit existant");
        return 0;
    }
    else if(currentRayon->premier == NULL){
        currentRayon->premier = produit;
        rayon->nombre_produit=produit->quantite_en_stock; //On suppose que le nombre de produit signifie le nombre de produit dans le rayon et non pas le nombre de reference de produit
        return 1;
    }
    else if(strcmp(currentRayon->premier->marque,produit->marque) == 0){   //la même marque de produit dans un rayon
        printf("un produit avec la marque %s existe dejà",produit->marque);
        return 0;
    }
    //le produit ajoute a un prix plus petit que le celui en tete de liste
    else if(currentRayon->premier->prix >= produit->prix) {
        produit->suivant = currentRayon->premier;   //ajouter dans le premier
        currentRayon->premier = produit;
        rayon->nombre_produit+=produit->quantite_en_stock;
        return 1;
    }
    else{
        while((currentRayon->premier->suivant != NULL) && (currentRayon->premier->suivant->prix < produit->prix) && (currentRayon->premier->prix <= produit->prix)) //pas de meme marque et trier
            currentRayon->premier = currentRayon->premier->suivant;
        
        if(currentRayon->premier->suivant == NULL){
            currentRayon->premier->suivant = produit;
            rayon->nombre_produit+=produit->quantite_en_stock;
            return 1;
        }
        else if(strcmp(currentRayon->premier->suivant->marque,produit->marque)==0)    //la même marque de produit dans un rayon
            return 0;
        else{
            produit->suivant = currentRayon->premier->suivant;  //ajouter dans le dernier
            currentRayon->premier->suivant = produit;
            rayon->nombre_produit+=produit->quantite_en_stock;
            return 1;
        }
    }


    
}

//Q4
void afficherMagasin(T_Magasin *magasin){
    //Recuperation du magasin afin de ne pas perdre l'adresse du magasin
    //Il comprend la liste simplement chainée des rayons
    T_Magasin *currentMagasin = magasin;
    
    if(currentMagasin==NULL){
        printf("Aucun magasin existant");
        exit(EXIT_FAILURE);
    }
    else if (currentMagasin->premier==NULL) {
        printf("Il n'existe aucun rayon pour ce magasin");
    }
    else{
        printf("||NOM\t||Nombre de produits||\n");
        while (currentMagasin->premier!=NULL) {
            printf("||%s\t||%d||\n",currentMagasin->premier->nom_rayon,currentMagasin->premier->nombre_produit);
            currentMagasin->premier = currentMagasin->premier->suivant;
        }
        
    }
}

//Q5
void afficherRayon(T_Rayon *rayon){
    
    T_Rayon *currentRayon = rayon;
    char c; //pour afficher qualite
    if(currentRayon == NULL){
        printf("Aucun rayon existant");
        exit(EXIT_FAILURE);
    }
    else if (currentRayon->premier == NULL) {
        printf("Il n'existe aucun produit pour ce magasin");
    }
    else{
        printf("||Marque   ||Prix ||Qualite||Quantite en stock||\n");
        while (currentRayon->premier!= NULL) {
            switch (currentRayon->premier->qualite) {   //pour afficher qualite
                case 0:
                    c = 'A';
                    break;
                case 1:
                    c = 'B';
                    break;
                default:
                    c = 'C';
                    break;
            }
            printf("||%s||%.2f||%c||%d||\n",currentRayon->premier->marque,currentRayon->premier->prix,c,currentRayon->premier->quantite_en_stock);
            currentRayon->premier = currentRayon->premier->suivant;
        }
    }
}

//Q6
int supprimerProduit(T_Rayon *rayon, char* marque_produit){
    T_Rayon *currentRayon = rayon;
    T_Produit *supprimer;
    if(currentRayon == NULL){
        printf("Aucun rayon existant");
        return 0;
    }
    if (currentRayon->premier == NULL) {
        printf("Il n'existe aucun produit pour ce rayon");
        return 0;
    }
    if (currentRayon->premier->marque == marque_produit){
        supprimer = currentRayon->premier;
        currentRayon->premier = currentRayon->premier->suivant;
        free(supprimer);
        return 1;
    }
    while((currentRayon->premier->suivant != NULL) && (currentRayon->premier->suivant->marque != marque_produit))
        currentRayon->premier = currentRayon->premier->suivant;
    if(currentRayon->premier->suivant == NULL){
        printf("Aucun rayon existant");
        return 0;
    }
    else{
        supprimer = currentRayon->premier->suivant;
        currentRayon->premier->suivant = currentRayon->premier->suivant->suivant;
        free(supprimer);
        return 1;
    }
}

//Q7
void supprimerRayon(T_Magasin *magasin, char *nom_rayon){

}




//*****
//ADDED
//*****
T_Rayon *retourneRayon(T_Magasin *magasin, char *nomRayon){
    T_Magasin *currentMagasin = magasin;
    while(currentMagasin->premier!=NULL && strcmp(currentMagasin->premier->nom_rayon,nomRayon)!=0){
        currentMagasin->premier=currentMagasin->premier->suivant;
    }
    return currentMagasin->premier;
}




//*******
//USELESS
//*******

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



 void afficherNomMagasin(T_Magasin *magasin){
 printf("Le nom du magasin est le suivant: %s\n",magasin->nom);
 } 

