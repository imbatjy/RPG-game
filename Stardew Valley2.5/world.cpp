#include "world.h"
#include "icon.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <QPainter>
#include <math.h>
using namespace std;
World::World(){
    this->setSituation(1);
    this->situ1.load("C:/Qt/map/Images/situ1.jpg");
    this->situ2.load("C:/Qt/map/Images/situ2.jpg");
    this->situ3.load("C:/Qt/map/Images/win.jpg");
}
void World::initWorld(string mapFile){
    //读入地图文件，生成地图上的对象
    const char * out=mapFile.c_str();
    ifstream _map(out);

    RPGObj _obj;
    int i=0;
    if(!_objs.empty()){//判断是否为空，并使其为空（为加载功能铺垫）
        _objs.clear();
    }
    while(!_map.eof())
    {
        char ch[100]="";
       _map.getline(ch,100);
       vector<string> res;
       string s="";
       s=ch;
       string result;
           //将字符串读到input中
       stringstream input(s);
       while(input>>result)//将文件每行按空格符分开
            res.push_back(result);

       if(i==0){//第一行为player信息
           _player.initp();
           _player.setRect(atof(res[1].c_str()),atof(res[2].c_str()),67,105);
           _player.setlife(atoi(res[3].c_str()));
       }else{
           _obj.initObj(res[0]);
           _obj.setPosX(atoi(res[1].c_str()));
           _obj.setPosY(atoi(res[2].c_str()));
           _obj.setRect(_obj.getPosX(),_obj.getPosY(),_obj.getWidth(),_obj.getHeight());
           this->_objs.push_back(_obj);//把静态物体放到存rbgobjs的vector里
       }
       i++;
    }
   if(situation==1){ //第一张图中的怪物
       _monster1=new Monster;
       _monster1->setRect(700,350,40,85);
       _monster1->setype("wolf");
       _monster1->initm();}
    if(situation==2){//第二图中的boss
        _b=new Boss;
        _b->setRect(700,200,95,224);
        _b->setype("boss");
        _b->initp();
    }
    fire=new Skills("fire");//技能声明
    thunder=new Skills("thunder");
    _ps.push_back(fire);//并将技能存到储存skill的vector里
    _ps.push_back(thunder);
    _map.close();
    cd=false;
    ifhurt=false;
}


void World::show(QPainter * painter){
    if(situation==1||situation==0)painter->drawImage(0,0,situ1);
    if(situation==2)painter->drawImage(0,0,situ2);
    vector<RPGObj>::iterator it;
    for(it=this->_objs.begin();it!=this->_objs.end();it++){
        if((*it).canEat())(*it).show(painter);
    }
    vector<Skills*>::iterator s;

    if(!_s.empty()){
        for(s=this->_s.begin();s!=this->_s.end();s++){

            if((*s)->getstart()!=3){
                (*s)->logic();
                monskills_move((*s)->getBindRect(),(*s));
                (*s)->draw(painter);
            }
            else (*s)->logic();
        }
    }
    vector<Skills*>::iterator bs;

    if(!_bs.empty()){
        for(bs=this->_bs.begin();bs!=this->_bs.end();bs++){

            if((*bs)->getstart()!=3){
                (*bs)->logic();
                monskills_move((*bs)->getBindRect(),(*bs));
                (*bs)->draw(painter);
            }
            //((*s)->getstart()==3)s=_s.erase(s);
        }
    }
    this->_player.logic();
    this->_player.draw(painter);
    if(_b->getlife()>0){
        _b->logic();
        _b->draw(painter);
    }else{
        painter->drawImage(100,0,situ3);
    }
       if(situation==1){_monster1->logic();
       _monster1->draw(painter);}else _monster1->logic();
     if(fire->getstart()!=3)
     {fire->logic();skills_if_move(fire->getBindRect(),fire);fire->draw(painter);}else fire->logic();
     if(_monster1->getBindRect().intersects(_player.getBindRect())&&!_player.get_invincible()){
         _player.setlife(_player.getlife()-1);
         ifhurt=true;
    }
}
int World::Player_if_move(QRectF bind){
    vector<RPGObj>::iterator it;
    for(it=this->_objs.begin();it!=this->_objs.end();it++){
        //cout<<"1"<<endl;
        if(bind.intersects((*it).getBindRect())){//判断移动点是否在图形边框内
            if((*it).canDead()&&!_player.get_invincible()){
                _player.setlife(_player.getlife()-1);//死亡点生命值减1
                ifhurt=true;
               if(_player.getlife()>=0)
                   cout<<"You have "<<_player.getlife()<<" life."<<endl;
            }
            if((*it).cantalk()&&!_player.get_invincible()){
                this->_words=(*it).talks();
                return 3;
            }
            if(!(*it).canCover())return 0;
            if((*it).canBang())return 2;
            if((*it).canEat()){
                //(*it).setRect(-1,-1,0,0);
                it=_objs.erase(it);//移除吃掉的物体
                break;
            }
        }
    }
    if(bind.left()>=1000&&bind.top()>=300&&bind.top()<=500){
        situation=2;
        initWorld("c:\\Qt\\map\\boss.txt");

    }
   // cout<<"test"<<endl;
    return 1;
}

void World::handlePlayerMove(int direction, int steps){
    _player.setFaceDirection(direction);
    switch (direction){
        case 1:
            _player.startMove(0,-steps);
            break;
        case 2:
            _player.startMove(0,steps);
            break;
        case 3:
            _player.startMove(-steps,0);
            break;
        case 4:
            _player.startMove(steps,0);
            break;
    }

}
void World::save_game(string save_file_name){
    string out="c:/Qt/map/Save&Load/"+save_file_name+".txt";
    const char * path=out.c_str();
    ofstream save(path);
    save<<"player"<<" "<<_player.getBindRect().left()<<" "<<_player.getBindRect().top()<<" "<<_player.getlife();
    vector<RPGObj>::iterator it;
    for(it=this->_objs.begin();it!=this->_objs.end();it++){
        save<<endl<<(*it).getObjType()<<" "<<(*it).getBindRect().left()<<" "<<(*it).getBindRect().top();
    }
    save_name(save_file_name);
}
void World::save_name(string save_file_name){
    string out="c:/Qt/map/Save&Load/save_name.txt";
    const char * path=out.c_str();
    ofstream savename(path,ios::app);
    savename<<save_file_name<<endl;
}
bool World::if_collapse(QRectF a, QRectF b){
    if(a.intersects(b))return true;
    return false;
}
void World::handleMonsterMove(int direction, int steps){
   _monster1->setFaceDirection(direction);
    switch (direction){
        case 1:
           _monster1->startMove(0,-steps);
            break;
        case 2:
           _monster1->startMove(0,steps);
            break;
        case 3:
           _monster1->startMove(-steps,0);
            break;
        case 4:
           _monster1->startMove(steps,0);
            break;
    }
}
void World::handleSkillsMove(int direction, int steps,int a){
    if(a==1){
        fire->resetall();
        fire->setRect(_player.getBindRect().left(),_player.getBindRect().top(),32,32);
        fire->setFaceDirection(direction);
        switch (direction){
        case 1:
            fire->startMove(0,-steps);
            break;
        case 2:
            fire->startMove(0,steps);
            break;
        case 3:
            fire->startMove(-steps,0);
            break;
        case 4:
            fire->startMove(steps,0);
            break;
        }
    }
}
void World::skills_if_move(QRectF bind,Skills* a){
    vector<RPGObj>::iterator it;
    for(it=this->_objs.begin();it!=this->_objs.end();it++){
        if(bind.intersects((*it).getBindRect())){//判断移动点是否在图形边框内
            if(!(*it).canCover()){
                a->endMove();
                a->setend(1);
            }
            if((*it).canEat()){
                it=_objs.erase(it);//移除吃掉的物体
                break;
            }
        }
    }
    vector<Skills*>::iterator s;
    if(!_s.empty()){
        for(s=this->_s.begin();s!=this->_s.end();s++){
            if(bind.intersects((*s)->getBindRect())){//判断移动点是否在图形边框内
                a->endMove();
                a->setend(1);
            }

        }
    }
        if(bind.intersects(_monster1->getBindRect())){
            _monster1->setlife(_monster1->getlife()-1);
            a->endMove();
            a->setend(1);
        }
    if(bind.intersects(_b->getBindRect())){
        _b->setlife(_b->getlife()-1);
        a->endMove();
        a->setend(1);
    }
}
void World::logic(){
    if((situation==1||situation==2)&&Dis(_monster1)<=300&&cd){
        attack(_monster1,_player.getBindRect().left(),_player.getBindRect().top());
        cd=false;
    }
}
double World::Dis(Monster* mons){
    return sqrt((mons->getBindRect().left()-_player.getBindRect().left())*(mons->getBindRect().left()-_player.getBindRect().left())
                +(mons->getBindRect().top()-_player.getBindRect().top())*(mons->getBindRect().top()-_player.getBindRect().top()));
}
void World::attack(Monster* a, double x, double y){
    double dx=a->getBindRect().left()-x;
    double dy=a->getBindRect().top()-y;
    double sin0=fabs(Dis(a)/dx);
    double cos0=fabs(Dis(a)/dy);
    Skills *b;
    if(a->gettype()=="wolf"){
        b=new Skills("fire");
    }
    if(dx>0&&dy>0)b->startMove(-2/sin0,-2/cos0);
    else if(dx>0&&dy<0)b->startMove(-2/sin0,2/cos0);
    else if(dx<0&&dy<0)b->startMove(2/sin0,2/cos0);
    else if(dx<0&&dy>0)b->startMove(2/sin0,-2/cos0);
    b->setRect(a->getBindRect().left(),a->getBindRect().top(),32,32);
    b->resetall();
    _s.push_back(b);

}
void World::monskills_move(QRectF bind, Skills * a){
    vector<RPGObj>::iterator it;
    for(it=this->_objs.begin();it!=this->_objs.end();it++){
        if(bind.intersects((*it).getBindRect())){//判断移动点是否在图形边框内
            if(!(*it).canCover()){
                a->endMove();
                a->setend(1);
            }
            if((*it).canEat()){
                it=_objs.erase(it);//移除吃掉的物体
                break;
            }
        }
    }
    vector<Skills*>::iterator s;
    for(s=this->_ps.begin();s!=this->_ps.end();s++){
        if(bind.intersects((*s)->getBindRect())&&!_player.get_invincible()){//判断移动点是否在图形边框内
            a->endMove();
            a->setend(1);
        }

    }
    if(bind.intersects(_player.getBindRect())&&!_player.get_invincible()){
        _player.setlife(_player.getlife()-1);
        a->endMove();
        a->setend(1);
        ifhurt=true;
    }
}
void World::handleBossmove(int direction, int steps){
    _b->setFaceDirection(direction);
    switch (direction){
        case 1:
            _b->startMove(0,-steps);
            break;
        case 2:
            _b->startMove(0,steps);
            break;
        case 3:
            _b->startMove(-steps,0);
            break;
        case 4:
            _b->startMove(steps,0);
            break;
    }
}
void World::bossattack(){
    Skills* a[5];
    for(int i=0;i<5;i++){
        a[i]=new Skills("thunder");
        _bs.push_back(a[i]);
        a[i]->startMove(-i/5.0,(5-i)/5.0);
        a[i]->setRect(_b->getBindRect().left(),_b->getBindRect().top(),32,32);
        a[i]->resetall();
    }
}
int World::getPlayerPsX(){
    return this->_player.getBindRect().left();
}

int World::getPlayerPsY(){
    return this->_player.getBindRect().top();
}
void World::setPlayerPs(int x, int y){
    this->_player.transed(x,y);
}
