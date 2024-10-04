#include "endingpanel.h"
#include <fstream>
#include<iostream>
#include <QPainter>

EndingPanel::EndingPanel(bool isLord, bool isWin, QWidget *parent) : QWidget(parent)
{
    m_bk.load(":/images/gameover.png");
    setFixedSize(m_bk.size());

    m_title = new QLabel(this);
    if(isLord && isWin)
    {
        m_title->setPixmap(QPixmap(":/images/lord_win.png"));
    }
    else if(isLord && !isWin)
    {
        m_title->setPixmap(QPixmap(":/images/lord_fail.png"));
    }
    else if(!isLord && isWin)
    {
        m_title->setPixmap(QPixmap(":/images/farmer_win.png"));
    }
    else if(!isLord && !isWin)
    {
        m_title->setPixmap(QPixmap(":/images/farmer_fail.png"));
    }
    m_title->move(125, 125);

    m_score = new ScorePanel(this);
    m_score->move(75, 230);
    m_score->setFixedSize(150, 150);
    m_score->setMyFontColor(ScorePanel::Red);
    m_score->setMyFontSize(10);

    m_continue = new QPushButton(this);
    m_continue->move(84, 429);
    QString style = R"(
        QPushButton{border-image: url(:/images/button_normal.png)}
        QPushButton:hover{border-image: url(:/images/button_hover.png)}
        QPushButton:pressed{border-image: url(:/images/button_pressed.png)}
    )";
    m_continue->setStyleSheet(style);
    m_continue->setFixedSize(231, 48);
    connect(m_continue, &QPushButton::clicked, this, &EndingPanel::continueGame);
}

void EndingPanel::setPlayerScore(int left, int right, int me) {
    int readLeft = 0, readRight, readMe;
    // 创建并打开一个本地.txt文件
    std::ofstream file("scores.txt");

    // 将left、right、me的值分别写入文件的三行
    file << "分数结算：" << std::endl;
    file << "左侧机器人: " << left << std::endl;
    file << "右侧机器人: " << right << std::endl;
    file << "我: " << me << std::endl;

    // 关闭文件
    file.close();

    // 读取文件
    std::ifstream readFile("scores.txt");

    // 检查文件是否成功打开
    if (readFile.is_open()) {
        std::string line;

        // 读取文件内容并解析值
        // 第一行为标题，可以跳过
        std::getline(readFile, line);

        // 读取左侧机器人的值
        std::getline(readFile, line);
        int readLeft = std::stoi(line.substr(line.find(":") + 2));

        // 读取右侧机器人的值
        std::getline(readFile, line);
        int readRight = std::stoi(line.substr(line.find(":") + 2));

        // 读取我的值
        std::getline(readFile, line);
        int readMe = std::stoi(line.substr(line.find(":") + 2));

        // 关闭读取文件
        readFile.close();

        // 现在，readLeft、readRight、readMe 分别包含了读取的值
        // 可以将它们用于其他逻辑或输出
    }
    else {
        // 文件打开失败的处理
        std::cerr << "无法打开文件 scores.txt" << std::endl;
    }

    m_score->setScores(left,right, me);
}

void EndingPanel::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev)
    QPainter p(this);
    p.drawPixmap(rect(), m_bk);
}
