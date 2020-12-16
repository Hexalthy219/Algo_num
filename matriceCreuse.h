typedef struct creuse_t Creuse;

Creuse **lecture(char *nom_fichier);

Creuse *produitMatriceVecteurDense(Creuse *A, float *vecteur);
unsigned int nombre_col(Creuse *A);
Creuse *produitMatriceVecteurCreux(Creuse *A, Creuse *x);