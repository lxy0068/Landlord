#include "buttongroup.h"
#include "ui_buttongroup.h"

ButtonGroup::ButtonGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ButtonGroup)
{
    ui->setupUi(this);
}

ButtonGroup::~ButtonGroup()
{
    delete ui;
}

void ButtonGroup::initButtons()
{
    ui->start->setImage(":/images/start-1.png", ":/images/start-3.png", ":/images/start-2.png");
    ui->playCard->setImage(":/images/chupai_btn-1.png", ":/images/chupai_btn-3.png", ":/images/chupai_btn-2.png");
    ui->playCard1->setImage(":/images/chupai_btn-1.png", ":/images/chupai_btn-3.png", ":/images/chupai_btn-2.png");

    ui->pass->setImage(":/images/pass_btn-1.png", ":/images/pass_btn-3.png", ":/images/pass_btn-2.png");
    ui->giveup->setImage(":/images/buqiang-1.png", ":/images/buqiang-3.png", ":/images/buqiang-2.png");
    ui->oneScore->setImage(":/images/1fen-1.png", ":/images/1fen-3.png", ":/images/1fen-2.png");
    ui->twoScore->setImage(":/images/2fen-1.png", ":/images/2fen-3.png", ":/images/2fen-2.png");
    ui->threeScore->setImage(":/images/3fen-1.png", ":/images/3fen-3.png", ":/images/3fen-2.png");

    QVector<MyButton*> btns;
    btns << ui->start << ui->playCard << ui->playCard1 << ui->pass
         << ui->giveup << ui->oneScore << ui->twoScore << ui->threeScore;
    for(int i=0; i<btns.size(); ++i)
    {
        btns[i]->setFixedSize(90, 45);
    }

    connect(ui->start, &MyButton::clicked, this, &ButtonGroup::startGame);
    connect(ui->playCard, &MyButton::clicked, this, &ButtonGroup::playHand);
    connect(ui->playCard1, &MyButton::clicked, this, &ButtonGroup::playHand);
    connect(ui->pass, &MyButton::clicked, this, &ButtonGroup::pass);
    connect(ui->giveup, &MyButton::clicked, this, [=]()
    {
        emit betPoint(0);
    });
    connect(ui->oneScore, &MyButton::clicked, this, [=]()
    {
        emit betPoint(1);
    });
    connect(ui->twoScore, &MyButton::clicked, this, [=]()
    {
        emit betPoint(2);
    });
    connect(ui->threeScore, &MyButton::clicked, this, [=]()
    {
        emit betPoint(3);
    });
}

void ButtonGroup::selectPanel(Panel type, int bet)
{
    ui->stackedWidget->setCurrentIndex(type);
    if(type != CallLord)
    {
        return;
    }
    if(bet == 0)
    {
        ui->oneScore->setVisible(true);
        ui->twoScore->setVisible(true);
        ui->threeScore->setVisible(true);
    }
    else if(bet == 1)
    {
        ui->oneScore->setVisible(false);
        ui->twoScore->setVisible(true);
        ui->threeScore->setVisible(true);
    }
    else if(bet == 2)
    {
        ui->oneScore->setVisible(false);
        ui->twoScore->setVisible(false);
        ui->threeScore->setVisible(true);
    }
}
