#include "bgmcontrol.h"
#include "playhand.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRandomGenerator>
#include <QTimer>

BGMControl::BGMControl(QObject *parent) : QObject(parent)
{
    for(int i=0; i<5; ++i)
    {
        QMediaPlayer* player = new QMediaPlayer(this);
        QMediaPlaylist* list = new QMediaPlaylist(this);
        if(i<2 || i == 4)
        {
            list->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        }
        else if(i == 2)
        {
            list->setPlaybackMode(QMediaPlaylist::Loop);
        }
        player->setPlaylist(list);
        player->setVolume(100);
        m_players.push_back(player);
        m_lists.push_back(list);
    }
    initPlayList();
}

void BGMControl::initPlayList()
{
    QStringList list;
    list << "Man" << "Woman" << "BGM" << "Other" << "Ending";

    QFile file(":/conf/playList.json");
    file.open(QFile::ReadOnly);
    QByteArray json = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonObject obj = doc.object();

    for(int i=0; i<list.size(); ++i)
    {
        QString prefix = list.at(i);
        QJsonArray array = obj.value(prefix).toArray();
        for(int j=0; j<array.size(); ++j)
        {
            m_lists[i]->addMedia(QMediaContent(QUrl(array.at(j).toString())));
        }
    }
}

void BGMControl::startBGM(int volume)
{
    m_lists[2]->setCurrentIndex(0);
    m_players[2]->setVolume(volume);
    m_players[2]->play();
}

void BGMControl::stopBGM()
{
    m_players[2]->stop();
}

void BGMControl::playerRobLordMusic(int point, RoleSex sex, bool isFirst)
{
    int index = sex == Man ? 0 : 1;
    if(isFirst && point > 0)
    {
        m_lists[index]->setCurrentIndex(Order);
    }
    else if(point == 0)
    {
        if(isFirst)
        {
            m_lists[index]->setCurrentIndex(NoOrder);
        }
        else
        {
            m_lists[index]->setCurrentIndex(NoRob);
        }
    }
    else if(point == 2)
    {
        m_lists[index]->setCurrentIndex(Rob1);
    }
    else if(point == 3)
    {
        m_lists[index]->setCurrentIndex(Rob2);
    }
    m_players[index]->play();
}

void BGMControl::playCardMusic(Cards cards, bool isFirst, RoleSex sex)
{
    int index = sex == Man ? 0 : 1;
    QMediaPlaylist* list = m_lists[index];

    Card::CardPoint pt = Card::CardPoint::Card_Begin;
    PlayHand hand(cards);
    PlayHand::HandType type = hand.getHandType();
    if(type == PlayHand::Hand_Single || type == PlayHand::Hand_Pair || type == PlayHand::Hand_Triple)
    {
        pt = cards.takeRandomCard().point();
    }
    int number = 0;
    switch(type)
    {
    case PlayHand::Hand_Single:
        number = pt - 1;
        break;
    case PlayHand::Hand_Pair:
        number = pt - 1 + 15;
        break;
    case PlayHand::Hand_Triple:
        number = pt - 1 + 15 + 13;
        break;
    case PlayHand::Hand_Triple_Single:
        number = ThreeBindOne;
        break;
    case PlayHand::Hand_Triple_Pair:
        number = ThreeBindPair;
        break;
    case PlayHand::Hand_Plane:
    case PlayHand::Hand_Plane_Two_Single:
    case PlayHand::Hand_Plane_Two_Pair:
        number = Plane;
        break;
    case PlayHand::Hand_Seq_Pair:
        number = SequencePair;
        break;
    case PlayHand::Hand_Seq_Single:
        number = Sequence;
        break;
    case PlayHand::Hand_Bomb:
        number = Bomb;
        break;
    case PlayHand::Hand_Bomb_Jokers:
        number = JokerBomb;
        break;
    case PlayHand::Hand_Bomb_Pair:
    case PlayHand::Hand_Bomb_Two_Single:
    case PlayHand::Hand_Bomb_Jokers_Pair:
    case PlayHand::Hand_Bomb_Jokers_Two_Single:
        number = FourBindTwo;

    default:
        break;
    }

    if(!isFirst && (number >= Plane && number <= FourBindTwo))
    {
        list->setCurrentIndex(MoreBiger1 + QRandomGenerator::global()->bounded(2));
    }
    else
    {
        list->setCurrentIndex(number);
    }
    m_players[index]->play();
    if(number == Bomb || number == JokerBomb)
    {
        playAssistMusic(BombVoice);
    }
    if(number == Plane)
    {
        playAssistMusic(PlaneVoice);
    }
}

void BGMControl::playLastMusic(CardType type, RoleSex sex)
{
    int index = sex == Man ? 0 : 1;
    QMediaPlaylist* list = m_lists[index];
    if(m_players[index]->state() == QMediaPlayer::StoppedState)
    {
        list->setCurrentIndex(type);
        m_players[index]->play();
    }
    else
    {
        QTimer::singleShot(1500, this, [=](){
            list->setCurrentIndex(type);
            m_players[index]->play();
        });
    }
}

void BGMControl::playPassMusic(RoleSex sex)
{
    int index = sex == Man ? 0 : 1;
    QMediaPlaylist* list = m_lists[index];
    int random = QRandomGenerator::global()->bounded(4);
    list->setCurrentIndex(Pass1 + random);
    m_players[index]->play();
}

void BGMControl::playAssistMusic(AssistMusic type)
{
    QMediaPlaylist::PlaybackMode mode;
    if(type == Dispatch)
    {
        mode = QMediaPlaylist::CurrentItemInLoop;
    }
    else
    {
        mode = QMediaPlaylist::CurrentItemOnce;
    }
    QMediaPlaylist* list = m_lists[3];
    list->setCurrentIndex(type);
    list->setPlaybackMode(mode);
    m_players[3]->play();
}

void BGMControl::stopAssistMusic()
{
    m_players[3]->stop();
}

void BGMControl::playEndingMusic(bool isWin)
{
    if(isWin)
    {
        m_lists[4]->setCurrentIndex(0);
    }
    else
    {
        m_lists[4]->setCurrentIndex(1);
    }
    m_players[4]->play();
}
