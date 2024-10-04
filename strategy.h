#ifndef STRATEGY_H
#define STRATEGY_H

#include "player.h"
#include "playhand.h"



class Strategy
{
public:
    Strategy(Player* player, const Cards& cards);


    Cards makeStrategy();
    Cards firstPlay();
    Cards getGreaterCards(PlayHand type);
    bool whetherToBeat(Cards& cs);

    Cards findSamePointCards(Card::CardPoint point, int count);
    QVector<Cards> findCardsByCount(int count);
    Cards getRangeCards(Card::CardPoint begin, Card::CardPoint end);
    QVector<Cards> findCardType(PlayHand hand, bool beat);

    void pickSeqSingles(QVector<QVector<Cards>> &allSeqRecord, const QVector<Cards> &seqSingle, const Cards& cards);
    QVector<Cards> pickOptimalSeqSingles();

private:
    using function = Cards (Strategy::*)(Card::CardPoint point);
    struct CardInfo
    {
        Card::CardPoint begin;
        Card::CardPoint end;
        int extra;
        bool beat;
        int number;
        int base;
        function getSeq;
    };
    QVector<Cards> getCards(Card::CardPoint point, int number);
    QVector<Cards> getTripleSingleOrPair(Card::CardPoint begin, PlayHand::HandType type);
    QVector<Cards> getPlane(Card::CardPoint begin);
    QVector<Cards> getPlane2SingleOr2Pair(Card::CardPoint begin, PlayHand::HandType type);
    QVector<Cards> getSepPairOrSeqSingle(CardInfo &info);
    Cards getBaseSeqPair(Card::CardPoint point);
    Cards getBaseSeqSingle(Card::CardPoint point);
    QVector<Cards> getBomb(Card::CardPoint begin);

private:
    Player* m_player;
    Cards m_cards;
};

#endif // STRATEGY_H
