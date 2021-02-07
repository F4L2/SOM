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

This file store simple utilitary functions that helps the code clarity.

*/


// rescale values into [0,1] range
double * normalize(double* vec){
    int i;
    double sum = 0.0;
    double norme;
    double * results = malloc(sizeof(double) * NB_FEATURE);
    for(i = 0; i< NB_FEATURE; i++){
        sum+= pow(vec[i], 2);
    }
    norme =  sqrt(sum);
    
    for(i = 0; i< NB_FEATURE; i++){
        results[i] = vec[i] / norme;
    }
    
    return results;
}


// return a single random value in between (min,max)
double randFrom(double min, double max) {
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}


// shuffle the list of indexes to read randomly
void shuffle( int * rand_lec ){
    int i, j, tmp;
    for( i = 0; i < DATA_LENGTH; i++){
        rand_lec[i] = i;
    }
    srand(time(NULL));
    for( i = 0; i < DATA_LENGTH-1; i++){
        j = i + rand() / (RAND_MAX / (DATA_LENGTH-i) +1);
        tmp = rand_lec[j];
        rand_lec[j] = rand_lec[i];
        rand_lec[i] = tmp;
    }
}

// compute euclidean distance betwen 2 vectors
double euclid(double *a, double *b){
	double sum = 0.0;
	for(int i = 0; i< NB_FEATURE; i++){
	    sum += pow((a[i] - b[i]), 2); 
	}                 
	return sqrt(sum);
}


// print each neuron's features and its predicted class
void print_neurons(reseau * net){
    int i,j,x;
    for(i = 0; i < NBL; i++){
        for(j = 0; j< NBC; j++){
            printf("[ ");
            for(x = 0; x< NB_FEATURE; x++){
                printf("%f, ", net->map[i * NBL +j].feat[x]);
            }
            printf(" ] ");
            if(net->map[i* NBL + j].etiq != NULL){
                printf(": %s\n", net->map[i* NBL + j].etiq);
            }else{
                printf(": none\n");
            }
        }
    }
}

// visualize the netword in 2D
void print_results(reseau * net){
    int i,j,y;
    int noclass = 0;
    for(i = 0; i < NBL; i++){
        for(j = 0; j< NBC; j++){
            if(net->map[i* NBL + j].etiq == NULL){
                printf(". ");
                noclass ++;
                continue;
            }
            for(y = 0; y < NB_CLASS; y++){
                if(strcmp(net->map[i* NBL + j].etiq, names[y]) == 0)
                    break;
            }
            printf("%c ", 'A' + y);
        }
        printf("\n");
    }
    printf("\nneuron(s) not classed: %d / %d\n",noclass, NBC*NBL);
}
