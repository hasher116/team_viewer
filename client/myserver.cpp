#include "myserver.h"

myserver::myserver(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(Connection()));

    if(!server->listen(QHostAddress::Any, 5656))
        qWarning() << "Server could not start";
    else
        qWarning() << "Server started";
}

void myserver::Connection()
{
    QTcpSocket * socket = server->nextPendingConnection();
    //char buff[50];
    socket->write(QString("Hello!!\r\n").toLatin1());
    connect(socket,SIGNAL(readyRead()),this,SLOT(slotClientReadyRead()));
    socket->waitForBytesWritten(3000);
}

void myserver::slotClientReadyRead()
{
    qDebug() << "slotClientReadyRead";
    QTcpSocket * socket = (QTcpSocket*)QObject::sender();

    QByteArray data = socket->readAll();

    qDebug() << QString(data);

    socket->write(data);
}
