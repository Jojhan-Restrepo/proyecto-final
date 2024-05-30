#ifndef ENEMIGOS_H
#define ENEMIGOS_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QObject>
#include <QGraphicsPixmapItem>
#include "Jugador.h"

class Enemigos : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemigos(QGraphicsView *view,QGraphicsItem* im = 0);
    void movimiento(int dx, int dy);
    void setSpritederecha(int dir);
    void setSpriteizquierda(int dir);
    void incrementarColision(); // Nuevo método para incrementar el contador de colisiones
    int getContador() const;
private:
    qreal x = 200;
    qreal y = 200;
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
    int contadorColisiones = 0; // Contador de colisiones
};

#endif // ENEMIGOS_H
