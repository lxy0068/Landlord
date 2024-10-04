#ifndef SCOREPANEL_H
#define SCOREPANEL_H

#include <QLabel>
#include <QWidget>

namespace Ui {
class ScorePanel;
}

class ScorePanel : public QWidget
{
    Q_OBJECT

public:
    enum FontColor{Black, White, Red, Blue, Green};
    explicit ScorePanel(QWidget *parent = nullptr);
    ~ScorePanel();

    void setScores(int left, int right, int user);
    void setMyFontSize(int point);
    void setMyFontColor(FontColor color);

private:
    Ui::ScorePanel *ui;
    QVector<QLabel*> m_list;
};

#endif // SCOREPANEL_H
