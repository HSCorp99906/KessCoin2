#!/bin/bash
# 
# Buildscript for KessCoin2

echo "Building..."
g++ ../src/*.cpp -o ../bin/main
gcc ../src/*.c -lssl -lcrypto -w -o ../bin/keygen
