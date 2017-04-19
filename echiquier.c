#include "header/outils.h"
#include"header/menus.h"
#include "header/echiquier.h"
#include "header/jeuOrdinateur.h"


void lancementEchiquier(SDL_Renderer* rendererWindow,struct Pseudo Nom[2],int numeroPartieEnregistree){

    int emplacementPions[8][8];

    printf("Lancement Echiquier\n");
    initalisationEchiquier(emplacementPions,numeroPartieEnregistree);

    affichagePartieEchiquier(rendererWindow,emplacementPions,Nom);
    SDL_RenderPresent(rendererWindow);
    printf("\n\n");

    lancementPartie(rendererWindow,emplacementPions,Nom,numeroPartieEnregistree);

}


void initalisationEchiquier(int emplacementPions[8][8],int numeroPartieEnregistree){
    if(numeroPartieEnregistree==0){
        premierRemplissageTableauEchiquier(emplacementPions);
    }
    else{
        recuperationEchiquiersauvegarde(emplacementPions,numeroPartieEnregistree);
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

void recuperationEchiquiersauvegarde(int emplacementPions[8][8],int numeroPartieEnregistree){
    int i;
    int emplacement[64];
    FILE* fichierEmplacement=fopen("DAT/sauvegardeEmplacement.dat","rb");


    fseek(fichierEmplacement, sizeof(emplacement)*(numeroPartieEnregistree-1), SEEK_SET);
    fread(emplacement,sizeof(int),64,fichierEmplacement);

    for(i=0;i<64;i++){
        emplacementPions[i/8][i%8]=emplacement[i]   ;
        printf("%d |",emplacement[i]);
    }
    fclose(fichierEmplacement);
}


void affichagePartieEchiquier(SDL_Renderer* rendererWindow,int emplacementPions[8][8],struct Pseudo Nom[2]){
    mettreFondEcranUni(rendererWindow);
    affichageEchiquierEtPions(rendererWindow,emplacementPions);
    affichageCarreBlanc(rendererWindow);
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

void affichageCarreBlanc(SDL_Renderer* rendererWindow){
    struct coordonnees tailleFenetre;
    SDL_Rect caractCarre[2];

    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);
    caractCarre[0].x=((tailleFenetre.x-tailleFenetre.y*7/8)/2)/10;
    caractCarre[0].y=tailleFenetre.y/15*4;
    caractCarre[0].w=((tailleFenetre.x-tailleFenetre.y*7/8)/2)/10*8;
    caractCarre[0].h=tailleFenetre.y/9*4;

    caractCarre[1].x=tailleFenetre.x-((tailleFenetre.x-tailleFenetre.y*7/8)/2)+((tailleFenetre.x-tailleFenetre.y*7/8)/2)/10;
    caractCarre[1].y=tailleFenetre.y-tailleFenetre.y/15*2-tailleFenetre.y/9*4;
    caractCarre[1].w=((tailleFenetre.x-tailleFenetre.y*7/8)/2)/10*8;
    caractCarre[1].h=tailleFenetre.y/9*4;

    SDL_SetRenderDrawColor(rendererWindow,187, 174, 152,255);
    SDL_RenderFillRects(rendererWindow,caractCarre,2);
    SDL_SetRenderDrawColor(rendererWindow,1, 1, 1,255);
    SDL_RenderDrawRects(rendererWindow,caractCarre,2);


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
            affichageTexte(rendererWindow,"Ordinateur",30,caractTextePseudo[i],0,1);
        }
        else{
            affichageTexte(rendererWindow,Nom[i].Nom,30,caractTextePseudo[i],0,1);
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
        affichageTexte(rendererWindow,Nb,30,CaractTexte[i],1,1);
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



void lancementPartie(SDL_Renderer* rendererWindow,int emplacementPions[8][8],struct Pseudo Nom[2],int numeroPartieEnregistree){
    int i,Quitter=0,causeFin=0, dernierJoueurQuiAjoue;

    if(numeroPartieEnregistree!=0 && ajoutTourEventuelPourSauvegarde(numeroPartieEnregistree)==1){
        deroulementDuTour(rendererWindow,emplacementPions,Nom,1,&causeFin,&dernierJoueurQuiAjoue);
        Quitter=verificationConditionFin(&causeFin, emplacementPions,1);
    }

    while(!Quitter){
        for(i=0;i<2;i++){
            deroulementDuTour(rendererWindow,emplacementPions,Nom,i,&causeFin,&dernierJoueurQuiAjoue);
            Quitter=verificationConditionFin(&causeFin, emplacementPions,i);
        }
    }
    issuePartie(rendererWindow,causeFin,emplacementPions,Nom,dernierJoueurQuiAjoue);
}

void deroulementDuTour(SDL_Renderer* rendererWindow,int emplacementPions[8][8],struct Pseudo Nom[2],int joueurQuiJoue,int* causeFin,int* dernierJoueurQuiAjoue){

    if(*causeFin==0){
            if(strcmp(&Nom[joueurQuiJoue].Nom[0],"")==0){
                printf("Ordinateur qui joue\n");
                lancementIA(rendererWindow,emplacementPions,joueurQuiJoue,Nom);
            }
            else{
                printf("Joueur 'réel' qui joue\n");
                actionDuJoueur(rendererWindow,emplacementPions,joueurQuiJoue,causeFin,Nom);
                *dernierJoueurQuiAjoue=joueurQuiJoue;
            }
            affichageNombreDePions(rendererWindow,emplacementPions);
            SDL_RenderPresent(rendererWindow);
    }
}

void actionDuJoueur(SDL_Renderer* rendererWindow,int emplacementPions[8][8],int joueurQuiJoue,int* causeFin,struct Pseudo Nom[2]){
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

void issuePartie(SDL_Renderer* rendererWindow,int causeFin,int emplacementPions[8][8],struct Pseudo Nom[2],int dernierJoueurQuiAjoue){ //Ajouter beaucoup de paramètres
    switch(causeFin){
        case -1:
            printf("\nJoueur blanc qui gagne\n");
            ajouterVictoireDefaiteAStatistiques(Nom,0,1);
            menuFinDePartie(rendererWindow,"blanc");
            break;
        case 1:
            printf("\nJoueur noir qui gagne\n");
            ajouterVictoireDefaiteAStatistiques(Nom,1,0);
            menuFinDePartie(rendererWindow,"noir");
            break;
        case 2:
            printf("\nAppuie sur la croix fin du programme\n");
            break;
        case 3:
            printf("\Egalité entre les deux joueurs\n");
            break;
        case 4:
            printf("\nSauvegarder et retour menu principal\n");
            sauvegardePartie(emplacementPions,Nom,dernierJoueurQuiAjoue);
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



void sauvegardePartie(int emplacementPions[8][8], struct Pseudo Nom[2], int JoueurQuiJoue){
    int i, emplacement[64];
    FILE* fichierNom=fopen("DAT/sauvegardeNom.dat","ab");
    FILE* fichierEmplacement=fopen("DAT/sauvegardeEmplacement.dat","ab");
    FILE* fichierTour=fopen("DAT/sauvegardeTour.dat","ab");

    for(i=0;i<64;i++){
        emplacement[i]=emplacementPions[i/8][i%8];
    }

    fwrite(Nom,sizeof(struct Pseudo),2,fichierNom);
    fwrite(emplacement,sizeof(int),64,fichierEmplacement);
    fwrite(&JoueurQuiJoue,sizeof(int),1,fichierTour);

    fclose(fichierNom);
    fclose(fichierEmplacement);
    fclose(fichierTour);
}

int ajoutTourEventuelPourSauvegarde(int numeroPartieEnregistree){
    int TourSuplementaire;
    FILE* fichierTour=fopen("DAT/sauvegardeTour.dat","rb");

    fseek(fichierTour, sizeof(int)*(numeroPartieEnregistree-1), SEEK_SET);
    fread(&TourSuplementaire,sizeof(int),1,fichierTour);

    fclose(fichierTour);

    return TourSuplementaire;
}


void ajouterVictoireDefaiteAStatistiques(struct Pseudo Nom[2], int joueurGagnant, int joueurPerdant){
    FILE* fichierStats=fopen("DAT/stat.dat","rb");
    struct Statistiques stats[50]={0};

    if(fichierStats!=NULL){

        fread(stats,sizeof(struct Statistiques),50,fichierStats);
        fclose(fichierStats);
    }
    fichierStats=fopen("DAT/stat.dat","wb+");
    mettreNomEtVictoireDansTableau(stats,joueurGagnant,joueurPerdant,Nom);
    fwrite(stats,sizeof(struct Statistiques),50,fichierStats);
    fclose(fichierStats);
}

void mettreNomEtVictoireDansTableau(struct Statistiques stats[50], int joueurGagnant,int joueurPerdant,struct Pseudo Nom[2]){
    int i,Quitter,j=0,correspondance[2]={0,0};

    for(i=0;i<50;i++){
        if(strcmp(Nom[joueurGagnant].Nom,"")!=0 && strcmp(stats[i].Pseudo,Nom[joueurGagnant].Nom)==0){
            stats[i].NombreVictoireDefaite[0]=stats[i].NombreVictoireDefaite[0]+1;
            printf("Ajout 1 victoire a %s. Mtn %d victoire(s)\n",stats[i].Pseudo,stats[i].NombreVictoireDefaite[0]);
            correspondance[joueurGagnant]=1;
        }
        if(strcmp(Nom[joueurPerdant].Nom,"")!=0 && strcmp(stats[i].Pseudo,Nom[joueurPerdant].Nom)==0){
            stats[i].NombreVictoireDefaite[1]=stats[i].NombreVictoireDefaite[1]+1;
            printf("Ajout 1 défaite a %s. Mtn %d perdu(s)\n",stats[i].Pseudo,stats[i].NombreVictoireDefaite[1]);
            correspondance[joueurPerdant]=1;
        }
    }

    for(i=0;i<2;i++){
        if(correspondance[i]==0){
            Quitter=0;
            j=0;
            while(!Quitter && j<50){
                if(strcmp(stats[j].Pseudo,"")==0 && strcmp(Nom[i].Nom,"")!=0){
                    strcpy(stats[j].Pseudo,Nom[i].Nom);
                    if(i==joueurGagnant){
                        stats[j].NombreVictoireDefaite[0]=1;
                        stats[j].NombreVictoireDefaite[1]=0;
                    }
                    else{
                        stats[j].NombreVictoireDefaite[0]=0;
                        stats[j].NombreVictoireDefaite[1]=1;

                    }
                    printf("Ajout %s avec %d et %d win/loose\n",stats[j].Pseudo,stats[j].NombreVictoireDefaite[0],stats[j].NombreVictoireDefaite[1]);
                    Quitter=1;
                }
                j++;
            }
        }
    }
}

void menuFinDePartie(SDL_Renderer* rendererWindow,char* couleurGagnante){
    SDL_Rect caractObjet[3];
    int action=0;
    remplirCaractMenuFinDePartie(rendererWindow, caractObjet);
    affichageMenuFinDePartie(rendererWindow, caractObjet,couleurGagnante);
    action=actionMenuFinDePartie(caractObjet);
    issueMenuFinDePartie(rendererWindow,action);
}

void remplirCaractMenuFinDePartie(SDL_Renderer* rendererWindow, SDL_Rect* caractObjet){
    struct coordonnees tailleFenetre;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);

    caractObjet[0].x=tailleFenetre.x/2;
    caractObjet[0].y=tailleFenetre.y/12*3;

    caractObjet[1].x=tailleFenetre.x/4;
    caractObjet[1].y=tailleFenetre.y/12*6;
    caractObjet[1].w=tailleFenetre.x/2;
    caractObjet[1].h=(tailleFenetre.y/12)*2;

    caractObjet[2].x=tailleFenetre.x/4;
    caractObjet[2].y=tailleFenetre.y/12*9;
    caractObjet[2].w=tailleFenetre.x/2;
    caractObjet[2].h=tailleFenetre.y/12*2;

}

void affichageMenuFinDePartie(SDL_Renderer* rendererWindow,SDL_Rect* caractObjet,char* couleurGagnante){
    char Texte[25];

    sprintf(Texte,"Joueur %s gagnant !",couleurGagnante);

    mettreFondEcranUni(rendererWindow);

    if(strcmp(couleurGagnante,"blanc")==0){
        affichageTexte(rendererWindow,Texte,70,caractObjet[0],0,0);
    }
    else{
        affichageTexte(rendererWindow,Texte,70,caractObjet[0],0,1);
    }
    Boutton(rendererWindow,caractObjet[1],"Rejouer");
    Boutton(rendererWindow,caractObjet[2],"Menu principal");
    SDL_RenderPresent(rendererWindow);
}

int actionMenuFinDePartie(SDL_Rect* caractObjet){
    int action,i,Quitter=0;
    struct coordonnees positionSouris;
    SDL_Event event;
    Uint32 Timer;

    while(!Quitter){
        Timer=SDL_GetTicks();
        if(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_MOUSEBUTTONUP:
                        SDL_GetMouseState(&positionSouris.x,&positionSouris.y);
                        for(i=1;i<3;i++){
                            if(positionSouris.x>caractObjet[i].x && positionSouris.x<caractObjet[i].x+caractObjet[i].w && positionSouris.y>caractObjet[i].y && positionSouris.y<caractObjet[i].y+caractObjet[i].h){
                                Quitter=1;
                                action=i;
                            }
                        }
                    break;

                    default:
                        Quitter=QuitterAppuieCroixOuEchap(event);
                        action=0;
                    break;
                }
        }
        PauseEnfonctionDureeExecution(Timer);
    }

    return action;
}

void issueMenuFinDePartie(SDL_Renderer* rendererWindow,int action){
    switch(action){
    case 0:
        printf("Fin du programme\n");
        break;
    case 1:
        printf("Appuie sur boutton Rejouer\n");
        menuNombredeJoueur(rendererWindow);
        break;
    case 2:
        printf("Appuie sur boutton MenuPrincipal\n");
        menuPrincipal(rendererWindow);
        break;

    }
}
