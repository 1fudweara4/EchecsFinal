#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
/*
struct Pseudo{
    char Nom[10];
};*/
/*
struct coordonnees{
    int x;
    int y;
};*/

void lancementEchiquier(SDL_Renderer* rendererWindow,struct Pseudo Nom[2],char* cheminEnregistrement);

void initalisationEchiquier(int emplacementPions[8][8],char* cheminEnregistrement);
void premierRemplissageTableauEchiquier(int emplacementPions[8][8]);

void affichagePartieEchiquier(SDL_Renderer* rendererWindow,int emplacementPions[8][8],struct Pseudo Nom[2]);
void affichageEchiquierEtPions(SDL_Renderer* rendererWindow,int emplacementPions[8][8]);
void affichageCaseCouleurEnFonctionPosition(SDL_Renderer* rendererWindow,int x,int y);
void affichagePions(SDL_Renderer* rendererWindow,int emplacementPions[8][8],int x,int y);
void affichagePseudo(SDL_Renderer*rendererWindow,struct Pseudo Nom[2]);
void affichageNombreDePions(SDL_Renderer*rendererWindow,int emplacementPions[8][8]);

int compterNbPions(int emplacementPions[8][8],int Couleur);

void lancementPartie(SDL_Renderer* rendererWindow,int emplacementPions[8][8],struct Pseudo Nom[2]);
int deroulementDuTour(SDL_Renderer* rendererWindow,int emplacementPions[8][8],struct Pseudo Nom[2],int joueurQuiJoue,int* causeFin);

void actionDuJoueur(SDL_Renderer* rendererWindow,int emplacementPions[8][8],int joueurQuiJoue,int* causeFin);
int actionPremierCLique(SDL_Renderer* rendererWindow,int emplacementPions[8][8],int joueurQuiJoue,int* causeFin);

struct coordonnees detectionEmplacementDuCliqueDansEchiquier();
void generationPropositionDeplacement(int emplacementPions[8][8],struct coordonnees positionDansEchiquier, struct coordonnees propositionDeplacement[3],int joueurQuiJoue);
void affichagePropositionDeplacement(SDL_Renderer* rendererWindow,struct coordonnees propositionDeplacement[3]);

int verificationSiIlyaPossibilites(struct coordonnees propositionDeplacement[3]);
int actionsDeplacement(SDL_Renderer* rendererWindow, int emplacementPions[8][8],struct coordonnees propositionDeplacement[3],struct coordonnees positionDansEchiquier,int joueurQuiJoue);
int evenementCliqueDemandeProposition(SDL_Renderer* rendererWindow, int emplacementPions[8][8],struct coordonnees propositionDeplacement[3],struct coordonnees positionDansEchiquier,int joueurQuiJoue);
void SuppressionPropositionsDeplacement(SDL_Renderer* rendererWindow,struct coordonnees propositionDeplacement[3]);
void deplacementPion(SDL_Renderer* rendererWindow,int emplacementPions[8][8], struct coordonnees propositionDeplacement[3],struct coordonnees positionDansEchiquier);
