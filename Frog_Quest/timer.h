#ifndef TIMER_H
#define TIMER_H

#include <QWidget>

class QProgressBar;

class Timer : public QWidget
{

    Q_OBJECT

public:
    Timer(QWidget *parent = 0);

public slots:
    void updateProgress();

private:
    QProgressBar *progressBar;
};

#endif // TIMER_H
