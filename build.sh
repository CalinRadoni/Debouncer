#!/bin/bash

set -ev

cd example
if [ $# -gt 0 ]; then
    make $1
else
    make
fi

[[ -f example ]] && ./example
