#include "entidad.h"

Entidad::Entidad(QGraphicsView *view, QGraphicsItem *parent)
    : QObject(nullptr), QGraphicsPixmapItem(parent), x(0), y(0), viewRect(view->viewport()->size()) {}

void Entidad::moveBy(int dx, int dy) {
    qreal newX = x + dx;
    qreal newY = y + dy;
    setPos(newX, newY);
    x = newX;
    y = newY;
}
