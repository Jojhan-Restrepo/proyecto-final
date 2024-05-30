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
    Enemigos(QGraphicsView *view, QGraphicsItem* im = nullptr);
    //void movimiento(qreal newX, qreal newY);
    void movimiento(int dx, int dy);
    void setSpritederecha(int dir);
    void setSpriteizquierda(int dir);
    void incrementarColision(); // Nuevo método para incrementar el contador de colisiones
    int getContador() const;
    qreal x = 200;
    qreal y = 200;
private:
    //qreal x = 200;
   // qreal y = 200;
    bool movingRight; // Variable para almacenar la dirección de movimient
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
    int contadorColisiones = 0; // Contador de colisiones
    QVector<Enemigos*> enemigos; // Vector para almacenar los enemigos
    int velocidadX; // Velocidad de movimiento en el eje x
    int velocidadY; // Velocidad de movimiento en el eje y
};

#endif // ENEMIGOS_H
