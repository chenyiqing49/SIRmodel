# SIRmodel

Per compilare il progetto

ATTRAVERSO CMAKE (ninja file)

cd SIRmodel
mkdir build
cmake -G Ninja ..
ninja 

./sir-sfml

DA TERMINALE:

g++ -c main.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
