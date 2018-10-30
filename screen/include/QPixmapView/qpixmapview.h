#ifndef QPIXMAPVIEW_H
#define QPIXMAPVIEW_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>

class QPixmapView : public QWidget
{
    Q_OBJECT
public:
    explicit QPixmapView(QPixmap &pixmap,QWidget *parent = nullptr);
    ~QPixmapView();

private:
    QPixmap currentPixmap;

    void paintEvent(QPaintEvent *event);


signals:

public slots:
};

#endif // QPIXMAPVIEW_H
