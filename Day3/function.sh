#!/usr/bin/env bash
make(){
    mkdir -p "$1"
    cd "$1"
}
make $1