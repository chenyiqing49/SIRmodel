# SIRmodel

Per compilare il progetto

1) ATTRAVERSO CMAKE (ninja file)

Come scaricare ninja(Ubuntu):
'''
sudo apt-get install ninja

cd SIRmodel

cd build

cmake -G Ninja ..

ninja 

./sir-sfml
'''

2) DA TERMINALE:

'g++ -c main.cpp'

'g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system'

'./sfml-app'
