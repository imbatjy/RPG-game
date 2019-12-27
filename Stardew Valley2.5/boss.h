#ifndef BOSS_H
#define BOSS_H
#include "monster.h"
#include "player.h"
#include "moveobjs.h"
#include <vector>
#include <string>
#include "icon.h"
#include "player.h"
#include <iostream>
using namespace std;

class Boss:public Monster
{
public:
    Boss(){}
    ~Boss();
    void initp();
    void move();//重载move（）
};

#endif // BOSS_H
