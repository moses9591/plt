# README

# Ninja Saga

This project tends to make a game close to Ninja Saga with simple rules.
## Getting Started

make diretory -> mkdir build
move into folder -> cd build
By making "cmake .." some errors will appear and will indicate the missing librairies
In our case, we used the following commands for packages and librairies:
  - sudo apt-get install libboost-all-dev
  - sudo apt-get install -y libpthread-stubs0-dev libsfml-dev libxml2-dev docker.io
  - sudo apt-get install -y libmicrohttpd-dev
Once all the useful packages and librairies installed,  cmake will no longer 
display errors.
The next step is to execute the executable file named client inside the folder bin.
----> "./client anyword " displays "Bonjour anyword".

## Running the unit tests

In order to test the code-coverage you may process as following:
1) In the folder "build" execute the command "cmake .." to compile the project
2) command "make" to execute the project
3) Then "make unittest" to execute the unit tests
4) "make code-coverage"
5) To finish execute the command "firefox code-coverage/index.html"
A web page will be open showing the code-coverage based on the functions and the lines of code.

## Different Command
* "cmake .." from "build" folder
* "make" from the same folder
* "./bin/client render" from  "plt"  to display the render of a state 
* "./bin/client engine" from "plt"  to display a gameplay 
* "./bin/client random_ai" from "plt"  to play against a random ai
* "./bin/client heuristic_ai" from "plt"  to play against a random ai
* "./bin/client thread" from "plt" to separate the engine and render in different threads
* "./bin/client record" from "plt"  for recording a game
* "./bin/client play" from "plt"  to replay a recorded game
* "./bin/server listen" from "plt" for launching a server
* "./bin/client network" from "plt" for connecting to a lobby

## Authors
* **Moïse BEUGRE** 
* **Ouajih DADAOUA** 

