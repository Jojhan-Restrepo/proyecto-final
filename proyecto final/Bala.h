#ifndef BALA_H
#define BALA_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QPointF>
#include "enemigos.h"

class Bala : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

public:
    Bala(QGraphicsScene *scene, const QPointF &startPos, const QPointF &targetPos, Enemigos *&enem1, QList<QGraphicsRectItem *> &obst);

public slots:
    void mover();

private:
    QPointF targetPos;
    QTimer *timer;
    Enemigos *&enem1;
    QList<QGraphicsRectItem *> &obst;
};

#endif // BALA_H
