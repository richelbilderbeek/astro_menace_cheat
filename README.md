# AstroMenace cheat

Patch to cheat at AstroMenace:
 * All weapons, equipment, ships cost $1
 * All ships have level 5 weapon slots only

![Screenshot](GameAstroMenaceCheated.png)


## Using the patch


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
