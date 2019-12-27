#ifndef WORLD_H
#define WORLD_H
#include "rpgobj.h"
#include <vector>
#include <string>
#include <QPainter>
#include "player.h"
#include "moveobjs.h"
#include "monster.h"
#include "boss.h"
class World
{
public:
    World();
    ~World(){}
    void initWorld(string mapFile);
        //输入的文件中定义了初始状态下游戏世界有哪些对象，出生点在哪
        /*e.g.
           player 5 5
           stone 3 3
           fruit 7 8
         */
    void show(QPainter * painter);
        //显示游戏世界所有对象
    void handlePlayerMove(int direction, int steps);//player移动
     void handleMonsterMove(int direction, int steps);//怪物移动
        //假定只有一个玩家
     void handleSkillsMove(int,int,int);//技能移动
    int Player_if_move(QRectF);//判断是否可以覆盖次移动点
    Player getplayer(){return _player;}
    Skills* getfire(){return fire;}
    Skills* getthunder(){return thunder;}
    void reset_player(int a){_player.setlife(a);}//重置player生命值
    string getwords(){return this->_words;}
    void setwords(string word){_words=word;}//设定对话
    void save_game(string save_file_name);//储存游戏中静态物品位置
    void save_name(string save_file_name);//储存存档名字
    bool if_collapse(QRectF,QRectF);//判断是否碰撞
    void player_end_move(){_player.endMove();}
    QRectF playertrans(int a,int b){return _player.trans(a,b);}
    void playertransed(int a ,int b){_player.transed(a,b);}
    void player_invincible(bool a){_player.set_invincible(a);}
    void skills_if_move(QRectF,Skills*);//技能移动判断逻辑
    void logic();//怪物攻击逻辑判断
    double Dis(Monster*);//判断player和怪物之间距离
    void attack(Monster*,double,double);//怪物攻击
    void setcd(bool a){cd=a;}//设置冷却
    void monskills_move(QRectF,Skills*);//怪物技能移动判断
    bool getifhurt(){return ifhurt;}
    void setifhurt(bool a){ifhurt=a;}//是否受伤
    void handleBossmove(int,int);//boss移动
    void bossattack();//boss攻击
    void setSituation(int situ){this->situation = situ;}//设置场景编号
    int getSituation(){return this->situation;}
    int getPlayerPsX();
    int getPlayerPsY();
    void setPlayerPs(int x, int y);
    Boss* getboss(){return this->_b;}
private:
    vector<RPGObj> _objs;//储存静态地图背景
    vector<Skills*>_s;//储存技能种类
    vector<Skills*>_ps;//储存玩家技能数量
    vector<Skills*>_bs;//储存怪物技能数量
    Skills *thunder;
    Skills *fire;
    Player _player;
    Monster *_monster1;
    string _words="0";
    Boss *_b;
    bool cd;
    bool ifhurt=false;//判断是否受伤
    int situation;//地图场景标志
public:
    QImage situ1, situ2, situ3;
};

#endif // WORLD_H
