
typedef struct neuron{
    double * feat;     //sepal_length; sepal_width; petal_length; petal_width;
    double act;
    char *etiq;
    int dist_to_bmu;
} neuron;

typedef struct reseau{
    double alph;
    int r_voisin;
    double * capt;
    neuron * map;
} reseau;