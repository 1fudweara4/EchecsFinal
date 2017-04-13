#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

struct coordonnees{
    int x;
    int y;
};

void mettreFondEcranUni(SDL_Renderer* rendererWindow);
void Boutton(SDL_Renderer* rendererWindow, SDL_Rect CaractSurface,char* Texte);
void affichageImageBMP(SDL_Renderer* rendererWindow,SDL_Rect CaractSurface, char* NomImage);
void affichageImagePNG(SDL_Renderer* rendererWindow,SDL_Rect CaractSurface, char* NomImage);
void affichageTexte(SDL_Renderer* rendererWindow,char* Texte,int taille, SDL_Rect Position);
