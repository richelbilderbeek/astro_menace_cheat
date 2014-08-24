svn checkout http://svn.code.sf.net/p/openastromenace/code/ .
cp AstroMenace.patch ../
cd ..
patch -p0 -i AstroMenace.patch
rm AstroMenace.patch