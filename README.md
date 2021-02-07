## Implementation of a Self-Organizing Map (SOM) neural network algorithm in C.  

The SOM neural network is a supervised learning algorithm.  
In short, it tries to represent the data in dimension D to a map of neurons in dimension K (in this case K=2).  
The principle is to intialize randomly a vector of neurons that has the same dimensions as the data.  
At each iteration, the neuron looks in its neighborhood the data point that is most similar to itself and fit its features to that data.  
The neighborhood gets smaller at each iteration.  


## Installation
No obscure pre-requisite to run the code, you just need to install the gcc compiler.  
Configure the model's parameters in *"./include/parameters.h"*  

```
// model parameters
#define NBL 10 // map lines
#define NBC 12 // map cols
#define ALPHA 0.7 // learning coeficient
#define ITER_MAX 500 // max learning iteration
```

To compile, you can either use the makefile or the following commandline.  

```
gcc -W -Wall -o som main.c func.c learn.c -lm -std=c11  
```

And run the program in the terminal by using this commandline with the data collection *"iris.data"* (https://archive.ics.uci.edu/ml/datasets/iris)
```
./som.exe iris.data  
```

## Results
The terminal results show the list of neurons with its features and the 2D neuron map with their predicted classes.  
