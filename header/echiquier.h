#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

void lancementEchiquier(SDL_Renderer* rendererWindow,struct Pseudo Nom[2],int numeroPartieEnregistree);

void initalisationEchiquier(int emplacementPions[8][8],int numeroPartieEnregistree);
void premierRemplissageTableauEchiquier(int emplacementPions[8][8]);
void recuperationEchiquiersauvegarde(int emplacementPions[8][8],int numeroPartieEnregistree);

void affichagePartieEchiquier(SDL_Renderer* rendererWindow,int emplacementPions[8][8],struct Pseudo Nom[2]);
void affichageEchiquierEtPions(SDL_Renderer* rendererWindow,int emplacementPions[8][8]);
void affichageCaseCouleurEnFonctionPosition(SDL_Renderer* rendererWindow,int x,int y);
void affichagePions(SDL_Renderer* rendererWindow,int emplacementPions[8][8],int x,int y);
void affichagePseudo(SDL_Renderer*rendererWindow,struct Pseudo Nom[2]);
void affichageNombreDePions(SDL_Renderer*rendererWindow,int emplacementPions[8][8]);

int compterNbPions(int emplacementPions[8][8],int Couleur);

void lancementPartie(SDL_Renderer* rendererWindow,int emplacementPions[8][8],struct Pseudo Nom[2],int numeroPartieEnregistree);
void deroulementDuTour(SDL_Renderer* rendererWindow,int emplacementPions[8][8],struct Pseudo Nom[2],int joueurQuiJoue,int* causeFin,int* dernierJoueurQuiAjoue);

void actionDuJoueur(SDL_Renderer* rendererWindow,int emplacementPions[8][8],int joueurQuiJoue,int* causeFin,struct Pseudo Nom[2]);
int actionPremierCLique(SDL_Renderer* rendererWindow,int emplacementPions[8][8],int joueurQuiJoue,int* causeFin);

struct coordonnees detectionEmplacementDuCliqueDansEchiquier();
void generationPropositionDeplacement(int emplacementPions[8][8],struct coordonnees positionDansEchiquier, struct coordonnees propositionDeplacement[3],int joueurQuiJoue);
void affichagePropositionDeplacement(SDL_Renderer* rendererWindow,struct coordonnees propositionDeplacement[3]);

int verificationSiIlyaPossibilites(struct coordonnees propositionDeplacement[3]);
int actionsDeplacement(SDL_Renderer* rendererWindow, int emplacementPions[8][8],struct coordonnees propositionDeplacement[3],struct coordonnees positionDansEchiquier,int joueurQuiJoue, int* causeFin);
int evenementCliqueDemandeProposition(SDL_Renderer* rendererWindow, int emplacementPions[8][8],struct coordonnees propositionDeplacement[3],struct coordonnees positionDansEchiquier,int joueurQuiJoue);
void SuppressionPropositionsDeplacement(SDL_Renderer* rendererWindow,struct coordonnees propositionDeplacement[3], int emplacementPions[8][8]);
void deplacementPion(SDL_Renderer* rendererWindow,int emplacementPions[8][8], struct coordonnees propositionDeplacement[3],struct coordonnees positionDansEchiquier, int joueurQuiJoue);

int verificationConditionFin (int* causeFin, int emplacementPions[8][8],int joueurQuiJoue);
void issuePartie(SDL_Renderer* rendererWindow,int causeFin,int emplacementPions[8][8],struct Pseudo Nom[2],int dernierJoueurQuiAjoue);
int verificationCasEgalite(int emplacementPions[8][8],int joueurQuiJoue);

int menuSauvegarder(SDL_Renderer* rendererWindow,int emplacementPions[8][8], struct Pseudo Nom[2], int* causeFin);
void affichageMenuSauvegarder(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton);
int issueMenuSauvegarder(SDL_Renderer* rendererWindow,int emplacementPions[8][8], struct Pseudo Nom[2],int action,int* causeFin);

void sauvegardePartie(int emplacementPions[8][8], struct Pseudo Nom[2], int JoueurQuiJoue);

int ajoutTourEventuelPourSauvegarde(int numeroPartieEnregistree);

void ajouterVictoireDefaiteAStatistiques(struct Pseudo Nom[2], int joueurGagnant, int joueurPerdant);
void mettreNomEtVictoireDansTableau(struct Statistiques stats[50], int joueurGagnant,int joueurPerdant,struct Pseudo Nom[2]);
