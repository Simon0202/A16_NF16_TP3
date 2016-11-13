#include "tp3.h"

int main(int argc, const char * argv[]) {
    //Title of the program
    printf("Bonjour, Bienvenue dans notre simulateur de magasin\n");
    T_Magasin *magasinPrincipal = initialisationBase();
    menu(magasinPrincipal);
    
    return 0;
}
