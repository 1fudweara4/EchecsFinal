
struct evaluationIA{
    int note;
    struct coordonnees meilleurDeplacementDuPion;

};

void lancementIA(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],int joueurQuiJoue,struct Pseudo Nom[2]);

void evaluationDesPossibilites(struct echiquier emplacementPions[8][8],struct evaluationIA evaluationPossibilites[8][8],int joueurQuiJoue);
void reinitilisationPropositionDeplacement(struct coordonnees propositionDeplacement[4]);
void generationDeLaNote(struct echiquier emplacementPions[8][8],struct evaluationIA evaluationPossibilites[8][8],int joueurQuiJoue,struct coordonnees emplacementInitial, struct coordonnees propositionDeplacement[4]);
void noteDeplacementHorizontaux(struct echiquier emplacementPions[8][8],struct evaluationIA evaluationPossibilites[8][8],int joueurQuiJoue,struct coordonnees emplacementInitial, struct coordonnees propositionDeplacement[4]);
void ajoutNoteSiPionPeuFinirPartie(struct coordonnees emplacementInitial,struct evaluationIA evaluationPossibilites[8][8],int joueurQuiJoue);

struct coordonnees selectionMeilleurePossibilite(struct evaluationIA evaluationPossibilites[8][8]);
void rechercheNoteMaxEtNombreIteration(struct evaluationIA evaluationPossibilites[8][8],int* noteMax, int* nombreNoteMax);
struct coordonnees selectionAuHasardPossibiliteAvecNoteMax(struct evaluationIA evaluationPossibilites[8][8],int noteMax,int nombreNoteMax);

void deplacementPionEnMeilleurePossibilite(SDL_Renderer* rendererWindow,struct echiquier emplacementPions[8][8],struct evaluationIA evaluationPossibilites[8][8],struct coordonnees meilleurDeplacement,int joueurQuiJoue);
