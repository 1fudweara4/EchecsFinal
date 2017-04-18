#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


struct coordonnees{
    int x;
    int y;
};

void initialisationSDL();

void initSDL();
void initSDLttf();
void initSDLimage();

void recuperationDeLaResolution(int* SCREEN_WIDTH,int* SCREEN_HEIGHT);

void verificationErreurFenetre(SDL_Window* window);
void verificationErreurRenderer(SDL_Renderer* rendererWindow);

void finLibrairies();
