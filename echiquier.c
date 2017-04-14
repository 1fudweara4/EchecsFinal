#include "header/outils.h"
#include"header/menus.h"
#include "header/echiquier.h"

void lancementEchiquier(SDL_Renderer* rendererWindow,struct Pseudo Nom[2],char* cheminEnregistrement){

    int emplacementPions[8][8];

    printf("Lancement Echiquier\n");
    initalisationEchiquier(emplacementPions,cheminEnregistrement);

    affichagePartieEchiquier(rendererWindow,emplacementPions,Nom);
    SDL_RenderPresent(rendererWindow);
    printf("\n\n");

    lancementPartie(rendererWindow,emplacementPions,Nom);

}


void initalisationEchiquier(int emplacementPions[8][8],char* cheminEnregistrement){
    if(strcmp(cheminEnregistrement,"")==0){
        premierRemplissageTableauEchiquier(emplacementPions);
    }
    else{
        /** Fonction Chargement echiquier sauvegardé **/
    }
}

void premierRemplissageTableauEchiquier(int emplacementPions[8][8]){
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
                if(i<2){
                    emplacementPions[i][j]=1;
                    printf(" 1|");
                }
                else if(i>5){
                    emplacementPions[i][j]=-1;
                    printf("-1|");
                }
                else{
                    emplacementPions[i][j]=0;
                    printf(" 0|");
                }
        }
        printf("\n");
    }
    printf("Echiquier rempli\n");
}


void affichagePartieEchiquier(SDL_Renderer* rendererWindow,int emplacementPions[8][8],struct Pseudo Nom[2]){
    mettreFondEcranUni(rendererWindow);
    affichageEchiquierEtPions(rendererWindow,emplacementPions);
    affichagePseudo(rendererWindow,Nom);
    affichageNombreDePions(rendererWindow,emplacementPions);
}

void affichageEchiquierEtPions(SDL_Renderer* rendererWindow,int emplacementPions[8][8]){
    int i,j;

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            affichageCaseCouleurEnFonctionPosition(rendererWindow,j,i);
            affichagePions(rendererWindow,emplacementPions,j,i);
        }
    }
}

void affichageCaseCouleurEnFonctionPosition(SDL_Renderer* rendererWindow,int x,int y){
    struct coordonnees tailleFenetre;
    SDL_Rect CaractCase;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);
    CaractCase.w=CaractCase.h=tailleFenetre.y*7/64;
    CaractCase.y=((tailleFenetre.y-tailleFenetre.y*7/8)/2)+CaractCase.h*y;
    CaractCase.x=((tailleFenetre.x-tailleFenetre.y*7/8)/2)+CaractCase.h*x;
    if(x%2==0){
                if(y%2==0){
                    affichageImageBMP(rendererWindow,CaractCase,"DAT/Image/caseBlanche.bmp");
                }
                else{
                    affichageImageBMP(rendererWindow,CaractCase,"DAT/Image/caseNoir.bmp");
                }
            }
            else{
                if(y%2==0){
                    affichageImageBMP(rendererWindow,CaractCase,"DAT/Image/caseNoir.bmp");
                }
                else{
                    affichageImageBMP(rendererWindow,CaractCase,"DAT/Image/caseBlanche.bmp");
                }
            }
            printf("Affichage couleur case en %d %d\n",x,y);

}

void affichagePions(SDL_Renderer* rendererWindow,int emplacementPions[8][8],int x,int y){
    struct coordonnees tailleFenetre;
    SDL_Rect CaractCase;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);
    CaractCase.w=CaractCase.h=tailleFenetre.y*7/64;
    CaractCase.y=((tailleFenetre.y-tailleFenetre.y*7/8)/2)+CaractCase.h*y;
    CaractCase.x=((tailleFenetre.x-tailleFenetre.y*7/8)/2)+CaractCase.h*x;

    if(emplacementPions[y][x]==-1){
        affichageImagePNG(rendererWindow,CaractCase,"DAT/Image/pionBlanc.png");
    }
    else if(emplacementPions[y][x]==1){
        affichageImagePNG(rendererWindow,CaractCase,"DAT/Image/pionNoir.png");
    }
}

void affichagePseudo(SDL_Renderer*rendererWindow,struct Pseudo Nom[2]){
    int i;
    struct coordonnees tailleFenetre;
    SDL_Rect caractTextePseudo[2];

    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);
    caractTextePseudo[0].h=caractTextePseudo[1].h=0;
    caractTextePseudo[0].w=caractTextePseudo[1].w=0;
    caractTextePseudo[1].x=((tailleFenetre.x-tailleFenetre.y*7/8)/2)/2;
    caractTextePseudo[0].x=tailleFenetre.x-((tailleFenetre.x-tailleFenetre.y*7/8)/2)/2;
    caractTextePseudo[1].y=tailleFenetre.y/3;
    caractTextePseudo[0].y=tailleFenetre.y/3*2;

    for(i=0;i<2;i++){
        if(strcmp(&Nom[i].Nom[0],"")==0){
            affichageTexte(rendererWindow,"Ordinateur",30,caractTextePseudo[i]);
        }
        else{
            affichageTexte(rendererWindow,Nom[i].Nom,30,caractTextePseudo[i]);
        }
    }
}

void affichageNombreDePions(SDL_Renderer*rendererWindow,int emplacementPions[8][8]){
    int i;
    struct coordonnees tailleFenetre;
    SDL_Rect CaractTexte[2];
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);
    char Nb[8];

    CaractTexte[0].h=CaractTexte[1].h=0;
    CaractTexte[0].w=CaractTexte[1].w=0;
    CaractTexte[1].x=((tailleFenetre.x-tailleFenetre.y*7/8)/2)/2;
    CaractTexte[1].y=tailleFenetre.y/3+tailleFenetre.y/10;

    CaractTexte[0].x=tailleFenetre.x-((tailleFenetre.x-tailleFenetre.y*7/8)/2)/2;
    CaractTexte[0].y=tailleFenetre.y-tailleFenetre.y/3+tailleFenetre.y/10;

    for(i=0;i<2;i++){
        sprintf (Nb, "%d", compterNbPions(emplacementPions,-1+2*i));
        if(compterNbPions(emplacementPions,-1+2*i)==1){
            strcat(Nb," pion ");
        }
        else{
            strcat(Nb," pions");
        }
        affichageTexte(rendererWindow,Nb,30,CaractTexte[i]);
        printf("%d pions restants\n",compterNbPions(emplacementPions,-1+2*i));
    }
}


int compterNbPions(int emplacementPions[8][8],int Couleur){
    int NombreDePions=0,i,j;

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(emplacementPions[i][j]==Couleur){
                NombreDePions++;
            }
        }
    }
    return NombreDePions;
}



void lancementPartie(SDL_Renderer* rendererWindow,int emplacementPions[8][8],struct Pseudo Nom[2]){
    int i,Quitter=0,causeFin=0;

    while(!Quitter){
        for(i=0;i<2;i++){
            deroulementDuTour(rendererWindow,emplacementPions,Nom,i,&causeFin);
            Quitter=verificationConditionFin(&causeFin, emplacementPions,i);
        }
    }
    issuePartie(rendererWindow,causeFin);
    /** METTRE ICI LA FONCTION POUR GERER LES ISSUES POSSIBLES DE LA PARTIE **/
}

void deroulementDuTour(SDL_Renderer* rendererWindow,int emplacementPions[8][8],struct Pseudo Nom[2],int joueurQuiJoue,int* causeFin){
    //int Quitter; //Chnager pour mettre à 0 quand la vérificationcondition fin est faite

    if(*causeFin==0){
            if(strcmp(&Nom[joueurQuiJoue].Nom[0],"")==0){
                printf("Ordinateur qui joue\n");
                /** Mettre la fonction pour l'IA **/
            }
            else{
                printf("Joueur 'réel' qui joue\n");
                actionDuJoueur(rendererWindow,emplacementPions,joueurQuiJoue,causeFin,Nom);
            }
    }
}

void actionDuJoueur(SDL_Renderer* rendererWindow,int emplacementPions[8][8],int joueurQuiJoue,int* causeFin,struct Pseudo Nom[2]){
    //Utiliser causeFin seulement pour sauvegarde
    int Quitter=0;
    SDL_Event event;
    Uint32 Timer;

    while(!Quitter){
        Timer=SDL_GetTicks();
        if(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_WINDOWEVENT:
                    if ( event.window.event == SDL_WINDOWEVENT_CLOSE ){
                          *causeFin=2;
                          Quitter=1;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    Quitter=actionPremierCLique(rendererWindow,emplacementPions,joueurQuiJoue,causeFin);
                    break;
                case SDL_KEYUP:
                    if ( event.key.keysym.sym == SDLK_ESCAPE ){
                        //Quitter=1; // Mettre après affichage menu avec demande de sauvegarde etc...
                        Quitter=menuSauvegarder(rendererWindow,emplacementPions,Nom, causeFin);
                    }
                    break;
            }
        }
        PauseEnfonctionDureeExecution(Timer);
    }
}

int actionPremierCLique(SDL_Renderer* rendererWindow,int emplacementPions[8][8],int joueurQuiJoue,int* causeFin){
    int Quitter=0;
    struct coordonnees propositionDeplacement[3]={{-1,-1},{-1,-1},{-1,-1}};
    struct coordonnees positionDansEchiquier=detectionEmplacementDuCliqueDansEchiquier(rendererWindow);

    if(emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x]==joueurQuiJoue+(joueurQuiJoue-1)){ //0=>-1 et 1=>1
        generationPropositionDeplacement(emplacementPions,positionDansEchiquier,propositionDeplacement,joueurQuiJoue);
        printf("%d %d\n",propositionDeplacement[0].x,propositionDeplacement[0].y);
        printf("%d %d\n",propositionDeplacement[1].x,propositionDeplacement[1].y);
        printf("%d %d\n",propositionDeplacement[2].x,propositionDeplacement[2].y);

        if(verificationSiIlyaPossibilites(propositionDeplacement)){
        affichagePropositionDeplacement(rendererWindow,propositionDeplacement);
        Quitter=actionsDeplacement(rendererWindow,emplacementPions,propositionDeplacement,positionDansEchiquier,joueurQuiJoue,causeFin);
        SuppressionPropositionsDeplacement(rendererWindow,propositionDeplacement,emplacementPions);
        }
        if(Quitter==1){
            deplacementPion(rendererWindow,emplacementPions,propositionDeplacement,positionDansEchiquier,joueurQuiJoue);
            affichageNombreDePions(rendererWindow,emplacementPions);
            SDL_RenderPresent(rendererWindow);
        }
    }
    return Quitter;
}

struct coordonnees detectionEmplacementDuCliqueDansEchiquier(SDL_Renderer* rendererWindow){
    struct coordonnees positionClique,tailleFenetre;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);
    SDL_GetMouseState(&positionClique.x,&positionClique.y);
    SDL_Rect CaracteristiqueEchiquier={ ((tailleFenetre.x-tailleFenetre.y*7/8)/2) , ((tailleFenetre.y-tailleFenetre.y*7/8)/2) , tailleFenetre.y*7/8/8 , tailleFenetre.y*7/8/8};

    if(positionClique.x>CaracteristiqueEchiquier.x && positionClique.x<CaracteristiqueEchiquier.x+8*CaracteristiqueEchiquier.h && positionClique.y>CaracteristiqueEchiquier.y && positionClique.y<CaracteristiqueEchiquier.y+8*CaracteristiqueEchiquier.w ){
        positionClique.x=(positionClique.x-CaracteristiqueEchiquier.x)/CaracteristiqueEchiquier.h;
        positionClique.y=(positionClique.y-CaracteristiqueEchiquier.y)/CaracteristiqueEchiquier.w;
        printf("Clique sur la case %d %d\n",positionClique.x ,positionClique.y);
    }
    else{
        printf("Clique en dehors de l'échiquier\n");
        positionClique.x=positionClique.y=-1;
    }

    return positionClique;
}

void generationPropositionDeplacement(int emplacementPions[8][8],struct coordonnees positionDansEchiquier, struct coordonnees propositionDeplacement[3],int joueurQuiJoue){
    int i;
    for(i=-1;i<2;i=i+2){
        if(positionDansEchiquier.x+i>=0 && positionDansEchiquier.x+i<8 && positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x]>=0 && positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x]<8){
            if(emplacementPions[positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x]][positionDansEchiquier.x+i]!=0 && emplacementPions[positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x]][positionDansEchiquier.x+i]!=joueurQuiJoue+(joueurQuiJoue-1)){
                propositionDeplacement[1+i].x=positionDansEchiquier.x+i;
                propositionDeplacement[1+i].y=positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x];
            }
        }
    }
    if(positionDansEchiquier.x>=0 && positionDansEchiquier.x<8 && positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x]>=0 && positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x]<8){
        if(emplacementPions[positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x]][positionDansEchiquier.x]==0){
            propositionDeplacement[1].x=positionDansEchiquier.x;
            propositionDeplacement[1].y=positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x];
        }
    }
}

void affichagePropositionDeplacement(SDL_Renderer* rendererWindow,struct coordonnees propositionDeplacement[3]){

    int i;
    struct coordonnees tailleFenetre;
    SDL_Rect positionProposition;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);
    positionProposition.h=positionProposition.w=tailleFenetre.y*7/8/8;

    printf("Affichage de :\n");
    for(i=0;i<3;i++){
        if(propositionDeplacement[i].x!=-1){
            positionProposition.x=((tailleFenetre.x-tailleFenetre.y*7/8)/2)+positionProposition.w*propositionDeplacement[i].x;
            positionProposition.y=((tailleFenetre.y-tailleFenetre.y*7/8)/2)+positionProposition.h*propositionDeplacement[i].y;
            affichageImagePNG(rendererWindow,positionProposition,"DAT/Image/proposition.png");
        }
    }
    SDL_RenderPresent(rendererWindow);

}

int verificationSiIlyaPossibilites(struct coordonnees propositionDeplacement[3]){
    int i,possibiliteExistante=0;

    for(i=0;i<3;i++){
            if(propositionDeplacement[i].x!=-1){
                possibiliteExistante=1;
            }
    }

    return possibiliteExistante;
}

int actionsDeplacement(SDL_Renderer* rendererWindow, int emplacementPions[8][8],struct coordonnees propositionDeplacement[3],struct coordonnees positionDansEchiquier,int joueurQuiJoue, int* causeFin){
    SDL_Event event;
    int Quitter=0,Quitter1=0;
    Uint32 Timer;

    while(!Quitter1){
        Timer=SDL_GetTicks();
        if(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEBUTTONUP:
                    Quitter=evenementCliqueDemandeProposition(rendererWindow, emplacementPions,propositionDeplacement,positionDansEchiquier,joueurQuiJoue);
                    Quitter1=1;
                    break;

                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_CLOSE){
                        Quitter1=1;
                        Quitter=1;
                        *causeFin=2;
                    }
                    break;
                case SDL_KEYUP:
                    if(event.key.keysym.sym == SDLK_ESCAPE){
                        Quitter1=1;
                    }
                    break;
            }
        }
    PauseEnfonctionDureeExecution(Timer);
    }
    return Quitter;
}

int evenementCliqueDemandeProposition(SDL_Renderer* rendererWindow, int emplacementPions[8][8],struct coordonnees propositionDeplacement[3],struct coordonnees positionDansEchiquier,int joueurQuiJoue){
    int i,Quitter=0;
    struct coordonnees positionCurseur,tailleEcran;
    SDL_GetRendererOutputSize(rendererWindow,&tailleEcran.x,&tailleEcran.y);
    SDL_GetMouseState(&positionCurseur.x,&positionCurseur.y);

    for(i=0;i<3;i++){
        if(positionCurseur.x>((tailleEcran.x-tailleEcran.y*7/8)/2)+tailleEcran.y*7/8/8*propositionDeplacement[i].x && positionCurseur.x<((tailleEcran.x-tailleEcran.y*7/8)/2)+tailleEcran.y*7/8/8*(propositionDeplacement[i].x+1)){
            if(positionCurseur.y>((tailleEcran.y-tailleEcran.y*7/8)/2)+tailleEcran.y*7/8/8*propositionDeplacement[i].y && positionCurseur.y<((tailleEcran.y-tailleEcran.y*7/8)/2)+tailleEcran.y*7/8/8*(propositionDeplacement[i].y+1)){
                emplacementPions[propositionDeplacement[i].y][propositionDeplacement[i].x]=joueurQuiJoue+(joueurQuiJoue-1);
                emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x]=0;
                printf("Mise en case %d %d de la valeur %d \n",propositionDeplacement[i].x, propositionDeplacement[i].y, joueurQuiJoue+(joueurQuiJoue-1));
                printf("Mise en case %d %d de la valeur 0\n",positionDansEchiquier.x,positionDansEchiquier.y);
                Quitter=1;
            }
        }
    }
    return Quitter;
}

void SuppressionPropositionsDeplacement(SDL_Renderer* rendererWindow,struct coordonnees propositionDeplacement[3],int emplacementPions[8][8]){
    int i;
    for(i=0;i<3;i++){
        if(propositionDeplacement[i].x!=-1){
            affichageCaseCouleurEnFonctionPosition(rendererWindow,propositionDeplacement[i].x,propositionDeplacement[i].y);
            affichagePions(rendererWindow,emplacementPions,propositionDeplacement[i].x,propositionDeplacement[i].y);
        }
    }
    SDL_RenderPresent(rendererWindow);
}

void deplacementPion(SDL_Renderer* rendererWindow,int emplacementPions[8][8], struct coordonnees propositionDeplacement[3],struct coordonnees positionDansEchiquier, int joueurQuiJoue){
    int i;
    for(i=0;i<3;i++){
        affichagePions(rendererWindow,emplacementPions,propositionDeplacement[i].x,propositionDeplacement[i].y);
    }
    affichageCaseCouleurEnFonctionPosition(rendererWindow,positionDansEchiquier.x,positionDansEchiquier.y);
    affichagePions(rendererWindow,emplacementPions,positionDansEchiquier.x,positionDansEchiquier.y);
}

int verificationConditionFin (int* causeFin, int emplacementPions[8][8],int joueurQuiJoue){
    int Quitter=0;
    int i;

    if(*causeFin!=0){
        Quitter=1;
    }
    else{
        *causeFin=verificationCasEgalite(emplacementPions,joueurQuiJoue); // met 3 si égalité
    }


    for(i=0;i<8;i++){
        if(emplacementPions[0][i]==-1 || compterNbPions(emplacementPions,1)==0){
            *causeFin=-1;
            Quitter=1;
        }
        if(emplacementPions[7][i]==1 || compterNbPions(emplacementPions,-1)==0){
            *causeFin=1;
            Quitter=1;
        }
    }

    return Quitter;
}

void issuePartie(SDL_Renderer* rendererWindow,int causeFin){
    switch(causeFin){
        case -1:
            printf("\nJoueur blanc qui gagne\n");
            break;
        case 1:
            printf("\nJoueur noir qui gagne\n");
            break;
        case 2:
            printf("\nAppuie sur la croix fin du programme\n");
            break;
        case 3:
            printf("\Egalité entre les deux joueurs\n");
            break;
        case 4:
            printf("\nSauvegarder et retour menu principal\n");
            //FonctionSauvegarder
            menuPrincipal(rendererWindow);
            break;
        case 5:
            printf("\nRetour menu principal\n");
            menuPrincipal(rendererWindow);
            break;
    }
}

int verificationCasEgalite(int emplacementPions[8][8],int joueurQuiJoue){
    int causeFin=3;
    struct coordonnees propositionDeplacement[3],positionDansEchiquier;

    for(positionDansEchiquier.y=0;positionDansEchiquier.y<8;positionDansEchiquier.y++){
        for(positionDansEchiquier.x=0;positionDansEchiquier.x<8;positionDansEchiquier.x++){
            if(emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x]==joueurQuiJoue+(joueurQuiJoue-1)){
                    generationPropositionDeplacement(emplacementPions,positionDansEchiquier,propositionDeplacement,joueurQuiJoue);
                    if(verificationSiIlyaPossibilites(propositionDeplacement)){
                        causeFin=0;
                    }
            }
        }
    }
    printf("\n\n\n");
    return causeFin;
}




int menuSauvegarder(SDL_Renderer* rendererWindow,int emplacementPions[8][8], struct Pseudo Nom[2], int* causeFin){
    int Quitter;
    int action;

    SDL_Rect CaractBoutton[3];
    printf("Execution menuSauvegarder\n");
    remplirCaractTroisBouttons(rendererWindow, CaractBoutton);
    affichageMenuSauvegarder(rendererWindow,CaractBoutton);
    action=evenementMenuTroisBouttons(rendererWindow,CaractBoutton);
    Quitter=issueMenuSauvegarder(rendererWindow,emplacementPions,Nom, action, causeFin);
    return Quitter;
}

void affichageMenuSauvegarder(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton){

    mettreFondEcranUni(rendererWindow);

    Boutton(rendererWindow,CaractBoutton[0],"Sauv. et quitter");
    Boutton(rendererWindow,CaractBoutton[1],"Retour menu principal");
    Boutton(rendererWindow,CaractBoutton[2],"Retour");
    SDL_RenderPresent(rendererWindow);
}

int issueMenuSauvegarder(SDL_Renderer* rendererWindow,int emplacementPions[8][8], struct Pseudo Nom[2],int action,int* causeFin){
    int Quitter;
    switch(action){
    case 0:
        printf("Appuie sur echap, retour à l'échiquier\n");
        Quitter=0;
        affichagePartieEchiquier(rendererWindow,emplacementPions,Nom);
        SDL_RenderPresent(rendererWindow);
        break;
    case 1:
        printf("\nAppuie sur Sauvegarder et quitter\n");
        *causeFin=4;
        Quitter=1;
        break;
    case 2:
        printf("\nAppuie sur Retour au menu princ.\n");
        *causeFin=5;
        Quitter=1;
        break;
    case 3:
        printf("\nRetour\n");
        Quitter=0;
        affichagePartieEchiquier(rendererWindow,emplacementPions,Nom);
        SDL_RenderPresent(rendererWindow);
        break;
    }
    return Quitter;
}
