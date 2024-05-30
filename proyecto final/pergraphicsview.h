#ifndef PERGRAPHICSVIEW_H
#define PERGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include "Bala.h"

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    CustomGraphicsView(QWidget *parent = nullptr);
    void setPlayerItem(QGraphicsItem *item);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QGraphicsItem *playerItem;
};
#endif // PERGRAPHICSVIEW_H
