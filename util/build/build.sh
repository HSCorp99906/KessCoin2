#!/bin/bash
# 
# Buildscript for KessCoin2

echo "Building..."
g++ ../_checktransaction.c -o ../bin/main -lcurl
