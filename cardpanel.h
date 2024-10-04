#ifndef CARDPANEL_H
#define CARDPANEL_H

#include <QWidget>
#include "card.h"
#include "player.h"

class CardPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CardPanel(QWidget *parent = nullptr);

    void setImage(const QPixmap &front, const QPixmap &back);
    QPixmap getImage();

    void setFrontSide(bool flag);
    bool isFrontSide();

    void setSeclected(bool flag);
    bool isSelected();

    void setCard(const Card& card);
    Card getCard();

    void setOwner(Player* player);
    Player* getOwner();

    void clicked();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);

signals:
    void cardSelected(Qt::MouseButton button);

private:
    QPixmap m_front;
    QPixmap m_back;
    bool m_isfront = true;
    bool m_isSelect = false;
    Card m_card;
    Player* m_owner = nullptr;
};

#endif // CARDPANEL_H
