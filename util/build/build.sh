#!/bin/bash
# 
# Buildscript for KessCoin2

echo "Building..."
gcc ../checktransaction.c -o ../bin/main -lcurl
