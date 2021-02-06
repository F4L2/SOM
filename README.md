Implementation of a Self-Organizing Map (SOM) neural network algorithm in C.  
To run the code, you just need to install the gcc compiler.  
To compile, you can either use the makefile or the command lines in run.sh.  


The SOM neural network is a supervised learning algorithm that separate classes of object iteratively.  
The principle is to intialize randomly a vector of neurons that has the same dimensions as the data.  
At each iteration, the neuron looks in its neighborhood the data that is most similar to itself and fit its features to that data.  
The neighborhood gets smaller at each iteration.  


Here's an example using the iris data (https://archive.ics.uci.edu/ml/datasets/iris).  
