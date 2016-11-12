#include "tp3.h"

#define MaxTaileForMagasinName 50
#define MaxTailleForRayonName 25
#define MaxTailleForProductName 20

int main(int argc, const char * argv[]) {
    //Title of the program
    printf("Bonjour, Bienvenue dans notre simulateur de magasin\n");
    
    //Variables
    int enFonctionnement = 0;
    char nomMagasin[MaxTaileForMagasinName];
    char nomRayon[MaxTailleForRayonName];
    T_Magasin *magasin=NULL;
    
    
    while(enFonctionnement==0){
        int choix = 0;
        printf("\nMenu des actions possibles\n");
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
                    printf("le magasin est déjà créé\n");
                }
                break;
                
            case 2:
                printf("Veuillez entrer le nom du rayon\n");
                scanf("%s",nomRayon);
                ajouterRayon(magasin, creerRayon(nomRayon));
                break;
                
            case 3:
                printf("Veuillez entrer le nom du produit");
                //scanf("s",nomProduit);
                //prod
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
                enFonctionnement++;
                break;
                
            default:
                exit(EXIT_FAILURE);
                break;
            }
            
        }

    return 0;
}
