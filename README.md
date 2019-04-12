# highSTASH
cHarming busIness manaGement macHinery (by) Seclì, Tisi, Angeli, genoveSe (and) koHn.


## Quick compile guide

### Requirements
So far, just standard libraries and `qmake`. You can install it in this way:

+ **Ubuntu:** `sudo apt install qt5-qmake`
+ **MacOS:** `brew install qt5` (unfortunately, no `qmake`-only solution)

As an alternative, you can also use `cmake` (though no support is guaranteed on it).

### Compiling procedure

#### qmake
Just run

```
mkdir build && cd build
qmake .. && make
./SimulationEngine
```

and you should see some Hello World stuff.

The Makefile has the usual syntax; to clan all the temporary files but not the final binary:

```
make clean
```

while instead if you want to clean everything:

```
make distclean
```

#### cmake
If you prefer `cmake`, try

```
mkdir build && cd build
cmake .. && make
./SimulationEngine
```

### Cleaning
To completely remove all the build files, including the Makefile:
```
cd ..
rm -rf build
```
