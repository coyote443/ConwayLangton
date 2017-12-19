#ifndef ANTWIDGET_H
#define ANTWIDGET_H

#include <QWidget>
#include <QImage>

class AntWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AntWidget(QWidget *parent = 0);
    QSize sizeHint() const;
    void paintEvent(QPaintEvent* evt);

public slots:
    void setImage(QImage &image);

private:
    QImage  m_image;
    QSize   m_size;
};

#endif // ANTWIDGET_H
