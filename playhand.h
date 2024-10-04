#ifndef PLAYHAND_H
#define PLAYHAND_H

#include "card.h"
#include "cards.h"



class PlayHand
{
public:
    // 出牌组合或者方式
    enum HandType
    {
        Hand_Unknown,               // 未知
        Hand_Pass,                  // 过

        Hand_Single,                // 单
        Hand_Pair,                  // 对

        Hand_Triple,                // 三个
        Hand_Triple_Single,         // 三带一
        Hand_Triple_Pair,           // 三带二

        Hand_Plane,                 // 飞机，555_666
        Hand_Plane_Two_Single,      // 飞机带单，555_666_3_4
        Hand_Plane_Two_Pair,        // 飞机带双，555_666_33_44

        Hand_Seq_Pair,              // 连对，33_44_55(_66...)
        Hand_Seq_Single,            // 顺子，34567(8...)

        Hand_Bomb,                  // 炸弹
        Hand_Bomb_Single,           // 炸弹带一个
        Hand_Bomb_Pair,             // 炸弹带一对
        Hand_Bomb_Two_Single,       // 炸弹带两单

        Hand_Bomb_Jokers,           // 王炸
        Hand_Bomb_Jokers_Single,    // 王炸带一个
        Hand_Bomb_Jokers_Pair,      // 王炸带一对
        Hand_Bomb_Jokers_Two_Single	// 王炸带两单
    };

    PlayHand();
    explicit PlayHand(Cards& cards);
    PlayHand(HandType type, Card::CardPoint pt, int extra);


    HandType getHandType();
    Card::CardPoint getCardPoint();
    int getExtra();

    bool canBeat(const PlayHand& other);

private:
    void classify(Cards& cards);
    void judgeCardType();
    bool isPass();
    bool isSingle();
    bool isPair();
    bool isTriple();
    bool isTripleSingle();
    bool isTriplePair();
    bool isPlane();
    bool isPlaneTwoSingle();
    bool isPlaneTwoPair();
    bool isSeqPair();
    bool isSeqSingle();
    bool isBomb();
    bool isBombSingle();
    bool isBombPair();
    bool isBombTwoSingle();
    bool isBombJokers();
    bool isBombJokersSingle();
    bool isBombJokersPair();
    bool isBombJokersTwoSingle();

private:
    HandType m_type;
    Card::CardPoint m_pt;
    int m_extra;
    QVector<Card::CardPoint> m_oneCard;
    QVector<Card::CardPoint> m_twoCard;
    QVector<Card::CardPoint> m_threeCard;
    QVector<Card::CardPoint> m_fourCard;
};

#endif // PLAYHAND_H
