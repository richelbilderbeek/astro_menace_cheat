

if [ d AstroMenaceSource ]
then
  svn checkout http://svn.code.sf.net/p/openastromenace/code/ .
fi

# Might install more than the minimum, feel free to improve this by submitting 
# an Issue on the GitHub :-)
sudo apt-get install libopenal1 libalut0 libogg0 libvorbis*

cp AstroMenace.patch ../
cd ..
patch -p0 -i AstroMenace.patch
rm AstroMenace.patch
cd AstroMenaceCheat
cmake ./
make
./AstroMenace --pack --rawdata=./RAW_VFS_DATA
./AstroMenace