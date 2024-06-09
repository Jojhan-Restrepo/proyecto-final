#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include "entidad.h"
#include <QVector>
#include "Jugador.h"

class Enemigos : public Entidad {
    Q_OBJECT
public:
    Enemigos(QGraphicsView *view, qreal startX, qreal startY, QGraphicsItem* im = nullptr);
    Enemigos(const Enemigos &other, qreal newX, qreal newY);

    void mover(int dx, int dy) override;
    void moveBy(int dx, int dy) override;
    void setSpritederecha(int dir);
    void setSpriteizquierda(int dir);
    void incrementarColision();
    int getContador() const;

private:
    Jugador *jug1; // Referencia al jugador
    bool movingRight;
    int direccion;
    bool flag;
    int cont;
    int contadorColisiones;
    QVector<Enemigos*> enemigos;
    QList<QGraphicsRectItem*> obst;
    int velocidadX;
    int velocidadY;
};

#endif // ENEMIGOS_H
