#include "tp3.h"



int main(int argc, const char * argv[]) {

    /*
    T_Magasin *carrefour = creerMagasin("Carrefour");
    T_Magasin *simply = creerMagasin("Simply");
    T_Rayon *laitier = creerRayon("laitier");
    T_Produit *danone = creerProduit("danone", 3.14, A, 200);
    
    ajouterRayon(carrefour, laitier);
    afficherMagasin(carrefour);
*/
    printf("Bonjour, Bienvenue dans notre simulateur de magasin\n");
    int enFonctionnement = 0;
    while(enFonctionnement==0){
        int choix = 0;
        printf("Menu des actions possibles\n");
        printf("Tapez 1 - Créer un magasin");
        printf("Tapez 2 - Ajouter un rayon au magasin");
        printf("Tapez 3 - Ajouter un produit dans un rayon");
        printf("Tapez 4 - Afficher les rayons du magasin");
        printf("Tapez 5 - Afficher les produits d'un rayon");
        printf("Tapez 6 - Supprimer un produit");
        printf("Tapez 7 - Supprimer un rayon");
        printf("Tapez 8 - Rechercher un produit par prix");
        printf("Tapez 9 - Quitter");
        
        switch(choix){
            case 1:
                printf("Veuillez entrer le nom du magasin");
                char *nomMagasin;
                scanf("%s",nomMagasin);
                creerMagasin(nomMagasin);
                break;
                
            case 2:
                break;
                
            case 3:
                break;
                
            case 4:
                break;
                
            case 5:
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
                choix++;
                break;
                
            default:
                exit(EXIT_FAILURE);
                break;
            }
            
        }
    return 0;
}
