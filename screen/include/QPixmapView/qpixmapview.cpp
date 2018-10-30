#include "qpixmapview.h"

QPixmapView::QPixmapView(QPixmap &pixmap, QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    currentPixmap = pixmap;
}

QPixmapView::~QPixmapView()
{

}

void QPixmapView::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPixmap picture = currentPixmap.scaled(this->size(),Qt::KeepAspectRatio);

    p.drawPixmap(0,0,picture);

    QWidget::paintEvent(event);
}
