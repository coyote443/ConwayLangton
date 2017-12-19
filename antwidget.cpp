#include "antwidget.h"
#include <QPainter>

AntWidget::AntWidget(QWidget *parent) : QWidget(parent){}

void AntWidget::setImage(QImage &image){
    m_size = image.size();
    m_image = image.scaled(size());
    update();
}

QSize AntWidget::sizeHint() const{
    return m_size;
}

void AntWidget::paintEvent(QPaintEvent* evt){
    QPainter painter(this);
    if(!m_image.isNull())
        painter.drawImage(QPoint(0,0), m_image);
}

