#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

void mettreFondEcranUni(SDL_Renderer* rendererWindow);
void Boutton(SDL_Renderer* rendererWindow, SDL_Rect CaractSurface,char* Texte);
void affichageImageBMP(SDL_Renderer* rendererWindow,SDL_Rect CaractSurface, char* NomImage);
void affichageImagePNG(SDL_Renderer* rendererWindow,SDL_Rect CaractSurface, char* NomImage);


void affichageTexte(SDL_Renderer* rendererWindow,char* Texte,int taille, SDL_Rect Position,int typeRendu,int couleurRendu);
SDL_Color choixCouleur(int couleurRendu);
SDL_Surface* creationTexte(int typeRendu,TTF_Font* Font,char* Texte,int taille,SDL_Color Couleur);
void fermetureSDLvariables(SDL_Surface* SurfaceText, TTF_Font *Font, SDL_Texture* texture);
