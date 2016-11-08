#include <stdio.h>
#include <stdlib.h>

#include "tp3.h"



int main(int argc, const char * argv[]) {

    T_Magasin *Carrefour = creerMagasin("carrefour");
    T_Rayon *laitier = creerRayon("laitier");
    T_Produit *danone = creerProduit("danone", 3.14, A, 200);
    
    return 0;
}
