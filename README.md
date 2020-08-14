# SIRmodel
Per compilare il progetto abbiamo due possibili strade:

> ### ATTRAVERSO CMAKE (ninja file)

Come installare ninja (Ubuntu):
```
sudo apt-get install ninja
```
Passiamo alla compilazione:
```
cd SIRmodel
cd option1 (cd option2)
mkdir build
cd build
cmake -G Ninja ..
ninja 
./sir-sfml
```
> ### DA TERMINALE:
```
g++ -c main.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
```
> ### IMMAGINI
Compilando il file `![option1](https://github.com/samuelelanzi/SIRmodel/blob/master/option1)` otteniamo il grafico degli andamenti delle funzioni nel tempo S(t) (suscettibili), I(t) (infetti) e R(t) (rimossi):

![opzione1](https://github.com/samuelelanzi/SIRmodel/blob/master/option1/sir.png)

Compilando il file `![option2](https://github.com/samuelelanzi/SIRmodel/blob/master/option2)` otteniamo una simulazione dell'evolversi di un'epidemia secondo il modello SIR:

![opzione1](https://github.com/samuelelanzi/SIRmodel/blob/master/option2/display.png)

