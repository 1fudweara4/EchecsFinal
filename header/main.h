#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


void initialisationSDL();

void initSDL();
void initSDLttf();
void initSDLimage();

void verrificationErreurFenetre(SDL_Window* window);
void verrificationErreurRenderer(SDL_Renderer* rendererWindow);

void finLibrairies();
