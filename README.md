# SIRmodel
Si tratta del modello matematico che descrive l'evoluzione di un epidemia (a questo livello in modo alquanto approssimato).
Le formule principali sulle quali si basa il modello, utlizzate anche nel nostro progetto sono:

<img src="https://render.githubusercontent.com/render/math?math=S_i = S_{i - 1} - \beta I_{i - 1}S_{i - 1}">

<img src="https://render.githubusercontent.com/render/math?math=I_i = I_{i - 1} - \beta I_{i - 1}S_{i - 1} - \gamma I_{i - 1}">

<img src="https://render.githubusercontent.com/render/math?math=R_i = R_{i - 1} - \gamma I_{i - 1}">

<img src="https://render.githubusercontent.com/render/math?math=N = S_i ++ I_i ++ R_i">

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

> ### RISULTATI
Compilando il file ![option1](https://github.com/samuelelanzi/SIRmodel/blob/master/option1) otteniamo il grafico degli andamenti delle funzioni nel tempo S(t) (suscettibili), I(t) (infetti) e R(t) (rimossi):

![opzione1](https://github.com/samuelelanzi/SIRmodel/blob/master/option1/sir.png)

Compilando il file ![option2](https://github.com/samuelelanzi/SIRmodel/blob/master/option2) otteniamo una simulazione dell'evolversi di un'epidemia secondo il modello SIR:

![opzione2](https://github.com/samuelelanzi/SIRmodel/blob/master/option2/display1.png)
![opzione2](https://github.com/samuelelanzi/SIRmodel/blob/master/option2/display2.png)

