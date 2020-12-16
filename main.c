#include "matriceCreuse.h"
#include <stdlib.h>
#include <stdio.h>

struct creuse_t
{
    unsigned int *startCol;
    unsigned int *row;
    float *values;
    unsigned int nz;
};

int main(int argc, char *argv[])
{
    char* nom_fichier = argv[1];


    Creuse **matrice = lecture(nom_fichier);

    unsigned int taille = nombre_col(matrice[0]);
    float *vecteur = malloc(sizeof(float)*taille);
    
    // // printf("%u\n",matrice[0]->nz);
    // printf("L: ");
    // for(int i = 0; i<7; i++)
    //     printf("%u ", matrice[0]->row[i]);
    // printf("\n");


    produitMatriceVecteurDense(matrice[0], vecteur);
    free(matrice[0]->row);
    free(matrice[0]->startCol);
    free(matrice[0]->values);
    free(matrice[0]);
    free(matrice[1]);
    free(vecteur);
    // free(matrice[1]->row);
    // free(matrice[1]->startCol);
    // free(matrice[1]->values);
    free(matrice);

    return 0;
}
