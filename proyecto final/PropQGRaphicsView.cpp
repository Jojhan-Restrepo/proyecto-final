#include "PropQGraphicsView.h"

PropQGraphicsView::PropQGraphicsView(QWidget *parent)
    : QGraphicsView(parent), playerItem(nullptr)
{
}

void PropQGraphicsView::setPlayerItem(QGraphicsItem *item)
{
    playerItem = item;
}

void PropQGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (playerItem) {
        this->scene()->setFocusItem(playerItem);
    }
    QGraphicsView::mousePressEvent(event); // Call the base class implementation
}
