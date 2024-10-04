#include "gamepanel.h"
#include "loading.h"

#include <QPainter>
#include <QTimer>

Loading::Loading(QWidget *parent) : QWidget(parent)
{
    m_bk.load(":/images/loading.png");
    setFixedSize(m_bk.size());

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);

    QPixmap pixmap(":/images/progress.png");
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){
        m_progress = pixmap.copy(0, 0, m_dist, pixmap.height());
        update();
        if(m_dist >= pixmap.width())
        {
            timer->stop();
            timer->deleteLater();
            GamePanel* panel = new GamePanel;
            panel->show();
            close();
        }
        m_dist += 5;
    });
    timer->start(15);
}

void Loading::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter p(this);
    p.drawPixmap(rect(), m_bk);
    p.drawPixmap(62, 417, m_progress.width(), m_progress.height(), m_progress);
}
