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
    
    NB_CLASS = 0;
    char ** more_class;
    char * tampon;
    
    //examiner la première ligne pour trouver le nombre de caractéristiques
    fgets(line, sizeof(line),database);
    tok = strtok(line, mark);
    while(tok != NULL){
            if(size_c == NB_FEATURE){
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
            car[NB_FEATURE] = carac;
            tok = strtok(NULL, mark);
            NB_FEATURE ++;
    }
    NB_FEATURE -= 1; // on suppose que la classe/l'étiquette est la dernière valeur, 
    data_collection[iter].carac = malloc(sizeof(double) * NB_FEATURE);
    for(i = 0; i < NB_FEATURE; i++){
        data_collection[iter].carac[i] = car[i];
    } 
    free(car);
    data_collection[iter].etiq = malloc(sizeof(char) * strlen(etiq));
    strcpy(data_collection[iter].etiq, etiq);
    
    //on suppose qu'il existe toujours une classe
    names = malloc(sizeof(char *));
    names[NB_CLASS] = malloc(sizeof(char) * strlen(etiq));
    strcpy(names[NB_CLASS], etiq);
    tampon = malloc(sizeof(char) * strlen(etiq));
    strcpy(tampon, etiq);
    NB_CLASS++;
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
        data_collection[DATA_LENGTH].carac = malloc(sizeof(double) * NB_FEATURE);
        iter = 0;
        tok = strtok(line, mark);
        while(tok != NULL){
            carac = strtod(tok, &etiq);
            if(iter < NB_FEATURE){
                data_collection[DATA_LENGTH].carac[iter] = carac;
                iter++;
            }
            tok = strtok(NULL, mark);
        }
        data_collection[DATA_LENGTH].etiq = malloc(sizeof(char) * strlen(etiq));
        strcpy(data_collection[DATA_LENGTH].etiq, etiq);
        
        //supposons que les données d'entrées sont triées par classe
        if(strcmp(tampon, etiq) != 0){
            NB_CLASS += 1;
            more_class = malloc(sizeof(char *) * NB_CLASS);
            for(j = 0; j < NB_CLASS-1; j++){
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