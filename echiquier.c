#include "header/lib.h"
#include "header/outils.h"
#include"header/menus.h"
#include "header/echiquier.h"
#include "header/jeuOrdinateur.h"


void lancementEchiquier(SDL_Renderer* rendererWindow,struct Pseudo Nom[2],int numeroPartieEnregistree){ // Lancement de l'échiquier

    struct echiquier emplacementPions[8][8];

    printf("Lancement Echiquier\n");
    initalisationEchiquier(emplacementPions,numeroPartieEnregistree);

    affichagePartieEchiquier(rendererWindow,emplacementPions,Nom,0);
    SDL_RenderPresent(rendererWindow);
    printf("\n\n");

    lancementPartie(rendererWindow,emplacementPions,Nom,numeroPartieEnregistree);

}


void initalisationEchiquier(struct echiquier emplacementPions[8][8],int numeroPartieEnregistree){ // On init le tableau où il y a les pions
    if(numeroPartieEnregistree==0){ // Si on commence une nouvelle partie
        premierRemplissageTableauEchiquier(emplacementPions);
        remplirPossibiliteAvancerDeDeux(emplacementPions);
    }
    else{ // sinon on reprend partie
        recuperationEchiquiersauvegarde(emplacementPions,numeroPartieEnregistree);
    }
}

void premierRemplissageTableauEchiquier(struct echiquier emplacementPions[8][8]){ // premier remplissage du tableau
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(i<2){
                emplacementPions[i][j].emplacementPions=1;
                printf(" 1|");
            }
            else if(i>5){
                emplacementPions[i][j].emplacementPions=-1;
                printf("-1|");
            }
            else{
                emplacementPions[i][j].emplacementPions=0;
                printf(" 0|");
            }
        }
        printf("\n");
    }
    printf("Echiquier rempli\n");
}

void remplirPossibiliteAvancerDeDeux(struct echiquier emplacementPions[8][8]){ // on rempli pour une nouvelle partie le tableau qui sert à voir si l'on peut déplacer le pion de deux cases en avant
    int i,j;

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
             if(i==1 || i==6){
                emplacementPions[i][j].possibiliteAvancerDeDeux=1;
            }
            else{
                emplacementPions[i][j].possibiliteAvancerDeDeux=0;
            }
        }
    }
}

void recuperationEchiquiersauvegarde(struct echiquier emplacementPions[8][8],int numeroPartieEnregistree){ //recupération du tableau dans le fichier sauvegardeEmplacement.dat
    FILE* fichierEmplacement=fopen("DAT/sauvegardeEmplacement.dat","rb"); //ouverture en lecture binaire
    FILE* fichierAvancementDeDeux=fopen("DAT/sauvegardeAvancementDeDeux.dat","rb");
    int i, emplacement[64],avancementDeDeux[64];

    fseek(fichierAvancementDeDeux, sizeof(avancementDeDeux)*(numeroPartieEnregistree-1), SEEK_SET);
    fseek(fichierEmplacement, sizeof(emplacement)*(numeroPartieEnregistree-1), SEEK_SET); // on met le curseur à l'enplacement la partie select
    fread(emplacement,sizeof(int),64,fichierEmplacement); // On passe par un tableau simple car on avait problème avec tableau à double entrée
    fread(avancementDeDeux,sizeof(int),64,fichierAvancementDeDeux); //idem

    for(i=0;i<64;i++){ // On repasse à un tableau à double entrée 8/8
        emplacementPions[i/8][i%8].emplacementPions=emplacement[i];
        emplacementPions[i/8][i%8].possibiliteAvancerDeDeux=avancementDeDeux[i];
    }
    fclose(fichierAvancementDeDeux);
    fclose(fichierEmplacement);
}

    /** AFFICHAGE **/

void affichagePartieEchiquier(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],struct Pseudo Nom[2],int joueurQuiJoue){ //affichage de tout l'écran lors de la partie d'echiquier
    struct coordonnees tailleFenetre;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);
    SDL_Rect positionTexte={tailleFenetre.x/2, tailleFenetre.y/40,0,0};

    mettreFondEcranUni(rendererWindow);
    affichageTexte(rendererWindow,"Appuyez sur Echap pour sauvegarder ou quitter.",30,positionTexte,0,1);
    affichageEchiquierEtPions(rendererWindow,emplacementPions);
    affichagePseudoEtNbPions(rendererWindow,emplacementPions,Nom,joueurQuiJoue);
}

void affichagePseudoEtNbPions(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],struct Pseudo Nom[2],int joueurQuiJoue){ // On affiche les carrés sur les cotés ou il y a l'avatar, le nom et le nombre de pions
    SDL_Rect caractAvatar[2];

    remplirCaractAvatar(rendererWindow, caractAvatar);
    affichageCarreBlanc(rendererWindow);
    affichageAvatarEnJeu(rendererWindow,Nom,caractAvatar);
    affichagePseudo(rendererWindow,Nom);
    affichageNombreDePions(rendererWindow,emplacementPions);
    entourerAvatarEnFonctionTour(rendererWindow,caractAvatar,joueurQuiJoue);
}

void affichageEchiquierEtPions(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8]){ //affichage de l'échiquier
    int i,j;

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            affichageCaseCouleurEnFonctionPosition(rendererWindow,j,i);
            affichagePions(rendererWindow,emplacementPions,j,i);
        }
    }
}

void affichageCaseCouleurEnFonctionPosition(SDL_Renderer* rendererWindow,int x,int y){ // en fonction de la coordonnée en paramètre on affiche la couleur de la case
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

void affichagePions(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],int x,int y){ // On affiche le pion en fonction de la valeur dans le tableau emplacementPions en x y
    struct coordonnees tailleFenetre;
    SDL_Rect CaractCase;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);
    CaractCase.w=CaractCase.h=tailleFenetre.y*7/64;
    CaractCase.y=((tailleFenetre.y-tailleFenetre.y*7/8)/2)+CaractCase.h*y;
    CaractCase.x=((tailleFenetre.x-tailleFenetre.y*7/8)/2)+CaractCase.h*x;

    if(emplacementPions[y][x].emplacementPions==-1){
        affichageImagePNG(rendererWindow,CaractCase,"DAT/Image/pionBlanc.png");
    }
    else if(emplacementPions[y][x].emplacementPions==1){
        affichageImagePNG(rendererWindow,CaractCase,"DAT/Image/pionNoir.png");
    }
}

void remplirCaractAvatar(SDL_Renderer* rendererWindow, SDL_Rect* caractAvatar){ // On rempli le sdl rect qui contient l'emplacement des deux avatars
    struct coordonnees tailleFenetre;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);

    caractAvatar[0].w=caractAvatar[0].h=caractAvatar[1].w=caractAvatar[1].h=tailleFenetre.x/10;

    caractAvatar[1].x=( ((tailleFenetre.x-tailleFenetre.y*7/8)/2)/10*8 - caractAvatar[0].w )/2 + ((tailleFenetre.x-tailleFenetre.y*7/8)/2)/10;
    caractAvatar[0].x= tailleFenetre.x - caractAvatar[1].x - caractAvatar[1].w;
    caractAvatar[0].y=tailleFenetre.y/9*4;
    caractAvatar[1].y=tailleFenetre.y/9*5;
}

void affichageCarreBlanc(SDL_Renderer* rendererWindow){ // On affiche le carré qui est arrière plan
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

void affichageAvatarEnJeu(SDL_Renderer* rendererWindow,struct Pseudo Nom[2],SDL_Rect* caractAvatar){ // On affiche les avatars
    int i;

    for(i=0;i<2;i++){

        if(strcmp(Nom[i].Nom,"")==0){ // si le nom d'un joueur est nul alors c'est un ordi donc on met l'avatar en conséquence
            affichageImagePNG(rendererWindow,caractAvatar[i],"DAT/Image/avatar/ordi.png");
        }
        else{ // si c'est un joueur réel alors on met son avatar qu'il a choisit
            affichageImagePNG(rendererWindow,caractAvatar[i],Nom[i].avatar);
        }
    }
}

void affichagePseudo(SDL_Renderer*rendererWindow,struct Pseudo Nom[2]){ // on affiche le pseudo
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
        if(strcmp(Nom[i].Nom,"")==0){ // si le pseudo est null alors c'est un ordi
            affichageTexte(rendererWindow,"Ordinateur",30,caractTextePseudo[i],0,1);
        }
        else{
            affichageTexte(rendererWindow,Nom[i].Nom,30,caractTextePseudo[i],0,1);
        }
    }
}

void affichageNombreDePions(SDL_Renderer*rendererWindow,struct echiquier emplacementPions[8][8]){ //affichage du nombre de pions d'un joueur
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

void entourerAvatarEnFonctionTour(SDL_Renderer* rendererWindow, SDL_Rect* caractAvatar, int joueurQuiJoue){ // On entoure en rouge l'avatar du joueur qui joue

    SDL_SetRenderDrawColor(rendererWindow,255, 0,0,255);
    SDL_RenderDrawRect(rendererWindow,&caractAvatar[joueurQuiJoue]);
}


int compterNbPions(struct echiquier emplacementPions[8][8],int Couleur){ //compte le nombre de pions pour le joueur mis en paramètre et le renvoie
    int NombreDePions=0,i,j;

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(emplacementPions[i][j].emplacementPions==Couleur){
                NombreDePions++;
            }
        }
    }
    return NombreDePions;
}


/** DEROULEMENT DE LA PARTIE **/
void lancementPartie(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],struct Pseudo Nom[2],int numeroPartieEnregistree){ // lance la partie
    int i,Quitter=0,causeFin=0, dernierJoueurQuiAjoue;

    if(numeroPartieEnregistree!=0 && ajoutTourEventuelPourSauvegarde(numeroPartieEnregistree)==1){ // si il y a reprise d'une partie sauvegardée et que c'était lors du deuxième tour que l'on avait sauvegardé
        deroulementDuTour(rendererWindow,emplacementPions,Nom,1,&causeFin,&dernierJoueurQuiAjoue);
        Quitter=verificationConditionFin(&causeFin, emplacementPions,1);
    }

    while(!Quitter){ // tant qu'il n'y a pas d'ordre de quitter on fait joueur 0 qui joue puis le 1,puis 0 puis 1 ....
        for(i=0;i<2;i++){
            deroulementDuTour(rendererWindow,emplacementPions,Nom,i,&causeFin,&dernierJoueurQuiAjoue);
            Quitter=verificationConditionFin(&causeFin, emplacementPions,i);
        }
    }
    issuePartie(rendererWindow,causeFin,emplacementPions,Nom,dernierJoueurQuiAjoue);
}

void deroulementDuTour(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],struct Pseudo Nom[2],int joueurQuiJoue,int* causeFin,int* dernierJoueurQuiAjoue){ // on sépare ici les tours ordi et les tours humains

    if(*causeFin==0){ // si il n'y aucune cause qui oblige la partie à se finir alors
            affichagePseudoEtNbPions(rendererWindow,emplacementPions,Nom,joueurQuiJoue); // on actualise
            SDL_RenderPresent(rendererWindow);

            if(strcmp(Nom[joueurQuiJoue].Nom,"")==0){ // si c'est un ordi
                printf("Ordinateur qui joue\n");
                lancementIA(rendererWindow,emplacementPions,joueurQuiJoue,Nom); // on lance """"""""" l'ia """""""""
            }
            else{
                printf("Joueur 'réel' qui joue\n");
                actionDuJoueur(rendererWindow,emplacementPions,joueurQuiJoue,causeFin,Nom); // on lance la suite d'event pour le tour d'un joueur
                *dernierJoueurQuiAjoue=joueurQuiJoue;
            }
    }
}

void actionDuJoueur(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],int joueurQuiJoue,int* causeFin,struct Pseudo Nom[2]){ // On attend qu'il clique sur l'une des cases de l'échiquier
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
                    if ( event.key.keysym.sym == SDLK_ESCAPE ){ // si appuie sur echap
                        Quitter=menuSauvegarder(rendererWindow,emplacementPions,Nom, causeFin,joueurQuiJoue);
                    }
                    break;
            }
        }
        PauseEnfonctionDureeExecution(Timer);
    }
}

int actionPremierCLique(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],int joueurQuiJoue,int* causeFin){ // si on a appuie sur la souris
    int Quitter=0;
    struct coordonnees propositionDeplacement[4]={{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
    struct coordonnees positionDansEchiquier=detectionEmplacementDuCliqueDansEchiquier(rendererWindow);

    if(emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions==joueurQuiJoue+(joueurQuiJoue-1)){ //0=>-1 et 1=>1     ///Si on a appuié sur l'un de nos pions
        generationPropositionDeplacement(emplacementPions,positionDansEchiquier,propositionDeplacement,joueurQuiJoue); //On génére les propositions
        printf("%d %d\n",propositionDeplacement[0].x,propositionDeplacement[0].y);
        printf("%d %d\n",propositionDeplacement[1].x,propositionDeplacement[1].y);
        printf("%d %d\n",propositionDeplacement[2].x,propositionDeplacement[2].y);
        printf("%d %d\n",propositionDeplacement[2].x,propositionDeplacement[2].y);

        if(verificationSiIlyaPossibilites(propositionDeplacement)){ // Il il y a des possiblités alors :
        affichagePropositionDeplacement(rendererWindow,propositionDeplacement);
        Quitter=actionsDeplacement(rendererWindow,emplacementPions,propositionDeplacement,positionDansEchiquier,joueurQuiJoue,causeFin);
        SuppressionPropositionsDeplacement(rendererWindow,propositionDeplacement,emplacementPions);
        }
        if(Quitter==1){ //si on veut quitter alors :
            deplacementPion(rendererWindow,emplacementPions,propositionDeplacement,positionDansEchiquier,joueurQuiJoue);
            SDL_RenderPresent(rendererWindow);
        }
    }
    return Quitter;
}

struct coordonnees detectionEmplacementDuCliqueDansEchiquier(SDL_Renderer* rendererWindow){ // On regarde si le clique était dans l'échiquier si oui alors on met en struct le x y de la case cliquée
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

void generationPropositionDeplacement(struct echiquier emplacementPions[8][8],struct coordonnees positionDansEchiquier, struct coordonnees propositionDeplacement[4],int joueurQuiJoue){ // On met dans propositionDeplacement les déplacements possibles
    int i;
    for(i=-1;i<2;i=i+2){ // On va remplir les conditions pour les déplacements latéraux si il y a un pion adverse
        if(positionDansEchiquier.x+i>=0 && positionDansEchiquier.x+i<8 && positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions>=0 && positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions<8){
            if(emplacementPions[positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions][positionDansEchiquier.x+i].emplacementPions!=0 && emplacementPions[positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions][positionDansEchiquier.x+i].emplacementPions!=joueurQuiJoue+(joueurQuiJoue-1)){
                propositionDeplacement[1+i].x=positionDansEchiquier.x+i;
                propositionDeplacement[1+i].y=positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions;
            }
        }
    } // On rempli le mouvement avant si il n'y a pas de pions adverse
    if(positionDansEchiquier.x>=0 && positionDansEchiquier.x<8 && positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions>=0 && positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions<8){
        if(emplacementPions[positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions][positionDansEchiquier.x].emplacementPions==0){
            propositionDeplacement[1].x=positionDansEchiquier.x;
            propositionDeplacement[1].y=positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions;
        }
    }
    if(positionDansEchiquier.x>=0 && positionDansEchiquier.x<8 && positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions>=0 && positionDansEchiquier.y+emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions<8){
        if(emplacementPions[positionDansEchiquier.y+2*emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions][positionDansEchiquier.x].emplacementPions==0 && emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].possibiliteAvancerDeDeux==1 ){
            propositionDeplacement[3].x=positionDansEchiquier.x;
            propositionDeplacement[3].y=positionDansEchiquier.y+2*emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions;
        }
    }
}

void affichagePropositionDeplacement(SDL_Renderer* rendererWindow,struct coordonnees propositionDeplacement[4]){ // on affiche une petite image montrant les déplacements possibles

    int i;
    struct coordonnees tailleFenetre;
    SDL_Rect positionProposition;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);
    positionProposition.h=positionProposition.w=tailleFenetre.y*7/8/8;

    printf("Affichage de :\n");
    for(i=0;i<4;i++){
        if(propositionDeplacement[i].x!=-1){
            positionProposition.x=((tailleFenetre.x-tailleFenetre.y*7/8)/2)+positionProposition.w*propositionDeplacement[i].x;
            positionProposition.y=((tailleFenetre.y-tailleFenetre.y*7/8)/2)+positionProposition.h*propositionDeplacement[i].y;
            affichageImagePNG(rendererWindow,positionProposition,"DAT/Image/proposition.png");
        }
    }
    SDL_RenderPresent(rendererWindow);

}

int verificationSiIlyaPossibilites(struct coordonnees propositionDeplacement[4]){ // fonction qui vérifie si des déplacements sont possibles, renvoie 0 si il n'y en a pas
    int i,possibiliteExistante=0;

    for(i=0;i<4;i++){
            if(propositionDeplacement[i].x!=-1){
                possibiliteExistante=1;
            }
    }

    return possibiliteExistante;
}

int actionsDeplacement(SDL_Renderer* rendererWindow, struct echiquier emplacementPions[8][8],struct coordonnees propositionDeplacement[4],struct coordonnees positionDansEchiquier,int joueurQuiJoue, int* causeFin){ //event quand on a clique une première fois sur un pion et qu'il y a les propositions affichées
    SDL_Event event;
    int Quitter=0,Quitter1=0;
    Uint32 Timer;

    while(!Quitter1){
        Timer=SDL_GetTicks();
        if(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEBUTTONUP:
                    Quitter=evenementCliqueDemandeProposition(rendererWindow, emplacementPions,propositionDeplacement,positionDansEchiquier,joueurQuiJoue);
                    Quitter1=1; // si on a fait un clique on quite forcement cette boucle et on passe peu être au tour de l'autre joueur si Quitter=1
                    break;

                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_CLOSE){
                        Quitter1=1; // Si on appuie sur croix ON ARRETE TOUT !
                        Quitter=1;
                        *causeFin=2;
                    }
                    break;
                case SDL_KEYUP:
                    if(event.key.keysym.sym == SDLK_ESCAPE){ // si on appuie sur echap alors on quitte seulement cette boucle donc on doit reselec un pion
                        Quitter1=1;
                    }
                    break;
            }
        }
    PauseEnfonctionDureeExecution(Timer);
    }
    return Quitter;
}

int evenementCliqueDemandeProposition(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],struct coordonnees propositionDeplacement[4],struct coordonnees positionDansEchiquier,int joueurQuiJoue){ // On vérifie si durant la deuxième vague d'attente de clique, le joueur a cliqué sur une des propositions
    int i,Quitter=0;
    struct coordonnees positionCurseur,tailleEcran;
    SDL_GetRendererOutputSize(rendererWindow,&tailleEcran.x,&tailleEcran.y);
    SDL_GetMouseState(&positionCurseur.x,&positionCurseur.y);

    for(i=0;i<4;i++){
        if(positionCurseur.x>((tailleEcran.x-tailleEcran.y*7/8)/2)+tailleEcran.y*7/8/8*propositionDeplacement[i].x && positionCurseur.x<((tailleEcran.x-tailleEcran.y*7/8)/2)+tailleEcran.y*7/8/8*(propositionDeplacement[i].x+1)){
            if(positionCurseur.y>((tailleEcran.y-tailleEcran.y*7/8)/2)+tailleEcran.y*7/8/8*propositionDeplacement[i].y && positionCurseur.y<((tailleEcran.y-tailleEcran.y*7/8)/2)+tailleEcran.y*7/8/8*(propositionDeplacement[i].y+1)){
                emplacementPions[propositionDeplacement[i].y][propositionDeplacement[i].x].emplacementPions=joueurQuiJoue+(joueurQuiJoue-1);
                emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions=0;
                printf("Mise en case %d %d de la valeur %d \n",propositionDeplacement[i].x, propositionDeplacement[i].y, joueurQuiJoue+(joueurQuiJoue-1));
                printf("Mise en case %d %d de la valeur 0\n",positionDansEchiquier.x,positionDansEchiquier.y);
                Quitter=1; // Si le joueur à cliquer sur l'une des proposiitons alors on modifie le tableau avec les pions et on quitte les deux boucles pour aller au tour suivant
                emplacementPions[propositionDeplacement[i].y][propositionDeplacement[i].x].possibiliteAvancerDeDeux=0; // si on  mange un pion qui était sur la deuxième case sans avoir encore bouger, supprime la possibilité de déplacement de deux cases
                if(i==3){
                    emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].possibiliteAvancerDeDeux=0; //si on a bouger un pion qui était sur la deuxième ligne on met la possibilité de bouger deux cases à 0
                }
            }
        }
    }
    return Quitter;
}

void SuppressionPropositionsDeplacement(SDL_Renderer* rendererWindow,struct coordonnees propositionDeplacement[4],struct echiquier emplacementPions[8][8]){ // On réactualise les cases où l'on avait affiché les propositions pour supprimier les images que l'on avait mises
    int i;
    for(i=0;i<4;i++){
        if(propositionDeplacement[i].x!=-1){
            affichageCaseCouleurEnFonctionPosition(rendererWindow,propositionDeplacement[i].x,propositionDeplacement[i].y);
            affichagePions(rendererWindow,emplacementPions,propositionDeplacement[i].x,propositionDeplacement[i].y);
        }
    }
    SDL_RenderPresent(rendererWindow);
}

void deplacementPion(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8], struct coordonnees propositionDeplacement[4],struct coordonnees positionDansEchiquier, int joueurQuiJoue){ //mise à jour de l'emplacement des pions
    int i;
    for(i=0;i<4;i++){
        affichagePions(rendererWindow,emplacementPions,propositionDeplacement[i].x,propositionDeplacement[i].y);
    }
    affichageCaseCouleurEnFonctionPosition(rendererWindow,positionDansEchiquier.x,positionDansEchiquier.y);
    affichagePions(rendererWindow,emplacementPions,positionDansEchiquier.x,positionDansEchiquier.y);
}

int verificationConditionFin (int* causeFin, struct echiquier emplacementPions[8][8],int joueurQuiJoue){ //vérification si l'une des conditions de fin est remplie
    int Quitter=0;

    if(*causeFin!=0){ // si la condition de fin est déjà !=0 alors on quitte la boucle joueur 0/1/0/1/0/.....
        Quitter=1;
    }
    else{
        *causeFin=verificationCasEgalite(emplacementPions,0); // On vérifie si il y a égalité pour le joueur 0 si oui on met 3
        if(*causeFin==0){
            *causeFin=verificationCasEgalite(emplacementPions,1); // on vérifie si il y a égalité pour le joueur 1 si oui on met 3
        }
        printf("\n\n");
    }
    verificationSiJoueurGagnant(emplacementPions,causeFin,&Quitter); // vérification si l'un des joueurs a atteind le bord du dammier


    return Quitter;
}

void verificationSiJoueurGagnant(struct echiquier emplacementPions[8][8],int* causeFin,int* Quitter){ // vérification si l'un des joueurs a atteind le bord du dammier
    int i;

    for(i=0;i<8;i++){
        if(emplacementPions[0][i].emplacementPions==-1 || compterNbPions(emplacementPions,1)==0){ // On verifie la ligne du haut
            *causeFin=-1;
            *Quitter=1;
        }
        if(emplacementPions[7][i].emplacementPions==1 || compterNbPions(emplacementPions,-1)==0){ // et la ligne du bas
            *causeFin=1;
            *Quitter=1;
        }
    }
}

void issuePartie(SDL_Renderer* rendererWindow,int causeFin,struct echiquier emplacementPions[8][8],struct Pseudo Nom[2],int dernierJoueurQuiAjoue){ // issue en fonction de causefin
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
            menuFinDePartie(rendererWindow,"");
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

int verificationCasEgalite(struct echiquier emplacementPions[8][8],int joueurQuiJoue){ // on vérifie les cas d'égalitéq
    int causeFin=3;
    struct coordonnees propositionDeplacement[4]={{-1,-1},{-1,-1},{-1,-1},{-1,-1}},positionDansEchiquier;

    for(positionDansEchiquier.y=0;positionDansEchiquier.y<8;positionDansEchiquier.y++){
        for(positionDansEchiquier.x=0;positionDansEchiquier.x<8;positionDansEchiquier.x++){ // pour toutes les cases du dammier
            if(emplacementPions[positionDansEchiquier.y][positionDansEchiquier.x].emplacementPions==joueurQuiJoue+(joueurQuiJoue-1)){ // si c'est le pion d'un des joueurs
                    generationPropositionDeplacement(emplacementPions,positionDansEchiquier,propositionDeplacement,joueurQuiJoue); // On génére les propositions de déplacement
                    if(verificationSiIlyaPossibilites(propositionDeplacement)){ // si il a une possibilité
                        causeFin=0; // pas de cause de fin !
                    }
            }
        }
    }
    printf("Verification égalité %d\n",causeFin);
    return causeFin;
}


/** SAUVEGARDE **/

int menuSauvegarder(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8], struct Pseudo Nom[2], int* causeFin,int joueurQuiJoue){ // menu sauvegarder  affichage puis actions
    int Quitter;
    int action;

    SDL_Rect CaractBoutton[3];
    printf("Execution menuSauvegarder\n");
    remplirCaractTroisBouttons(rendererWindow, CaractBoutton);
    affichageMenuSauvegarder(rendererWindow,CaractBoutton);
    action=evenementMenuTroisBouttons(rendererWindow,CaractBoutton);
    Quitter=issueMenuSauvegarder(rendererWindow,emplacementPions,Nom, action, causeFin,joueurQuiJoue);

    return Quitter;
}

void affichageMenuSauvegarder(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton){ //affichage du menu sauvegarder

    mettreFondEcranUni(rendererWindow);

    Boutton(rendererWindow,CaractBoutton[0],"Sauv. et quitter");
    Boutton(rendererWindow,CaractBoutton[1],"Retour menu principal");
    Boutton(rendererWindow,CaractBoutton[2],"Retour");
    SDL_RenderPresent(rendererWindow);
}

int issueMenuSauvegarder(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8], struct Pseudo Nom[2],int action,int* causeFin,int joueurQuiJoue){ // issue du menu sauvegarder
    int Quitter;
    switch(action){
    case 0:
        printf("Appuie sur echap, retour à l'échiquier\n");
        Quitter=0;
        affichagePartieEchiquier(rendererWindow,emplacementPions,Nom,joueurQuiJoue);
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
        affichagePartieEchiquier(rendererWindow,emplacementPions,Nom,joueurQuiJoue);
        SDL_RenderPresent(rendererWindow);
        break;
    }
    return Quitter;
}


void sauvegardePartie(struct echiquier emplacementPions[8][8], struct Pseudo Nom[2], int JoueurQuiJoue){ // on sauvegarde la partie dans un fichier
    int i, emplacement[64],possibiliteDeux[64];
    FILE* fichierNom=fopen("DAT/sauvegardeNom.dat","ab");
    FILE* fichierEmplacement=fopen("DAT/sauvegardeEmplacement.dat","ab"); // ouvertures en ajout
    FILE* fichierAvancementDeDeux=fopen("DAT/sauvegardeAvancementDeDeux.dat","ab");
    FILE* fichierTour=fopen("DAT/sauvegardeTour.dat","ab"); // que des ouvertures en binaire !!!!!!!

    for(i=0;i<64;i++){
        emplacement[i]=emplacementPions[i/8][i%8].emplacementPions;
        possibiliteDeux[i]=emplacementPions[i/8][i%8].possibiliteAvancerDeDeux;
    }

    fwrite(Nom,sizeof(struct Pseudo),2,fichierNom);
    fwrite(emplacement,sizeof(int),64,fichierEmplacement);
    fwrite(possibiliteDeux,sizeof(int),64,fichierAvancementDeDeux);
    fwrite(&JoueurQuiJoue,sizeof(int),1,fichierTour); // On écrit dans les 3 fichiers et on les ferme

    fclose(fichierNom);
    fclose(fichierEmplacement);
    fclose(fichierAvancementDeDeux);
    fclose(fichierTour);
}

int ajoutTourEventuelPourSauvegarde(int numeroPartieEnregistree){ // renvoie 1 pour le numéro de la partie envoyée dans le fichier sauvegardeTour il y a 1
    int TourSuplementaire;
    FILE* fichierTour=fopen("DAT/sauvegardeTour.dat","rb");

    fseek(fichierTour, sizeof(int)*(numeroPartieEnregistree-1), SEEK_SET);
    fread(&TourSuplementaire,sizeof(int),1,fichierTour);

    fclose(fichierTour);

    return TourSuplementaire;
}


    /** GESTION DE LA FIN DE PARTIE **/

void ajouterVictoireDefaiteAStatistiques(struct Pseudo Nom[2], int joueurGagnant, int joueurPerdant){ // On ajoute les victoires défaites au fichier stats
    FILE* fichierStats=fopen("DAT/stat.dat","rb"); // Mode lecture binaire
    struct Statistiques stats[50]={0};

    if(fichierStats!=NULL){ // si le fichier est présent

        fread(stats,sizeof(struct Statistiques),50,fichierStats);
        fclose(fichierStats);
    } // On prend le fichier dans une struct
    fichierStats=fopen("DAT/stat.dat","wb+"); // on réini le fichier
    mettreNomEtVictoireDansTableau(stats,joueurGagnant,joueurPerdant,Nom);
    fwrite(stats,sizeof(struct Statistiques),50,fichierStats);
    fclose(fichierStats);
}

void mettreNomEtVictoireDansTableau(struct Statistiques stats[50], int joueurGagnant,int joueurPerdant,struct Pseudo Nom[2]){ // On met la victoire défaite au pseudo du joueur
    int correspondance[2]={0,0};

    ajoutVictoireDefaiteSiNomPresentDansLeFichier(stats, joueurGagnant, joueurPerdant, Nom, correspondance);
    ajoutVictoireDefaiteSiNomPasPresentDansLeFichier(stats, joueurGagnant, joueurPerdant, Nom, correspondance);

}

void ajoutVictoireDefaiteSiNomPresentDansLeFichier(struct Statistiques stats[50], int joueurGagnant,int joueurPerdant,struct Pseudo Nom[2],int correspondance[2]){
    int i;

    for(i=0;i<50;i++){
            // Si le joueur est déjà présent dans le fichier alors on va ajouter la victoire/défaite
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
}

void ajoutVictoireDefaiteSiNomPasPresentDansLeFichier(struct Statistiques stats[50], int joueurGagnant,int joueurPerdant,struct Pseudo Nom[2], int correspondance[2]){
    int i,j=0,Quitter;

    for(i=0;i<2;i++){ //sinon on ajoute a un emplacement libre le nom du jeu et sa victoire/defaite
        if(correspondance[i]==0){
            j=Quitter=0;
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


/** MENU DE FIN DE PARTIE **/

void menuFinDePartie(SDL_Renderer* rendererWindow,char* couleurGagnante){ // menu qui apparait quand on a fini une partie
    SDL_Rect caractObjet[3];
    int action=0;
    remplirCaractMenuFinDePartie(rendererWindow, caractObjet);
    affichageMenuFinDePartie(rendererWindow, caractObjet,couleurGagnante);
    action=actionMenuFinDePartie(caractObjet);
    issueMenuFinDePartie(rendererWindow,action);
}

void remplirCaractMenuFinDePartie(SDL_Renderer* rendererWindow, SDL_Rect* caractObjet){ // on rempli les sdl caract pour les elements visuels
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

void affichageMenuFinDePartie(SDL_Renderer* rendererWindow,SDL_Rect* caractObjet,char* couleurGagnante){ //affichage visuel du menu
    char Texte[25];

    sprintf(Texte,"Joueur %s gagnant !",couleurGagnante);

    mettreFondEcranUni(rendererWindow);

    if(strcmp(couleurGagnante,"blanc")==0){ //en fonction du texte envoyé en paramètre on écrit la bonne sortie
        affichageTexte(rendererWindow,Texte,70,caractObjet[0],0,0);
    }
    else if(strcmp(couleurGagnante,"noir")==0){
        affichageTexte(rendererWindow,Texte,70,caractObjet[0],0,1);
    }
    else{
        affichageTexte(rendererWindow,"Egalite entre les deux joueurs..",70,caractObjet[0],0,1);
    }
    Boutton(rendererWindow,caractObjet[1],"Rejouer");
    Boutton(rendererWindow,caractObjet[2],"Menu principal");
    SDL_RenderPresent(rendererWindow);
}

int actionMenuFinDePartie(SDL_Rect* caractObjet){ // attente d'actions dans le menu
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

void issueMenuFinDePartie(SDL_Renderer* rendererWindow,int action){ // issues en fonction de la variable action
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
