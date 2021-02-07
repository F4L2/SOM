#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<limits.h>
#include<float.h>

#include"../include/parameters.h"
#include"../include/network.h"
#include"../include/data_format.h"

/*

This file contain the learning algorithm of SOM,
In short, it tries to represent the data in dimension N to a map of neurons in dimension 2

*/

extern double * normalize(double* vec);
extern double randFrom(double min, double max);
extern void shuffle( int * rand_lec );
extern double euclid(double *a, double *b);


//learning function
void fit(reseau * network, data * data_col){

    int i,j,n,x,iter = 0;

    // initialize data index list for data lecture
    int * rand_lec = malloc(sizeof(int) * DATA_LENGTH);
    for(i = 0; i< DATA_LENGTH; i++)
        rand_lec[i] = i;
    
    //normalize feature values to be between [0,1]
    for(i = 0; i< DATA_LENGTH; i++){
        data_col[i].norm = malloc(sizeof(double) * NB_FEATURE);
        data_col[i].norm = normalize(data_col[i].carac);
    }  

    // feature average / average vector (initial weights)
    // The 
    double * middle = malloc(sizeof(double) * NB_FEATURE);
    double sum;
    for(i = 0; i < NB_FEATURE ; i++){
        sum = 0;
        for(j = 0; j< DATA_LENGTH; j++){
            sum += data_col[j].norm[i];
        }
        sum /= DATA_LENGTH;
        middle[i] = sum;
    }
    
    // init Wi centré
    double borne_sup = 0.005;
    double borne_inf = -0.005;
    double rnd;
    srand(time(NULL));
    for(i = 0; i< NBL; i++){
        for(j = 0; j< NBC; j++){
            network->map[i* NBL +j].feat = malloc(sizeof(double) * NB_FEATURE);
            for(n = 0; n < NB_FEATURE; n++){
                rnd = randFrom(borne_inf, borne_sup);
                network->map[i* NBL +j].feat[n] = middle[n] + rnd;
            }
            network->map[i* NBL +j].etiq = NULL;
        }
    }

    
    
    list * bmu = malloc(sizeof(list));
    head h;
    h.nb_node = 0;
    h.first = bmu;
    h.last = bmu;
    double best_dist, tmp;
    srand(time(NULL));
    
    // SOM network, learning loop
    for(iter = 0; iter < ITER_MAX; iter++){
        // déterminer le voisinnage en fonction du temps d'apprentissage
        // le voisinage devient plus petit à chaque itération
        int rayon = max(NBL, NBC);
        double nominator = (ITER_MAX - iter);
        double fraction = nominator / ITER_MAX;
        network->r_voisin = rayon * fraction;
        network->alph = fraction * ALPHA;  // what ?? comparer avec une variable dissociée du réseau
        
        shuffle(rand_lec);
        
        // phase 1
        // seek BMU (best matching unit), the data point closest to the neuron
        for(n = 0; n < DATA_LENGTH; n++){    
            bmu = h.last;
            h.toChecks = 0;
            h.check_point = h.last;
            best_dist = DBL_MAX; // infinie mathématique
            //chercher BMU
            for(i = 0; i < NBL; i++){
                for(j = 0; j < NBC; j++){
                    tmp = euclid(network->map[i* NBL +j].feat, data_col[rand_lec[n]].norm);
                    if(tmp < best_dist){
                        bmu->line = i;
                        bmu->col = j;
                        bmu->act = tmp;
                        bmu->data_id = rand_lec[n];
                        best_dist = tmp;
                    }
                }      
            }            
            //chercher les unités équivalentes
            // TODO:    pas besoin de refaire une recherche, je peux stocker les équivalents dans une liste chainée (si je trouve plus près je supprime la liste et en refait une)
            //          et itérer sur cette liste chainée
            for(i = 0; i < NBL; i++){
                for(j = 0; j < NBC; j++){
                    tmp = euclid(network->map[i* NBL +j].feat, data_col[rand_lec[n]].norm);
                    if(tmp == best_dist){
                        bmu->suiv = malloc(sizeof(list));
                        h.toChecks++;
                        bmu = bmu->suiv;
                    
                        bmu->line = i;
                        bmu->col = j;
                        bmu->act = tmp;
                        bmu->data_id = rand_lec[n];
                    }
                }      
            }
            bmu->suiv = malloc(sizeof(list));
            h.last = bmu->suiv;
            
            bmu = h.check_point;
            h.isCheck = rand() % (h.toChecks+1);
            if(h.isCheck != 0){
                for(x = 0; x < h.isCheck; x++){
                    bmu = bmu->suiv;
                }
            }
            
            //adjust neighborhood
            // phase 2  
            //LEARNING
            //rapprocher le neurone à la position de la donnée, utiliser alph
            for(i = 0; i < NBL; i++){
                for(j = 0; j < NBC; j++){
                    //determine distance to BMU
                    network->map[i * NBL + j].dist_to_bmu = 0;
                    if(i > bmu->line)
                        network->map[i * NBL + j].dist_to_bmu += i - bmu->line;
                    else
                        network->map[i * NBL + j].dist_to_bmu += bmu->line - i;
                    if(j > bmu->col)
                        network->map[i * NBL + j].dist_to_bmu += j - bmu->col;
                    else
                        network->map[i * NBL + j].dist_to_bmu += bmu->col - j;
                    
                    //si hors du rayon, passer au suivant
                    if(network->map[i * NBL + j].dist_to_bmu > network->r_voisin)
                        continue;
                        
                    // close the distance toward the BMU
                    for(x = 0; x < NB_FEATURE ; x++){
                        double diff = network->map[i * NBL + j].feat[x] - data_col[bmu->data_id].norm[x];
                        network->map[i * NBL + j].feat[x] -= (network->alph * diff) /(network->map[i * NBL + j].dist_to_bmu +1);  
                    
                    }
                }
            }
        }
    }
    

    // class attribution
    typing * first = malloc(sizeof(typing));
    first->suiv = malloc(sizeof(typing));
    typing * get;
    get = first->suiv; 
    get->suiv = NULL;
    int bmu_id;  
    int nb_bmu;
    srand(time(NULL)); 
    for(n = 0; n < DATA_LENGTH; n++){
        get = first->suiv;
        nb_bmu = 0;
        best_dist = DBL_MAX; // assuming a ridiculously high initial distance, the true closest can only be closer
        
        //search BMU (closest)
        for(i=0; i<NBL; i++){
            for(j=0;j<NBC;j++){
                tmp = euclid(network->map[i * NBL + j].feat, data_col[n].norm);
                if(tmp <= best_dist){
                    get->y = i;
                    get->x = j;
                    get->id = n;
                    best_dist = tmp;
                }
            }
        }
        //search for equivalent matching (as close as) unit
        // TODO:    pas besoin de refaire une recherche, je peux stocker les équivalents dans une liste chainée (si je trouve plus près je supprime la liste et en refait une)
        //          et itérer sur cette liste chainée
        for(i=0; i<NBL; i++){
            for(j=0;j<NBC;j++){
                tmp = euclid(network->map[i * NBL + j].feat, data_col[n].norm);
                //un doublon du premier
                if(tmp == best_dist){
                    if(!get->suiv){
                        get->suiv = malloc(sizeof(typing));
                        get = get->suiv;
                        get->suiv = NULL;
                    }else{
                        get = get->suiv;
                    }
                    nb_bmu++;
                    get->y = i;
                    get->x = j;
                    get->id = n;
                }
            }
        }
        get = first->suiv;
        bmu_id = rand() % (nb_bmu+1);
        if(bmu_id != 0){
            for(x = 0; x < bmu_id; x++){
                get = get->suiv;
            }
        }
        network->map[get->y * NBL + get->x].etiq = malloc(sizeof(char) * strlen(data_col[get->id].etiq));
        strcpy(network->map[get->y * NBL + get->x].etiq , data_col[get->id].etiq);
    }
}