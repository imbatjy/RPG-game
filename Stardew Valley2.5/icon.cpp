#include "icon.h"
#include<iostream>
int ICON::GRID_SIZE = 32;


pair<string,ICON> pairArray[] =
{
    //make_pair("player",ICON("player",1,13, 1, 2)),
    make_pair("stone",ICON("stone",4,9, 1, 1)),
    make_pair("fruit",ICON("fruit",3,6, 1, 1)),
    make_pair("tree1",ICON("tree1",0,9,2,2)),
    make_pair("house",ICON("house",12,4,4,6)),
    make_pair("bottom",ICON("bottom",3,2,3,1)),
    make_pair("road1",ICON("road1",0,13,1,3)),
    make_pair("bottle",ICON("bottle",12,2,1,1)),
    make_pair("store",ICON("store",8,7,4,3)),
    make_pair("tomb",ICON("tomb",8,12,1,2)),
    make_pair("well",ICON("well",2,10,2,3))

};

map<string,ICON> ICON::GAME_ICON_SET(pairArray,pairArray+sizeof(pairArray)/sizeof(pairArray[0]));


ICON::ICON(string name, int x, int y, int w, int h){
    this->typeName = name;
    this->srcX = x;
    this->srcY = y;
    this->width = w;
    this->height = h;
}

ICON ICON::findICON(string type){
    map<string,ICON>::iterator kv;
    kv = ICON::GAME_ICON_SET.find(type);
    if (kv==ICON::GAME_ICON_SET.end()){

       cout<<"Error: cannot find ICON"<<endl;
       return ICON();
    }
    else{
        return kv->second;
    }
}
