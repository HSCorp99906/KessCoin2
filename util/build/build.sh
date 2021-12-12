#!/bin/bash
# 
# Buildscript for KessCoin2

echo "Building..."
g++ ../checktransaction.c -o ../bin/main -lcurl
