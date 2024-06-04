#ifndef BALA_H
#define BALA_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QVector>
#include "enemigos.h"
#include "jugador.h"

class Enemigos;
class Jugador;

class Bala : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    Bala(QGraphicsScene *scene, const QPointF &startPos, const QPointF &targetPos, QVector<Enemigos*> &enemigos, QVector<Jugador*> &jugador, QList<QGraphicsRectItem *> &obst);
    ~Bala() = default;

signals:
    void enemigoEliminado();

private slots:
    void mover();

private:
    QPointF targetPos;
    QVector<Enemigos*> &enemigos;
    QVector<Jugador*> &jugador;
    QList<QGraphicsRectItem *> &obst;
    QTimer *timer;
};

#endif // BALA_H

