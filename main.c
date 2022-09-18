#include <stdlib.h>
#include <stdio.h>

//------------------------------------------------------------------//
//                                                                  //
//  NoeudAllumette : structure                                      //
//            - int nballumette : nombre d'allumettes restantes     //
//            - int typejoueur :                                    //
//                  * 0 : joueur humain                             //
//                  * 1 : ordinateur                                //
//            - int eval : le résultat de la fonction d'évaluation  //
//            - NoeudAllumette *fg : fils gauche                    //
//            - NoeudAllumette *fd : fils droit                     //
//------------------------------------------------------------------//

typedef struct NoeudAllumette {
    int nballumette;
    int typejoueur;
    int eval;
    struct NoeudAllumette *fg;
    struct NoeudAllumette *fm;
    struct NoeudAllumette *fd;
} noeudallumette;


//------------------------------------------------------------------//
//  creeNoeudAllumette : fonction                                   //
//           - but de la fonction : initialise un  noeud de l'arbre //
//           - ce qu'il faut savoir :                               //
//                * nballumette : -1 donc pas d'allumette           //
//                * typejoueur : -1 pas de joueur                   //
//                * eval : -1 pas d'évaluation                      //
//                * fg : pas de fils gauche                         //
//                * fd : pas de fils droit                          //
//------------------------------------------------------------------//

noeudallumette* creerNoeudAllumette() {
    noeudallumette* temp = (noeudallumette*) malloc(sizeof (noeudallumette));
    temp->nballumette = -1;
    temp->typejoueur = -1;
    temp->eval = -1;
    temp->fg = NULL;
    temp->fm = NULL;
    temp->fd = NULL;

    return temp;
}

//------------------------------------------------------------------//
//  testNoeudAllumette : fonction                                   //
//           - but de la fonction : tester un  noeud de l'arbre     //
//           - ce qu'il faut savoir :                               //
//                * nballumette : -1 donc pas d'allumette           //
//                * typejoueur : -1 pas de joueur                   //
//                * eval : -1 pas d'évaluation                      //
//                * fg : pas de fils gauche                         //
//                * fd : pas de fils droit                          //
//           - code retour :                                        //
//                * 0 : pas d'erreur                                //
//                * 1 : pas d'allocation                            //
//                * 2 : pas de nombre d'allumette                   //
//                * 3 : pas de type de joueur                       //
//                * 4 : pas d'évaluation                            //
//------------------------------------------------------------------//

int testNoeudAllumette(noeudallumette *noeud) {
    if (noeud == NULL) return 1;
    if (noeud->nballumette == -1) return 2;
    if (noeud->typejoueur == -1) return 3;
    if (noeud->eval == -1) return 4;
    return 0;
}

//------------------------------------------------------------------//
//  ajouteNoeudAllumette : fonction                                 //
//           - but de la fonction : ajouter un  noeud dans l'arbre  //
//           - ce qu'il faut savoir :                               //
//             ajout de trois fils si assez d'allumettes            //
//------------------------------------------------------------------//

int ajouteNoeudAllumette(noeudallumette *noeud) {
    if (noeud == NULL) return 1;

    if (noeud->nballumette >= 3) {
        noeud->fd = creerNoeudAllumette();
        noeud->fd->nballumette = noeud->nballumette - 3;
        if (noeud->typejoueur == 0) noeud->fd->typejoueur = 1;
        else noeud->fd->typejoueur = 0;
        noeud->fd->fd = NULL;
        noeud->fd->fm = NULL;
        noeud->fd->fg = NULL;

    }
    if (noeud->nballumette >= 2) {
        noeud->fm = creerNoeudAllumette();
        noeud->fm->nballumette = noeud->nballumette - 2;
        if (noeud->typejoueur == 0) noeud->fm->typejoueur = 1;
        else noeud->fm->typejoueur = 0;
        noeud->fm->fd = NULL;
        noeud->fm->fm = NULL;
        noeud->fm->fg = NULL;
    }
    if (noeud->nballumette >= 1) {
        noeud->fg = creerNoeudAllumette();
        noeud->fg->nballumette = noeud->nballumette - 1;
        if (noeud->typejoueur == 0) noeud->fg->typejoueur = 1;
        else noeud->fg->typejoueur = 0;
        noeud->fg->fd = NULL;
        noeud->fg->fm = NULL;
        noeud->fg->fg = NULL;
    }
    return 0;
}

//------------------------------------------------------------------//
//  testvaleurmin : fonction                                        //
//           - but de la fonction : tester pour trouver le meilleur fils  //
//------------------------------------------------------------------//

noeudallumette* testvaleurmin(noeudallumette* noeud) {
    if (noeud == NULL) return NULL;
    int filsd = noeud->fd == NULL ? 0 : 1;
    int filsm = noeud->fm == NULL ? 0 : 1;
    int filsg = noeud->fg == NULL ? 0 : 1;

    if (filsd) {
        if (filsm) {
            if (filsg) {
                if (noeud->fg->eval > noeud->fm->eval) {
                    if (noeud->fg->eval > noeud->fd->eval)
                        return noeud->fg;
                    else {
                        if (noeud->fd->eval > noeud->fm->eval)
                            return noeud->fd;
                        return noeud->fm;
                    }
                } else {
                    if (noeud->fm->eval > noeud->fd->eval)
                        return noeud->fm;
                    else {
                        if (noeud->fd->eval > noeud->fg->eval)
                            return noeud->fd;
                        return noeud->fg;
                    }
                }

                return noeud->fm;
            } else {
                if (noeud->fm->eval > noeud->fd->eval) return noeud->fm;
                return noeud->fd;
            }
        } else {
            if (filsg) {
                if (noeud->fg->eval > noeud->fd->eval) return noeud->fg;
                return noeud->fd;
            }
            return noeud->fd;
        }
    } else {
        if (filsm) {
            if (filsg) {
                if (noeud->fg->eval > noeud->fm->eval) return noeud->fg;
                return noeud->fm;
            } else return noeud->fm;
        } else {
            if (filsg) return noeud->fg;
            return NULL;
        }
    }
}

//------------------------------------------------------------------//
// fonction destructeur
//------------------------------------------------------------------//

void libererarbre(noeudallumette* noeud) {
    if (noeud != NULL) {
        libererarbre(noeud->fg);
        libererarbre(noeud->fd);
        free(noeud);
    }
}

void initarbreNoeudAllumette(noeudallumette *arbre) {
    if (arbre->nballumette > 0) {
        ajouteNoeudAllumette(arbre);
        if (arbre->fd != NULL) initarbreNoeudAllumette(arbre->fd);
        if (arbre->fm != NULL) initarbreNoeudAllumette(arbre->fm);
        if (arbre->fg != NULL) initarbreNoeudAllumette(arbre->fg);
    }
}

void affiche(noeudallumette *arbre) {
    if (arbre != NULL) {
        affiche(arbre->fg);
        printf("---> %d avec comme evaluation : %d \n", arbre->nballumette, arbre->eval);
        affiche(arbre->fm);
        affiche(arbre->fd);
    }

}

void getevalfeuille(noeudallumette *arbre) {
    if (arbre != NULL) {
        getevalfeuille(arbre->fg);
        getevalfeuille(arbre->fm);
        getevalfeuille(arbre->fd);

        if (arbre->fg == NULL) {
            if (arbre->typejoueur == 1) {
                arbre->eval = 1; // l'ordi a gagné
            } else {
                arbre->eval = 0; // le joueur a gagné la partie
            }
        }
    }
}

void getevalother(noeudallumette *arbre) {
    if (arbre != NULL) {
        getevalother(arbre->fg);
        getevalother(arbre->fm);
        getevalother(arbre->fd);

        if (arbre->fd != NULL) {
            if (arbre->typejoueur == 1) {
                if (arbre->fg->eval > arbre->fm->eval) {
                    if (arbre->fg->eval > arbre->fd->eval) {
                        arbre->eval = arbre->fg->eval;
                    } else arbre->eval = arbre->fd->eval;
                } else {
                    if (arbre->fm->eval > arbre->fd->eval) {
                        arbre->eval = arbre->fm->eval;
                    } else arbre->eval = arbre->fd->eval;

                }
            } else {
                if (arbre->fg->eval < arbre->fm->eval) {
                    if (arbre->fg->eval < arbre->fd->eval) {
                        arbre->eval = arbre->fg->eval;
                    } else arbre->eval = arbre->fd->eval;
                } else {
                    if (arbre->fm->eval < arbre->fd->eval) {
                        arbre->eval = arbre->fm->eval;
                    } else arbre->eval = arbre->fd->eval;

                }
            }

        } else if (arbre->fm != NULL) {
            if (arbre->typejoueur == 1) {
                if (arbre->fg->eval > arbre->fm->eval) {
                    arbre->eval = arbre->fg->eval;
                } else
                    arbre->eval = arbre->fm->eval;
            } else {
                if (arbre->fg->eval < arbre->fm->eval) {
                    arbre->eval = arbre->fg->eval;
                } else
                    arbre->eval = arbre->fm->eval;
            }
        } else if (arbre->fg != NULL)
            arbre->eval = arbre->fg->eval;

    }

}

int main() {
    //------------------------------------------------------------------//
    // déclaration des variables
    int quicommence = -1;
    noeudallumette *arbre = (noeudallumette *) creerNoeudAllumette();
    int estlafin = -1;
    int choixallumette = 0;
    noeudallumette *noeudachoisir;
    noeudallumette *savearbre = arbre;
    //------------------------------------------------------------------//


    //------------------------------------------------------------------//
    // détermination du joueur qui va commencer

    printf("- Choisissez combien d'allumettes seront mis en jeu : ");
    scanf("%d", &quicommence);
    printf("\n");


    arbre->nballumette = quicommence;

    printf("- Choisissez quel joueur va commenter la partie :\n");
    printf("  ° 0 : vous commencez le jeu \n");
    printf("  ° 1 : l'ordinateur commence \n");
    printf("    --> Votre choix : ");
    scanf("%d", &quicommence);

    if (quicommence == 0) printf("\n\n Le joueur va commencer en premier \n");
    else if (quicommence == 1) printf("\n\n L'ordinateur va commencer en premier \n");
    else {
        printf("\n\n Vous avez tapé une mauvaise touche, ... c'est pas grave, l'ordinateur va commencer\n");
        quicommence = 1;
    }
    arbre->typejoueur = quicommence;


    //------------------------------------------------------------------//
    // initialisation de l'arbre

    initarbreNoeudAllumette(arbre);
    getevalfeuille(arbre);
    getevalother(arbre);
    //affiche(arbre);
    //------------------------------------------------------------------//


    //------------------------------------------------------------------//
    // boucle de jeu

    while (estlafin == -1) {
        // c'est à l'ordi de jouer, on regenere l'arbre pour choisir la meilleure combinaison
        if (arbre->typejoueur == 1) {
            noeudachoisir = testvaleurmin(arbre);
            if (noeudachoisir == arbre->fg) printf("L'ordinateur a choisi de retirer 1 allumette \n");
            if (noeudachoisir == arbre->fm) printf("L'ordinateur a choisi de retirer 2 allumettes\n");
            if (noeudachoisir == arbre->fd) printf("L'ordinateur a choisi de retirer 3 allumettes\n");
            arbre = noeudachoisir;
        } else {
            printf("C'est à vous de jouer : combien d'allumette souhaitez vous retirer?\n");
            printf("(Nombre d'allumettes restantes : %d) \n", arbre->nballumette);

            if (arbre->fg != NULL) printf("1) retirer une allumette\n");
            if (arbre->fm != NULL) printf("2) retirer deux allumettes\n");
            if (arbre->fd != NULL) printf("3) retirer trois allumettes\n");

            printf("\n Votre choix (attention : en cas d'erreur de frappe, le jeu retira une allumette automatiquement) : ");
            scanf("%d", &choixallumette);

            if ((choixallumette == 1) && (arbre->fg != NULL)) arbre = arbre->fg;
            else if ((choixallumette == 2) && (arbre->fm != NULL)) arbre = arbre->fm;
            else if ((choixallumette == 3) && (arbre->fd != NULL)) arbre = arbre->fd;
            else if (arbre->fg != NULL) arbre = arbre->fg;
        }

        if (arbre->nballumette == 1) estlafin = 0;
    }
    //------------------------------------------------------------------//


    //------------------------------------------------------------------//    
    // fin de partie 
    if (arbre->typejoueur == 1) printf("\n\n Vous avez gagné, Bravo !!!!!!!!!!!!!!!!!!!!! \n");
    else printf("\n\n C'est pas grave, perdre peut etre de temps en temps une bonne chose \n");
    //------------------------------------------------------------------//

    libererarbre(savearbre);

    scanf("%d", &quicommence);
    return 0;
}
