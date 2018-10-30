#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QBuffer>
#include <QDebug>

#include "include/QPixmapView/qpixmapview.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QTimer *timer;
    QPixmap screenShot;
    void createForm();
    QHBoxLayout *mainlayout;
    QPushButton *buttonCreate;
    QPushButton *buttonShow = NULL;
    QPixmapView *view=NULL;
    void serialize(QPixmap pixmap);

private slots:
    void slotPushCreate();
    void slotPushShow();

    void slotTimerUpdate();
    void slotViewDestroyed(QObject *object);
};

#endif // WIDGET_H
