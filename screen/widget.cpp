#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    createForm();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(slotTimerUpdate()));
    timer->start(500);
}

Widget::~Widget()
{

}

void Widget::createForm()
{
    mainlayout = new QHBoxLayout(this);
    buttonCreate = new QPushButton(tr("Создать"),this);
    connect(buttonCreate,SIGNAL(pressed()),this,SLOT(slotPushCreate()));
    mainlayout->addWidget(buttonCreate);
    buttonShow = new QPushButton(tr("Показать"),this);
    buttonShow->setEnabled(false);
    connect(buttonShow,SIGNAL(pressed()),this,SLOT(slotPushShow()));
    mainlayout->addWidget(buttonShow);

}

void Widget::slotPushCreate()
{
    QScreen *screen = QApplication::primaryScreen();
    screenShot = screen->grabWindow(QApplication::desktop()->winId());
    serialize(screenShot);
}

void Widget::slotPushShow()
{
    if (view == NULL)
    {
        view = new QPixmapView(screenShot);
        connect(view,SIGNAL(destroyed(QObject*)),this,SLOT(slotViewDestroyed(QObject*)));
        view->show();
    }

}

void Widget::slotTimerUpdate()
{
    buttonShow->setEnabled(!screenShot.isNull());
}

void Widget::slotViewDestroyed(QObject *object)
{
    view = NULL;
}


void Widget::serialize(QPixmap pixmap)
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG"); // writes pixmap into bytes in PNG format
    qDebug() << bytes.length();
}
