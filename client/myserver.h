#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QDebug>

class myserver : public QObject
{
    Q_OBJECT
public:
    explicit myserver(QObject *parent = nullptr);

signals:  

public slots:
    void Connection();

private:
    QTcpServer *server;

private slots:
    void slotClientReadyRead();
};

#endif // MYSERVER_H
