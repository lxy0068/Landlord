#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include "cardpanel.h"
#include "gamecontrol.h"
#include "animationwindow.h"
#include "player.h"
#include "countdown.h"
#include "bgmcontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GamePanel; }
QT_END_NAMESPACE

class GamePanel : public QMainWindow
{
    Q_OBJECT

public:
    GamePanel(QWidget *parent = nullptr);
    ~GamePanel();
    enum AnimationType{ShunZi, LianDui, Plane, JokerBomb, Bomb, Bet};
    void gameControlInit();
    void updatePlayerScore();
    void initCardMap();
    void cropImage(QPixmap& pix, int x, int y, Card& c);
    void initButtonsGroup();
    void initPlayerContext();
    void initGameScene();
    void gameStatusPrecess(GameControl::GameStatus status);
    void startDispatchCard();
    void cardMoveStep(Player* player, int curPos);
    void disposeCard(Player* player, const Cards& cards);
    void updatePlayerCards(Player* player);
    QPixmap loadRoleImage(Player::Sex sex, Player::Direction direct, Player::Role role);

    void onDispatchCard();
    void onPlayerStatusChanged(Player* player, GameControl::PlayerStatus status);
    void onGrabLordBet(Player* player, int bet, bool flag);
    void onDisposePlayHand(Player* player, const Cards& cards);
    void onCardSelected(Qt::MouseButton button);
    void onUserPlayHand();
    void onUserPass();

    void showAnimation(AnimationType type, int bet = 0);
    void hidePlayerDropCards(Player* player);
    void showEndingScorePanel();
    void initCountDown();

protected:
    void paintEvent(QPaintEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);


private:
    enum CardAlign{Horizontal, Vertical};
    struct PlayerContext
    {
        QRect cardRect;
        QRect playHandRect;
        CardAlign align;
        bool isFrontSide;
        QLabel* info;
        QLabel* roleImg;
        Cards lastCards;
    };

    Ui::GamePanel *ui;
    QPixmap m_bkImage;
    GameControl* m_gameCtl;
    QVector<Player*> m_playerList;
    QMap<Card, CardPanel*> m_cardMap;
    QSize m_cardSize;
    QPixmap m_cardBackImg;
    QMap<Player*, PlayerContext> m_contextMap;
    CardPanel* m_baseCard;
    CardPanel* m_moveCard;
    QVector<CardPanel*> m_last3Card;
    QPoint m_baseCardPos;
    GameControl::GameStatus m_gameStatus;
    QTimer* m_timer;
    AnimationWindow* m_animation;
    CardPanel* m_curSelCard;
    QSet<CardPanel*> m_selectCards;
    QRect m_cardsRect;
    QHash<CardPanel*, QRect> m_userCards;
    CountDown* m_countDown;
    BGMControl* m_bgm;
};
#endif // GAMEPANEL_H
