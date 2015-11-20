#ifndef RINGER_H
#define RINGER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QMutex>

class Ringer : public QObject
{
    Q_OBJECT
public:
    explicit Ringer(QObject *parent = 0);

public slots:
    void start();
    void stop();

private:
    QMutex mutex;
    bool ringing;
};

class Controller : public QObject
{
    Q_OBJECT
    QThread thread;
    QTimer timer;

public:
    explicit Controller() {
        Ringer *ringer = new Ringer;
        ringer->moveToThread(&thread);

        connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));

        connect(this, SIGNAL(start()), ringer, SLOT(start()));
        connect(this, SIGNAL(stop()), ringer, SLOT(stop()));

        timer.setInterval(2000);
        timer.setSingleShot(true);
        timer.start();

        thread.start();

        emit start();
    }

    ~Controller() {
        thread.quit();
        thread.wait();
    }

signals:
    void start();
    void stop();

private slots:
    void timeout();


};

#endif // RINGER_H
