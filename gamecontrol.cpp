#include "gamecontrol.h"
#include "playhand.h"
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>

// 构造函数
GameControl::GameControl(QObject *parent) : QObject(parent)
{

}

void GameControl::playerInit()
{
    // 初始化玩家和机器人对象
    m_robotLeft = new Robot("机器人A", this);
    m_robotRight = new Robot("机器人B", this);
    m_user = new UserPlayer("我自己", this);

    // 设置玩家方向
    m_robotLeft->setDirection(Player::Left);
    m_robotRight->setDirection(Player::Right);
    m_user->setDirection(Player::Right);

    // 随机设置玩家性别
    Player::Sex sex;
    sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
    m_robotLeft->setSex(sex);
    sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
    m_robotRight->setSex(sex);
    sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
    m_user->setSex(sex);

    // 设置玩家间的前后关系
    m_user->setPrevPlayer(m_robotLeft);
    m_user->setNextPlayer(m_robotRight);   
    m_robotLeft->setPrevPlayer(m_robotRight);
    m_robotLeft->setNextPlayer(m_user);
    m_robotRight->setPrevPlayer(m_user);
    m_robotRight->setNextPlayer(m_robotLeft);

    // 设置当前玩家为用户
    m_currPlayer = m_user;

    // 连接信号槽
    connect(m_user, &UserPlayer::notifyGrabLordBet, this, &GameControl::onGrabBet);
    connect(m_robotLeft, &UserPlayer::notifyGrabLordBet, this, &GameControl::onGrabBet);
    connect(m_robotRight, &UserPlayer::notifyGrabLordBet, this, &GameControl::onGrabBet);
    connect(this, &GameControl::pendingInfo, m_robotLeft, &Robot::storePendingInfo);
    connect(this, &GameControl::pendingInfo, m_robotRight, &Robot::storePendingInfo);
    connect(this, &GameControl::pendingInfo, m_user, &Robot::storePendingInfo);
    connect(m_robotLeft, &Robot::notifyPlayHand, this, &GameControl::onPlayHand);
    connect(m_robotRight, &Robot::notifyPlayHand, this, &GameControl::onPlayHand);
    connect(m_user, &Robot::notifyPlayHand, this, &GameControl::onPlayHand);
}

// 获取左侧机器人对象
Robot *GameControl::getLeftRobot()
{
    return m_robotLeft;
}

// 获取右侧机器人对象
Robot *GameControl::getRightRobot()
{
    return m_robotRight;
}

// 获取用户玩家对象
UserPlayer *GameControl::getUserPlayer()
{
    return m_user;
}

// 设置当前玩家
void GameControl::setCurrentPlayer(Player *player)
{
    m_currPlayer = player;
}

// 获取当前玩家
Player *GameControl::getCurrentPlayer()
{
    return m_currPlayer;
}

// 获取挂起玩家
Player *GameControl::getPendPlayer()
{
    return m_pendPlayer;
}

// 获取挂起牌组
Cards GameControl::getPendCards()
{
    return m_pendCards;
}

// 初始化所有牌
void GameControl::initAllCards()
{
    // 清空所有牌组
    m_allCards.clear();

    // 生成普通扑克牌
    for(int p = Card::Card_Begin+1; p<Card::Card_SJ; ++p)
    {
        for(int s = Card::Suit_Begin+1; s<Card::Suit_End; ++s)
        {
            Card c((Card::CardPoint)p, (Card::CardSuit)s);
            m_allCards.add(c);
        }
    }

    // 添加大小王
    m_allCards.add(Card(Card::Card_SJ, Card::Suit_Begin));
    m_allCards.add(Card(Card::Card_BJ, Card::Suit_Begin));
}

// 从牌堆中抽取一张牌
Card GameControl::takeOneCard()
{
#if 0
    // test code 测试飞机
    static bool flag = true;
    static Cards tmp;
    if(flag)
    {
        Card c1(Card::Card_10, Card::Club);
        Card c2(Card::Card_10, Card::Diamond);
        Card c3(Card::Card_10, Card::Heart);

        Card c4(Card::Card_J, Card::Club);
        Card c5(Card::Card_J, Card::Diamond);
        Card c6(Card::Card_J, Card::Heart);

        tmp << c1 << c2 << c3 << c4 << c5 << c6;
        m_allCards.remove(tmp);
        flag = false;
    }

    if(getCurrentPlayer() == m_user && !tmp.isEmpty())
    {
        return tmp.takeRandomCard();
    }
    else
    {
        return m_allCards.takeRandomCard();
    }
#else
    // not test code 从真实的牌堆中抽取一张牌
    return m_allCards.takeRandomCard();
#endif
}

// 获取剩余的牌堆中的所有牌
Cards GameControl::getSurplusCards()
{
    return m_allCards;
}

// 重置牌局数据，包括初始化所有牌、清空玩家手牌、重置挂起玩家和挂起牌组
void GameControl::resetCardData()
{
    initAllCards();
    m_robotLeft->clearCards();
    m_robotRight->clearCards();
    m_user->clearCards();
    m_pendPlayer = nullptr;
    m_pendCards.clear();
}

// 开始叫地主阶段，通知当前玩家准备叫地主
void GameControl::startLordCard()
{
    m_currPlayer->prepareCallLord();
    emit playerStatusChanged(m_currPlayer, ThinkingForCallLord);
}

// 成为地主的处理，设置地主和农民角色，发牌，触发出牌阶段
void GameControl::becomeLord(Player *player, int bet)
{
    m_curBet = bet;
    player->setRole(Player::Lord);
    player->getPrevPlayer()->setRole(Player::Farmer);
    player->getNextPlayer()->setRole(Player::Farmer);

    m_currPlayer = player;
    player->storeDispatchCard(m_allCards);

    QTimer::singleShot(1000, this, [=]()
    {
        emit gameStatusChanged(PlayingHand);
        emit playerStatusChanged(player, ThinkingForPlayHand);
        m_currPlayer->preparePlayHand();
    });
}

// 清空玩家分数
void GameControl::clearPlayerScore()
{
    m_robotLeft->setScore(0);
    m_robotRight->setScore(0);
    m_user->setScore(0);
}

// 获取当前游戏中最大的叫地主分数
int GameControl::getPlayerMaxBet()
{
    return m_betRecord.bet;
}

// 处理玩家叫地主的情况
void GameControl::onGrabBet(Player *player, int bet)
{
    // 如果叫分为0或者当前记录的最高分大于等于本次叫分，则通知其他玩家不叫地主
    if(bet == 0 || m_betRecord.bet >= bet)
    {
        emit notifyGrabLordBet(player, 0, false);
    }
    // 如果本次叫分大于0且当前记录的最高分为0，则通知其他玩家叫地主
    else if(bet > 0 && m_betRecord.bet == 0)
    {
        emit notifyGrabLordBet(player, bet, true);
    }
    // 其他情况通知其他玩家不叫地主
    else
    {
        emit notifyGrabLordBet(player, bet, false);
    }

    // 如果叫分为3，则当前玩家成为地主，重置叫分记录并返回
    if(bet == 3)
    {
        becomeLord(player, bet);
        m_betRecord.reset();
        return;
    }
    // 更新叫分记录
    if(m_betRecord.bet < bet)
    {
        m_betRecord.bet = bet;
        m_betRecord.player = player;
    }
    m_betRecord.times ++;

    // 如果已经叫了3轮，根据最终叫分情况触发发牌或成为地主
    if(m_betRecord.times == 3)
    {
        if(m_betRecord.bet == 0)
        {
            emit gameStatusChanged(DispatchCard);
        }
        else
        {
            becomeLord(m_betRecord.player, m_betRecord.bet);
        }
        m_betRecord.reset();
        return;
    }

    // 切换到下一个玩家进行叫地主
    m_currPlayer = player->getNextPlayer();
    emit playerStatusChanged(m_currPlayer, ThinkingForCallLord);
    m_currPlayer->prepareCallLord();
}

// 处理玩家出牌的情况
void GameControl::onPlayHand(Player *player, const Cards &card)
{
    // 通知其他玩家当前玩家出牌的信息
    emit notifyPlayHand(player, card);

    // 如果出牌非空，更新挂起牌组和挂起玩家
    if(!card.isEmpty())
    {
        m_pendCards = card;
        m_pendPlayer = player;
        emit pendingInfo(player, card);
    }

    // 获取当前玩家手牌，并判断出牌的类型
    Cards myCards = const_cast<Cards&>(card);
    PlayHand::HandType type = PlayHand(myCards).getHandType();

    // 如果是炸弹或王炸，翻倍当前叫地主的分数
    if(type == PlayHand::Hand_Bomb || type == PlayHand::Hand_Bomb_Jokers)
    {
        m_curBet = m_curBet * 2;
    }

    // 如果当前玩家手牌为空，表示出完牌，根据角色和叫分情况结算分数
    if(player->getCards().isEmpty())
    {
        Player* prev = player->getPrevPlayer();
        Player* next = player->getNextPlayer();
        if(player->getRole() == Player::Lord)
        {
            player->setScore(player->getScore() + 2 * m_curBet);
            prev->setScore(prev->getScore() - m_curBet);
            next->setScore(next->getScore() - m_curBet);
            player->setWin(true);
            prev->setWin(false);
            next->setWin(false);
        }
        else
        {
            player->setWin(true);
            player->setScore(player->getScore() + m_curBet);
            if(prev->getRole() == Player::Lord)
            {
                prev->setScore(prev->getScore() - 2 * m_curBet);
                next->setScore(next->getScore() + m_curBet);
                prev->setWin(false);
                next->setWin(true);
            }
            else
            {
                next->setScore(next->getScore() - 2 * m_curBet);
                prev->setScore(prev->getScore() + m_curBet);
                next->setWin(false);
                prev->setWin(true);
            }
        }
        // 触发玩家胜利状态改变
        emit playerStatusChanged(player, GameControl::Winning);
        return;
    }
    // 切换到下一个玩家进行出牌
    m_currPlayer = player->getNextPlayer();
    m_currPlayer->preparePlayHand();
    emit playerStatusChanged(m_currPlayer, GameControl::ThinkingForPlayHand);
}


