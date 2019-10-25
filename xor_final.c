#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef double RN_float;

typedef struct {
    RN_float *poids_lien;//poid synaptique , logique
    RN_float *neurone_val; // valeur neurone
    RN_float *valeur_erreur_neurone; //
    RN_float *neurone_entree;
    RN_float *neurone_sortie;
    RN_float *valeur_erreur_sortie;
    int *indexdescouches;
    int *tailledescouches;
    int *indexdesynapses;
    int nombredecouches;
    int nombredeneuronnes;
    int nombredesynapses;
    int tailledescouches_entree;
    int tailledescouches_sortie;
} RN;


static RN_float nombre_poids = 0.5f;
static RN_float nombre_apprentissage = 0.05f;



RN *_init_RN(int nombredecouches, int *tailledescouches) {

    RN *mon_reseau = malloc(sizeof * mon_reseau);//PENSER A FREE

    mon_reseau->nombredecouches = nombredecouches;
    mon_reseau->tailledescouches = malloc(sizeof * mon_reseau->tailledescouches * mon_reseau->nombredecouches);//PENSER A FREE
    mon_reseau->indexdescouches = malloc(sizeof * mon_reseau->indexdescouches * mon_reseau->nombredecouches);//PENSER A FREE

    int i;
    mon_reseau->nombredeneuronnes = 0;
    for (i = 0; i < nombredecouches; i++) {
        mon_reseau->tailledescouches[i] = tailledescouches[i];
        mon_reseau->indexdescouches[i] = mon_reseau->nombredeneuronnes;
        mon_reseau->nombredeneuronnes += tailledescouches[i];
    }

    mon_reseau->neurone_val = malloc(sizeof * mon_reseau->neurone_val * mon_reseau->nombredeneuronnes);
    mon_reseau->valeur_erreur_neurone = malloc(sizeof * mon_reseau->valeur_erreur_neurone * mon_reseau->nombredeneuronnes);

    mon_reseau->tailledescouches_entree = tailledescouches[0];
    mon_reseau->tailledescouches_sortie = tailledescouches[nombredecouches-1];
    mon_reseau->neurone_entree = mon_reseau->neurone_val;
    mon_reseau->neurone_sortie = &mon_reseau->neurone_val[mon_reseau->indexdescouches[nombredecouches-1]];
    mon_reseau->valeur_erreur_sortie = &mon_reseau->valeur_erreur_neurone[mon_reseau->indexdescouches[nombredecouches-1]];

    mon_reseau->indexdesynapses = malloc(sizeof * mon_reseau->indexdesynapses * (mon_reseau->nombredecouches-1));
    mon_reseau->nombredesynapses = 0;
    for (i = 0; i < nombredecouches - 1; i++) {
        mon_reseau->indexdesynapses[i] = mon_reseau->nombredesynapses;
        mon_reseau->nombredesynapses += (mon_reseau->tailledescouches[i]+1) * mon_reseau->tailledescouches[i+1];
    }

    mon_reseau->poids_lien = malloc(sizeof * mon_reseau->poids_lien * mon_reseau->nombredesynapses);

    for (i = 0; i < mon_reseau->nombredesynapses; i++) {
        mon_reseau->poids_lien[i] = nombre_poids * (RN_float)rand() / RAND_MAX - nombre_poids/2;

    }
    return mon_reseau;
}

void free_RN (RN *mon_reseau) {
    free(mon_reseau->tailledescouches);
    free(mon_reseau->indexdescouches);
    free(mon_reseau->neurone_val);
    free(mon_reseau->valeur_erreur_neurone);
    free(mon_reseau->indexdesynapses);
    free(mon_reseau->poids_lien);
    free(mon_reseau);
}


void start_RN (RN * mon_reseau, RN_float *vecteur) {
    if (vecteur != NULL) {
        int i;
        for (i = 0; i < mon_reseau->tailledescouches_entree; i++) {
            mon_reseau->neurone_entree[i] = vecteur[i];
        }
    }
    int i;
    int indexdesynapses;
    indexdesynapses = 0;
    for (i = 1; i < mon_reseau->nombredecouches; i++) {
        int j;
        for (j = mon_reseau->indexdescouches[i]; j < mon_reseau->indexdescouches[i] + mon_reseau->tailledescouches[i]; j++) {
            RN_float somme_ponderee = 0.0;
            int k;
            for (k = mon_reseau->indexdescouches[i-1]; k < mon_reseau->indexdescouches[i-1] + mon_reseau->tailledescouches[i-1]; k++) {
                somme_ponderee += mon_reseau->neurone_val[k] * mon_reseau->poids_lien[indexdesynapses];
                indexdesynapses++;
            }
            somme_ponderee += mon_reseau->poids_lien[indexdesynapses];
            indexdesynapses++;
            mon_reseau->neurone_val[j] = somme_ponderee;
            if (i != mon_reseau->nombredecouches - 1) mon_reseau->neurone_val[j] = tanh(mon_reseau->neurone_val[j]);
            //mon_reseau->neurone_val[j] = 1.0 / (exp(-somme_ponderee) + 1.0);
        }
    }
}


void get_RN (RN *mon_reseau, RN_float *vecteur) {
    int i;
    for (i = 0; i < mon_reseau->tailledescouches_sortie; i++) {
        vecteur[i] = mon_reseau->neurone_sortie[i];
    }
}

void Aprrentisage_RN (RN *mon_reseau, RN_float *Sortie_souhaitée) {


    int i;
    //RN_float marge_erreur = 0;
    int indexdesynapses = mon_reseau->indexdesynapses[mon_reseau->nombredecouches-2];

    for (i = 0; i < mon_reseau->tailledescouches_sortie; i++) {
        mon_reseau->valeur_erreur_sortie[i] = mon_reseau->neurone_sortie[i] - Sortie_souhaitée[i];
        //printf(" %d = %f \n", 7, mon_reseau->valeur_erreur_neurone[7]);
        int j;
        for (j = mon_reseau->indexdescouches[mon_reseau->nombredecouches-2]; j < mon_reseau->indexdescouches[mon_reseau->nombredecouches-2] + mon_reseau->tailledescouches[mon_reseau->nombredecouches-2]; j++) {
            RN_float weightChange;
            weightChange = nombre_apprentissage * mon_reseau->valeur_erreur_sortie[i] * mon_reseau->neurone_val[j];
            mon_reseau->poids_lien[indexdesynapses] -= weightChange;

            if (mon_reseau->poids_lien[indexdesynapses] > 5)
            	mon_reseau->poids_lien[indexdesynapses] = 5;
            if (mon_reseau->poids_lien[indexdesynapses] < -5)
            	mon_reseau->poids_lien[indexdesynapses] = -5;

            indexdesynapses++;
        }
        RN_float weightChange;
        weightChange = nombre_apprentissage * mon_reseau->valeur_erreur_sortie[i];
        mon_reseau->poids_lien[indexdesynapses] -= weightChange;

        if (mon_reseau->poids_lien[indexdesynapses] > 5)
        	mon_reseau->poids_lien[indexdesynapses] = 5;
        if (mon_reseau->poids_lien[indexdesynapses] < -5)
        	mon_reseau->poids_lien[indexdesynapses] = -5;

        indexdesynapses++;
    }


    for (i = mon_reseau->nombredecouches - 2; i > 0; i--) {
        int j;
        int jj= 0;
        int indexdesynapses = mon_reseau->indexdesynapses[i-1];
        for (j = mon_reseau->indexdescouches[i]; j < mon_reseau->indexdescouches[i] + mon_reseau->tailledescouches[i]; j++,jj++) {
            int k;

            int indexdesynapses2 = mon_reseau->indexdesynapses[i] + jj;
            mon_reseau->valeur_erreur_neurone[j] = 0;
            for (k = mon_reseau->indexdescouches[i+1]; k < mon_reseau->indexdescouches[i+1] + mon_reseau->tailledescouches[i+1]; k++) {
                mon_reseau->valeur_erreur_neurone[j] += mon_reseau->poids_lien[indexdesynapses2] * mon_reseau->valeur_erreur_neurone[k];
                indexdesynapses2+=mon_reseau->tailledescouches[i]+1;
            }
            //printf(" %d = %f \n", j, mon_reseau->valeur_erreur_neurone[j]);


            for (k = mon_reseau->indexdescouches[i-1]; k < mon_reseau->indexdescouches[i-1] + mon_reseau->tailledescouches[i-1]; k++) {

                RN_float weightChange;

                weightChange = 1.0 - mon_reseau->neurone_val[j] * mon_reseau->neurone_val[j];
                //weightChange *= mon_reseau->poids_lien[12+jj] * mon_reseau->valeur_erreur_sortie[0] * nombre_apprentissage;
                weightChange *= mon_reseau->valeur_erreur_neurone[j] * nombre_apprentissage;
                //printf(" %d = %f  bis\n", j, mon_reseau->poids_lien[12+jj] * mon_reseau->valeur_erreur_sortie[0]);
                weightChange *= mon_reseau->neurone_val[k];

                mon_reseau->poids_lien[indexdesynapses] -= weightChange;
                indexdesynapses++;
            }
            RN_float weightChange;

            weightChange = 1.0 - mon_reseau->neurone_val[j] * mon_reseau->neurone_val[j];
            weightChange *= mon_reseau->valeur_erreur_neurone[j] * nombre_apprentissage;
            mon_reseau->poids_lien[indexdesynapses] -= weightChange;
            indexdesynapses++;
            /*for (int i = 0; i < mon_reseau->nombredeneuronnes; i++)
                printf("%f\n",mon_reseau->poids_lien[i]);*/
        }
    }
}


int main() {
    srand(time(NULL));
    int tailledescouches[] = {2, 4, 1};
    int mini = 100000000, maxi = 0;
    int g;
    int nbessai = 1000;
	//printf("debut des %d essais pour voir combien d'iterations sont necessaires pour faire un XOR\n", nbessai);
    for (g=0; g < nbessai; g++) {
        //printf("%d\n",g);
        RN * mon_reseau = _init_RN (3, tailledescouches);

        RN_float data2[4][3] = {
            {0, 0,  0},
            {0, 1,   1},
            {1, 0,   1},
            {1, 1,  0}
        };

        int i = 0;
        RN_float marge_erreur = 1;
        float marge_erreur_wanted = 0.05;
        /*if (g == 1) // La marge d'erreur que on veut 
            printf("Marge d'erreur souhaitée : %f\n", marge_erreur_wanted);*/
        while (marge_erreur > marge_erreur_wanted) {
            //if (marge_erreur < 0.0000000000000004) break; //nombre_apprentissage = 0.00001;

            int k;
            int iter;

            for (iter=0; iter < 100; iter++) {
                k = 4.0*rand()/(RAND_MAX+1.0);
                start_RN(mon_reseau,&data2[k][0]);
                Aprrentisage_RN(mon_reseau,&data2[k][2]);
            }

            marge_erreur = 0;
            for (k=0; k < 4; k++) {
                start_RN(mon_reseau,&data2[k][0]);
                marge_erreur += (data2[k][2] - mon_reseau->neurone_sortie[0]) * (data2[k][2] - mon_reseau->neurone_sortie[0]);
            }

            marge_erreur *= 0.25; // marge_erreur /= 4;
            marge_erreur = sqrt(marge_erreur);
            //printf("error: %.40f\n",marge_erreur);
            i++;
        }
        if (i > maxi ) maxi = i;
        if (i < mini ) mini = i;

        if (g == nbessai - 1) { // Print des resultats pour le dernier essai
			printf("DERNIER ESSAI\n ------- \n");
			RN_float data[4];
			RN_float data4;
			data[2] = 0;
			data[0] = 0; data[1] = 0;
			start_RN(mon_reseau,data); get_RN(mon_reseau,&data4);
			printf(" %f\t %f\t %f\t %.40f\n", data[0], data[1], data[2], data4);
            //printf(" %d\t %d\t %d\t %f\t %.40f\n", 0, 0, 0,1-data4 ,data4);
			data[0] = 0; data[1] = 1;
            data[2] = 1;
			start_RN(mon_reseau,data); get_RN(mon_reseau,&data4);
			printf(" %f\t %f\t %f\t %.40f\n", data[0], data[1], data[2], data4);
            //printf(" %d\t %d\t %d\t %f\t %.40f\n", 0, 1, 1,1-data4, data4);
			data[0] = 1; data[1] = 0;
            data[2] = 1;
			start_RN(mon_reseau,data); get_RN(mon_reseau,&data4);
			printf(" %f\t %f\t %f\t %.40f\n", data[0], data[1], data[2], data4);
            //printf(" %d\t %d\t %d\t %f\t %.40f\n", 1, 0, 1,1-data4, data4);

			data[0] = 1; data[1] = 1;
            data[2] = 0;
			start_RN(mon_reseau,data); get_RN(mon_reseau,&data4);
			printf(" %f\t %f\t %f\t %.40f\n", data[0], data[1], data[2], data4);
            //printf(" %d\t %d\t %d\t %f\t %.40f\n", 1, 1, 0,1-data4, data4);
		}
		free_RN(mon_reseau);
    }
	//printf("\nnombre d'aprrentissages:\n");
    //printf( "mininimum d'iterations: %d maximum d'iterations: %d\n",mini*100, maxi*100);
    //printf("Marge d'erreur :%f\n", marge_erreur);
    return 0;
}
