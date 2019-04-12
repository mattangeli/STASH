#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

using namespace std;

/* Generic block */
class Block
{
private:
    int id;
    int nLegsOut;
    vector<int> idsOut;
    vector<float> probsOut;
public:
    Block(int, vector<int>, vector<float>);
    virtual void ABBA() {
        cout << "I'm a Block and you are a Block." << endl;
    }
};


/* Generic task block */
class taskBlock : public Block
{
private:

public:
    taskBlock(int, vector<int>, vector<float>);
    void ABBA() {
        cout << "I'm a taskBlock and I suck!" << endl;
    }
};


/* Exclusive gateway */
class xorBlock : public Block
{
private:

public:
    xorBlock(int, vector<int>, vector<float>);
    void ABBA() {
        cout << "I'm a xorBlock and I suck even more!" << endl;
    }
};


#endif // BLOCK_H
