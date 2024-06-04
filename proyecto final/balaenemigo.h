#ifndef BALAENEMIGO_H
#define BALAENEMIGO_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPointF>
#include <QTimer>
#include <QVector>
#include <QList>

class QGraphicsScene;
class Jugador;

class BalaEnemigo : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    BalaEnemigo(QGraphicsScene *scene, const QPointF &startPos, const QPointF &targetPos, QVector<Jugador*> &jugador, QList<QGraphicsRectItem *> &obst);
    ~BalaEnemigo(); // Destructor

public slots:
    void mover();
private:
    QPointF targetPos;
    QVector<Jugador*> &jugador;
    QList<QGraphicsRectItem *> &obst;
    QTimer *timer; // Puntero al temporizado
signals:
    void jugadorMuerto();
};

#endif // BALAENEMIGO_H
