
typedef struct data{
    double *carac;     //sepal_length; sepal_width; petal_length; petal_width;
    double *norm;
    char *etiq;
} data;

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