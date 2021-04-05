#!/bin/sh

g++ -shared -O3 -Wall -std=c++11 -ggdb -fPIC -DUNIX -DLINUX $(python3 -m pybind11 --includes) ./CAENHV.cpp -o ./CAENHV$(python3-config --extension-suffix) -lcaenhvwrapper -lncurses -lpthread -ldl -lm $(python3-config --ldflags)