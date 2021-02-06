gcc -W -Wall -o som main.c func.c learn.c -lm -std=c11      #compile the code into som.exe
./som.exe iris.data                                         #run the binary with the dataset file
