#!/bin/bash

if [ ! -d AstroMenaceSource ]
then
  git clone https://github.com/viewizard/astromenace

fi

# cp AstroMenace.patch ../
# cd ..
# 
# if [ ! -e AstroMenace.patch ]
# then
#   echo "ERROR: AstroMenace.patch not found in parent folder of AstroMenaceCheat"
#   exit
# fi

# patch -p0 -i AstroMenace.patch
# rm AstroMenace.patch

if [ ! -d astromenace ]
then
  echo "ERROR: 'astromenace' folder not found"
  exit
fi

g++ main.cpp -o astromenace_patch_code

# qmake patch.pro || exit 42
# make debug || exit 42
./astromenace_patch_code \
  astromenace/src/menu/menu_workshop_workshop.cpp \
  astromenace/src/menu/menu_workshop_shipyard.cpp \
  astromenace/src/menu/menu_workshop_weaponry.cpp || exit 42

cd astromenace || exit 42

cmake ./
make
# ./astromenace --pack --rawdata=./RAW_VFS_DATA
./astromenace
