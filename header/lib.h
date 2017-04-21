        /** LIBRAIRIES**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>



    /** STRUCTURES UTILISES PARTOUT **/

struct coordonnees{
    int x;
    int y;
};

struct Pseudo{
    char Nom[10];
    char avatar[50];
};

struct echiquier{
    int emplacementPions;
    int possibiliteAvancerDeDeux;
};
