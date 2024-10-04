#ifndef ANIMATIONWINDOW_H
#define ANIMATIONWINDOW_H

#include <QWidget>

class AnimationWindow : public QWidget
{
    Q_OBJECT
public:
    enum Type{Sequence, Pair};
    explicit AnimationWindow(QWidget *parent = nullptr);

    // 显示下注分数
    void showBetScore(int bet);
    // 显示顺子和连对
    void showSequence(Type type);
    // 显示王炸
    void showJokerBomb();
    // 显示炸弹
    void showBomb();
    // 显示飞机
    void showPlane();

signals:

protected:
    void paintEvent(QPaintEvent* ev);

private:
    QPixmap m_image;
    int m_index = 0;
    int m_x = 0;

};

#endif // ANIMATIONWINDOW_H
