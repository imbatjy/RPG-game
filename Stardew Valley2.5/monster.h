#ifndef MONSTER_H
#define MONSTER_H
#include "moveobjs.h"
#include <vector>
#include <string>
#include "icon.h"
#include "player.h"
#include <iostream>
using namespace std;
class Monster:public Player
{
public:
    Monster(){}
    ~Monster(){}
    string gettype(){return type;}
    void initm();
    void setype(string a){type=a;}//设定怪物名称
    void logic();
private:
    string type;
};

#endif // MONSTER_H
