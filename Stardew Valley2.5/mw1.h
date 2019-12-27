#ifndef MW1_H
#define MW1_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QPushButton>
#include<QKeyEvent>
#include "rpgobj.h"
#include "world.h"
#include "player.h"
#include <QLineEdit>
#include <QTimer>
#include <QProgressDialog>
#include <QTime>
namespace Ui {
class MW1;
}
struct load_name{
    string n="0";
};
class MW1 : public QMainWindow
{
    Q_OBJECT

public:
    QPushButton* startButton;
    QPushButton* SaveButton;
    QPushButton* LoadButton;
    QPushButton* ContinueButton;
    QPushButton* Confirm_save;
    QPushButton* Loadname[8];
    QProgressBar* lifeValue;
    explicit MW1(QWidget *parent = 0);
    ~MW1();
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void isSaved(int a){issaved=a;}
    void isLoaded(int a){isloaded=a;}

private:
    Ui::MW1 *ui;
    World _game;
    int issaved=0;
    int isloaded=0;
    load_name l[8];
    QLineEdit*savename;
    Player _hero;
    QTimer move,*lifetimer,*monstertimer,*invincible,*monscd, *_boss;//刷新率、怪物移动、无敌时间、怪物技能冷却时间、boss冷却时间
    int up=1,down=1,right=1,left=1;

public slots:
    void Playerup(){if(_game.Player_if_move(_game.playertrans(0,-1))==0){up=0;_game.playertransed(0,2);}else up=1;}
    void Playerdown(){if(_game.Player_if_move(_game.playertrans(0,1))==0){down=0;_game.playertransed(0,-2);}else down=1;}
    void Playerleft(){if(_game.Player_if_move(_game.playertrans(-1,0))==0){left=0;_game.playertransed(2,0);}else left=1;}
    void Playeright(){if(_game.Player_if_move(_game.playertrans(1,0))==0){right=0;_game.playertransed(-2,0);}else right=1;}
    void start();
    void movingmonster();
    void movingboss();
    void updateProgress();
    void setinvinc();
    void save();
    void load();
    void Continue();
    void logic();
    void load_file1(){string path="c:/Qt/map/Save&Load/"+l[0].n+".txt";_game.initWorld(path);isSaved(0);this->update();for(int i=0;i<8;i++){
            Loadname[i]->setVisible(false);
        }}
    void load_file2(){string path="c:/Qt/map/Save&Load/"+l[1].n+".txt";_game.initWorld(path);isSaved(0);this->update();for(int i=0;i<8;i++){
            Loadname[i]->setVisible(false);
        }}
    void load_file3(){string path="c:/Qt/map/Save&Load/"+l[2].n+".txt";_game.initWorld(path);isSaved(0);this->update();for(int i=0;i<8;i++){
            Loadname[i]->setVisible(false);
        }}
    void load_file4(){string path="c:/Qt/map/Save&Load/"+l[3].n+".txt";_game.initWorld(path);isSaved(0);this->update();for(int i=0;i<8;i++){
            Loadname[i]->setVisible(false);
        }}
    void load_file5(){string path="c:/Qt/map/Save&Load/"+l[4].n+".txt";_game.initWorld(path);isSaved(0);this->update();for(int i=0;i<8;i++){
            Loadname[i]->setVisible(false);
        }}
    void load_file6(){string path="c:/Qt/map/Save&Load/"+l[5].n+".txt";_game.initWorld(path);isSaved(0);this->update();for(int i=0;i<8;i++){
            Loadname[i]->setVisible(false);
        }}
    void load_file7(){string path="c:/Qt/map/Save&Load/"+l[6].n+".txt";_game.initWorld(path);isSaved(0);this->update();for(int i=0;i<8;i++){
            Loadname[i]->setVisible(false);
        }}
    void load_file8(){string path="c:/Qt/map/Save&Load/"+l[7].n+".txt";_game.initWorld(path);isSaved(0);this->update();for(int i=0;i<8;i++){
            Loadname[i]->setVisible(false);
        }}
    string confirm();
};

#endif // MW1_H
