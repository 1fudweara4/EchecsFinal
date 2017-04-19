#include "header/lib.h"
#include"header/menus.h"
#include"header/outils.h"
#include "header/echiquier.h"

void menuPrincipal(SDL_Renderer* rendererWindow){ // Menu principal : affichage graphique puis actions
    int Action;
    SDL_Rect CaractBoutton[3];
    SDL_Rect caractImageTexteIntro[3];

    printf("Execution menuPrincipal\n");
    remplirCaractTroisBouttons(rendererWindow, CaractBoutton);
    remplirCaractImageEtTexteIntro(rendererWindow,caractImageTexteIntro);
    affichageMenuPrincipal(rendererWindow,CaractBoutton,caractImageTexteIntro);
    Action=evenementMenuPrincipal(rendererWindow,CaractBoutton,caractImageTexteIntro);
    issueMenuPrincipal(rendererWindow,Action);
}

void remplirCaractTroisBouttons(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton){ // rempli caractéristiques pour 3 boutons
    int i;
    struct coordonnees tailleFenetre;

    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);

    for(i=0;i<3;i++){
        CaractBoutton[i].x=(tailleFenetre.x/2)-(tailleFenetre.x/10)*2;;
        CaractBoutton[i].y=((tailleFenetre.y/13)*3+(tailleFenetre.y/13)*3*i);
        CaractBoutton[i].w=(tailleFenetre.x/5)*2;
        CaractBoutton[i].h=(tailleFenetre.y/13)*2;
    }
}

void remplirCaractImageEtTexteIntro(SDL_Renderer* rendererWindow,SDL_Rect* caractImageTexteIntro){
    struct coordonnees tailleFenetre;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);

    caractImageTexteIntro[0].x=tailleFenetre.x/2;
    caractImageTexteIntro[0].y=tailleFenetre.y/13;

    caractImageTexteIntro[1].x=tailleFenetre.x/15;
    caractImageTexteIntro[1].y=tailleFenetre.x/50;
    caractImageTexteIntro[1].w=tailleFenetre.x/6;
    caractImageTexteIntro[1].h=tailleFenetre.x/6/1.75;

    caractImageTexteIntro[2].x=tailleFenetre.x- (tailleFenetre.y/10)-10;
    caractImageTexteIntro[2].y=tailleFenetre.y- (tailleFenetre.y/10)-10;
    caractImageTexteIntro[2].w= (tailleFenetre.y/10);
    caractImageTexteIntro[2].h= (tailleFenetre.y/10);

}

void affichageMenuPrincipal(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton,SDL_Rect* caractImageTexteIntro){ //Affichage des 3 bouttons dans menu principal

    mettreFondEcranUni(rendererWindow);

    Boutton(rendererWindow,CaractBoutton[0],"Jouer");
    Boutton(rendererWindow,CaractBoutton[1],"Statistiques");
    Boutton(rendererWindow,CaractBoutton[2],"Quitter");
    affichageTexte(rendererWindow,"Echecs modifies",75,caractImageTexteIntro[0],0,1);
    affichageImagePNG(rendererWindow,caractImageTexteIntro[1],"DAT/Image/imageAccueil.jpg");
    affichageImagePNG(rendererWindow,caractImageTexteIntro[2],"DAT/Image/bouttonOptions.png");

    SDL_RenderPresent(rendererWindow);
}

int evenementMenuPrincipal(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton,SDL_Rect* caractImageTexteIntro){ // Attente de clique sur l'un des trois bouttons
    int Quitter=0, Action=0;
    SDL_Event event;
    struct coordonnees positionSouris;
    Uint32 Timer;

    while(!Quitter){
        Timer=SDL_GetTicks();
        if(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_MOUSEBUTTONUP:
                        Action=actionEnFonctionCliqueMenuTroisBouttons(rendererWindow,CaractBoutton);
                        SDL_GetMouseState(&positionSouris.x,&positionSouris.y);
                        if(positionSouris.x>caractImageTexteIntro[2].x && positionSouris.x<caractImageTexteIntro[2].x+caractImageTexteIntro[2].w && positionSouris.y>caractImageTexteIntro[2].y && positionSouris.y<caractImageTexteIntro[2].y+caractImageTexteIntro[2].h){
                            Action=4;
                        }
                        if(Action!=0){
                            Quitter=1;
                        }
                    break;

                    default:
                        Quitter=QuitterAppuieCroixOuEchap(event);
                    break;
                }
        }
        PauseEnfonctionDureeExecution(Timer);
    }
    return Action;
}

int evenementMenuTroisBouttons(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton){ // Attente de clique sur l'un des trois bouttons
    int Quitter=0, Action=0;
    SDL_Event event;
    Uint32 Timer;

    while(!Quitter){
        Timer=SDL_GetTicks();
        if(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_MOUSEBUTTONUP:
                        Action=actionEnFonctionCliqueMenuTroisBouttons(rendererWindow,CaractBoutton);

                        if(Action!=0){
                            Quitter=1;
                        }
                    break;

                    default:
                        Quitter=QuitterAppuieCroixOuEchap(event);
                    break;
                }
        }
        PauseEnfonctionDureeExecution(Timer);
    }
    return Action;
}

int actionEnFonctionCliqueMenuTroisBouttons(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton){ // Si clique alors remplir variable Action avec le numéro du bouton
    struct coordonnees positionSouris;
    int i,action=0;

    SDL_GetMouseState(&positionSouris.x,&positionSouris.y);

    for(i=1;i<4;i++){
        if(positionSouris.x>CaractBoutton[i-1].x && positionSouris.x<CaractBoutton[i-1].x+CaractBoutton[i-1].w && positionSouris.y>CaractBoutton[i-1].y && positionSouris.y<CaractBoutton[i-1].y+CaractBoutton[i-1].h){
            action=i;
    }
    }

    return action;
}

void issueMenuPrincipal(SDL_Renderer* rendererWindow, int Action){ // Issue du menu en fonction du boutton cliqué
    switch(Action){
    case 1:
        printf("Appuie sur le boutton Jouer\n\n");
        menuJouer(rendererWindow);
        break;
    case 2:
        printf("Appuie sur le boutton Statistiques\n\n");
        menuStatistiques(rendererWindow);
        break;
    case 3:
        printf("Appuie sur le boutton Quitter\n\n");
        break;
    case 4:
        printf("Appuie sur le boutton Options\n\n");
        menuOptions(rendererWindow);
        break;
    }
}



void menuOptions(SDL_Renderer* rendererWindow){
    int action=0;
    SDL_Rect caractAffichage[11];

    remplirCaractMenuOptions(rendererWindow, caractAffichage);
    affichageMenuOptions(rendererWindow, caractAffichage);
    action=evenementMenuOptions(rendererWindow, caractAffichage);

    IssueMenuOptions(rendererWindow,action);
}

void remplirCaractMenuOptions(SDL_Renderer* rendererWindow, SDL_Rect* caractAffichage){
    struct coordonnees tailleFenetre;
    int i;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);

    caractAffichage[0].x=tailleFenetre.x/2;
    caractAffichage[0].y=tailleFenetre.y/8;

    caractAffichage[1].x=tailleFenetre.x/2;
    caractAffichage[1].y=tailleFenetre.y/8*2;

    for(i=2;i<5;i++){
        caractAffichage[i].x=tailleFenetre.x/3;
        caractAffichage[i].y=tailleFenetre.y/8*(i+1);

        caractAffichage[i+3].y=tailleFenetre.y/8*(i+1)-15;
        caractAffichage[i+3].x=tailleFenetre.x/3*2;
        caractAffichage[i+3].w=caractAffichage[i+3].h=tailleFenetre.y/8-10;
    }
    for(i=8;i<10;i++){
        caractAffichage[i].x=tailleFenetre.x/10;
        caractAffichage[i].y=tailleFenetre.y/8*(i-2);
        caractAffichage[i].w=tailleFenetre.x/2;
        caractAffichage[i].h=tailleFenetre.y/12;
    }
    caractAffichage[10].x=tailleFenetre.x-150;
    caractAffichage[10].y=tailleFenetre.y-100;
    caractAffichage[10].w=100;
    caractAffichage[10].h=50;

}

void affichageMenuOptions(SDL_Renderer* rendererWindow, SDL_Rect* caractAffichage){
    int i;
    mettreFondEcranUni(rendererWindow);

    affichageTexte(rendererWindow,"Options",50,caractAffichage[0],0,0);
    affichageTexte(rendererWindow,"Resolution (quitte le programme):",50,caractAffichage[1],0,0);
    affichageTexte(rendererWindow,"640 x 480",50,caractAffichage[2],0,0);
    affichageTexte(rendererWindow,"1 024 x 768",50,caractAffichage[3],0,0);
    affichageTexte(rendererWindow,"1 280 x 960",50,caractAffichage[4],0,0);

    SDL_SetRenderDrawColor(rendererWindow,1, 1, 1,255);
    for(i=5;i<8;i++){
            SDL_RenderDrawRect(rendererWindow,&caractAffichage[i]);
    }
    mettreSigneSurDefinitionActuelle(rendererWindow,caractAffichage);
    Boutton(rendererWindow,caractAffichage[8],"Reset statistiques");
    Boutton(rendererWindow,caractAffichage[9],"Reset sauvegardes");

    Boutton(rendererWindow,caractAffichage[10],"Retour");

    SDL_RenderPresent(rendererWindow);
}

void mettreSigneSurDefinitionActuelle(SDL_Renderer* rendererWindow, SDL_Rect* CaractAffichage){
    struct coordonnees tailleFenetre;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);

    switch(tailleFenetre.x){
    case 640:
        affichageImagePNG(rendererWindow,CaractAffichage[5],"DAT/Image/valide.png");
        break;
    case 1024:
        affichageImagePNG(rendererWindow,CaractAffichage[6],"DAT/Image/valide.png");
        break;
    case 1280:
        affichageImagePNG(rendererWindow,CaractAffichage[7],"DAT/Image/valide.png");
        break;
    }
}

int evenementMenuOptions(SDL_Renderer* rendererWindow, SDL_Rect* CaractAffichage){
    int Quitter=0, Action=0;
    SDL_Event event;
    Uint32 Timer;

    while(!Quitter){
        Timer=SDL_GetTicks();
        if(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_MOUSEBUTTONUP:
                        Quitter=actionCliqueMenuOptions(rendererWindow,CaractAffichage,&Action);
                    break;

                    default:
                        Quitter=QuitterAppuieCroixOuEchap(event);
                    break;
                }
        }
        PauseEnfonctionDureeExecution(Timer);
    }
    return Action;
}

int actionCliqueMenuOptions(SDL_Renderer* rendererWindow, SDL_Rect* CaractAffichage,int* Action){
    int Quitter=0,i;
    struct coordonnees positionSouris;

    SDL_GetMouseState(&positionSouris.x,&positionSouris.y);

    for(i=5;i<11;i++){
        if(positionSouris.x>CaractAffichage[i].x && positionSouris.x<CaractAffichage[i].x+CaractAffichage[i].w && positionSouris.y>CaractAffichage[i].y && positionSouris.y<CaractAffichage[i].y+CaractAffichage[i].h){
            *Action=i;
            Quitter=1;
        }
    }

    return Quitter;
}

void IssueMenuOptions(SDL_Renderer* rendererWindow,int action){
    switch(action){
        case 0:
            printf("Appuie sur la croix ou echap\n\n");
            break;
        case 5:
            printf("Changement de resolution en 640 x 480\n\n");
            changementDefinition(rendererWindow,640,480);
            break;
        case 6:
            printf("Changement de resolution en 1 024 x 768\n\n");
            changementDefinition(rendererWindow,1024,768);
            break;
        case 7:
            printf("Changement de resolution en 1 280 x 960\n\n");
            changementDefinition(rendererWindow,1280,960);
            break;
        case 8:
            printf("Reset fichier statistiques\n\n");
            remove("DAT/stat.dat");
            menuOptions(rendererWindow);
            break;
        case 9:
            printf("Reset fichiers sauvegarde\n\n");
            resetSauvegardes();
            menuOptions(rendererWindow);
            break;
        case 10:
            printf("Appuie sur Boutton retour\n\n");
            menuPrincipal(rendererWindow);
            break;
    }
}

void resetSauvegardes(){
    remove("DAT/sauvegardeEmplacement.dat");
    remove("DAT/sauvegardeNom.dat");
    remove("DAT/sauvegardeTour.dat");
}

void changementDefinition(SDL_Renderer* rendererWindow,int x,int y){
    struct coordonnees tailleFenetre;
    FILE* fichierDefinition;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);

    if(tailleFenetre.x==x){
        menuOptions(rendererWindow);
    }
    else{
        fichierDefinition=fopen("DAT/settings.dat","w");
        tailleFenetre.x=x;
        tailleFenetre.y=y;
        fwrite(&tailleFenetre,sizeof(struct coordonnees),1,fichierDefinition);
        fclose(fichierDefinition);
    }

}


void menuJouer(SDL_Renderer* rendererWindow){
    int Action;
    SDL_Rect CaractBoutton[3];

    printf("Execution menuJouer\n");
    remplirCaractTroisBouttons(rendererWindow, CaractBoutton);
    affichageMenuJouer(rendererWindow,CaractBoutton);
    Action=evenementMenuTroisBouttons(rendererWindow,CaractBoutton);
    issueMenuJouer(rendererWindow,Action);
}

void affichageMenuJouer(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton){

    mettreFondEcranUni(rendererWindow);

    Boutton(rendererWindow,CaractBoutton[0],"Nouvelle partie");
    Boutton(rendererWindow,CaractBoutton[1],"Reprendre partie");
    Boutton(rendererWindow,CaractBoutton[2],"Retour");
    SDL_RenderPresent(rendererWindow);
}

void issueMenuJouer(SDL_Renderer* rendererWindow, int Action){
    switch(Action){
    case 1:
        printf("Appuie sur le boutton Nouvelle partie\n\n");
        menuNombredeJoueur(rendererWindow);
        break;
    case 2:
        printf("Appuie sur le boutton Reprendre partie\n\n");
        menuReprendrePartie(rendererWindow);
        break;
    case 3:
        printf("Appuie sur le boutton Retour\n\n");
        menuPrincipal(rendererWindow);
        break;
    }
}



void menuNombredeJoueur(SDL_Renderer* rendererWindow){
    int Action;
    SDL_Rect CaractBoutton[3];

    printf("Execution menuNombredeJoueur\n");
    remplirCaractTroisBouttons(rendererWindow, CaractBoutton);
    affichageMenuNombredeJoueur(rendererWindow,CaractBoutton);
    Action=evenementMenuTroisBouttons(rendererWindow,CaractBoutton);
    issueMenuNombredeJoueur(rendererWindow,Action);
}

void affichageMenuNombredeJoueur(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton){
    mettreFondEcranUni(rendererWindow);

    Boutton(rendererWindow,CaractBoutton[0],"1 joueur");
    Boutton(rendererWindow,CaractBoutton[1],"2 joueurs");
    Boutton(rendererWindow,CaractBoutton[2],"Retour");
    SDL_RenderPresent(rendererWindow);
}

void issueMenuNombredeJoueur(SDL_Renderer* rendererWindow, int Action){
    switch(Action){
    case 1:
        printf("Appuie sur le boutton 1 Joueur\n\n");
        menuSelectionPseudo(rendererWindow,1);
        break;
    case 2:
        printf("Appuie sur le boutton 2 Joueur\n\n");
        menuSelectionPseudo(rendererWindow,2);
        break;
    case 3:
        printf("Appuie sur le boutton Retour\n\n");
        menuJouer(rendererWindow);
        break;
    }
}



void menuSelectionPseudo(SDL_Renderer* rendererWindow,int nombreDeJoueur){
    int Action;
    SDL_Rect CaractBoutton[4];
    struct Pseudo Nom[2];

    Nom[0].Nom[0]='\0';
    Nom[1].Nom[0]='\0';

    printf("Execution menuSelectionPseudo\n");
    remplirCaractBouttonSelectionPseudo(rendererWindow, CaractBoutton);
    affichageMenuSelectionPseudo(rendererWindow,CaractBoutton);
    Action=evenementMenuSelectionPseudo(rendererWindow,CaractBoutton,Nom,nombreDeJoueur);
    issueMenuMenuSelectionPseudo(rendererWindow,Nom,Action);

}

void remplirCaractBouttonSelectionPseudo(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton){
    struct coordonnees tailleFenetre;

    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);

    CaractBoutton[0].x=tailleFenetre.x-150;
    CaractBoutton[0].y=tailleFenetre.y-100;
    CaractBoutton[0].w=100;
    CaractBoutton[0].h=50;

    CaractBoutton[1].x=tailleFenetre.x/3;
    CaractBoutton[1].y=tailleFenetre.y/4;
    CaractBoutton[1].w=tailleFenetre.x/3;
    CaractBoutton[1].h=tailleFenetre.y/5;

    CaractBoutton[2].x=tailleFenetre.x*3.5/9;
    CaractBoutton[2].y=tailleFenetre.y/2;
    CaractBoutton[2].w=tailleFenetre.x*2/9;
    CaractBoutton[2].h=tailleFenetre.y/6;

    CaractBoutton[3].x=tailleFenetre.x/2;
    CaractBoutton[3].y=tailleFenetre.y/6;
}

void affichageMenuSelectionPseudo(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton){

    mettreFondEcranUni(rendererWindow);

    affichageTexte(rendererWindow,"Entrez votre pseudo:",50,CaractBoutton[3],0,1);
    Boutton(rendererWindow,CaractBoutton[1],"  ");
    Boutton(rendererWindow,CaractBoutton[0],"Retour");
    Boutton(rendererWindow,CaractBoutton[2],"Valider");
    SDL_RenderPresent(rendererWindow);
}

int evenementMenuSelectionPseudo(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton,struct Pseudo Nom[2], int nombreDeJoueur){
    SDL_Event event;
    int Quitter=0, Action=0, NombrePseudoEntree=0,Avancement=0;
    Uint32 Timer;

    SDL_StartTextInput();
    while(!Quitter){
        Timer=SDL_GetTicks();
        if(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_MOUSEBUTTONUP:
                        Quitter=actionMOUSEBUTTONUPMenuSelectionPseudo(rendererWindow,CaractBoutton,Nom,nombreDeJoueur,&NombrePseudoEntree,&Avancement,&Action);
                    break;

                    case SDL_TEXTINPUT:
                        actionTEXTINPUTMenuSelectionPseudo(rendererWindow,event,Nom,NombrePseudoEntree,&Avancement);
                        Boutton(rendererWindow,CaractBoutton[1],&Nom[NombrePseudoEntree].Nom[0]);
                        SDL_RenderPresent(rendererWindow);
                    break;

                    case SDL_KEYDOWN:
                        actionKEYDOWNMenuSelectionPseudo(rendererWindow,CaractBoutton,event,Nom,NombrePseudoEntree,&Avancement);
                    break;

                    default:
                        Quitter=QuitterAppuieCroixOuEchap(event);
                    break;
                }
        }
        PauseEnfonctionDureeExecution(Timer);
    }
    SDL_StopTextInput();

    return Action;
}

int actionMOUSEBUTTONUPMenuSelectionPseudo(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton,struct Pseudo Nom[2],int nombreDeJoueur,int* NombrePseudoEntree,int* Avancement,int* Action){
    struct coordonnees positionSouris;
    int Quitter=0;

    SDL_GetMouseState(&positionSouris.x,&positionSouris.y);
    if(positionSouris.x>CaractBoutton[0].x && positionSouris.x<CaractBoutton[0].x+CaractBoutton[0].w && positionSouris.y>CaractBoutton[0].y && positionSouris.y<CaractBoutton[0].y+CaractBoutton[0].h){
        *Action=1;
        Quitter=1;
    }
    if(positionSouris.x>CaractBoutton[2].x && positionSouris.x<CaractBoutton[2].x+CaractBoutton[2].w && positionSouris.y>CaractBoutton[2].y && positionSouris.y<CaractBoutton[2].y+CaractBoutton[2].h){
        if(strlen(Nom[*NombrePseudoEntree].Nom)!=0){
            if(*NombrePseudoEntree!=nombreDeJoueur-1){
                *Avancement=0;
                *NombrePseudoEntree=1;
                Boutton(rendererWindow,CaractBoutton[1],"  ");
                SDL_RenderPresent(rendererWindow);
            }
            else{
                *Action=2;
                Quitter=1;
            }
        }
    }

    return Quitter;
}

void actionTEXTINPUTMenuSelectionPseudo(SDL_Renderer* rendererWindow,SDL_Event event, struct Pseudo Nom[2],int NombrePseudoEntree,int* Avancement){
    if(*Avancement<10){
        strcat(Nom[NombrePseudoEntree].Nom, event.text.text);
        *Avancement=*Avancement+1;
    }
}

void actionKEYDOWNMenuSelectionPseudo(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton, SDL_Event event,struct Pseudo Nom[2],int NombrePseudoEntree,int* Avancement){

    if(event.key.keysym.sym==SDLK_BACKSPACE){
        if(*Avancement!=0){
            Nom[NombrePseudoEntree].Nom[*Avancement-1]='\0';
            *Avancement=*Avancement-1;
        }
    }
    if(strlen(Nom[NombrePseudoEntree].Nom)==0){
        Boutton(rendererWindow,CaractBoutton[1],"  ");
    }
    else{
        Boutton(rendererWindow,CaractBoutton[1],&Nom[NombrePseudoEntree].Nom[0]);
    }
    SDL_RenderPresent(rendererWindow);
}

void issueMenuMenuSelectionPseudo(SDL_Renderer* rendererWindow,struct Pseudo Nom[2],int Action){
    switch(Action){
    case 1:
        printf("Appuie sur le boutton Retour\n\n");
        menuNombredeJoueur(rendererWindow);
        break;
    case 2:
        printf("Appuie sur le boutton Valider\n\n");
        lancementEchiquier(rendererWindow,Nom,0);
        break;
    }
}




int QuitterAppuieCroixOuEchap(SDL_Event event){
    int Quitter=0;

    if(event.type==SDL_WINDOWEVENT){
        if(event.window.event==SDL_WINDOWEVENT_CLOSE){
        Quitter=1;
        }
    }
    if(event.type==SDL_KEYUP){
        if(event.key.keysym.sym==SDLK_ESCAPE){
            Quitter=1;
        }
    }
    return Quitter;
}

void PauseEnfonctionDureeExecution(Uint32 Timer){
    if(SDL_GetTicks()-Timer<50 && SDL_GetTicks()-Timer>0){
        SDL_Delay(50+SDL_GetTicks()-Timer);
    }
}


void menuReprendrePartie(SDL_Renderer* rendererWindow){
    int action, nombrePartie=0;
    SDL_Rect caractBoutton[6];
    FILE* fichierNom=fopen("DAT/sauvegardeNom.dat","rb");
    struct Pseudo Nom[2];

        remplirCaractmenuReprendrePartie(rendererWindow,caractBoutton);
        affichageMenuReprendrePartie(rendererWindow,caractBoutton,fichierNom,&nombrePartie);
        action=actionMenuReprendrePartie(rendererWindow,caractBoutton,nombrePartie);

        if(fichierNom!=NULL){
            recuperationNom(fichierNom,Nom,action);
            fclose(fichierNom);
        }
        issueMenuReprendrePartie(rendererWindow,action,Nom);
}

void remplirCaractmenuReprendrePartie(SDL_Renderer* rendererWindow,SDL_Rect* caractBoutton){
    int i;
    struct coordonnees tailleFenetre;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);

    for(i=1;i<6;i++){
            caractBoutton[i].w=tailleFenetre.x/6*5;
            caractBoutton[i].h=tailleFenetre.y/10;
            caractBoutton[i].x=tailleFenetre.x/12;
            caractBoutton[i].y=tailleFenetre.y/10*(i-1)+tailleFenetre.y/10/3*(i);
    }
    caractBoutton[0].x=tailleFenetre.x-150;
    caractBoutton[0].y=tailleFenetre.y-100;
    caractBoutton[0].w=100;
    caractBoutton[0].h=50;

}

void affichageMenuReprendrePartie(SDL_Renderer* rendererWindow,SDL_Rect* caractBoutton,FILE*fichier,int* nombrePartie){
    int i;
    char nomPartie[50];

    mettreFondEcranUni(rendererWindow);
    for(i=1;i<6;i++){
        recuperationNomDesParties(fichier,nomPartie,nombrePartie);
        Boutton(rendererWindow,caractBoutton[i],nomPartie);
    }

    Boutton(rendererWindow,caractBoutton[0],"Retour");
    SDL_RenderPresent(rendererWindow);
}

void recuperationNomDesParties(FILE*fichier,char* nomPartie,int* nombrePartie){
    struct Pseudo Nom[2];
    if(fichier!=NULL && fread(Nom,sizeof(struct Pseudo),2,fichier) && !feof(fichier)){
        if(strcmp(Nom[1].Nom,"")==0){
                sprintf(nomPartie,"Partie 1 joueur avec %s",Nom[0].Nom);
                *nombrePartie=*nombrePartie+1;
        }
        else{
                sprintf(nomPartie,"Partie 2 joueurs avec %s & %s",Nom[0].Nom,Nom[1].Nom);
                *nombrePartie=*nombrePartie+1;
        }
    }
    else{
        sprintf(nomPartie,"Vide");
    }

}

int actionMenuReprendrePartie(SDL_Renderer* rendererWindow,SDL_Rect* caractBoutton,int nombrePartie){
    int action,Quitter=0;
    SDL_Event event;
    Uint32 Timer;

        while(!Quitter){
            Timer=SDL_GetTicks();
            if(SDL_PollEvent(&event)){
                    switch(event.type){
                        case SDL_MOUSEBUTTONUP:
                            action=actionEnFonctionCliqueMenuReprendrePartie(rendererWindow,caractBoutton,nombrePartie);
                            if(action!=-1){
                                Quitter=1;
                            }
                        break;

                        default:
                            Quitter=QuitterAppuieCroixOuEchap(event);
                        break;
                    }
            }
            PauseEnfonctionDureeExecution(Timer);
        }

    return action;
}

int actionEnFonctionCliqueMenuReprendrePartie(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton,int nombrePartie){
    struct coordonnees positionSouris;
    int i,action=-1;

    SDL_GetMouseState(&positionSouris.x,&positionSouris.y);

    for(i=0;i<nombrePartie+1;i++){
        if(positionSouris.x>CaractBoutton[i].x && positionSouris.x<CaractBoutton[i].x+CaractBoutton[i].w && positionSouris.y>CaractBoutton[i].y && positionSouris.y<CaractBoutton[i].y+CaractBoutton[i].h){
            action=i;
    }
    }

    return action;
}

void issueMenuReprendrePartie(SDL_Renderer* rendererWindow,int action, struct Pseudo Nom[2]){
    if(action==0){
        menuJouer(rendererWindow);
    }
    else{
        printf("Choix partie %d avec %s et %s\n",action-1, Nom[0].Nom, Nom[1].Nom);
        lancementEchiquier(rendererWindow,Nom,action);
    }
}

void recuperationNom(FILE* fichier, struct Pseudo Nom[2],int nombrePartie){

    fseek(fichier, sizeof(struct Pseudo)*2*(nombrePartie-1), SEEK_SET);
    fread(Nom,sizeof(struct Pseudo),2,fichier);
    printf("%s\n\n",Nom[1].Nom);
}



void menuStatistiques(SDL_Renderer* rendererWindow){
    FILE* fichierStat=fopen("DAT/stat.dat","rb");
    struct Statistiques stats[50]={0};
    int action;
    SDL_Rect caractGraphisme[8];
    remplirCaractMenuStatistiques(rendererWindow,caractGraphisme);

    if(fichierStat!=NULL){

        fread(stats,sizeof(struct Statistiques),50,fichierStat);

        affichageTop5Victoire(rendererWindow, stats,caractGraphisme);
        fclose(fichierStat);
    }
    else{
        affichageStatQuandPasDeFichier(rendererWindow,caractGraphisme);
    }
    action=actionMenuStatistiques(rendererWindow,caractGraphisme);
    issueMenuStatistiques(rendererWindow,action);
}

void remplirCaractMenuStatistiques(SDL_Renderer* rendererWindow, SDL_Rect caractGraphisme[8]){
    int i;
    struct coordonnees tailleFenetre;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);

    for(i=1;i<7;i++){
            caractGraphisme[i].x=tailleFenetre.x/2;
            caractGraphisme[i].y=tailleFenetre.y/10*(i)+tailleFenetre.y/10/3*(i);
    }
    caractGraphisme[0].x=tailleFenetre.x-150;
    caractGraphisme[0].y=tailleFenetre.y-100;
    caractGraphisme[0].w=100;
    caractGraphisme[0].h=50;

    caractGraphisme[7].x=tailleFenetre.x/4;
    caractGraphisme[7].y=tailleFenetre.x/100;
    caractGraphisme[7].w=tailleFenetre.x/2;
    caractGraphisme[7].h=tailleFenetre.x/2/0.71;

}

void affichageTop5Victoire(SDL_Renderer* rendererWindow, struct Statistiques stats[50],SDL_Rect caractGraphisme[8]){
    struct Statistiques top[5]={0};
    int i;
    char texte[50];

    remplirTop5(stats,top);
    mettreFondEcranUni(rendererWindow);
    affichageImagePNG(rendererWindow, caractGraphisme[7],"DAT/Image/tableau.png");

    for(i=0;i<5;i++){
        if(strcmp(top[i].Pseudo,"")!=0){
            sprintf(texte,"%d. %s   %d/%d",i+1,top[i].Pseudo, top[i].NombreVictoireDefaite[0],top[i].NombreVictoireDefaite[1]);
            affichageTexte(rendererWindow,texte,50,caractGraphisme[i+2],0,0);
            printf("%s avec %d win(s)\n",top[i].Pseudo, top[i].NombreVictoireDefaite[0]);
        }
    }
    affichageTexte(rendererWindow,"Classement",65,caractGraphisme[1],0,0);
    Boutton(rendererWindow, caractGraphisme[0],"Retour");
    SDL_RenderPresent(rendererWindow);
}

void affichageStatQuandPasDeFichier(SDL_Renderer* rendererWindow,SDL_Rect caractGraphisme[8]){

    mettreFondEcranUni(rendererWindow);

    printf("Aucun résultat en mémoire\n");
    affichageTexte(rendererWindow,"Aucun resultat en memoire",50,caractGraphisme[3],0,0);

    affichageTexte(rendererWindow,"Classement",65,caractGraphisme[1],0,0);
    Boutton(rendererWindow, caractGraphisme[0],"Retour");
    SDL_RenderPresent(rendererWindow);

}

void remplirTop5(struct Statistiques stats[50],struct Statistiques top[5]){
    int i,j,k;
    for(i=0;i<50;i++){
        if(strcmp(stats[i].Pseudo,"")!=0){
            for(j=0;j<5;j++){
                if(stats[i].NombreVictoireDefaite[0]>top[j].NombreVictoireDefaite[0]){
                    for(k=4;k>j;k--){
                        top[k]=top[k-1];
                    }
                    top[j].NombreVictoireDefaite[0]=stats[i].NombreVictoireDefaite[0];
                    top[j].NombreVictoireDefaite[1]=stats[i].NombreVictoireDefaite[1];
                    strcpy(top[j].Pseudo,stats[i].Pseudo);
                    strcpy(stats[i].Pseudo,"");
                    stats[i].NombreVictoireDefaite[0]=0;
                }
            }
        }
    }
}

int actionMenuStatistiques(SDL_Renderer* rendererWindow,SDL_Rect caractGraphismes[6]){
    int action,Quitter=0;
    struct coordonnees positionSouris;
    SDL_Event event;
    Uint32 Timer;

    while(!Quitter){
        Timer=SDL_GetTicks();
        if(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_MOUSEBUTTONUP:
                        SDL_GetMouseState(&positionSouris.x,&positionSouris.y);
                        if(positionSouris.x>caractGraphismes[0].x && positionSouris.x<caractGraphismes[0].x+caractGraphismes[0].w && positionSouris.y>caractGraphismes[0].y && positionSouris.y<caractGraphismes[0].y+caractGraphismes[0].h){
                            Quitter=1;
                            action=1;
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

void issueMenuStatistiques(SDL_Renderer* rendererWindow, int action){
    switch(action){
    case 0:
        printf("Fin de l'execution du programme\n\n");
        break;
    case 1:
        printf("Appuie sur le boutton retour\n\n");
        menuPrincipal(rendererWindow);
        break;
    }
}
