#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
/*
struct coordonnees{
    int x;
    int y;
};*/

struct Pseudo{
    char Nom[10];
};

struct Sauvegarde{
    int emplacementPions[64];
    int tourJoueur;
    struct Pseudo Nom[2];

};

void menuPrincipal(SDL_Renderer* rendererWindow);
void remplirCaractTroisBouttons(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton);
void affichageMenuPrincipal(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton);
int evenementMenuTroisBouttons(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton);
int actionEnFonctionCliqueMenuTroisBouttons(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton);
void issueMenuPrincipal(SDL_Renderer* rendererWindow, int Action);

void menuJouer(SDL_Renderer* rendererWindow);
void affichageMenuJouer(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton);
int evenementMenuJouer(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton);
void issueMenuJouer(SDL_Renderer* rendererWindow, int Action);

void menuNombredeJoueur(SDL_Renderer* rendererWindow);
void affichageMenuNombredeJoueur(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton);
void issueMenuNombredeJoueur(SDL_Renderer* rendererWindow, int Action);

void menuSelectionPseudo(SDL_Renderer* rendererWindow,int nombreDeJoueur);
void remplirCaractBouttonSelectionPseudo(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton);
void affichageMenuSelectionPseudo(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton);
int evenementMenuSelectionPseudo(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton,struct Pseudo Nom[2], int nombreDeJoueur);
int actionMOUSEBUTTONUPMenuSelectionPseudo(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton,struct Pseudo Nom[2],int nombreDeJoueur,int* NombrePseudoEntree,int* Avancement,int* Action);
void actionTEXTINPUTMenuSelectionPseudo(SDL_Renderer* rendererWindow,SDL_Event event, struct Pseudo Nom[2],int NombrePseudoEntree,int* Avancement);
void actionKEYDOWNMenuSelectionPseudo(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton, SDL_Event event,struct Pseudo Nom[2],int NombrePseudoEntree,int* Avancement);
void issueMenuMenuSelectionPseudo(SDL_Renderer* rendererWindow,struct Pseudo Nom[2],int Action);

int QuitterAppuieCroixOuEchap(SDL_Event event);
void PauseEnfonctionDureeExecution(Uint32 Timer);

void menuReprendrePartie(SDL_Renderer* rendererWindow);
void remplirCaractmenuReprendrePartie(SDL_Renderer* rendererWindow,SDL_Rect* caractBoutton);
void affichageMenuReprendrePartie(SDL_Renderer* rendererWindow,SDL_Rect* caractBoutton,FILE*fichierNom,int* nombrePartie);
void recuperationNomDesParties(FILE*fichier,char* nomPartie,int* nombrePartie);
int actionMenuReprendrePartie(SDL_Renderer* rendererWindow,SDL_Rect* caractBoutton,int nombrePartie);
int actionEnFonctionCliqueMenuReprendrePartie(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton,int nombrePartie);
void issueMenuReprendrePartie(SDL_Renderer* rendererWindow,int action, struct Pseudo Nom[2]);
void recuperationNom(FILE* fichier, struct Pseudo Nom[2],int nombrePartie);
