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

void Aprrentisage_RN (RN *mon_reseau, RN_float *Sortie_souhaitee) {


    int i;
    //RN_float marge_erreur = 0;
    int indexdesynapses = mon_reseau->indexdesynapses[mon_reseau->nombredecouches-2];

    for (i = 0; i < mon_reseau->tailledescouches_sortie; i++) {
        mon_reseau->valeur_erreur_sortie[i] = mon_reseau->neurone_sortie[i] - Sortie_souhaitee[i];
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

RN_float conv(char * s) {
    RN_float sum = 0;
    sum = (s[7]-48) + 2*(s[6]-48) + 4*(s[5]-48) + 8*(s[4]-48) + 16*(s[3]-48) + 32*(s[2]-48) + 64*(s[1]-48) + 128*(s[0]-48);
    return sum/255;
}



int main() {
    srand(time(NULL));
    int tailledescouches[] = {256, 306, 26};
    int nbcouches = 3;
    RN * mon_reseau = _init_RN (nbcouches, tailledescouches);


    FILE* file ;
    file = fopen("alphabet.txt" , "r");
    RN_float data3[256];
    RN_float data4[26];
    char s[8] ="";

    for (int iter=0; iter < 1000; iter++) {
        for(int i = 0; i<26; i++) {
            data4[i] = 0;
        }
        //int m = rand() % 27;
        fseek(file, 2050 , SEEK_SET);

        for(int i=0; i<256 ; i++) {
            fgets(s, 9, file);
            //printf("%s\n", s);
            data3[i] = conv(s);
            //printf("%lf\n", data3[i]);
            //printf("%lf\n", data3[i]);
            //while (fgetc(file) !=',')
            //    fseek(file, 1, SEEK_CUR);
            //fseek(file, 1, SEEK_CUR);
        }
        //data4[m] = 1;
        start_RN(mon_reseau,data3);
        Aprrentisage_RN(mon_reseau,data4);
    }

    printf("DERNIER ESSAI\n ------- \n");

    int m = rand() % 27;
    fseek(file, 2050 , SEEK_SET);

    for(int i=0; i<256 ; i++) {
        fgets(s, 9, file);
        //printf("%s %d\n", s, 8*i);
        data3[i] = conv(s);
        //printf("%lf\n", data3[i]);
        //while (fgetc(file) !=',')
        //    fseek(file, 1, SEEK_CUR);
        //fseek(file, 1, SEEK_CUR);
    }
	start_RN(mon_reseau,data3); //get_RN(mon_reseau,result);
    int max = 0;
    for (int f =0 ; f<26; f++) {
        if (mon_reseau->neurone_sortie[f] > mon_reseau->neurone_sortie[max])
            max = f;
        printf("%lf\n",mon_reseau->neurone_sortie[f]);

    }
    printf(" %c: %c\n",97+m, max+97);
    /*
    RN_float dat2[9] = {1, 0, 1,
    	                1, 0.2, 1,
    	                0.7, 1, 0.7};
	start_RN(mon_reseau,dat2); //get_RN(mon_reseau,result);
    max = 0;
    for (int f =0 ; f<6; f++) {
        if (mon_reseau->neurone_sortie[f] > mon_reseau->neurone_sortie[max])
            max = f;
    }
    printf(" U %d\n", max);

	RN_float dat3[9] = {1, 0, 0.7,
    	                1, 0, 1,
  		                0.1, 1, 0.1};
	start_RN(mon_reseau,dat3); //get_RN(mon_reseau,result);
    max = 0;
    for (int f =0 ; f<6; f++) {
        if (mon_reseau->neurone_sortie[f] > mon_reseau->neurone_sortie[max])
            max = f;
    }
    printf(" V %d\n", max);

	RN_float dat4[9] = {1, 0, 1,
    	                0.2, 0.8, 0.2,
  		                0, 1, 0};
	start_RN(mon_reseau,dat4); //get_RN(mon_reseau,result);
    max = 0;
    for (int f =0 ; f<6; f++) {
        if (mon_reseau->neurone_sortie[f] > mon_reseau->neurone_sortie[max])
            max = f;
    }
    printf(" Y %d\n", max);

	RN_float dat5[9] = {1, 1, 0.8,
    	                0, 1, 0,
  			            0, 0.7, 0};
	start_RN(mon_reseau,dat5); //get_RN(mon_reseau,result);
    max = 0;
    for (int f =0 ; f<6; f++) {
        if (mon_reseau->neurone_sortie[f] > mon_reseau->neurone_sortie[max])
            max = f;
    }
    printf(" T %d\n", max);
    RN_float dat6[9] = {0.9, 0, 0,
                        1, 0.1, 0,
                        0.6, 1, 1};
    start_RN(mon_reseau,dat6); //get_RN(mon_reseau,result);
    max = 0;
    for (int f =0 ; f<6; f++) {
        if (mon_reseau->neurone_sortie[f] > mon_reseau->neurone_sortie[max])
            max = f;
    }
    printf(" L %d\n", max);
    */
    fclose(file);
	free_RN(mon_reseau);
    return 0;
}