# Markov Chain
This is a Markov Chain text generator written in C.


Givin a corpus text this program will output a random 
text generated with an n-gram markov chain
There is a makefile included. To build enter make into 
the terminal. make clean will clean the folder.

To run the unit tests run the following commands:

git clone https://github.com/aguerriero1998/Markov-Chain.git

cd Markov-Chain

git clone http://troydhanson.github.com/uthash/

mv uthash/uthash.h ..

git clone https://github.com/ThrowTheSwitch/Unity.git

make tests

./tests


Dependencies:
* Hash Table Libary http://troydhanson.github.com/uthash/
* Unity Testing Library http://www.throwtheswitch.org/unity/
