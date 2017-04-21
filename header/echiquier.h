void lancementEchiquier(SDL_Renderer* rendererWindow,struct Pseudo Nom[2],int numeroPartieEnregistree);

void initalisationEchiquier(struct echiquier emplacementPions[8][8],int numeroPartieEnregistree);
void premierRemplissageTableauEchiquier(struct echiquier emplacementPions[8][8]);
void remplirPossibiliteAvancerDeDeux(struct echiquier emplacementPions[8][8]);
void recuperationEchiquiersauvegarde(struct echiquier emplacementPions[8][8],int numeroPartieEnregistree);

void affichagePartieEchiquier(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],struct Pseudo Nom[2],int joueurQuiJoue);
void affichageEchiquierEtPions(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8]);
void affichageCaseCouleurEnFonctionPosition(SDL_Renderer* rendererWindow,int x,int y);
void affichagePions(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],int x,int y);
void affichagePseudoEtNbPions(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],struct Pseudo Nom[2],int joueurQuiJoue);

void remplirCaractAvatar(SDL_Renderer* rendererWindow, SDL_Rect* caractAvatar);
void affichageCarreBlanc(SDL_Renderer* rendererWindow);
void affichageAvatarEnJeu(SDL_Renderer* rendererWindow,struct Pseudo Nom[2],SDL_Rect* caractAvatar);
void affichagePseudo(SDL_Renderer*rendererWindow,struct Pseudo Nom[2]);
void affichageNombreDePions(SDL_Renderer*rendererWindow,struct echiquier emplacementPions[8][8]);
void entourerAvatarEnFonctionTour(SDL_Renderer* rendererWindow, SDL_Rect* caractAvatar, int joueurQuiJoue);


int compterNbPions(struct echiquier emplacementPions[8][8],int Couleur);

void lancementPartie(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],struct Pseudo Nom[2],int numeroPartieEnregistree);
void deroulementDuTour(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],struct Pseudo Nom[2],int joueurQuiJoue,int* causeFin,int* dernierJoueurQuiAjoue);

void actionDuJoueur(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],int joueurQuiJoue,int* causeFin,struct Pseudo Nom[2]);
int actionPremierCLique(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],int joueurQuiJoue,int* causeFin);

struct coordonnees detectionEmplacementDuCliqueDansEchiquier(SDL_Renderer* rendererWindow);
void generationPropositionDeplacement(struct echiquier emplacementPions[8][8],struct coordonnees positionDansEchiquier, struct coordonnees propositionDeplacement[4],int joueurQuiJoue);
void affichagePropositionDeplacement(SDL_Renderer* rendererWindow,struct coordonnees propositionDeplacement[4]);

int verificationSiIlyaPossibilites(struct coordonnees propositionDeplacement[4]);
int actionsDeplacement(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],struct coordonnees propositionDeplacement[4],struct coordonnees positionDansEchiquier,int joueurQuiJoue, int* causeFin);
int evenementCliqueDemandeProposition(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],struct coordonnees propositionDeplacement[4],struct coordonnees positionDansEchiquier,int joueurQuiJoue);
void SuppressionPropositionsDeplacement(SDL_Renderer* rendererWindow,struct coordonnees propositionDeplacement[4], struct echiquier emplacementPions[8][8]);
void deplacementPion(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8], struct coordonnees propositionDeplacement[4],struct coordonnees positionDansEchiquier, int joueurQuiJoue);

int verificationConditionFin (int* causeFin, struct echiquier emplacementPions[8][8],int joueurQuiJoue);
void verificationSiJoueurGagnant(struct echiquier emplacementPions[8][8],int* causeFin,int* Quitter);
void issuePartie(SDL_Renderer* rendererWindow,int causeFin,struct echiquier emplacementPions[8][8],struct Pseudo Nom[2],int dernierJoueurQuiAjoue);
int verificationCasEgalite(struct echiquier emplacementPions[8][8],int joueurQuiJoue);

int menuSauvegarder(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8], struct Pseudo Nom[2], int* causeFin,int joueurQuiJoue);
void affichageMenuSauvegarder(SDL_Renderer* rendererWindow, SDL_Rect* CaractBoutton);
int issueMenuSauvegarder(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8], struct Pseudo Nom[2],int action,int* causeFin,int joueurQuiJoue);

void sauvegardePartie(struct echiquier emplacementPions[8][8], struct Pseudo Nom[2], int JoueurQuiJoue);

int ajoutTourEventuelPourSauvegarde(int numeroPartieEnregistree);

void ajouterVictoireDefaiteAStatistiques(struct Pseudo Nom[2], int joueurGagnant, int joueurPerdant);
void mettreNomEtVictoireDansTableau(struct Statistiques stats[50], int joueurGagnant,int joueurPerdant,struct Pseudo Nom[2]);
void ajoutVictoireDefaiteSiNomPresentDansLeFichier(struct Statistiques stats[50], int joueurGagnant,int joueurPerdant,struct Pseudo Nom[2],int correspondance[2]);
void ajoutVictoireDefaiteSiNomPasPresentDansLeFichier(struct Statistiques stats[50], int joueurGagnant,int joueurPerdant,struct Pseudo Nom[2], int correspondance[2]);

void menuFinDePartie(SDL_Renderer* rendererWindow,char* couleurGagnante);
void remplirCaractMenuFinDePartie(SDL_Renderer* rendererWindow, SDL_Rect* caractObjet);
void affichageMenuFinDePartie(SDL_Renderer* rendererWindow,SDL_Rect* caractObjet,char* couleurGagnante);
int actionMenuFinDePartie(SDL_Rect* caractObjet);
void issueMenuFinDePartie(SDL_Renderer* rendererWindow,int action);
