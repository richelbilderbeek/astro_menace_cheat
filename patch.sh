#!/bin/bash

if [ ! -d astromenace ]
then
  git clone https://github.com/viewizard/astromenace
fi

if [ ! -d astromenace ]
then
  echo "ERROR: 'astromenace' folder not found"
  exit
fi

# qmake patch.pro || exit 42
# make debug || exit 42
g++ main.cpp -o astromenace_patch_code

./astromenace_patch_code \
  astromenace/src/menu/menu_workshop_workshop.cpp \
  astromenace/src/menu/menu_workshop_shipyard.cpp \
  astromenace/src/menu/menu_workshop_weaponry.cpp || exit 42
