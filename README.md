# AstroMenace cheat

Patch to cheat at [AstroMenace](https://github.com/viewizard/astromenace):

 * All weapons, equipment, ships cost $1
 * All ships have level 5 weapon slots only

![Screenshot](GameAstroMenaceCheated.png)


## Using the patch

Using the script patch.sh:

```
./patch.sh
```

This
* downloads the code
* applies the patch
* builds the code
* starts the game


## Creating the patch

Obtained code at 2014-08-24:

```
svn checkout http://svn.code.sf.net/p/openastromenace/code/ AstroMenace
```

(there must be a space between `code/` and `AstroMenace`)


Copied code:

```
cp -r AstroMenace AstroMenaceCheat
```

Modified code of `AstroMenaceCheat`.

Created patch:

```
diff -crB AstroMenace AstroMenaceCheat > AstroMenace.patch
```
