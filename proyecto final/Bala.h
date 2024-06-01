#ifndef BALA_H
#define BALA_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include "enemigos.h"
#include "Jugador.h"
class Bala : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Bala(QGraphicsScene *scene, const QPointF &startPos, const QPointF &targetPos, QVector<Enemigos*> &enemigos, QList<QGraphicsRectItem *> &obst);

public slots:
    void mover();

private:
    QPointF targetPos;
    QVector<Enemigos*> &enemigos;
    QList<QGraphicsRectItem *> &obst;
    QTimer *timer;
};

#endif // BALA_H

