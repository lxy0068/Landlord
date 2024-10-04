/********************************************************************************
** Form generated from reading UI file 'gamepanel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEPANEL_H
#define UI_GAMEPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "buttongroup.h"
#include "scorepanel.h"

QT_BEGIN_NAMESPACE

class Ui_GamePanel
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    ScorePanel *scorePanel;
    QSpacerItem *verticalSpacer;
    ButtonGroup *btnGroup;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GamePanel)
    {
        if (GamePanel->objectName().isEmpty())
            GamePanel->setObjectName(QString::fromUtf8("GamePanel"));
        GamePanel->resize(800, 600);
        centralwidget = new QWidget(GamePanel);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(736, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        scorePanel = new ScorePanel(widget);
        scorePanel->setObjectName(QString::fromUtf8("scorePanel"));

        horizontalLayout->addWidget(scorePanel);


        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btnGroup = new ButtonGroup(centralwidget);
        btnGroup->setObjectName(QString::fromUtf8("btnGroup"));

        verticalLayout->addWidget(btnGroup);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        GamePanel->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GamePanel);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        GamePanel->setMenuBar(menubar);
        statusbar = new QStatusBar(GamePanel);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GamePanel->setStatusBar(statusbar);

        retranslateUi(GamePanel);

        QMetaObject::connectSlotsByName(GamePanel);
    } // setupUi

    void retranslateUi(QMainWindow *GamePanel)
    {
        GamePanel->setWindowTitle(QCoreApplication::translate("GamePanel", "GamePanel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GamePanel: public Ui_GamePanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEPANEL_H
