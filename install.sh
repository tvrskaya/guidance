#!/bin/bash

if [ ! -d lib ]; then 
    mkdir lib
fi

cd lib

git clone https://github.com/google/googletest.git
