#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


void initialisationSDL();

void initSDL();
void initSDLttf();
void initSDLimage();

void verificationErreurFenetre(SDL_Window* window);
void verificationErreurRenderer(SDL_Renderer* rendererWindow);

void finLibrairies();
