struct Statistiques{
   char Pseudo[10];
   int NombreVictoireDefaite[2];
};

void menuPrincipal(SDL_Renderer* rendererWindow);
void remplirCaractTroisBouttons(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton);
void remplirCaractImageEtTexteIntro(SDL_Renderer* rendererWindow,SDL_Rect* caractImageTexteIntro);
void affichageMenuPrincipal(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton,SDL_Rect* caractImageTexteIntro);
int evenementMenuPrincipal(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton,SDL_Rect* caractImageTexteIntro);
int evenementMenuTroisBouttons(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton);
int actionEnFonctionCliqueMenuTroisBouttons(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton);
void issueMenuPrincipal(SDL_Renderer* rendererWindow, int Action);

void menuOptions(SDL_Renderer* rendererWindow);
void remplirCaractMenuOptions(SDL_Renderer* rendererWindow, SDL_Rect* CaractTexte);
void affichageMenuOptions(SDL_Renderer* rendererWindow, SDL_Rect* caractAffichage);
void mettreSigneSurDefinitionActuelle(SDL_Renderer* rendererWindow, SDL_Rect* CaractAffichage);
int evenementMenuOptions(SDL_Renderer* rendererWindow, SDL_Rect* CaractAffichage);
int actionCliqueMenuOptions(SDL_Renderer* rendererWindow, SDL_Rect* CaractAffichage,int* Action);
void IssueMenuOptions(SDL_Renderer* rendererWindow,int action);
void resetSauvegardes();
void changementDefinition(SDL_Renderer* rendererWindow,int x,int y);

void menuJouer(SDL_Renderer* rendererWindow);
void affichageMenuJouer(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton);
int evenementMenuJouer(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton);
void issueMenuJouer(SDL_Renderer* rendererWindow, int Action);

void menuNombredeJoueur(SDL_Renderer* rendererWindow);
void affichageMenuNombredeJoueur(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton);
void issueMenuNombredeJoueur(SDL_Renderer* rendererWindow, int Action);

void menuSelectionPseudo(SDL_Renderer* rendererWindow,int nombreDeJoueur);
void remplirCaractEmplacementAvatar(SDL_Renderer* rendererWindow,SDL_Rect* CaractAvatar);
void remplirCaractBouttonSelectionPseudo(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton);
void affichageMenuSelectionPseudo(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton,SDL_Rect* CaractAvatar);
void affichageAvatar(SDL_Renderer* rendererWindow,SDL_Rect* CaractAvatar);
int evenementMenuSelectionPseudo(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton, SDL_Rect* CaractAvatar,struct Pseudo Nom[2], int nombreDeJoueur);
int actionMOUSEBUTTONUPMenuSelectionPseudo(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton, SDL_Rect* CaractAvatar,struct Pseudo Nom[2],int nombreDeJoueur,int* NombrePseudoEntree,int* Avancement,int* Action,int* avatarSelectionne);
int verificationCliqueBouttonValiderMenuSelectionPseudo(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton,SDL_Rect* CaractAvatar,struct Pseudo Nom[2],int nombreDeJoueur,int* NombrePseudoEntree,int* Avancement,int* Action,int* avatarSelectionne);
void verificationCliqueSurPseudo(SDL_Renderer* rendererWindow,SDL_Rect* CaractAvatar, struct Pseudo Nom[2],int NombrePseudoEntree,int* avatarSelectionne);
void actualisationRectanglesAvatar(SDL_Renderer* rendererWindow,SDL_Rect* CaractAvatar,int AvatarSelectionne);
void modifierStructPseudoEnFonctionAvatar(struct Pseudo Nom[2],int NombrePseudoEntree,int avatarSelectionne);
void actionTEXTINPUTMenuSelectionPseudo(SDL_Renderer* rendererWindow,SDL_Event event, struct Pseudo Nom[2],int NombrePseudoEntree,int* Avancement);
void actionKEYDOWNMenuSelectionPseudo(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton, SDL_Event event,struct Pseudo Nom[2],int NombrePseudoEntree,int* Avancement);
void issueMenuMenuSelectionPseudo(SDL_Renderer* rendererWindow,struct Pseudo Nom[2],int Action);

int QuitterAppuieCroixOuEchap(SDL_Event event);
void PauseEnfonctionDureeExecution(Uint32 Timer);

void menuReprendrePartie(SDL_Renderer* rendererWindow);
void remplirCaractmenuReprendrePartie(SDL_Renderer* rendererWindow,SDL_Rect* caractBoutton);
void affichageMenuReprendrePartie(SDL_Renderer* rendererWindow,SDL_Rect* caractBoutton,FILE*fichierNom,int* nombrePartie);
void recuperationNomDesParties(FILE*fichier,char* nomPartie,int* nombrePartie);
int actionMenuReprendrePartie(SDL_Renderer* rendererWindow,SDL_Rect* caractBoutton,int nombrePartie);
int actionEnFonctionCliqueMenuReprendrePartie(SDL_Renderer* rendererWindow,SDL_Rect* CaractBoutton,int nombrePartie);
void issueMenuReprendrePartie(SDL_Renderer* rendererWindow,int action, struct Pseudo Nom[2]);
void recuperationNom(FILE* fichier, struct Pseudo Nom[2],int nombrePartie);

void menuStatistiques(SDL_Renderer* rendererWindow);
void remplirCaractMenuStatistiques(SDL_Renderer* rendererWindow, SDL_Rect caractGraphisme[8]);
void affichageTop5Victoire(SDL_Renderer* rendererWindow, struct Statistiques stats[50],SDL_Rect caractGraphisme[8]);
void affichageStatQuandPasDeFichier(SDL_Renderer* rendererWindow,SDL_Rect caractGraphisme[8]);
void remplirTop5(struct Statistiques stats[50],struct Statistiques top[10]);
int actionMenuStatistiques(SDL_Renderer* rendererWindow,SDL_Rect caractGraphismes[8]);
void issueMenuStatistiques(SDL_Renderer* rendererWindow, int action);
