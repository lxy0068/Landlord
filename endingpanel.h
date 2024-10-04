#ifndef ENDINGPANEL_H
#define ENDINGPANEL_H

#include "scorepanel.h"

#include <QLabel>
#include <QPushButton>
#include <QWidget>

class EndingPanel : public QWidget
{
    Q_OBJECT
public:
    explicit EndingPanel(bool isLord, bool isWin, QWidget *parent = nullptr);

    void setPlayerScore(int left, int right, int me);

signals:
    void continueGame();

protected:
    void paintEvent(QPaintEvent* ev);

private:
    QPixmap m_bk;
    QLabel* m_title;
    ScorePanel *m_score;
    QPushButton* m_continue;

};

#endif // ENDINGPANEL_H
