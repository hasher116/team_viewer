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
    //Серверная часть
    
    QImage image(pixmap.toImage());
    QByteArray ba;
    QDataStream ds(&ba, QIODevice::WriteOnly);
    
        ds << (int)image.format();
        ds << image.byteCount();
        ds << image.width();
        ds << image.height();
        ds.writeRawData((char*)image.bits(), image.byteCount());
        qDebug() << ba.length();
        
    //Клиентская часть

    QByteArray ba1 = ba; //ПОЛУЧАЕШЬ ПО СОКЕТУ
    QDataStream ds1(&ba1, QIODevice::ReadOnly);
        
            int format = - 1;
            int bytesCount = -1;
            int width = 0;
            int height = 0;

            ds1 >> format;
            ds1 >> bytesCount;
            ds1 >> width;
            ds1 >> height;
            uchar* bytes = new uchar[bytesCount];
            ds1.readRawData((char*)bytes, bytesCount);

            QImage* img = new QImage(bytes, width, height, (QImage::Format)format);
            screenShot = QPixmap::fromImage(*img,Qt::AutoColor);
            view2 = new QPixmapView(screenShot);
            connect(view2,SIGNAL(destroyed(QObject*)),this,SLOT(slotViewDestroyed(QObject*)));
            view2->show();

}
