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
TODO :  environ 1/6 des neurones ne sont pas classés
*/

extern void print_neurons(reseau *);
extern void print_results(reseau *);

extern data* load(char *);
extern void fit(reseau *, data *);


//global variables
int DATA_LENGTH;
int NB_FEATURE;
char ** names;
int NB_CLASS;


int main(int argc, char**argv){

    // check input
    if(argc != 2){
        printf("usage : %s iris.data\n", argv[0]);
        return 0;
    }
    
    // set initial value of global variable 
    NB_FEATURE = 0;
    DATA_LENGTH = 0;

    //load database
    data * data_col = load(argv[1]);


    //create network
    reseau * network = malloc(sizeof(reseau));
    network->map = malloc(sizeof(neuron) * (NBL * NBC));
    network->alph = ALPHA;  

    //learn data with the network
    fit(network, data_col);


    print_neurons(network);
    printf("\n");
    print_results(network);
  
    return 0;
}
