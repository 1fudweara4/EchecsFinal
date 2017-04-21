#include "header/lib.h"
#include "header/outils.h"
#include"header/menus.h"
#include "header/jeuOrdinateur.h"
#include "header/echiquier.h"

void lancementIA(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],int joueurQuiJoue,struct Pseudo Nom[2]){ //lancement de """"" l'ia""""""
    struct evaluationIA evaluationPossibilites[8][8];
    struct coordonnees meilleurDeplacement;

    printf("Lancement IA\n");

    printf("\nCalcul des possibilités...bip..bip\n"); // lol
    evaluationDesPossibilites(emplacementPions,evaluationPossibilites,joueurQuiJoue);
    printf("\nSelection meilleure possibilité...bip..bip\n"); // re lol
    meilleurDeplacement=selectionMeilleurePossibilite(evaluationPossibilites);
    deplacementPionEnMeilleurePossibilite(rendererWindow, emplacementPions,evaluationPossibilites,meilleurDeplacement,joueurQuiJoue);
}

void evaluationDesPossibilites(struct echiquier emplacementPions[8][8],struct evaluationIA evaluationPossibilites[8][8],int joueurQuiJoue){ //on met une note a a tous les pions de notre couleur en fonction des déplacements possibles et on met ce déplacement dans une variable
    int i,j;
    struct coordonnees emplacementInitial, propositionDeplacement[4];

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            reinitilisationPropositionDeplacement(propositionDeplacement);
            if(emplacementPions[i][j].emplacementPions==joueurQuiJoue){
                emplacementInitial.x=j;
                emplacementInitial.y=i;
                generationPropositionDeplacement(emplacementPions,emplacementInitial,propositionDeplacement,joueurQuiJoue);
                generationDeLaNote(emplacementPions, evaluationPossibilites, joueurQuiJoue, emplacementInitial, propositionDeplacement);
            }
            else{
                evaluationPossibilites[i][j].note=0;
            }
        }
    }
}

void reinitilisationPropositionDeplacement(struct coordonnees propositionDeplacement[4]){
    int i;
    for(i=0;i<4;i++){
         propositionDeplacement[i].x=-1;
         propositionDeplacement[i].y=-1;
    }
}

void generationDeLaNote(struct echiquier emplacementPions[8][8],struct evaluationIA evaluationPossibilites[8][8],int joueurQuiJoue,struct coordonnees emplacementInitial, struct coordonnees propositionDeplacement[4]){ // On génére la note en fonction de certains paramètres

    if(propositionDeplacement[0].x!=-1 || propositionDeplacement[2].x!=-1){
            noteDeplacementHorizontaux(emplacementPions,evaluationPossibilites,joueurQuiJoue,emplacementInitial,propositionDeplacement);
    }
    else if(propositionDeplacement[1].x!=-1){
        printf("Déplacement avant possible en %d %d\n",emplacementInitial.x,emplacementInitial.y);
        evaluationPossibilites[emplacementInitial.y][emplacementInitial.x].note=1;
        evaluationPossibilites[emplacementInitial.y][emplacementInitial.x].meilleurDeplacementDuPion.x=propositionDeplacement[1].x;
        evaluationPossibilites[emplacementInitial.y][emplacementInitial.x].meilleurDeplacementDuPion.y=propositionDeplacement[1].y;
    }
    else{
        printf("Pas de déplacement possible en %d %d\n",emplacementInitial.x,emplacementInitial.y);
        evaluationPossibilites[emplacementInitial.y][emplacementInitial.x].note=0;
    }
}

void noteDeplacementHorizontaux(struct echiquier emplacementPions[8][8],struct evaluationIA evaluationPossibilites[8][8],int joueurQuiJoue,struct coordonnees emplacementInitial, struct coordonnees propositionDeplacement[4]){ // On note les déplacement horizontaux, il y a les deux déplacements posisbles on va toujours prendre celui de droite (Pourquoi? Parce que.)

    if(propositionDeplacement[0].x!=-1){

        printf("Deplacement latéraux possibles en %d %d\n",emplacementInitial.x,emplacementInitial.y);
        evaluationPossibilites[emplacementInitial.y][emplacementInitial.x].note=5;
        evaluationPossibilites[emplacementInitial.y][emplacementInitial.x].meilleurDeplacementDuPion.x=propositionDeplacement[0].x;
        evaluationPossibilites[emplacementInitial.y][emplacementInitial.x].meilleurDeplacementDuPion.y=propositionDeplacement[0].y;
    }
    if(propositionDeplacement[2].x!=-1){

        printf("Deplacement latéraux possibles en %d %d\n",emplacementInitial.x,emplacementInitial.y);
        evaluationPossibilites[emplacementInitial.y][emplacementInitial.x].note=5;
        evaluationPossibilites[emplacementInitial.y][emplacementInitial.x].meilleurDeplacementDuPion.x=propositionDeplacement[2].x;
        evaluationPossibilites[emplacementInitial.y][emplacementInitial.x].meilleurDeplacementDuPion.y=propositionDeplacement[2].y;
    }
}

struct coordonnees selectionMeilleurePossibilite(struct evaluationIA evaluationPossibilites[8][8]){ //fonction qui renvoie la meilleure possibilité quand elle a le tableau contenant les notes des déplacements
    int noteMax,nombreNoteMax;
    struct coordonnees meilleurDeplacement;

    rechercheNoteMaxEtNombreIteration(evaluationPossibilites, &noteMax,&nombreNoteMax);
    printf("Note max : %d /Nombre Iteration: %d\n",noteMax, nombreNoteMax);
    meilleurDeplacement=selectionAuHasardPossibiliteAvecNoteMax(evaluationPossibilites,noteMax,nombreNoteMax);

    printf("Possibilité choisie: %d %d \n\n",meilleurDeplacement.x ,meilleurDeplacement.y);

    return meilleurDeplacement;
}

void rechercheNoteMaxEtNombreIteration(struct evaluationIA evaluationPossibilites[8][8],int* noteMax, int* nombreNoteMax){ // on regarde quelle est la meilleure note et le nombre de fois qu'elle est présente
    int i,j;
    *noteMax=0;
    *nombreNoteMax=0;

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(evaluationPossibilites[i][j].note>0){
                if(evaluationPossibilites[i][j].note==*noteMax){
                    *nombreNoteMax=*nombreNoteMax+1;
                }
                if(evaluationPossibilites[i][j].note>*noteMax){
                    *noteMax=evaluationPossibilites[i][j].note;
                    *nombreNoteMax=1;
                }
            }
        }
    }
}

struct coordonnees selectionAuHasardPossibiliteAvecNoteMax(struct evaluationIA evaluationPossibilites[8][8],int noteMax,int nombreNoteMax){ //On selectionne la note max et on fait un random si elle est présente plusieurs fois
    struct coordonnees meilleurDeplacement;
    int i,j, choix, avancement=0;

    srand(time(NULL));
    choix=rand()%nombreNoteMax;

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(evaluationPossibilites[i][j].note==noteMax){
                if(avancement==choix){
                    meilleurDeplacement.x=j;
                    meilleurDeplacement.y=i;
                }
                avancement++;
            }
        }
    }
    return meilleurDeplacement;
}



void deplacementPionEnMeilleurePossibilite(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],struct evaluationIA evaluationPossibilites[8][8],struct coordonnees meilleurDeplacement,int joueurQuiJoue){ // déplacement du pion au "meilleur déplacement"

    emplacementPions[meilleurDeplacement.y][meilleurDeplacement.x].emplacementPions=0;
    emplacementPions[ evaluationPossibilites[meilleurDeplacement.y][meilleurDeplacement.x].meilleurDeplacementDuPion.y ][ evaluationPossibilites[meilleurDeplacement.y][meilleurDeplacement.x].meilleurDeplacementDuPion.x ].emplacementPions=joueurQuiJoue+(joueurQuiJoue-1);

    SDL_Delay(500);
    printf("Mise à jour des pions\n");
    affichageCaseCouleurEnFonctionPosition(rendererWindow,meilleurDeplacement.x,meilleurDeplacement.y);
    affichageCaseCouleurEnFonctionPosition(rendererWindow, evaluationPossibilites[meilleurDeplacement.y][meilleurDeplacement.x].meilleurDeplacementDuPion.x , evaluationPossibilites[meilleurDeplacement.y][meilleurDeplacement.x].meilleurDeplacementDuPion.y );
    affichagePions(rendererWindow,emplacementPions, evaluationPossibilites[meilleurDeplacement.y][meilleurDeplacement.x].meilleurDeplacementDuPion.x , evaluationPossibilites[meilleurDeplacement.y][meilleurDeplacement.x].meilleurDeplacementDuPion.y );
    SDL_RenderPresent(rendererWindow);
}


// IA ok car Victor perd contre 1 fois sur 2.....
