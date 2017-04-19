#include "header/lib.h"
#include"header/outils.h"

void mettreFondEcranUni(SDL_Renderer* rendererWindow){
    struct coordonnees tailleFenetre;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);
    SDL_Rect caract={0,0,tailleFenetre.x,tailleFenetre.x};

    affichageImagePNG(rendererWindow,caract,"DAT/Image/fondEcran.jpg");
    SDL_RenderPresent(rendererWindow);
}

void Boutton(SDL_Renderer* rendererWindow, SDL_Rect CaractSurface,char* Texte){

    struct coordonnees tailleFenetre;
    SDL_GetRendererOutputSize(rendererWindow,&tailleFenetre.x,&tailleFenetre.y);
    SDL_Surface* SurfaceText=NULL;
    SDL_Color Couleur={1,1,1};
    TTF_Font *Police = NULL;
    SDL_Texture* textureTexte;

    if(strcmp(Texte,"")!=0){
        Police = TTF_OpenFont("DAT/chesterfield.ttf",50);
        SurfaceText = TTF_RenderText_Solid(Police, Texte, Couleur);

        SDL_SetRenderDrawColor(rendererWindow,204, 204, 255,255);
        SDL_RenderFillRect(rendererWindow,&CaractSurface);

        SDL_SetRenderDrawColor(rendererWindow,1, 1, 1,255);
        SDL_RenderDrawRect(rendererWindow,&CaractSurface);
        textureTexte=SDL_CreateTextureFromSurface(rendererWindow, SurfaceText);

        CaractSurface.x=(CaractSurface.x+((CaractSurface.w)-(SurfaceText->w))/2);
        CaractSurface.y=(CaractSurface.y+((CaractSurface.h)-(SurfaceText->h))/2);
        CaractSurface.w=SurfaceText->w;
        CaractSurface.h=SurfaceText->h;

        SDL_RenderCopy(rendererWindow,textureTexte,NULL ,&CaractSurface);

        printf("Boutton %s fait\n",Texte);
    }
    else{
        printf("Texte non défini, erreur!\n");
    }

    SDL_FreeSurface(SurfaceText);
    TTF_CloseFont(Police);
    SDL_DestroyTexture(textureTexte);
    SurfaceText=NULL;
    Police=NULL;
    textureTexte=NULL;
}

void affichageImageBMP(SDL_Renderer* rendererWindow,SDL_Rect CaractSurface, char* NomImage){

    SDL_Surface* Surface=NULL;
    SDL_Texture *TextureImage;

    if(NomImage!=NULL){
        Surface=SDL_LoadBMP(NomImage);

        TextureImage = SDL_CreateTextureFromSurface(rendererWindow, Surface);
        SDL_RenderCopy(rendererWindow,TextureImage,NULL,&CaractSurface);

        SDL_DestroyTexture(TextureImage);
        SDL_FreeSurface(Surface);
        Surface=NULL;
        TextureImage=NULL;
        printf("Affichage %s : ok\n", NomImage);
    }
    else{
        printf("Erreur nom d'image non défini\n");
    }
}

void affichageImagePNG(SDL_Renderer* rendererWindow,SDL_Rect CaractSurface, char* NomImage){
    SDL_Surface* imageChargee = IMG_Load(NomImage);
    SDL_Texture *TextureImage;

    if(imageChargee==NULL){
        printf("Impossible de charger l'image %s! SDL_image Error: %s\n",NomImage, IMG_GetError());
    }
    else{
        TextureImage = SDL_CreateTextureFromSurface(rendererWindow, imageChargee);
        SDL_RenderCopy(rendererWindow,TextureImage,NULL,&CaractSurface);
        SDL_DestroyTexture(TextureImage);
        TextureImage=NULL;
        SDL_FreeSurface(imageChargee);
        imageChargee=NULL;
        printf("Affichage %s : ok\n", NomImage);
    }
}

void affichageTexte(SDL_Renderer* rendererWindow,char* Texte,int taille, SDL_Rect Position,int typeRendu,int couleurRendu){

    SDL_Surface* SurfaceText=NULL;
    SDL_Texture* texture;
    TTF_Font *Font = NULL;
    SDL_Color Couleur;

    Couleur=choixCouleur(couleurRendu);

    if(strcmp(Texte,"")==0){
        printf("Erreur texte non défini\n");
    }
    else{
        SurfaceText=creationTexte(typeRendu,Font,Texte,taille,Couleur);
        texture = SDL_CreateTextureFromSurface(rendererWindow, SurfaceText);

        Position.w=SurfaceText->w;
        Position.h=SurfaceText->h;
        Position.x=Position.x-(Position.w/2);
        Position.y=Position.y-(Position.h/2);

        SDL_RenderCopy(rendererWindow,texture,NULL ,&Position);
        printf("Texte '%s' affiché\n",Texte);

        fermetureSDLvariables(SurfaceText,Font,texture);
    }
}

SDL_Color choixCouleur(int couleurRendu){

    SDL_Color couleur;

    if(couleurRendu==1){
        couleur.r=couleur.g=couleur.b=1;
    }
    else{
        couleur.r=couleur.g=couleur.b=255;
    }
    return couleur;
}

SDL_Surface* creationTexte(int typeRendu,TTF_Font* Font,char* Texte,int taille,SDL_Color Couleur){

    SDL_Surface* surfaceText;
    Font = TTF_OpenFont("DAT/chesterfield.ttf",taille);

    if(typeRendu==0){
        surfaceText = TTF_RenderText_Solid(Font, Texte, Couleur);
    }
    else{
        SDL_Color Fond={187, 174, 152};
        surfaceText = TTF_RenderText_Shaded(Font, Texte, Couleur,Fond);
    }

    return surfaceText;

}

void fermetureSDLvariables(SDL_Surface* SurfaceText, TTF_Font *Font, SDL_Texture* texture){
    SDL_FreeSurface(SurfaceText);
    TTF_CloseFont(Font);
    SDL_DestroyTexture(texture);
    Font = NULL;
    SurfaceText=NULL;
    texture=NULL;
}

