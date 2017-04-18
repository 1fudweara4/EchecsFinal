#include "header/main.h"
#include"header/menus.h"

int main(int argc, char** args){

    SDL_Window* window = NULL;
    SDL_Renderer* rendererWindow=NULL;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

    initialisationSDL();
    recuperationDeLaResolution(&SCREEN_WIDTH,&SCREEN_HEIGHT);
    window=SDL_CreateWindow("L'échec ou la réussite ?", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    verificationErreurFenetre(window);
    rendererWindow = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    verificationErreurRenderer(rendererWindow);

    menuPrincipal(rendererWindow);

    SDL_DestroyRenderer(rendererWindow);
    SDL_DestroyWindow(window);

    finLibrairies();// Fermeture librairies

    return EXIT_SUCCESS;
}

void initialisationSDL(){ //Initialisation SDL + extensions TTF et image

    initSDL();
    initSDLttf();
    initSDLimage();
}

void initSDL(){ // Init SDL

    if(SDL_Init(SDL_INIT_VIDEO)<0) {
		printf("SDL n'a pas reussi à se lancer. SDL_Error: %s\n", SDL_GetError());
    }
    else{
        printf("Lancement de la libraire SDL : OK\n");
    }
}

void initSDLttf(){ //Init SDL true type font

    if(TTF_Init()==-1){
        printf("Erreur lors de l'initialisation de SDL_ttf. SDL_ttf Error: %s\n",TTF_GetError());
    }
    else{
        printf("Lancement de la libraire SDL_ttf : OK\n");
    }
}

void initSDLimage(){ //Init SDL image

    if(!(IMG_Init(IMG_INIT_PNG)) && !(IMG_Init(IMG_INIT_JPG)) ){
        printf("Erreur lors de l'initialisation de SDL_image. SDL_image Error: %s\n",TTF_GetError());
    }
    else{
        printf("Lancement de la libraire SDL_image : OK\n");
    }
}

void recuperationDeLaResolution(int* SCREEN_WIDTH,int* SCREEN_HEIGHT){
    FILE* fichierDefinition=fopen("DAT/settings.dat","r");
    struct coordonnees tailleFenetre;
    if(fichierDefinition==NULL){
        *SCREEN_WIDTH=640;
        *SCREEN_HEIGHT=480;
    }
    else{
        fread(&tailleFenetre,sizeof(struct coordonnees),1,fichierDefinition);
        *SCREEN_WIDTH=tailleFenetre.x;
        *SCREEN_HEIGHT=tailleFenetre.y;
    }
}

void verificationErreurFenetre(SDL_Window* window){ // Vérification erreur Fenetre

    if( window == NULL ){
        printf("La fenetre n'a pas pu être créee. SDL_Error: %s\n",SDL_GetError());
    }
    else{
        printf("Fenetre : OK\n");
    }

    SDL_Delay(100);
}

void verificationErreurRenderer(SDL_Renderer* rendererWindow){ //Verification erreur renderer

    if(rendererWindow == NULL){
        printf("Erreur lors de la creation d'un renderer : %s\n",SDL_GetError());
    }

    else{
        printf("Initialisation renderer : OK\n\n");
    }

    SDL_Delay(100);
}

void finLibrairies(){ // Fermeture SDL + extensions

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
