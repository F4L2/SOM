## Implementation of a Self-Organizing Map (SOM) neural network algorithm in C.  

The SOM neural network is a supervised learning algorithm that separate classes of object iteratively.  
The principle is to intialize randomly a vector of neurons that has the same dimensions as the data.  
At each iteration, the neuron looks in its neighborhood the data that is most similar to itself and fit its features to that data.  
The neighborhood gets smaller at each iteration.  


## Installation
No obscure pre-requisite to run the code, you just need to install the gcc compiler.  
To compile, you can either use the makefile or the following commandlines to respectively compile an run the program with iris.data (https://archive.ics.uci.edu/ml/datasets/iris).  

```
gcc -W -Wall -o som main.c func.c learn.c -lm -std=c11  
./som.exe iris.data  
```

## Results
The terminal results show the list of neurons with its features and the 2D neuron map with their predicted classes.  
