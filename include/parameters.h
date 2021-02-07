// model parameters
#define NBL 10 // map lines
#define NBC 12 // map cols
#define ALPHA 0.7 // learning coeficient
#define ITER_MAX 500 // max learning iteration

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

// export global variables of main.c to all files that includes this library
extern int DATA_LENGTH;
extern int NB_FEATURE;
extern char ** names;
extern int NB_CLASS;