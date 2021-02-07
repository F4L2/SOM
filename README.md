## Implementation of a Self-Organizing Map (SOM) neural network algorithm in C.  

The SOM neural network is a supervised learning algorithm.  
In short, it tries to represent the data in dimension D to a map of neurons in dimension K (in this case K=2).  
The principle is to intialize randomly a vector of neurons that has the same dimensions as the data.  
At each iteration, the neuron looks in its neighborhood the data point that is most similar to itself and fit its features to that data.  
The neighborhood gets smaller at each iteration.  


## Instructions
No obscure pre-requisite to run the code, you just need to install the gcc compiler.  
Configure the model's parameters in **"./include/parameters.h"**  

```
// model parameters
#define NBL 10 // map lines
#define NBC 12 // map cols
#define ALPHA 0.7 // learning coeficient
#define ITER_MAX 500 // max learning iteration
```

To compile, you can either use the **makefile** with the command.  
```
make
```

Or the following commandline.  

```
gcc -W -Wall -o som main.c func.c learn.c -lm -std=c11  
```

And run the program in the terminal by using this commandline with the data collection *"iris.data"* (https://archive.ics.uci.edu/ml/datasets/iris)
```
#linux
./som iris.data  

#windows
./som.exe iris.data  
```

## Results
The terminal results show the list of neurons with its features and the 2D neuron map with their predicted classes.  


```
$ ./som.exe iris.data
[ 0.707484, 0.246039, 0.628713, 0.207888,  ] : Iris-virginica
[ 0.712917, 0.268617, 0.618851, 0.191084,  ] : Iris-virginica
[ 0.719901, 0.275210, 0.611358, 0.179069,  ] : Iris-virginica
[ 0.698135, 0.296168, 0.630621, 0.163620,  ] : Iris-virginica
[ 0.696029, 0.309195, 0.612169, 0.209895,  ] : none
[ 0.694147, 0.304136, 0.607931, 0.236723,  ] : Iris-virginica
[ 0.688607, 0.321175, 0.606636, 0.233563,  ] : Iris-virginica
[ 0.660148, 0.342155, 0.617119, 0.256724,  ] : Iris-virginica
[ 0.679334, 0.330150, 0.595228, 0.273642,  ] : Iris-virginica
[ 0.700080, 0.322887, 0.585985, 0.249036,  ] : Iris-virginica
[ 0.715074, 0.301758, 0.593577, 0.212561,  ] : Iris-virginica
[ 0.719995, 0.282198, 0.600208, 0.202527,  ] : none
[ 0.715074, 0.301758, 0.593577, 0.212561,  ] : Iris-virginica
[ 0.719995, 0.282198, 0.600208, 0.202527,  ] : none
[ 0.726251, 0.279681, 0.599726, 0.185556,  ] : Iris-virginica
[ 0.711603, 0.317617, 0.599096, 0.183627,  ] : Iris-virginica
[ 0.699648, 0.322332, 0.606324, 0.196982,  ] : Iris-virginica
[ 0.690707, 0.321491, 0.607153, 0.225567,  ] : Iris-virginica
[ 0.677464, 0.341618, 0.606355, 0.237617,  ] : Iris-virginica
[ 0.672856, 0.364740, 0.591927, 0.252483,  ] : Iris-virginica
[ 0.692217, 0.344468, 0.583107, 0.249125,  ] : Iris-virginica
[ 0.705719, 0.328465, 0.581007, 0.237304,  ] : Iris-virginica
[ 0.718044, 0.315224, 0.579786, 0.220812,  ] : Iris-virginica
[ 0.730575, 0.288048, 0.579153, 0.218675,  ] : Iris-virginica
[ 0.718044, 0.315224, 0.579786, 0.220812,  ] : Iris-virginica
[ 0.730575, 0.288048, 0.579153, 0.218675,  ] : Iris-virginica
[ 0.740044, 0.293791, 0.577946, 0.178158,  ] : Iris-versicolor
[ 0.727119, 0.313440, 0.587200, 0.167633,  ] : Iris-virginica
[ 0.713732, 0.332324, 0.589209, 0.178984,  ] : none
[ 0.695613, 0.339887, 0.601163, 0.197864,  ] : Iris-virginica
[ 0.692873, 0.346736, 0.594805, 0.214107,  ] : Iris-virginica
[ 0.690157, 0.366632, 0.583632, 0.218196,  ] : none
[ 0.706962, 0.341998, 0.571003, 0.237412,  ] : none
[ 0.726907, 0.326577, 0.552095, 0.244864,  ] : Iris-virginica
[ 0.723013, 0.328178, 0.567662, 0.217351,  ] : Iris-virginica
[ 0.732097, 0.312059, 0.568192, 0.208678,  ] : Iris-virginica
[ 0.723013, 0.328178, 0.567662, 0.217351,  ] : Iris-virginica
[ 0.732097, 0.312059, 0.568192, 0.208678,  ] : Iris-virginica
[ 0.763604, 0.277407, 0.554457, 0.178552,  ] : Iris-versicolor
[ 0.737545, 0.334080, 0.567105, 0.149509,  ] : Iris-versicolor
[ 0.725520, 0.347912, 0.570777, 0.163365,  ] : Iris-versicolor
[ 0.716468, 0.345113, 0.578789, 0.179883,  ] : Iris-virginica
[ 0.706960, 0.366315, 0.571500, 0.195611,  ] : none
[ 0.699448, 0.380749, 0.571130, 0.198572,  ] : Iris-versicolor
[ 0.711033, 0.353688, 0.569814, 0.211144,  ] : Iris-virginica
[ 0.716843, 0.350384, 0.560997, 0.220083,  ] : Iris-virginica
[ 0.738985, 0.332200, 0.553770, 0.191273,  ] : Iris-versicolor
[ 0.754708, 0.315391, 0.547168, 0.176611,  ] : Iris-versicolor
[ 0.738985, 0.332200, 0.553770, 0.191273,  ] : Iris-versicolor
[ 0.754708, 0.315391, 0.547168, 0.176611,  ] : Iris-versicolor
[ 0.781654, 0.286650, 0.533962, 0.146192,  ] : Iris-versicolor
[ 0.766786, 0.312012, 0.539034, 0.155014,  ] : Iris-versicolor
[ 0.742153, 0.341537, 0.552501, 0.162257,  ] : none
[ 0.733847, 0.357754, 0.551922, 0.169749,  ] : Iris-versicolor
[ 0.730470, 0.377012, 0.541363, 0.176277,  ] : Iris-versicolor
[ 0.715898, 0.399664, 0.540042, 0.189117,  ] : Iris-versicolor
[ 0.723263, 0.374517, 0.545904, 0.195918,  ] : Iris-versicolor
[ 0.733470, 0.354993, 0.549087, 0.185181,  ] : Iris-versicolor
[ 0.754379, 0.348405, 0.529259, 0.170383,  ] : Iris-versicolor
[ 0.753641, 0.335035, 0.538644, 0.171863,  ] : Iris-versicolor
[ 0.754379, 0.348405, 0.529259, 0.170383,  ] : Iris-versicolor
[ 0.753641, 0.335035, 0.538644, 0.171863,  ] : Iris-versicolor
[ 0.769009, 0.324492, 0.530588, 0.144672,  ] : none
[ 0.761670, 0.340492, 0.531545, 0.145711,  ] : Iris-versicolor
[ 0.758782, 0.353121, 0.523936, 0.157898,  ] : Iris-versicolor
[ 0.743654, 0.365086, 0.533737, 0.169395,  ] : Iris-versicolor
[ 0.742053, 0.374716, 0.525484, 0.180865,  ] : Iris-versicolor
[ 0.731237, 0.388098, 0.536801, 0.162505,  ] : Iris-versicolor
[ 0.750486, 0.445407, 0.444391, 0.119666,  ] : none
[ 0.759545, 0.416608, 0.455021, 0.147611,  ] : none
[ 0.778279, 0.386031, 0.462798, 0.163738,  ] : Iris-versicolor
[ 0.763054, 0.342658, 0.524086, 0.159063,  ] : Iris-versicolor
[ 0.778279, 0.386031, 0.462798, 0.163738,  ] : Iris-versicolor
[ 0.763054, 0.342658, 0.524086, 0.159063,  ] : Iris-versicolor
[ 0.771255, 0.338705, 0.519531, 0.143075,  ] : Iris-versicolor
[ 0.767235, 0.349134, 0.515342, 0.154416,  ] : Iris-versicolor
[ 0.768290, 0.353649, 0.508942, 0.160013,  ] : Iris-versicolor
[ 0.760220, 0.369173, 0.510920, 0.156831,  ] : Iris-versicolor
[ 0.757189, 0.389655, 0.493703, 0.175522,  ] : Iris-versicolor
[ 0.757926, 0.449687, 0.431465, 0.115294,  ] : none
[ 0.779598, 0.549018, 0.298933, 0.033008,  ] : Iris-setosa
[ 0.771475, 0.566773, 0.283061, 0.054704,  ] : Iris-setosa
[ 0.775717, 0.541517, 0.293989, 0.069314,  ] : none
[ 0.775638, 0.508285, 0.324853, 0.086168,  ] : none
[ 0.775717, 0.541517, 0.293989, 0.069314,  ] : none
[ 0.775638, 0.508285, 0.324853, 0.086168,  ] : none
[ 0.786904, 0.453408, 0.370272, 0.107589,  ] : none
[ 0.783869, 0.357804, 0.487302, 0.140766,  ] : Iris-versicolor
[ 0.772723, 0.357224, 0.499769, 0.154312,  ] : none
[ 0.800264, 0.474578, 0.330653, 0.064306,  ] : none
[ 0.783853, 0.467661, 0.364346, 0.104323,  ] : none
[ 0.801592, 0.542794, 0.247611, 0.033328,  ] : none
[ 0.794108, 0.546054, 0.264475, 0.033814,  ] : Iris-setosa
[ 0.795715, 0.554264, 0.241344, 0.034741,  ] : Iris-setosa
[ 0.781250, 0.575709, 0.237930, 0.038329,  ] : Iris-setosa
[ 0.785005, 0.568189, 0.239304, 0.059612,  ] : Iris-setosa
[ 0.781250, 0.575709, 0.237930, 0.038329,  ] : Iris-setosa
[ 0.785005, 0.568189, 0.239304, 0.059612,  ] : Iris-setosa
[ 0.793202, 0.547657, 0.253659, 0.079013,  ] : Iris-setosa
[ 0.811515, 0.479485, 0.297958, 0.083450,  ] : none
[ 0.815873, 0.502176, 0.274162, 0.037121,  ] : none
[ 0.815464, 0.517866, 0.256691, 0.028445,  ] : Iris-setosa
[ 0.808585, 0.529455, 0.253646, 0.036800,  ] : Iris-setosa
[ 0.813886, 0.535049, 0.224102, 0.032092,  ] : Iris-setosa
[ 0.805130, 0.542219, 0.237712, 0.034792,  ] : Iris-setosa
[ 0.802473, 0.553209, 0.220294, 0.036763,  ] : Iris-setosa
[ 0.788378, 0.572666, 0.223082, 0.024889,  ] : Iris-setosa
[ 0.780549, 0.579871, 0.228075, 0.045245,  ] : Iris-setosa
[ 0.788378, 0.572666, 0.223082, 0.024889,  ] : Iris-setosa
[ 0.780549, 0.579871, 0.228075, 0.045245,  ] : Iris-setosa
[ 0.808097, 0.519147, 0.265678, 0.077693,  ] : Iris-setosa
[ 0.854727, 0.449893, 0.250645, 0.057010,  ] : Iris-setosa
[ 0.827735, 0.495592, 0.260217, 0.033675,  ] : Iris-setosa
[ 0.825051, 0.511139, 0.239209, 0.026093,  ] : Iris-setosa
[ 0.822098, 0.516148, 0.233677, 0.054908,  ] : Iris-setosa
[ 0.825498, 0.527312, 0.198479, 0.031978,  ] : Iris-setosa
[ 0.809807, 0.543984, 0.215377, 0.033467,  ] : none
[ 0.805781, 0.559676, 0.190425, 0.027055,  ] : Iris-setosa
[ 0.792567, 0.575617, 0.193218, 0.051936,  ] : Iris-setosa
[ 0.773508, 0.600798, 0.197622, 0.032577,  ] : Iris-setosa

C C C C . C C C C C C . 
C . C C C C C C C C C C
C C B C . C C . . C C C
C C B B B C . B C C B B
B B B B . B B B B B B B
B B . B B B B B . . B B
B B B B B B B . A A . . 
. . . B . . . . A A A A
A A A . . A A A A A A A
A A A A A A A A . A A A

neuron(s) not classed: 24 / 120
```

Here we have a map containing 10x12 neurons, after 500 iteration 96 neurons have found a class (Iris-setosa/A, Iris-versicolor/B or Iris-virginica/C).  
We can see in the map visualization that the classes are well separated.  
The algorithm still can't find 24 neurons, this project would require a little more work.
