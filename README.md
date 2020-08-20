# SIRmodel
Per compilare il progetto abbiamo due possibili modi: cmake (consigliato) o terminale.

> ### ATTRAVERSO CMAKE

Come installare cmake (Ubuntu):
```
sudo apt-get install cmake
```
Passiamo alla compilazione:
```
cd SIRmodel
cd option1 (cd option2)
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --target all
make VERBOSE=1
./sir-sfml
```
Successivamente alla compilazione del progetto, per quanto riguarda gli unit test:
```
ctest
```

> ### DA TERMINALE:
```
g++ -c main.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
```
> ### RISULTATI
Compilando il file ![option1](https://github.com/samuelelanzi/SIRmodel/blob/master/option1) otteniamo il grafico degli andamenti delle funzioni nel tempo S(t) (suscettibili), I(t) (infetti) e R(t) (rimossi):

![opzione1](https://github.com/samuelelanzi/SIRmodel/blob/master/option1/sir.png)

Compilando il file ![option2](https://github.com/samuelelanzi/SIRmodel/blob/master/option2) otteniamo una simulazione dell'evolversi di un'epidemia secondo il modello SIR:

![opzione2](https://github.com/samuelelanzi/SIRmodel/blob/master/option2/display1.png)
![opzione2](https://github.com/samuelelanzi/SIRmodel/blob/master/option2/display2.png)

