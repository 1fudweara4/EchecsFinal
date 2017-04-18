#include"header/menus.h"
#include"header/outils.h"
#include "header/echiquier.h"

void menuPrincipal(SDL_Renderer* rendererWindow){ // Menu principal : affichage graphique puis actions
    int Action;
    SDL_Rect CaractBoutton[3];
    SDL_Rect caractImageTexteIntro[2];

    printf("Execution menuPrincipal\n");
    remplirCaractTroisBouttons(rendererWindow, CaractBoutton);
    remplirCaractImageEtTexteIntro(rendererWindow,caractImageTexteIntro);
    affichageMenuPrincipal(rendererWindow,CaractBoutton,caractImageTexteIntro);
    Action=evenementMenuTroisBouttons(rendererWindow,CaractBoutton);
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

}

void affichageMenuPrincipal(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton,SDL_Rect* caractImageTexteIntro){ //Affichage des 3 bouttons dans menu principal

    mettreFondEcranUni(rendererWindow);

    Boutton(rendererWindow,CaractBoutton[0],"Jouer");
    Boutton(rendererWindow,CaractBoutton[1],"Statistiques");
    Boutton(rendererWindow,CaractBoutton[2],"Quitter");
    affichageTexte(rendererWindow,"Echecs modifies",75,caractImageTexteIntro[0],0,1);
    affichageImagePNG(rendererWindow,caractImageTexteIntro[1],"DAT/Image/imageAccueil.jpg");

    SDL_RenderPresent(rendererWindow);
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
    int i,j;
    for(j=0;j<5;j++){
        for(i=0;i<50;i++){
            if(strcmp(stats[i].Pseudo,"")!=0 && stats[i].NombreVictoireDefaite[0]>top[j].NombreVictoireDefaite[0]){
                top[j].NombreVictoireDefaite[0]=stats[i].NombreVictoireDefaite[0];
                top[j].NombreVictoireDefaite[1]=stats[i].NombreVictoireDefaite[1];
                strcpy(top[j].Pseudo,stats[i].Pseudo);
                strcpy(stats[i].Pseudo,"");
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
