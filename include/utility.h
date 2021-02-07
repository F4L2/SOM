// model parameters
#define NBL 10 // map lines
#define NBC 12 // map cols
#define ALPHA 0.7 // learning coeficient
#define ITER_MAX 500 // max learning iteration

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

// global variables
extern int DATA_LENGTH;
extern int NB_CARAC;
extern char ** names;
extern int nb_class;

typedef struct neuron{
    double * feat;     //sepal_length; sepal_width; petal_length; petal_width;
    double act;
    char *etiq;
    int dist_to_bmu;
} neuron;

typedef struct data{
    double *carac;     //sepal_length; sepal_width; petal_length; petal_width;
    double *norm;
    char *etiq;
} data;

typedef struct reseau{
    double alph;
    int r_voisin;
    double * capt;
    neuron * map;
} reseau;

typedef struct list{
    int line;
    int col;
    int data_id;
    double act;
    struct list * suiv;
} list;

typedef struct head{
    int nb_node;
    struct list * first;
    struct list * last;
    int toChecks;
    int isCheck;
    struct list * check_point;
} head;

typedef struct typing{
    int x;
    int y;
    int id;
    struct typing * suiv;
} typing;

