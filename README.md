# SIRmodel

Per compilare il progetto

> ATTRAVERSO CMAKE (ninja file)

Come scaricare ninja(Ubuntu):
```
sudo apt-get install ninja

cd SIRmodel

cd build

cmake -G Ninja ..

ninja 

./sir-sfml
```
> DA TERMINALE:
```
g++ -c main.cpp

g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

./sfml-app
```
