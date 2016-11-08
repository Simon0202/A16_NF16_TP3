#include "tp3.h"



int main(int argc, const char * argv[]) {

    T_Magasin *carrefour = creerMagasin("carrefour");
    T_Rayon *laitier = creerRayon("laitier");
    T_Produit *danone = creerProduit("danone", 3.14, A, 200);
    
    ajouterRayon(carrefour, laitier);
    afficherMagasin(carrefour);
    ajouterProduit(laitier, danone);
    afficherRayon(laitier);
    return 0;
}
