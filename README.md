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
qmake && make
./SimulationEngine
```

and you should see some Hello World stuff.

#### cmake
If you prefer `cmake`, try

```
cmake . && make
./SimulationEngine
```