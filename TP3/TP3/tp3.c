/*
 *************************************************
 Liste des erreurs notifiées lors de l'utilisation
 *************************************************
Ajouter produit --> rayon == NULL ??

 
 
 
 */

#include "tp3.h"

//*********************
//FONCTIONS DE CREATION
//*********************

T_Produit *creerProduit(char *marque, double prix, enum quality qualite,unsigned int quantite){
    T_Produit *NewProduit = malloc(sizeof(struct Produit));
    if (NewProduit==NULL)
        exit(EXIT_FAILURE);
    
    NewProduit->marque = malloc(sizeof(char)*MaxTailleForBrandName);
    strcpy(NewProduit->marque,marque);
    NewProduit->prix= prix;
    NewProduit->qualite = qualite;
    NewProduit->quantite_en_stock = quantite;
    NewProduit->suivant=NULL;
    
    return NewProduit;
}
//Fin de CreerProduit


T_Rayon *creerRayon(char *nom)
{
    T_Rayon *NewRayon = malloc(sizeof(struct Rayon));
    if(NewRayon==NULL)
        exit(EXIT_FAILURE);
    
    NewRayon->nom_rayon = malloc(sizeof(char)*MaxTailleForRayonName);
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
    
    NewMagasin->nom=malloc(sizeof(char)*MaxTaileForMagasinName);
    strcpy(NewMagasin->nom, nom);
    NewMagasin->premier = NULL;
    
    return NewMagasin;
}
//Fin de CreerMagasin


T_Ord *creerOrd(char *marque, char *nomRayon, double prix, enum quality qualite, unsigned int quantite){
    T_Ord *newOrd = malloc(sizeof(*newOrd));
    if(newOrd==NULL)
        exit(EXIT_FAILURE);
    
    newOrd->marque=marque;
    newOrd->nomRayon=nomRayon;
    newOrd->prix=prix;
    newOrd->qualite=qualite;
    newOrd->quantite=quantite;
    newOrd->suivant=NULL;
    
    return newOrd;
}
//Fin de CreerOrd

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
    
    T_Produit *firstProduct = rayon->premier;
    
    if(rayon == NULL||produit == NULL){
        printf("Aucun rayon ou produit existant\n");
        return 0;
    }
    else if(rayon->premier == NULL){
        rayon->premier = produit;
        //On suppose que le nombre de produit signifie le nombre de produit dans le rayon et non pas le nombre de reference de produit
        rayon->nombre_produit += produit->quantite_en_stock;
        return 1;
    }
    else{
        while(firstProduct != NULL){
            if(strcmp(firstProduct->marque,produit->marque) == 0){   //la même marque de produit dans un rayon
                printf("un produit avec la marque %s existe dejà\n",produit->marque);
                return 0;
            }
            else{
                firstProduct=firstProduct->suivant;
            }
        }
    
    //On reinitialise firstProduct
    firstProduct = rayon->premier;
    
    while((firstProduct->suivant != NULL) && (firstProduct->suivant->prix < produit->prix) && (firstProduct->prix <= produit->prix)){            firstProduct = firstProduct->suivant;
    }
    
        if(firstProduct->suivant == NULL){
            if(firstProduct->prix < produit->prix){
                firstProduct->suivant = produit;
                rayon->nombre_produit+=produit->quantite_en_stock;
                return 1;
            }
            else{
                produit->suivant=firstProduct;
                rayon->nombre_produit+=produit->quantite_en_stock;
                rayon->premier=produit;
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
    
    
    char c; //pour afficher qualite
    
    if(rayon == NULL){
        printf("Aucun rayon existant");
        exit(EXIT_FAILURE);
    }
    else if (rayon->premier == NULL) {
        printf("Il n'existe aucun produit pour ce magasin");
    }
    else{
        T_Produit *firstProduct = rayon->premier;
        
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
    T_Produit *precedent=NULL;

    if(rayon == NULL){
        printf("Aucun rayon existant");
        return 0;
    }
    if (rayon->premier == NULL) {
        printf("Il n'existe aucun produit pour ce rayon");
        return 0;
    }

    while((firstProduct != NULL) && strcmp(firstProduct->marque,marque_produit)!=0){
        precedent = firstProduct;
        firstProduct = firstProduct->suivant;
    }
    
    if(firstProduct->suivant == NULL){
        printf("Ce produit n'est pas dans le rayon");
        return 0;
    }
    else{
        //Test en tete
        if(rayon->premier == firstProduct){
            rayon->nombre_produit-=firstProduct->quantite_en_stock;
            rayon->premier = firstProduct->suivant;
            firstProduct->suivant = NULL;
            free(firstProduct->marque);
            free(firstProduct);
            return 1;
        }
        //Test en queue
        else if(firstProduct->suivant==NULL){
            rayon->nombre_produit-=firstProduct->quantite_en_stock;
            precedent->suivant = firstProduct->suivant;
            free(firstProduct->marque);
            free(firstProduct);
            return 1;
        }
        //Test milieu
        else{
            rayon->nombre_produit-=firstProduct->quantite_en_stock;
            precedent->suivant=firstProduct->suivant;
            firstProduct->suivant = NULL;
            free(firstProduct->marque);
            free(firstProduct);
            return 1;
        }
    }
}
//Fin de supprimerProduit


//Q7
int supprimerRayon(T_Magasin *magasin, char *nom_rayon){
    T_Rayon *firstRayon = magasin->premier;
    T_Rayon *precedent=NULL;
    T_Produit *produit=NULL;
    
    if(magasin == NULL){
        printf("Aucun magasin existant");
        return 0;
    }
    else if (magasin->premier == NULL) {
        printf("Il n'existe aucun rayon pour ce magasin");
        return 0;
    }
    
    while(firstRayon != NULL && strcmp(firstRayon->nom_rayon,nom_rayon)!=0){
        precedent = firstRayon;
        firstRayon = firstRayon->suivant;
    }
    
    if(firstRayon == NULL){
        printf("Ce rayon n'est pas dans le magasin");
        return 0;
    }
    
    else{
        //Test en tete
        if(magasin->premier == firstRayon){
            magasin->premier = firstRayon->suivant;
            firstRayon->suivant = NULL;
            
            while(firstRayon->premier!=NULL){
                produit = firstRayon->premier;
                firstRayon->nombre_produit -= produit->quantite_en_stock;
                firstRayon->premier = produit->suivant;
                produit->suivant = NULL;
                free(produit->marque);
                free(produit);
            }
            
            free(firstRayon->nom_rayon);
            free(firstRayon);
            return 1;
        }
        //Test en queue
        else if(firstRayon->suivant==NULL){
            precedent->suivant = firstRayon->suivant;
            
            while(firstRayon->premier!=NULL){
                produit = firstRayon->premier;
                firstRayon->nombre_produit -= produit->quantite_en_stock;
                firstRayon->premier = produit->suivant;
                produit->suivant = NULL;
                free(produit->marque);
                free(produit);
            }
            
            free(firstRayon->nom_rayon);
            free(firstRayon);
            return 1;
        }
        //Test milieu
        else{
            precedent->suivant=firstRayon->suivant;
            firstRayon->suivant = NULL;
            
            while(firstRayon->premier!=NULL){
                produit = firstRayon->premier;
                firstRayon->nombre_produit -= produit->quantite_en_stock;
                firstRayon->premier = produit->suivant;
                produit->suivant = NULL;
                free(produit->marque);
                free(produit);
            }
            
            free(firstRayon->nom_rayon);
            free(firstRayon);
            return 1;
        }
    }
}
//Fin de supprimerRayon




//***********************************************************************
//***********************************************************************
//***********************************************************************
//***********************************************************************



/*
//Q8
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max){
    T_Rayon *temp = creerRayon("zzz");
    T_Rayon *rayon = magasin->premier;
    T_Produit *produit;
    T_Ord *ordre=creerOrd();
    
    
    while(rayon!=NULL){
        
        produit=rayon->premier
        while(produit!=NULL){
            if(produit->prix>=prix_min && produit->prix<=prix_max){
                ajouterRayon(mag, <#T_Rayon *rayon#>)
            }
            
            
            produit=produit->suivant
        }
        
        
        rayon->suivant
    }
    
    supprimerRayon(magasin, "zzz");
    
}
//Fin de recherProduits
*/



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
    char nomRayon[MaxTailleForRayonName];
    //Menu - 3
    char marqueProduit[MaxTailleForBrandName];
    double prixProduit = 0;
    enum quality qualiteProduit;
    int quantiteProduit = 0;
    //Menu - 4
    //Menu - 5
    //Menu - 6
    //Menu - 7
    //Menu - 8
    //Menu - 9
    int enFonctionnement = 0;
    
    
    
    while(enFonctionnement==0){
        int choix = 0;
      
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
                else if (magasin->premier==NULL){
                    printf("Veuillez selectionner le menu 2, afin de créer un rayon\n");
                }
                else{
                    printf("Veuillez entrer la marque du produit\n");
                    scanf("%s",marqueProduit);
                    
                    printf("Veuillez entrer le prix du produit\n");
                    scanf("%lf",&prixProduit);
                    
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
                if (magasin==NULL){
                    printf("Veuillez selectionner le menu 1, afin de créer un magasin\n");
                }
                else{
                afficherMagasin(magasin);
                }
                break;
                
            case 5:
                if (magasin==NULL){
                    printf("Veuillez selectionner le menu 1, afin de créer un magasin\n");
                }
                else if (magasin->premier==NULL){
                    printf("Veuillez créer un rayon avec le menu 2");
                }
                else{
                printf("Veuillez entrer le nom du rayon\n");
                scanf("%s",nomRayon);
                afficherRayon(retourneRayon(magasin, nomRayon));
                }
                break;
                
            case 6:
                if (magasin==NULL){
                    printf("Veuillez selectionner le menu 1, afin de créer un magasin\n");
                }
                else{
                afficherMagasin(magasin);
                printf("Veuillez entrer le nom du rayon dans lequel il faut supprimer un produit\n");
                scanf("%s",nomRayon);
                afficherRayon(retourneRayon(magasin, nomRayon));
                printf("quel produit voulez vous supprimer?\n");
                scanf("%s",marqueProduit);
                supprimerProduit(retourneRayon(magasin, nomRayon), marqueProduit);
                }
                break;
                
            case 7:
                if (magasin==NULL){
                    printf("Veuillez selectionner le menu 1, afin de créer un magasin\n");
                }
                else{
                afficherMagasin(magasin);
                printf("Veuillez entrer le nom du rayon à supprimer \n");
                scanf("%s",nomRayon);
                supprimerRayon(magasin, nomRayon);
                }
                break;
                
            case 8:
                break;
                
            case 9:
                if (magasin==NULL){
                    printf("Veuillez selectionner le menu 1, afin de créer un magasin\n");
                }
                else{
                    while(magasin->premier != NULL){
                        supprimerRayon(magasin, magasin->premier->nom_rayon);
                    }
                    
                    printf("La mémoire a été désallouée correctement\n");
                    printf("Aurevoir\n");
                    enFonctionnement++;
                }
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


//
//Table d'initialisation d'une base
//
void initialisationBase(T_Magasin *firstMagasin){

    T_Produit *produit = NULL;
    
    //Premier Rayon
    T_Rayon *milk = creerRayon("milk");
    ajouterRayon(firstMagasin, milk);
    
    produit = creerProduit("danone", 1.25, A, 200);
    ajouterProduit(milk, produit);
    produit = creerProduit("actimel", 2, A, 1200);
    ajouterProduit(milk, produit);
    produit = creerProduit("fromage", 1.25, C, 20);
    ajouterProduit(milk, produit);
    produit = creerProduit("lait", 1.02, B, 78);
    ajouterProduit(milk, produit);
 
    //Deuxieme Rayon
    T_Rayon *meat = creerRayon("meat");
    ajouterRayon(firstMagasin, meat);
    
    produit = creerProduit("boeuf", 4, A, 100);
    ajouterProduit(meat, produit);
    produit = creerProduit("poulet", 2, B, 120);
    ajouterProduit(meat, produit);
    produit = creerProduit("dinde", 3.12, C, 57);
    ajouterProduit(meat, produit );
    produit = creerProduit("mouton", 8, A, 90);
    ajouterProduit(meat, produit);
 
 
    //Troisieme Rayon
    T_Rayon *drink = creerRayon("drink");
    ajouterRayon(firstMagasin, drink);
    
    produit = creerProduit("coca", 1.2, A, 1000);
    ajouterProduit(drink, produit);
    produit = creerProduit("fanta", 3.4, A, 1200);
    ajouterProduit(drink, produit);
    produit = creerProduit("orangina", 3.12, A, 5700);
    ajouterProduit(drink, produit);
    produit =  creerProduit("iceTea", 5, A, 900);
    ajouterProduit(drink, produit);
}
//Fin de initialisationBase
