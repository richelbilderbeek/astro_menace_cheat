#!/bin/bash
#
# Build and run AstroMenace
#

if [ ! -d astromenace ]
then
  git clone https://github.com/viewizard/astromenace
fi

if [ ! -d astromenace ]
then
  echo "ERROR: 'astromenace' folder not found"
  exit
fi

cd astromenace || exit 42
cmake ./
make
./astromenace
