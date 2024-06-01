#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QVector> // Se agrega para utilizar QVector
#include "Jugador.h"

class Enemigos : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemigos(QGraphicsView *view, qreal startX, qreal startY, QGraphicsItem* im = nullptr);
    void movimiento(int dx, int dy);
    void setSpritederecha(int dir);
    void setSpriteizquierda(int dir);
    void incrementarColision();
    int getContador() const;
    //void disparar();
    //void disparar();
    qreal x;
    qreal y;

private:
    Jugador *jug1; // Referencia al jugador
    bool movingRight;
    int direccion;
    QSize viewRect;
    int dir = 1;
    bool flag = true;
    int cont = 0;
    int spriteX = 0;
    int spriteY = 120;
    int spriteWidth;
    int spriteHeight;
    QPixmap sprite;
    QPixmap spriteSheet;
    int contadorColisiones = 0;
    QVector<Enemigos*> enemigos;
    QList<QGraphicsRectItem*> obst;
    int velocidadX;
    int velocidadY;
};

#endif // ENEMIGOS_H


