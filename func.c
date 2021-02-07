#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<limits.h>
#include<float.h>

#include"include/utility.h"


// rescale values into [0,1] range
double * normalize(double* vec){
    int i;
    double sum = 0.0;
    double norme;
    double * results = malloc(sizeof(double) * NB_CARAC);
    for(i = 0; i< NB_CARAC; i++){
        sum+= pow(vec[i], 2);
    }
    norme =  sqrt(sum);
    
    for(i = 0; i< NB_CARAC; i++){
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
	for(int i = 0; i< NB_CARAC; i++){
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
            for(x = 0; x< NB_CARAC; x++){
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
            for(y = 0; y < nb_class; y++){
                if(strcmp(net->map[i* NBL + j].etiq, names[y]) == 0)
                    break;
            }
            printf("%c ", 'A' + y);
        }
        printf("\n");
    }
    printf("\nneuron(s) not classed: %d / %d\n",noclass, NBC*NBL);
}





// loading data of dynamic size
data * load(char * file){
    FILE * database = fopen(file, "r");
    
    int i,j, iter = 0;
    
    char line[64];
    const char mark[3] = { ',', '\n'};
    char * tok;
    double carac;
    char * etiq;
    
    int size = 32; //arbitrary little number before determining real sizes.
    data * data_collection = malloc(sizeof(data) * size);
    data * more_data;
    int size_c = 1, sav_size;
    double * car = malloc(sizeof(double) * size_c);
    double * more_car;
    
    nb_class = 0;
    char ** more_class;
    char * tampon;
    
    //examiner la première ligne pour trouver le nombre de caractéristiques
    fgets(line, sizeof(line),database);
    tok = strtok(line, mark);
    while(tok != NULL){
            if(size_c == NB_CARAC){
                sav_size = size_c;
                size_c = size_c << 1;
                more_car = malloc(sizeof(double) * size_c);
                for(i =0; i < sav_size; i++){
                    more_car[i] = car[i];
                }
                free(car);
                car = more_car;
            }
            carac = strtod(tok, &etiq);
            car[NB_CARAC] = carac;
            tok = strtok(NULL, mark);
            NB_CARAC ++;
    }
    NB_CARAC -= 1; // on suppose que la classe/l'étiquette est la dernière valeur, 
    data_collection[iter].carac = malloc(sizeof(double) * NB_CARAC);
    for(i = 0; i < NB_CARAC; i++){
        data_collection[iter].carac[i] = car[i];
    } 
    free(car);
    data_collection[iter].etiq = malloc(sizeof(char) * strlen(etiq));
    strcpy(data_collection[iter].etiq, etiq);
    
    //on suppose qu'il existe toujours une classe
    names = malloc(sizeof(char *));
    names[nb_class] = malloc(sizeof(char) * strlen(etiq));
    strcpy(names[nb_class], etiq);
    tampon = malloc(sizeof(char) * strlen(etiq));
    strcpy(tampon, etiq);
    nb_class++;
    DATA_LENGTH++;
    
    //examiner le reste des données et trouver la taille de la database.
    while(fgets(line, sizeof(line),database)){
        if(size <= DATA_LENGTH){ //si on a plus de place, doubler la mémoire de la liste
           sav_size = size;
           size = size << 1;
           more_data = malloc(sizeof(data) * size);
           for(i = 0; i < sav_size; i++){
                more_data[i] = data_collection[i];
           }
           free(data_collection);
           data_collection = more_data; 
        }
        data_collection[DATA_LENGTH].carac = malloc(sizeof(double) * NB_CARAC);
        iter = 0;
        tok = strtok(line, mark);
        while(tok != NULL){
            carac = strtod(tok, &etiq);
            if(iter < NB_CARAC){
                data_collection[DATA_LENGTH].carac[iter] = carac;
                iter++;
            }
            tok = strtok(NULL, mark);
        }
        data_collection[DATA_LENGTH].etiq = malloc(sizeof(char) * strlen(etiq));
        strcpy(data_collection[DATA_LENGTH].etiq, etiq);
        
        //supposons que les données d'entrées sont triées par classe
        if(strcmp(tampon, etiq) != 0){
            nb_class += 1;
            more_class = malloc(sizeof(char *) * nb_class);
            for(j = 0; j < nb_class-1; j++){
                more_class[j] = names[j];
            }
            more_class[j] = malloc(sizeof(char) * strlen(etiq));
            strcpy(more_class[j], etiq);
            free(names);
            names = more_class;
            free(tampon);
            tampon = malloc(sizeof(char) * strlen(etiq));
            strcpy(tampon, etiq);
        }
        DATA_LENGTH++;
    }
    
    //réduire l'utilisation de mémoire en stockant dans un nouveau tableau de la taille exacte des données
    data * data_col = malloc(sizeof(data) * DATA_LENGTH);
    for(i = 0; i< DATA_LENGTH ; i++) data_col[i] = data_collection[i]; 
    free(data_collection);
    fclose(database);
    
    /* printf the loaded database for sceptics
    
    for(i = 0; i < DATA_LENGTH; i++){
        printf("%f,%f,%f,%f,%s\n", data_col[i].carac[0], data_col[i].carac[1], data_col[i].carac[2], data_col[i].carac[3],data_col[i].etiq);
    }
    */
    
    return data_col;
}
