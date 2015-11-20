#include "ringer.h"
#include <QDebug>
#include <QCoreApplication>

Ringer::Ringer(QObject *parent) : QObject(parent), ringing(false)
{
}

void Ringer::start()
{
    if (ringing)
        return;

    qDebug() << "start" << this;
    ringing = true;
    while (ringing) {
        QCoreApplication::processEvents();
    }
    qDebug() << "stopped, ringing:" << ringing;
}

void Ringer::stop()
{
    qDebug() << "try to stop" << this;
    ringing = false;
}

void Controller::timeout()
{
    qDebug() << "try to stop from" << this;
    emit stop();
}
