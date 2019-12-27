#include "mw1.h"
#include "ui_mw1.h"
#include "icon.h"
#include <string>
#include <map>
#include <iostream>
#include <QVBoxLayout>
#include <fstream>
#include <QProgressBar>
#include <QTime>
using namespace std;
static int k=0;
MW1::MW1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MW1)
{
    ui->setupUi(this);
    this->setFixedSize(1300,800);
    QObject::connect(&move,SIGNAL(timeout()),this,SLOT(update()));
    move.stop();
    monstertimer = new QTimer(this);
    monstertimer->stop();
    connect(monstertimer,SIGNAL(timeout()),this,SLOT(movingmonster()));
    _boss=new QTimer(this);
    _boss->stop();
    connect(_boss,SIGNAL(timeout()),this,SLOT(movingboss()));
    invincible=new QTimer(this);
    invincible->stop();
    connect(invincible,SIGNAL(timeout()),this,SLOT(setinvinc()));
    monscd=new QTimer;
    monscd->stop();
    connect(monscd,SIGNAL(timeout()),this,SLOT(logic()));
    lifeValue = new QProgressBar(this);
    lifetimer = new QTimer(this);
    lifeValue->setRange(0, 100);
    lifeValue->setValue(100);
    lifeValue->setGeometry(50,550,300,20);
    connect(&move, SIGNAL(timeout()), this, SLOT(updateProgress()));
    savename=new QLineEdit(this);
    savename->setGeometry(250,300,300,50);
    savename->setVisible(false);
    startButton = new QPushButton(this);
    startButton->setGeometry(250,600,100,50);
    if(_game.getSituation()==1)startButton->setText("开始游戏");

    QObject::connect(startButton,SIGNAL(clicked()),this,SLOT(start()));
    SaveButton = new QPushButton(this);
    SaveButton->setGeometry(350,600,100,50);
    SaveButton->setText("保存游戏");
    QObject::connect(SaveButton,SIGNAL(clicked()),this,SLOT(save()));
    LoadButton = new QPushButton(this);
    LoadButton->setGeometry(450,600,100,50);
    LoadButton->setText("加载游戏");
    QObject::connect(LoadButton,SIGNAL(clicked()),this,SLOT(load()));
    ContinueButton = new QPushButton(this);
    ContinueButton->setGeometry(250,100,200,200);
    ContinueButton->setStyleSheet("QPushButton{border-image:url(C:/Qt/map/Images/continuebutton.jpg)}""QPushButton:pressed{margin:2px 2px 2px 2px}");
    QObject::connect(ContinueButton,SIGNAL(clicked()),this,SLOT(Continue()));
    ContinueButton->setVisible(false);
    Confirm_save = new QPushButton(this);
    Confirm_save->setGeometry(300,400,100,100);
    Confirm_save->setStyleSheet("QPushButton{border-image:url(C:/Qt/map/Images/confirm_save.jpg);}""QPushButton:pressed{margin:2px 2px 2px 2px}");
    QObject::connect(Confirm_save,SIGNAL(clicked()),this,SLOT(confirm()));
    Confirm_save->setVisible(false);
    ifstream names("c:/Qt/map/Save&Load/save_name.txt");
    for(int i=0;i<8;i++){
        char ch[100]="";
        names.getline(ch,100);
        if(ch==""){ch[0]='E',ch[1]='m',ch[2]='p',ch[3]='t',ch[4]='y';}
        Loadname[i]=new QPushButton(tr(ch),this);
        Loadname[i]->setGeometry(150+(i%4)*200,100+(i/4)*300,150,150);
        Loadname[i]->setStyleSheet("QPushButton{background-color:black;color: white;   border-radius: 10px;  border: 2px groove gray;border-style: outset;}"

                                  "QPushButton:hover{background-color:white; color: black;}"

                                 "QPushButton:pressed{background-color:rgb(85, 170, 255);\border-style: inset; }"

                                  );
        Loadname[i]->setVisible(false);
        string str1(ch);
        l[i].n=str1;

    }
    QObject::connect(Loadname[0],SIGNAL(clicked()),this,SLOT(load_file1()));
    QObject::connect(Loadname[1],SIGNAL(clicked()),this,SLOT(load_file2()));
    QObject::connect(Loadname[2],SIGNAL(clicked()),this,SLOT(load_file3()));
    QObject::connect(Loadname[3],SIGNAL(clicked()),this,SLOT(load_file4()));
    QObject::connect(Loadname[4],SIGNAL(clicked()),this,SLOT(load_file5()));
    QObject::connect(Loadname[5],SIGNAL(clicked()),this,SLOT(load_file6()));
    QObject::connect(Loadname[6],SIGNAL(clicked()),this,SLOT(load_file7()));
    QObject::connect(Loadname[7],SIGNAL(clicked()),this,SLOT(load_file8()));
    //init game world
    _game.initWorld("c:\\Qt\\map\\map1.txt");//TODO 应该是输入有效的地图文件
    _game.setSituation(1);
}

MW1::~MW1()
{
    delete ui;
}

void MW1::paintEvent(QPaintEvent *e){
    QPainter *pa;
    pa = new QPainter();
    pa->begin(this);
    if(_game.getboss()->getlife()<=0)lifeValue->setVisible(false);
    //pa->drawImage(0,0,QImage("c:\\Qt\\map\\Images\\Wood1"));
    if(_game.getSituation()==2)startButton->setText("攻打女巫");
    if((up==0||left==0||right==0||down==0)&&_game.getplayer().getlife()>0){
        cout<<"0"<<endl;

    }
    _game.logic();
    this->_game.show(pa);
    pa->end();
    delete pa;
    if(_game.getwords()!="0"){
        QPainter painter(this);
        //设置一个矩形
        QRectF rect((_game.getplayer().getBindRect().left()+32), _game.getplayer().getBindRect().top(), 300, 50);

        //为了更直观地看到字体的位置，我们绘制出这个矩形
        painter.fillRect(rect,QBrush(QColor(0,85,255)));
        //我们这里先让字体水平居中
        QFont font("宋体", 10, QFont::Bold, true);
        //设置下划线
        font.setUnderline(true);
        //设置上划线
        font.setOverline(true);
        //设置字母大小写
        font.setCapitalization(QFont::SmallCaps);
        //设置字符间的间距
        font.setLetterSpacing(QFont::AbsoluteSpacing, 5);
        //使用字体
        painter.setFont(font);
        painter.setPen(Qt::white);
        painter.drawText(rect, Qt::AlignHCenter, QString::fromStdString(_game.getwords()));
        painter.translate(50, 50);
        //painter.rotate(90);
        //painter.drawText(0, 0, tr("helloqt"));
        _game.setwords("0");
    }
    if(issaved==1){

        QPainter painter(this);
        QRectF source(0,0,719,568);
        QRectF target(0,0,1000,700);
        QImage back("C:/Qt/map/Images/save_back.jpg");
        painter.drawImage(target,back,source);
        if(isloaded==1){
            QFont font("宋体", 12, QFont::Bold, true);
        font.setCapitalization(QFont::SmallCaps);
        //设置字符间的间距
        font.setLetterSpacing(QFont::AbsoluteSpacing, 4.5);
        //使用字体
        painter.setFont(font);
        painter.setPen(Qt::black);
        painter.drawText(170,250, QString::fromStdString("Please input the save file name:"));
        savename->setVisible(true);
        Confirm_save->setVisible(true);
        }
    }

}

void MW1::keyPressEvent(QKeyEvent *e)
{
    //direction = 1,2,3,4 for 上下左右
    if(_game.getplayer().getlife()>0&&!startButton->isVisible()&&issaved==0){

    if(e->key() == Qt::Key_A)
    {
        //left=1;
        connect(&move,SIGNAL(timeout()),this,SLOT(Playerleft()));
        this->_game.handlePlayerMove(3,2);
    }
    if(e->key() == Qt::Key_D)
    {
        //right=1;
        connect(&move,SIGNAL(timeout()),this,SLOT(Playeright()));
        this->_game.handlePlayerMove(4,2);
    }
    if(e->key() == Qt::Key_W)
    {
        //up=1;
        connect(&move,SIGNAL(timeout()),this,SLOT(Playerup()));
        this->_game.handlePlayerMove(1,2);
    }
    if(e->key() == Qt::Key_S)
    {
        //down=1;
        connect(&move,SIGNAL(timeout()),this,SLOT(Playerdown()));
         this->_game.handlePlayerMove(2,2);
    }
    if(e->key()==Qt::Key_J){
        _game.handleSkillsMove(_game.getplayer().getFaceDirection(),3,1);
    }
    }
    if(e->key()==Qt::Key_Escape){
        savename->setVisible(false);
        startButton->setVisible(true);
        LoadButton->setVisible(true);
        SaveButton->setVisible(true);
        Confirm_save->setVisible(false);
        move.stop();
        isSaved(0);
        isLoaded(0);
        for(int i=0;i<8;i++){
            Loadname[i]->setVisible(false);
        }

    }
    //this->repaint();
    if(_game.getplayer().getlife()<=0){
        ContinueButton->setVisible(true);
        LoadButton->setVisible(true);
        SaveButton->setVisible(true);
    }


}
void MW1::keyReleaseEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_W)
    {        
        _game.player_end_move();
    }
    if(event->key() == Qt::Key_S)
    {        
         _game.player_end_move();
    }
    if(event->key() == Qt::Key_A)
    {       
         _game.player_end_move();
    }
    if(event->key() == Qt::Key_D)
    {
        _game.player_end_move();
    }
}
void MW1::start(){
    startButton->setVisible(false);
    LoadButton->setVisible(false);
    SaveButton->setVisible(false);
    ContinueButton->setVisible(false);
    move.start(15);
    if(_game.getSituation()==1){monstertimer->start(1000);//怪兽移动
    monscd->start(3000);}
    invincible->start(5000);
    if(_game.getSituation()==2)_boss->start(3000);
}
void MW1::load(){
    /*string load="c:/Qt/map/Save&Load/test.txt";
    _game.initWorld(load);
    this->repaint();*/
    isSaved(1);
    this->update();
    _game.setSituation(0);
    startButton->setVisible(false);
    LoadButton->setVisible(false);
    SaveButton->setVisible(false);
    ContinueButton->setVisible(false);
    for(int i=0;i<8;i++){
        Loadname[i]->setVisible(true);
    }
}
void MW1::save(){
    isSaved(1);
    isLoaded(1);
    this->update();
    startButton->setVisible(false);
    LoadButton->setVisible(false);
    SaveButton->setVisible(false);
    ContinueButton->setVisible(false);
}
void MW1::Continue(){
    _game.reset_player(100);
    _game.player_invincible(true);
    _game.setifhurt(false);
    invincible->start(5000);
    lifeValue->setValue(100);
    this->repaint();
    startButton->setVisible(false);
    LoadButton->setVisible(false);
    SaveButton->setVisible(false);
    ContinueButton->setVisible(false);
}
string MW1::confirm(){
    string name=savename->text().toStdString();
    _game.save_game(name);
    Confirm_save->setVisible(false);
    savename->setVisible(false);
    startButton->setVisible(true);
    LoadButton->setVisible(true);
    SaveButton->setVisible(true);
    ContinueButton->setVisible(false);
    isSaved(0);
    isLoaded(0);
    this->repaint();
    ifstream names("c:/Qt/map/Save&Load/save_name.txt");
    for(int i=0;i<8;i++){
        char ch[100]="";
        names.getline(ch,100);
        string str1(ch);
        cout<<str1<<endl;
        Loadname[i]->setText(QString::fromStdString(str1));
        Loadname[i]->setVisible(false);
        l[i].n=str1;

    }
    return name;
}
void MW1::movingmonster(){//让怪物开始移动
    switch(k){
    case 0:
        _game.handleMonsterMove(1,2);
        k++;
        break;
    case 1:
        _game.handleMonsterMove(2,2);
        k--;
        break;
    }
    //this->repaint();
}

void MW1::updateProgress()
{
    if(_game.getifhurt()){
        // 获取当前进度值，+1
        _game.setifhurt(false);
        int nCurrentValue = lifeValue->value();
        nCurrentValue=_game.getplayer().getlife();
        // 设置新的进度值
        lifeValue->setValue(nCurrentValue);
    }
}
void MW1::setinvinc(){//无敌取消
    invincible->stop();
    _game.player_invincible(false);
}
void MW1::logic(){//冷却结束
    _game.setcd(true);
}
void MW1::movingboss(){//boss移动
    static int i=0;
    if(_game.getboss()->getlife()>0){
        _game.handleBossmove(i%4+1,1);
        _game.bossattack();
        i++;
    }
}
