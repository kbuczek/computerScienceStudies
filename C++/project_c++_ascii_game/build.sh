#!/bin/bash

cmake -S . -B bin
cd bin
make
cd ..
./bin/projekt_c__
