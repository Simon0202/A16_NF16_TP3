/*
 *************************************************
 Liste des erreurs notifiées lors de l'utilisation
 *************************************************
Ajout rayon à améliorer
Supression produit à refaire
 */

#include "tp3.h"

//*********************
//FONCTIONS DE CREATION
//*********************

T_Produit *creerProduit(char *marque, float prix, enum quality qualite,unsigned int quantite){
    T_Produit *NewProduit = malloc(sizeof(struct Produit));
    if (NewProduit==NULL)
        exit(EXIT_FAILURE);
    
    NewProduit->marque = malloc(MaxTailleForBrandName);
    strcpy(NewProduit->marque,marque);
    NewProduit->prix= prix;
    NewProduit->qualite = qualite;
    NewProduit->quantite_en_stock = quantite;
    
    return NewProduit;
}
//Fin de CreerProduit


T_Rayon *creerRayon(char *nom)
{
    T_Rayon *NewRayon = malloc(sizeof(struct Rayon));
    if(NewRayon==NULL)
        exit(EXIT_FAILURE);
    
    NewRayon->nom_rayon = malloc(MaxTailleForRayonName);
    strcpy(NewRayon->nom_rayon,nom);
    NewRayon->nombre_produit = 0;
    NewRayon->premier = NULL;
    NewRayon->suivant = NULL;
    
    return NewRayon;
}
//Fin de CreerRayon


T_Magasin *creerMagasin(char *nom)
{
    T_Magasin *NewMagasin = malloc(sizeof(*NewMagasin));
    if (NewMagasin==NULL)
        exit(EXIT_FAILURE);
    
    NewMagasin->nom=malloc(MaxTaileForMagasinName);
    strcpy(NewMagasin->nom, nom);
    NewMagasin->premier = NULL;
    
    return NewMagasin;
}
//Fin de CreerMagasin




//***********************************************************************
//***********************************************************************
//***********************************************************************
//***********************************************************************




//***************
//FONCTIONS AJOUT
//***************

//Q2
//Les rayons sont triés par ordre croissant sur le nom des rayons
int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon){
    
    T_Rayon *firstRayon = magasin->premier;

    //On verifie qu'un magasin existe
    if(magasin==NULL||rayon==NULL){
        printf("Il n'y a pas de magasin ou de rayon, on ne peut ajouter le rayon\n");
        return 0;
    }
    
    //On verifie si le magasin contient dejà des rayons
    else if(magasin->premier == NULL){
        magasin->premier = rayon;
        return 1;
    }
    
    //On verifie qu'il n'y a pas de rayons avec le meme nom
    while(firstRayon!=NULL){
        if(strcmp(firstRayon->nom_rayon,rayon->nom_rayon)==0){
            printf("Il existe déjà un rayon se nommant: %s\n",rayon->nom_rayon);
            return 0;
        }
        else{
            firstRayon=firstRayon->suivant;
        }
    }
    
    
    //On réinitialise firstRayon pour chainer le nouveau rayon
    firstRayon = magasin->premier;

    //Parcours pour insertion
    while(firstRayon->suivant!=NULL && strcmp(firstRayon->suivant->nom_rayon,rayon->nom_rayon)<0 && strcmp(firstRayon->nom_rayon, rayon->nom_rayon)<=0){
           firstRayon = firstRayon->suivant;
    }
    if(firstRayon->suivant==NULL){
        if(strcmp(firstRayon->nom_rayon,rayon->nom_rayon)>0){
            rayon->suivant = firstRayon;
            magasin->premier = rayon;
            return 1;
        }
        else{
            firstRayon->suivant=rayon;
            return 1;
        }
    }
    else{
        if(strcmp(firstRayon->nom_rayon,rayon->nom_rayon)<0){
            rayon->suivant = firstRayon->suivant;
            firstRayon->suivant = rayon;
            return 1;
        }
        else{
            rayon->suivant=firstRayon;
            magasin->premier = rayon;
            return 1;
        }
    }
}
//Fin de ajouterRayon



//Q3
//Les produits sont triés par ordre croissant du prix du produit
int ajouterProduit(T_Rayon *rayon, T_Produit *produit){
    
     //on récupère l'adresse du premier produit sur lequel on fait l'ajout
    T_Produit *firstProduct = rayon->premier;
    
    if(rayon == NULL||produit == NULL){
        printf("Aucun rayon ou produit existant");
        return 0;
    }
    else if(firstProduct == NULL){
        rayon->premier = produit;
        //On suppose que le nombre de produit signifie le nombre de produit dans le rayon et non pas le nombre de reference de produit
        rayon->nombre_produit += produit->quantite_en_stock;
        return 1;
    }
    else{
        while(firstProduct!=NULL){
            if(strcmp(firstProduct->marque,produit->marque) == 0){   //la même marque de produit dans un rayon
                printf("un produit avec la marque %s existe dejà",produit->marque);
                return 0;
            }
            else{
                firstProduct=firstProduct->suivant;
            }
        }
    }
    
    //On reinitialise firstProduct
    firstProduct = rayon->premier;
    
/*
    }    //le produit ajoute a un prix plus petit que le celui en tete de liste
    else if(firstProduct->prix >= produit->prix) {
        produit->suivant = firstProduct;   //ajouter dans le premier
        rayon->premier = produit;
        rayon->nombre_produit+=produit->quantite_en_stock;
        return 1;
    }
*/
    while((firstProduct->suivant != NULL) && (firstProduct->suivant->prix < produit->prix) && (firstProduct->prix <= produit->prix)){            firstProduct = firstProduct->suivant;
    }
    
        if(firstProduct->suivant == NULL){
            if(firstProduct->prix < produit->prix){
                firstProduct->suivant = produit;
                rayon->nombre_produit+=produit->quantite_en_stock;
                return 1;
            }
            else{
                firstProduct->suivant=produit;
                return 1;
            }
        }
        else{
            if(firstProduct->prix<produit->prix){
                produit->suivant = firstProduct->suivant;  //ajouter dans le dernier
                firstProduct->suivant = produit;
                rayon->nombre_produit+=produit->quantite_en_stock;
                return 1;
            }
            else{
                produit->suivant=firstProduct;
                rayon->premier=produit;
                rayon->nombre_produit+=produit->quantite_en_stock;
                return 1;
            }
        }
}
//Fin de ajouterProduit



//***********************************************************************
//***********************************************************************
//***********************************************************************
//***********************************************************************




//*******************
//FONCTIONS AFFICHAGE
//*******************
//Q4
void afficherMagasin(T_Magasin *magasin){
    //Recuperation du magasin afin de ne pas perdre l'adresse du magasin
    //Il comprend la liste simplement chainée des rayons
    T_Rayon *firstRayon = magasin->premier;
    
    if(magasin==NULL){
        printf("Aucun magasin existant\n");
        exit(EXIT_FAILURE);
    }
    else if (firstRayon==NULL) {
        printf("Il n'existe aucun rayon pour ce magasin\n");
    }
    else{
        printf("||NOM\t||Nombre de produits||\n");
        while (firstRayon!=NULL) {
            printf("||%s\t||%d||\n",firstRayon->nom_rayon,firstRayon->nombre_produit);
            firstRayon = firstRayon->suivant;
        }
        
    }
}


//Q5
void afficherRayon(T_Rayon *rayon){
    
    T_Produit *firstProduct = rayon->premier;
    char c; //pour afficher qualite
    
    if(rayon == NULL){
        printf("Aucun rayon existant");
        exit(EXIT_FAILURE);
    }
    else if (firstProduct == NULL) {
        printf("Il n'existe aucun produit pour ce magasin");
    }
    else{
        printf("||Marque\t||Prix\t||Qualite\t||Quantite en stock\t||\n");
        while (firstProduct!= NULL) {
            switch(firstProduct->qualite){   //pour afficher qualite
                case 0:
                    c = 'A';
                    break;
                case 1:
                    c = 'B';
                    break;
                case 2:
                    c = 'C';
                    break;
                default:
                    exit(EXIT_FAILURE);
                    break;
            }
            printf("||%s\t||%.2f\t||%c\t||%d\t||\n",firstProduct->marque,firstProduct->prix,c,firstProduct->quantite_en_stock);
            firstProduct = firstProduct->suivant;
        }
    }
}




//***********************************************************************
//***********************************************************************
//***********************************************************************
//***********************************************************************




//*********************
//FONCTIONS SUPPRESSION
//*********************
//Q6
int supprimerProduit(T_Rayon *rayon, char* marque_produit){
    T_Produit *firstProduct = rayon->premier;

    if(rayon == NULL){
        printf("Aucun rayon existant");
        return 0;
    }
    if (rayon->premier == NULL) {
        printf("Il n'existe aucun produit pour ce rayon");
        return 0;
    }
    if (strcmp(firstProduct->marque,marque_produit)==0){
        rayon->premier = firstProduct->suivant;
        free(firstProduct);
        return 1;
    }
    while((firstProduct->suivant != NULL) && strcmp(firstProduct->suivant->marque,marque_produit)!=0){
        firstProduct = firstProduct->suivant;
    }
    
    if(firstProduct->suivant == NULL){
        printf("Aucun rayon existant");
        return 0;
    }
    else{
        rayon->premier->suivant = firstProduct->suivant->suivant;
        free(firstProduct->suivant);
        return 1;
    }
}
//Fin de supprimerProduit


//Q7
void supprimerRayon(T_Magasin *magasin, char *nom_rayon){

}
//Fin de supprimerRayon




//***********************************************************************
//***********************************************************************
//***********************************************************************
//***********************************************************************




//****
//MENU
//****
void menu(T_Magasin *magasin){
    //Menu - 1
    char nomMagasin[MaxTaileForMagasinName];
    //Menu - 2
    char *nomRayon;
    //Menu - 3
    char marqueProduit[MaxTailleForBrandName];
    int prixProduit;
    enum quality qualiteProduit;
    int quantiteProduit;
    //Menu - 4
    //Menu - 5
    //Menu - 6
    //Menu - 7
    //Menu - 8
    //Menu - 9
    int enFonctionnement = 0;
    
    
    
    while(enFonctionnement==0){
        int choix = 0;
        
        if(magasin!=NULL){
            afficherNomMagasin(magasin);
        }
        
        printf("\nMenu des actions possibles\n");
        printf("Tapez 0 - Initialiser un magasin\n");
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
            case 0:
                if (magasin==NULL){
                    printf("Veuillez selectionner le menu 1, afin de créer un magasin\n");
                }
                else{
                    initialisationBase(magasin);
                }
                break;
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
                if (magasin==NULL){
                    printf("Veuillez selectionner le menu 1, afin de créer un magasin\n");
                }
                else{
                    printf("Veuillez entrer le nom du rayon\n");
                    scanf("%s",nomRayon);
                    if (ajouterRayon(magasin, creerRayon(nomRayon))!=1){
                        printf("erreur lors de l'ajout du rayon\n");
                    }
                }
                break;
                
            case 3:
                if (magasin==NULL){
                    printf("Veuillez selectionner le menu 1, afin de créer un magasin\n");
                }
                if (magasin->premier==NULL){
                    printf("Veuillez selectionner le menu 2, afin de créer un rayon\n");
                }
                else{
                    printf("Veuillez entrer la marque du produit\n");
                    scanf("%s",marqueProduit);
                    printf("Veuillez entrer le prix du produit\n");
                    scanf("%d",&prixProduit);
                    printf("Veuillez entrer la qualite du produit\n");
                    scanf("%d",&qualiteProduit);
                    printf("Veuillez entrer la quantite du produit\n");
                    scanf("%d", &quantiteProduit);
                    printf("Veuillez indiquer le rayon dans lequel vous voulez le placer, parmi les suivants:\n");
                    afficherMagasin(magasin);
                    scanf("%s",nomRayon);
                    ajouterProduit(retourneRayon(magasin, nomRayon), creerProduit(marqueProduit, prixProduit, qualiteProduit, quantiteProduit));
                }
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
                afficherMagasin(magasin);
                printf("Veuillez entrer le nom du rayon dans lequel il faut supprimer un produit\n");
                scanf("%s",nomRayon);
                afficherRayon(retourneRayon(magasin, nomRayon));
                printf("quel produit voulez vous supprimer?\n");
                scanf("%s",marqueProduit);
                supprimerProduit(retourneRayon(magasin, nomRayon), marqueProduit);
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
//Fin de Menu




//***********************************************************************
//***********************************************************************
//***********************************************************************
//***********************************************************************




//*****
//ADDED
//*****
T_Rayon *retourneRayon(T_Magasin *magasin, char *nomRayon){
    T_Rayon *firstRayon = magasin->premier;
    while(firstRayon!=NULL && strcmp(firstRayon->nom_rayon,nomRayon)!=0){
        firstRayon=firstRayon->suivant;
    }
    return firstRayon;
}
//Fin de retournerRayon



void afficherNomMagasin(T_Magasin *magasin){
    printf("Le nom du magasin est le suivant: %s\n",magasin->nom);
}
//Fin de afficherNomMagasin



void initialisationBase(T_Magasin *firstMagasin){
 //
 //Table d'initialisation d'une base
 //
 
    
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
 ajouterProduit(drink, creerProduit("iceTea", 5, A, 900));
 
 }
//Fin de initialisationBase




//***********************************************************************
//***********************************************************************
//***********************************************************************
//***********************************************************************




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
    else if (firstProduct==NULL){
    return total;
    }
    else{
        while(firstProduct!=NULL){
            total+=firstProduct->quantite_en_stock;
            firstProduct = firstProduct->suivant;
        }
        return total;
    }
 }
 //Fin de totalProduitDansUnRayon
 


 int conversionEnumInt(char lettre){
    if(lettre=='A')
        return 0;
    else if(lettre=='B')
        return 1;
    else if(lettre=='C')
        return 2;
    else
        return -1;
 }
 //Fin de conversionEnumInt
 */



