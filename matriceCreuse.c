#include <stdlib.h>
#include <stdio.h>
#include "matriceCreuse.h"



struct creuse_t{
    unsigned int *startCol;
    unsigned int *row;
    float *values;
    unsigned int nz;
};

static void swap(unsigned int *array, int a, int b){
    unsigned int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

static int partition(unsigned int *array, int p, int r)
{
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (array[j] <= array[r])
        {
            i++;
            swap(array, i, j);
        }
    }
    swap(array, i + 1, r);

    return i + 1;
}

static int partition2(unsigned int *array1, unsigned int *array2, int p, int r){
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (array1[j] <= array1[r])
        {
            i++;
            swap(array1, i, j);
            swap(array2, i, j);
        }
    }
    swap(array1, i + 1, r);
    swap(array2, i + 1, r);

    return i + 1;
}
static void quicksort(unsigned int *array, int p, int r)
{
    int position_pivot;
    if (p < r)
    {
        position_pivot = partition(array, p, r);
        quicksort(array, p, position_pivot - 1);
        quicksort(array, position_pivot + 1, r);
    }
}

static void quicksort2(unsigned int *array1, unsigned int *array2, int p, int r){
    int position_pivot;
    if (p < r)
    {
        position_pivot = partition2(array1, array2, p, r);
        quicksort2(array1, array2, p, position_pivot - 1);
        quicksort2(array1, array2, position_pivot + 1, r);
    }
}

Creuse **lecture(char* nom_fichier){
    unsigned int *tampon1 = malloc(sizeof(int) * 66965);
    unsigned int *tampon2 = malloc(sizeof(int) * 66965);
    unsigned int indice = 0;
    size_t taille = 66965;
    size_t i = 0;
    FILE *fichier = fopen(nom_fichier, "r");
    if(!fichier)
        return NULL;

    unsigned int tampon ;

    while (fscanf(fichier, "%u", &tampon)!= EOF)
    {
        if(i == taille){
            taille*=2;
            tampon1 = realloc(tampon1, sizeof(unsigned int)*taille);
            if(!tampon1)
                return NULL;
            tampon2 = realloc(tampon2, sizeof(unsigned int)*taille);
            if (!tampon2)
                return NULL;
        }
        tampon1[i] = tampon;
        if(fscanf(fichier, "%u", &tampon) == EOF)
            return NULL;

        tampon2[i] = tampon;

        if(fscanf(fichier, "%u", &tampon) == EOF)
            return NULL;
        
        indice = tampon;
        if(indice == 2){
            indice = tampon1[i];
            tampon1[i] = tampon2[i];
            tampon2[i] = indice;
        }

        i++;

    }
    fclose(fichier);
    quicksort2(tampon1, tampon2, 0, i-1);
    unsigned int nombre_colonne = 0;
    tampon = tampon1[0];
    for(size_t j = 1; j<i; j++){
        if(tampon != tampon1[j])
            nombre_colonne++;
        tampon = tampon1[j];
    }

        
    Creuse *matrice1 = malloc(sizeof(Creuse));
    matrice1->nz = i;
    matrice1->startCol = malloc(sizeof(unsigned int)*nombre_colonne);
    matrice1->row = malloc(sizeof(unsigned int)*i);
    matrice1->values = malloc(sizeof(float)*i);
    matrice1->startCol[0] = 0;
    tampon = tampon1[0]; 
    unsigned int add=1;
    unsigned int compteur=1;
    for(unsigned int k = 1; k<i; k++){
        if(tampon!= tampon1[k]){
            matrice1->startCol[compteur] = add;
            compteur++;
            
        }
        add++;
        tampon = tampon1[k];

    }

    for(unsigned int j = 0; j<i; j++)
        tampon1[j] = tampon2[j];
    quicksort(tampon1,0,i-1);

    // for(size_t j = 1; j<i; j++){
    //     if(tampon1[j-1] == tampon1[j]){
    //         pos=j;
    //         while (j < i&&tampon1[j - 1] == tampon1[j])
    //         {
    //             j++;
    //             tri--;
    //         }
    //         tampon1[pos] = tampon1[j];
    //         pre_pos= pos +1;
    //     }
    // }

    unsigned int max = i-1;
    unsigned int min = 0;
    for(size_t j = 0; j<i;j++){
        compteur=i/2;
        max = i+1;
        min = 0;
        while(tampon1[compteur]!=tampon2[j]){
            if(tampon1[compteur]>tampon2[j])
                max = compteur;
            else
                min = compteur;
            compteur = (max + min)/2;
        }
        matrice1->row[j]=compteur;
    }

    float diff=0;
    add=0;
    unsigned int k;
    for(k = 1; k<nombre_colonne; k++){
        diff = matrice1->startCol[k]- matrice1->startCol[k-1];
        for(float j = 0; j<diff; j++){
            matrice1->values[k-1+add] = 1/diff;
            add++;
        }
        add--;
    }

    diff = i-k-add+1;
    for(unsigned int j = 0; j<diff; j++){
        matrice1->values[k-1+add+j]= 1/diff;
    }

    Creuse *matrice2 = malloc(sizeof(Creuse));
    matrice2->nz = i;
    // matrice2->startCol = malloc(sizeof(unsigned int) * nombre_colonne);
    // matrice2->row = malloc(sizeof(unsigned int) * i);
    // matrice2->values = malloc(sizeof(float) * i);
    // for(unsigned int b = 0; b<i;b++){
    //     matrice2->values[b] = 1;
    //     matrice2->row[b] = matrice1->row[b];
    // }
    // for (unsigned int b = 0; b < nombre_colonne; b++)
    //     matrice2->startCol[b]=matrice1->startCol[b];

    Creuse **tableau_matrice = malloc(sizeof(Creuse)*2);
    tableau_matrice[0] = matrice1;
    tableau_matrice[1] = matrice2;


    free(tampon1);
    free(tampon2);

    return tableau_matrice;
}


unsigned int nombre_col(Creuse *A){
    unsigned int taille_col = 0;
    unsigned int diff = A->startCol[1] - A->startCol[0];
    unsigned int pos_prec = 0;

    for (unsigned int i = 0; i < A->nz; i++)
    {
        if (diff == i - pos_prec)
        {
            taille_col++;
            diff = A->startCol[taille_col + 1] - A->startCol[taille_col];
            pos_prec = i;
        }
    }
    return taille_col +1;
}

Creuse *produitMatriceVecteurDense(Creuse *A, float *vecteur){
    unsigned int taille_vecteur = nombre_col(A);
    unsigned int add = 0;
    float *vecteur_y = malloc(sizeof(float)*taille_vecteur);

    unsigned int dif = A->startCol[1] - A->startCol[0];
    for(unsigned int i = 1; i<taille_vecteur; i++){
        for(unsigned int j = 0; j<dif; j++){
            vecteur_y[A->row[add]]+= A->values[A->row[add]]*vecteur[i-1];
            add++;
        }
        
        if(i!=taille_vecteur-1)
            dif = A->startCol[i+1] - A->startCol[i];
    }
    return vecteur_y;
}

// Creuse *produitMatriceVecteurCreux(Creuse *A, Creuse *x){
//     unsigned int taille_vecteur = nombre_col(A);
//     unsigned int add = 0;
//     Creuse *vecteur_y = malloc(sizeof(Creuse));
//     unsigned int dif = A->startCol[1] - A->startCol[0];

//     for (unsigned int i = 1; i < taille_vecteur; i++)
//     {
//         for (unsigned int j = 0; j < dif; j++)
//         {
//             vecteur_y += A->values[A->row[add]] * vecteur[i - 1];
//             add++;
//         }

//         if (i != taille_vecteur - 1)
//             dif = A->startCol[i + 1] - A->startCol[i];
//     }
// }